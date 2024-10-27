#pragma once
#include "entity/ent_main.h"
#include "entity/weapon/zwep_weapon.h"

class CZKit
{
public:
	CZKit();
	~CZKit();

	void SetItemByIndex(int index, CZWeapon* weapon);
	void SetWeaponInfoChanged();
	void NVG_Enabled(bool enable);

	void* GetIcon(int index) const;
	float GetFireDelay() const;
	CZWeapon* GetCurItem() const;
	int GetNumItems() const;
	float GetCurZoom() const;

	void SetBody(const CZSealBody& body);
private:
	CZSealBody* seal;
	int curWeaponIdx;
	CZWeapon** arsenal;
	int numItems;
};

class CZSealBody : CEntity
{
public:
	CZSealBody(const zdb::CNode& node, const CCharacterType& character) : CEntity(CEntity::type_02, node) {}

	~CZSealBody();

	// Tomb Of The Unknown Functions
	static CZSealBody* Create(long param_1, int param_2, int param_3);

	void OnDeath();

	void TeleportTo(const CMatrix& mat);

	CCharacterType* GetCharacter() const;
	int GetHeadDamage(float headDmgOld, float headDmgNew);
	int GetBodyDamage(float bodyDmgOld, float bodyDmgNew);
	int GetArmDamage(float armDmgOld, float armDmgNew);
	int GetLegDamage(float legDmgOld, float legDmgNew);

	float SetHealth(float health);
	void SetArmor(float armor, DAMAGE_LOCATION location);
	void SetupDefaultArmor();
	void SetupKevlarArmor();
	void SetupKevlarInsertArmor();

	float GetFormationHeading(float heading) const;
	void UpdateFollowParams(float heading);
	void HandleKiller(const CZSealBody& killer);

	CZBodyPart* GetRootPart() const;
private:
	CCharacterType* character;
	float health;
	bool dead;

	float velX;
	float velY;

	float armorHead;
	float armorBody;
	float armorLArm;
	float armorRArm;
	float armorLLeg;
	float armorRLeg;

	bool hasFollower;

	CZBodyPart* skel_root;
};

class CZSealEx : public zdb::CNodeEx
{

};