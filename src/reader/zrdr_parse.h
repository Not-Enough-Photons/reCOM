#pragma once
#include <iostream>
#include <string>
#include <cstring>
#include <cstdint>

#include "Windows.h"

namespace zdb
{
    const char ZAR_HASH_TABLE[128]
    {
        20,20,20,20,20,20,20,00,
        20,28,28,28,28,28,20,20,
        20,20,20,20,20,20,20,20,
        20,20,20,20,20,20,20,20,
        10,10,10,10,10,10,88,20,
        10,10,10,10,10,10,10,10,
        04,04,04,04,04,04,04,10,
        10,10,10,10,10,04,04,04,
        41,41,41,41,41,41,10,10,
        01,01,01,01,01,01,01,01,
        01,01,01,01,01,01,01,01,
        10,10,10,10,01,01,01,01,
        42,42,42,42,42,42,10,10,
        02,02,02,02,02,02,02,02,
        02,02,02,02,02,02,02,02,
        10,10,10,10,02,02,02,02
    };

	const int TWO_BYTES = 2;
	const int FOUR_BYTES = 4;
	const int EIGHT_BYTES = 8;

    typedef struct ZAmmo
    {
        const char* internalName;
        const char* displayName;
        const char* description;
        int id;

        float impactDamage;
        const char* hitAnimName;
        float stun;
        float piercing;
        float explosionDamage;
        float explosionRadius;
        int numProjectilesFired;
        float blowbackFalloff;
        float blowbackEnd;
        float proximityDistance;
        float accelerationFactor;
        int32_t volitile;
        int32_t ignoreExplosionDI;
    } zammo_t;

    static uintptr_t dwEEMem = 0;
    static uintptr_t BasePS2MemorySpace = 0;

    static zammo_t zAmmoValues;
    

    // From https://www.unknowncheats.me/forum/general-programming-and-reversing/569991-pcsx2-guide-cheats-trainers.html
    uintptr_t GetPS2Address(unsigned int RAW_PS2_OFFSET);
    template<typename T> inline T PS2Read(uintptr_t Address);
    template<typename T> inline void PS2Write(uintptr_t Address, T Patch);
    template<typename T> inline T PS2Read(int32_t ps2Address);
    inline std::string PS2Read(uintptr_t address);
    inline std::string PS2Read(int32_t address);

    // Zipper Reader specific prototypes
    int32_t GetPathToLabel(int32_t pointer, const char* entry, int iterations);
    int ReadString(int32_t pointer, const char* entry, std::string* output);
    int ReadInt(int32_t pointer, const char* entry, int* output, int param_4);
	int ReadFloat(int32_t pointer, const char* entry, float* output, int param_4);

    // Weapon parsing
    void ParseZAmmo(int param_1, int32_t pointer);
    void ReadWeaponArchive(int32_t pointer, const char* file);

	static void FlipBytes(char* src, char* buffer, int offset);
    static char* TrimUpTowards(char* src, char* match);
}