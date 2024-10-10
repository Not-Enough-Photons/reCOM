#include "zrdr_parse.h"
namespace zdb
{
    // From https://www.unknowncheats.me/forum/general-programming-and-reversing/569991-pcsx2-guide-cheats-trainers.html
    uintptr_t GetPS2Address(unsigned int RAW_PS2_OFFSET)
    {
        return (BasePS2MemorySpace + RAW_PS2_OFFSET);
    }

    template<typename T> inline T PS2Read(uintptr_t Address)
    {
        unsigned int format = *(int32_t*)Address;
        T A{};
        A = (T)format;
        return A;
    }

    template<typename T> inline void PS2Write(uintptr_t Address, T Patch)
    {
        *(int32_t*)Address = Patch;
    }

    template<typename T> inline T PS2Read(int32_t ps2Address)
    {
        return PS2Read<T>(GetPS2Address(ps2Address));
    }

    inline std::string PS2Read(uintptr_t address)
    {
        std::string str;
        uintptr_t addr = address;

        char c = PS2Read<char>(addr);

        while (c != '\0')
        {
            c = PS2Read<char>(addr++);
            str += c;
        }

        return str;
    }

    inline std::string PS2Read(int32_t address)
    {
        uintptr_t addr = GetPS2Address(address);
        return PS2Read(addr);
    }

    int32_t GetPathToLabel(int32_t pointer, const char* entry, int iterations)
    {
        if (pointer == 0)
        {
            return 0;
        }

        int type = static_cast<int>(PS2Read<char>(pointer));

        if (type != 4)
        {
            return 0;
        }

        int depth = static_cast<int>(PS2Read<char>(pointer + TWO_BYTES));
        int32_t path = 0;

        for (; path == 0 && iterations < depth; iterations++)
        {
            int count = 0;

            if (type == 4)
            {
                count = static_cast<int>(PS2Read<char>(pointer + TWO_BYTES));
            }

            int32_t nextPath = 0;

            if (iterations < count)
            {
                nextPath = PS2Read<int32_t>((pointer + FOUR_BYTES) + iterations * EIGHT_BYTES);
            }

            char nextPathType = PS2Read<char>(nextPath);

            if (nextPathType == 4)
            {
                path = GetPathToLabel(nextPath, entry, 0);
            }
            else
            {
                bool entriesMatch = false;

                if (nextPathType == 3)
                {
                    int32_t labelPtr = PS2Read<int32_t>(nextPath + FOUR_BYTES);
                    std::string other = PS2Read(labelPtr);

                    entriesMatch = strcmp(entry, other.c_str()) == 0;

                    if (entriesMatch)
                    {
                        path = static_cast<int32_t>(PS2Read<int32_t>((pointer + FOUR_BYTES)) + (iterations + 1) * EIGHT_BYTES);
                    }
                }
            }
        }

        return path;
    }

    int ReadString(int32_t pointer, const char* entry, std::string* output)
    {
        int32_t entryPath = GetPathToLabel(pointer, entry, 0);

        if (entryPath != 0 && output != nullptr)
        {
            char type = PS2Read<char>(entryPath);
            int depth = PS2Read<char>(entryPath + TWO_BYTES);

            if (type == 4)
            {
                if (depth == 0)
                {
                    entryPath = 0;
                }
                else
                {
                    entryPath = PS2Read<int32_t>(entryPath + FOUR_BYTES);
                }
            }

            int32_t nextData = PS2Read<int32_t>(entryPath + FOUR_BYTES);
            type = PS2Read<char>(entryPath);
            int dataExists = PS2Read<int>(nextData);
            if (type == 1 && nextData == 0)
            {
                output = 0;
                return 1;
            }
            else if (type == 3)
            {
                std::string out = PS2Read(nextData);
                *output = out.c_str();
                return 1;
            }
        }

        return 0;
    }

