#include <string>


void FUN_001be4a0(void* param_1, const char* buffer, int* output)
{

}

void WeaponRdr(void* param_1, void* param_2, void* param_3, void* param_4)
{
	int numEntries = 0;
	std::string propertyBuffer;
	FUN_001be4a0(param_2, "WEAPON_ZAR_VERSION", &numEntries);
	FUN_001be4a0(param_2, propertyBuffer.c_str(), &numEntries);
}