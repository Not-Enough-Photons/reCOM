#include "zsnd.h"

// Number of sample bytes
#define VAG_SAMPLE_BYTES 14 
// Number of bytes expanded for decompressed audio quality
#define VAG_SAMPLE_NIBBLE VAG_SAMPLE_BYTES * 2 

f32 ps_adpcm_coeffs_f[5][2]
{
    { 0.0f, 0.0f },
    { 0.9375f, 0.0f },
    { 1.796875f, -0.8125f },
    { 1.53125f, -0.859375f },
    { 1.90625f, -0.9375f }
};

f32 hist1 = 0.0f;
f32 hist2 = 0.0f;

extern s16* vagDecode(u8* ptr, tag_VAGHeader& header)
{
    struct tag_VAGChunk
    {
        u8 decode_coeff;
        s8 shift;
        s8 predict;
        u8 flags;
        u8 sample[VAG_SAMPLE_BYTES];
    };
    
    std::vector<s16> output;
    hist1 = 0.0f;
    hist2 = 0.0f;

    CBufferIO io;
    io.Open(ptr, header.samples);

    io.fread(&header, sizeof(tag_VAGHeader));

    header.version = U32_BE(&header.version);
    header.rate = U32_BE(&header.rate);
    header.samples = U32_BE(&header.samples);

    output.reserve(header.samples);
    
    io.fseek(16, SEEK_CUR);
    
    // go through every sample and increase its bit depth
    // from 4 bits to 8 bits
    // we need to store the data inside of an s16
    for (u32 i = 0; i < header.samples / 16; i++)
    {
        tag_VAGChunk chunk;
        io.fread(&chunk.decode_coeff, 1);
        chunk.shift = (u8)(chunk.decode_coeff & 0xF);
        chunk.predict = (u8)((chunk.decode_coeff & 0xF0) >> 4);
        io.fread(&chunk.flags, 1);
        io.fread(chunk.sample, VAG_SAMPLE_BYTES);

        // Buffer to store our decompressed audio
        s32 samples[VAG_SAMPLE_NIBBLE];
        memset(samples, 0, sizeof(s32) * VAG_SAMPLE_NIBBLE);

        for (u32 sample_idx = 0; sample_idx < VAG_SAMPLE_BYTES; sample_idx++)
        {
            // Skip two bytes         Target first 4 bytes of sample
            samples[sample_idx * 2] = chunk.sample[sample_idx] & 0xF;

            // Skip two bytes + 1     Target the upper half and move it
            samples[sample_idx * 2 + 1] = (chunk.sample[sample_idx] & 0xF0) >> 4;
        }

        for (u32 nibble_idx = 0; nibble_idx < VAG_SAMPLE_NIBBLE; nibble_idx++)
        {
            s32 s = samples[nibble_idx] << 12;

            if ((s & 0x8000) != 0)
            {
                s = (s32)(s | 0xFFFF0000);
            }

            s8 predict = std::min(chunk.predict, (s8)4);
            
            f32 decode_sample = (s >> chunk.shift) + hist1 * ps_adpcm_coeffs_f[predict][0] + hist2 * ps_adpcm_coeffs_f[predict][1];
            hist2 = hist1;
            hist1 = decode_sample;

            output.push_back((s16)decode_sample);
        }
    }
    
    io.Close();
    
    return output.data();
}