    int ReadInt(int32_t pointer, const char* entry, int* output, int param_4)
    {
        int var4 = 0;
        int32_t entryPath = GetPathToLabel(pointer, entry, 0);

        std::cout << "Entry pointer: " << entryPath << std::hex << std::endl;

        if (entryPath == 0)
        {
            return 0.0f;
        }

        char type = PS2Read<char>(entryPath);
        int depth = PS2Read<char>(entryPath + TWO_BYTES);

        std::cout << "Type: " << (int)type << std::endl;
        std::cout << "Depth: " << depth << std::endl;

        if (type == 4 && param_4 <= depth)
        {
            var4 = 1;
            int var3 = 0;
            if (0 < param_4)
            {
                do
                {
                    int var2 = 0;
                    if (type == 4)
                    {
                        var2 = depth;
                        std::cout << "Type is 4, depth is set" << std::endl;
                    }

                    int32_t next = 0;
                    if (var3 < var2)
                    {
                        next = PS2Read<int32_t>((pointer + FOUR_BYTES) + var3 * EIGHT_BYTES);
                        std::cout << "Next pointer: " << std::hex << next << std::endl;
                    }

                    int value = 0;
                    char nextType = PS2Read<char>(next);
                    if (nextType == 2)
                    {
                        value = PS2Read<int>(next + FOUR_BYTES);
                        std::cout << "Next type is 2" << std::endl;
                        std::cout << "Value is: " << value << std::endl;
                    }
                    else if (nextType == 1)
                    {
                        int32_t a = PS2Read<int32_t>(next + FOUR_BYTES);
                        value = PS2Read<int>(a);
                        std::cout << "Next type is 1" << std::endl;
                        std::cout << "Value is: " << value << std::endl;
                    }
                    else
                    {
                        std::cout << "There was no type" << std::endl;
                        value = 0;
                        std::cout << "Value is: " << value << std::endl;
                    }

                    var3++;
                    *output = value;
                    output++;
                } while (var3 < param_4);
            }
        }

        return var4;
    }

    int ReadFloat(int32_t pointer, const char* entry, float* output, int param_4)
    {
        int var4 = 0;
        int32_t entryPath = GetPathToLabel(pointer, entry, 0);

        std::cout << "Entry pointer: " << entryPath << std::hex << std::endl;

        if (entryPath == 0)
        {
            return 0.0f;
        }

        char type = PS2Read<char>(entryPath);
        int depth = PS2Read<char>(entryPath + TWO_BYTES);

        std::cout << "Type: " << (int)type << std::endl;
        std::cout << "Depth: " << depth << std::endl;

        if (type == 4 && param_4 <= depth)
        {
            var4 = 1;
            int var3 = 0;
            if (0 < param_4)
            {
                do
                {
                    int var2 = 0;
                    if (type == 4)
                    {
                        var2 = depth;
                        std::cout << "Type is 4, depth is set" << std::endl;
                    }

                    int32_t next = 0;
                    if (var3 < var2)
                    {
                        next = PS2Read<int32_t>((pointer + FOUR_BYTES) + var3 * EIGHT_BYTES);
                        std::cout << "Next pointer: " << std::hex << next << std::endl;
                    }

                    float value = 0.0f;
                    char nextType = PS2Read<char>(next);
                    if (nextType == 2)
                    {
                        value = PS2Read<float>(next + FOUR_BYTES);
                        std::cout << "Next type is 2" << std::endl;
                        std::cout << "Value is: " << value << std::endl;
                    }
                    else if (nextType == 1)
                    {
                        int32_t a = PS2Read<int32_t>(next + FOUR_BYTES);
                        value = PS2Read<float>(a);
                        std::cout << "Next type is 1" << std::endl;
                        std::cout << "Value is: " << value << std::endl;
                    }
                    else
                    {
                        std::cout << "There was no type" << std::endl;
                        value = 0.0f;
                        std::cout << "Value is: " << value << std::endl;
                    }

                    var3++;
                    *output = value;
                    output++;
                } while (var3 < param_4);
            }
        }

        return var4;
    }

    void ParseZAmmo(int param_1, int32_t pointer)
    {
        const char* missingEntryString = "NOT FOUND";
        int result = 0;

        std::string* stringOut = new std::string;
        float* floatOut = new float;
        int* intOut = new int;

        result = ReadString(pointer, "InternalName", stringOut);
        zAmmoValues.internalName = result == 1 ? stringOut->c_str() : missingEntryString;

        result = ReadString(pointer, "DisplayName", stringOut);
        zAmmoValues.displayName = result == 1 ? stringOut->c_str() : missingEntryString;

        result = ReadString(pointer, "Description", stringOut);
        zAmmoValues.description = result == 1 ? stringOut->c_str() : missingEntryString;

        result = ReadInt(pointer, "ID", intOut, 1);
        zAmmoValues.id = result != 0 ? *intOut : 0;

        result = ReadFloat(pointer, "ImpactDamage", floatOut, 1);
        zAmmoValues.impactDamage = result != 0.0f ? *floatOut : 0.0f;

        result = ReadString(pointer, "HitAnimName", stringOut);
        zAmmoValues.hitAnimName = result == 1 ? stringOut->c_str() : missingEntryString;

        result = ReadFloat(pointer, "Stun", floatOut, 1);
        zAmmoValues.stun = result != 0.0f ? *floatOut : 0.0f;

        result = ReadFloat(pointer, "Piercing", floatOut, 1);
        zAmmoValues.piercing = result != 0.0f ? *floatOut : 0.0f;

        result = ReadFloat(pointer, "Explosion_Damage", floatOut, 1);
        zAmmoValues.explosionDamage = result != 0.0f ? *floatOut : 0.0f;

        result = ReadFloat(pointer, "Explosion_Radius", floatOut, 1);
        zAmmoValues.explosionRadius = result != 0.0f ? *floatOut : 0.0f;

        result = ReadInt(pointer, "NumProjectilesFired", intOut, 1);
        zAmmoValues.numProjectilesFired = result != 0 ? *intOut : 0;

        result = ReadFloat(pointer, "Blowback_Falloff", floatOut, 1);
        zAmmoValues.blowbackFalloff = result != 0.0f ? *floatOut : 0.0f;

        result = ReadFloat(pointer, "Blowback_End", floatOut, 1);
        zAmmoValues.blowbackEnd = result != 0.0f ? *floatOut : 0.0f;

        result = ReadFloat(pointer, "ProximityDistance", floatOut, 1);
        zAmmoValues.proximityDistance = result != 0.0f ? *floatOut : 0.0f;

        result = ReadFloat(pointer, "AccelerationFactor", floatOut, 1);
        zAmmoValues.accelerationFactor = result != 0.0f ? *floatOut : 0.0f;

        result = GetPathToLabel(pointer, "Volitile", 0);
        zAmmoValues.volitile = result;

        result = GetPathToLabel(pointer, "IgnoreExplosionDI", 0);
        zAmmoValues.ignoreExplosionDI = result;

        delete stringOut;
        delete floatOut;
        delete intOut;
    }

