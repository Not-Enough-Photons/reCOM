#include "zsnd.h"

#define VAG_SAMPLE_BYTES 14
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
    std::vector<s16> output;
    hist1 = 0.0f;
    hist2 = 0.0f;

    CBufferIO io;
    io.Open(ptr, header.samples);

    io.fread(&header, sizeof(tag_VAGHeader));

    header.version = U32_BE(&header.version);
    header.rate = U32_BE(&header.rate);
    header.samples = U32_BE(&header.samples);
 
    io.fseek(16, SEEK_CUR);

    while (io.ftell() < header.samples)
    {
        s32 coeff_idx = 0;
        s32 shift = 0;

        io.fread(&coeff_idx, sizeof(s32));
    }

    io.Close();
    
    return output.data();
}