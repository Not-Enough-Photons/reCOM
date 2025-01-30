#include "zsnd.h"

#define VAG_SAMPLE_BYTES 14
#define VAG_SAMPLE_NIBBLE VAG_SAMPLE_BYTES * 2

// From:
// https://github.com/eurotools/es-ps2-vag-tool/blob/main/PS2VagTool/Vag%20Functions/SonyVagDecoder.cs
f32 vagLUT[5][2]
{
    { 0.0f, 0.0f },
    { 60.0f / 64.0f, 0.0f },
    { 115.0f / 64.0f, -52.0f / 64.0f },
    { 98.0f / 64.0f, -55.0f / 64.0f },
    { 122.0f / 64.0f, -60.0f / 64.0f }
};

f32 hist1 = 0.0f;
f32 hist2 = 0.0f;

extern u8* vagDecode(u8* ptr, const tag_VAGHeader& header)
{
    std::vector<u8> output;
    hist1 = 0.0f;
    hist2 = 0.0f;
    
    ptr += sizeof(tag_VAGHeader);
    ptr += 16;

    s8 coeff = *ptr++;

    tag_VAGChunk chunk
    {
        (s8)(coeff & 0xF),
        (s8)((coeff & 0xF0) >> 4),
        *ptr++
    };

    chunk.sample = new u8[VAG_SAMPLE_BYTES];
        
    for (u8 i = 0; i < VAG_SAMPLE_BYTES; i++)
    {
        chunk.sample[i] = *ptr++;
    }

    s8 samples[VAG_SAMPLE_NIBBLE];

    // Upscale 4-bit sample to 8-bits
    for (u8 i = 0; i < VAG_SAMPLE_BYTES; i++)
    {
        samples[i * 2] = chunk.sample[i] & 0xF;
        samples[i * 2 + 1] = (chunk.sample[i] & 0xF0) >> 4;
    }

    // Decode
    for (u8 i = 0; i < VAG_SAMPLE_NIBBLE; i++)
    {
        // Shift 4 bits to top range of s16
        s32 s = samples[i] << 12;

        if ((s & 0x8000) != 0)
        {
            s = (s32)(s | 0xFFFF0000);
        }

        // swy: don't overflow the LUT array access; limit the max allowed index
        s8 four = 4;
        s8 predict = min(chunk.predict, four);
        f32 sample = (s >> chunk.shift) + hist1 * vagLUT[predict][0] + hist2 * vagLUT[predict][1];
        hist2 = hist1;
        hist1 = sample;
        output.push_back(sample);
    }
        
    ptr++;

    return output.data();
}