    void ReadWeaponArchive(int32_t pointer, const char* file)
    {
        if (pointer != 0)
        {
            int32_t weaponGlobal = GetPathToLabel(pointer, "WEAPON_GLOBAL", 0);
            float output = 0.0f;
            int result = 0;
            result = ReadFloat(weaponGlobal, "SoundDistanceClose", &output, 1);
            result = ReadFloat(weaponGlobal, "SoundDistanceMed", &output, 1);
            result = ReadFloat(weaponGlobal, "SoundDistanceFar", &output, 1);

            int32_t zAmmo = GetPathToLabel(pointer, "ZAMMO", 0);
            char ammoEntryType = PS2Read<char>(zAmmo);
            int ammoEntryDepth = 0;
            if (ammoEntryType == 4)
            {
                ammoEntryDepth = PS2Read<int>(zAmmo + TWO_BYTES);
            }
            else
            {
                ammoEntryDepth = 0;
            }

            int i = 0;
            if (ammoEntryDepth != 0)
            {
                do
                {
                    int var3 = 0;
                    if (ammoEntryType == 4)
                    {
                        var3 = ammoEntryDepth;
                    }

                    int var1 = 0;
                    if (i < var3)
                    {
                        var1 = PS2Read<int>((pointer + FOUR_BYTES) + var3 * EIGHT_BYTES);
                    }

                    ParseZAmmo(pointer, var1);
                    i++;
                } while (i < ammoEntryDepth);
            }
        }

        std::cout << zAmmoValues.internalName << std::endl;
        std::cout << zAmmoValues.displayName << std::endl;
        std::cout << zAmmoValues.description << std::endl;
    }

    static void FlipBytes(char* src, char* buffer, int offset)
    {
        int i;
        char* pbVar1;

        if ((src != '\0') && (i = 0, 0 < offset))
        {
            if (8 < offset)
            {
                do
                {
                    pbVar1 = buffer + i;
                    i += 8;
                    *pbVar1 = ~*pbVar1;
                    pbVar1[1] = ~pbVar1[1];
                    pbVar1[2] = ~pbVar1[2];
                    pbVar1[3] = ~pbVar1[3];
                    pbVar1[4] = ~pbVar1[4];
                    pbVar1[5] = ~pbVar1[5];
                    pbVar1[6] = ~pbVar1[6];
                    pbVar1[7] = ~pbVar1[7];
                } while (i < offset - 8);
            }

            for (; i < offset; i++)
            {
                *(buffer + i) = ~*(buffer + i);
            }
        }
    }

    static char* TrimUpTowards(char* src, char* match)
    {
        if (*src == '\0')
        {
            char* terminator = '\0';

            if (*match == '\0')
            {
                terminator = src;
            }

            return terminator;
        }

        while (true)
        {
            // hit a null terminator
            // return the character buffer
            if (*match == '\0')
            {
                return src;
            }

            // match landed on our first character
            if (*match == *src)
            {
                int next = 1;

                while (true)
                {
                    // next character is a null terminator?
                    if (match[next] == '\0')
                    {
                        return src;
                    }

                    // not our target character in the target string, 
                    // ignore and break out of this loop
                    if (match[next] != src[next])
                    {
                        break;
                    }

                    next++;
                }
            }

            src++;
            if (*src == '\0')
            {
                break;
            }
        }

        return '\0';
    }
}