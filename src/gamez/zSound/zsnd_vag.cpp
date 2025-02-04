#include "zsnd.h"

#include <cstdio>
#include <vector>

#include <SDL3/SDL_log.h>
#include <SDL3/SDL_assert.h>

f32 ps_adpcm_coeffs_f[5][2]
{
    { 0.0f, 0.0f },
    { 0.9375f, 0.0f },
    { 1.796875f, -0.8125f },
    { 1.53125f, -0.859375f },
    { 1.90625f, -0.9375f }
};

s32 hist1 = 0.0f;
s32 hist2 = 0.0f;

// https://github.com/vgmstream/vgmstream/blob/master/src/util/reader_get_nibbles.h#L15
s32 nibble_to_int[16] = { 0, 1, 2, 3, 4, 5, 6, 7, -8, -7, -6, -5, -4, -3, -2, -1 };

s32 get_nibble_signed(u8 n, s32 upper)
{
    return nibble_to_int[(n >> (upper ? 4 : 0)) & 0x0f];
}

s32 get_high_nibble_signed(u8 n)
{
    return nibble_to_int[n >> 4];
}

s32 get_low_nibble_signed(u8 n)
{
    return nibble_to_int[n & 0x0f];
}

void vag_read_header(CBufferIO* io, tag_VAGHeader* header)
{
    if (!io)
    {
        return;
    }

    io->fread(header, sizeof(tag_VAGHeader));

    header->version = U32_BE(&header->version);
    header->size = U32_BE(&header->size);
    header->rate = U32_BE(&header->rate);
}

void vag_decode(CBufferIO* io, std::vector<s16>& out)
{
    tag_VAGChunk chunk;
    io->fread(&chunk, sizeof(tag_VAGChunk));

    u8 coeff = (chunk.shift >> 4) & 0xF;
    u8 shift = (chunk.shift >> 0) & 0xF;
    chunk.shift = shift;

    SDL_assert(chunk.flags < 0x7, "Invalid VAG chunk flag");

    chunk.shift = 20 - chunk.shift;
    
    for (u32 i = 0; i < VAG_EXPAND_SAMPLES; i++)
    {
        s32 sample = 0;

        if (chunk.flags < 0x7)
        {
            u8 nibbles = chunk.sample[i / 2];

            sample = (i & 1 ? get_high_nibble_signed(nibbles) :
                               get_low_nibble_signed (nibbles)) << chunk.shift;

            sample = sample + (s32)((ps_adpcm_coeffs_f[coeff][0] * hist1 + ps_adpcm_coeffs_f[coeff][1] * hist2) * 256.0f);
            sample >>= 8;
        }

        if (sample > 32767)
        {
            sample = 32767;
        }
        else if (sample < -32768)
        {
            sample = -32768;
        }
        
        out.push_back((s16)sample);

        hist2 = hist1;
        hist1 = sample;
    }
}
