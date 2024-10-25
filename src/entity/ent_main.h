#pragma once
#include "anim/anim_main.h"
#include "node/node_main.h"
#include "math/zmath_main.h"
#include "reader/zrdr_main.h"

class CharacterDynamics;
class CZSealBody;
class CZBodyPart;

int recycler_index = 0;
CftsPlayer* ftsPlayer;
CSealAnim* m_sealanim;
CharacterDynamics theDynamics;

void SealInitCharacterDynamics();

enum DAMAGE_LOCATION
{
	HEAD,
	BODY,
	LARM,
	RARM,
	LLEG,
	RLEG
};

class CCharacterType
{

};

class CharacterDynamics
{

};

class CEntity
{
public:
	CEntity();
	~CEntity();

	void IncrementAwareCounter();
	void DecrementAwareCounter();

	// Recycler functions
	virtual void OnRecycleEntity();
	void OpenRecycler();

	// Mission callback functions
	virtual void OnMissionStart();
	virtual void OnMissionEnd();

	// Tick virtual functions
	virtual void PreTick() {};
	virtual void PostPreTick() {};
	virtual void PrePostTick() {};
	virtual void Tick() {};
	virtual void PostTick() {};

	void SetDisplayName(const char* displayName);

	virtual void TeleportTo(const CMatrix& mat);

	zdb::CNode& GetNode() const;
	bool IsValid() const;

	void SetController(CEntityCtrl* controller);
private:
	zdb::CNode* m_node;

	float m_x00;
	float m_y00;
	float m_z00;
	float m_x01;
	float m_y01;
	float m_z01;
	float m_x02;
	float m_y02;
	float m_z02;
	float m_x03;
	float m_y03;
	float m_z03;
};

class CEntityCtrl
{
public:
	virtual void PreTick() = 0;
	virtual void Tick() = 0;
};

/// <summary>
/// Base FTS player class. FTS stands for "Fireteam Seal."
/// </summary>
class CftsPlayer
{
public:
	/// <summary>
	/// Gets the static player instance.
	/// </summary>
	/// <returns></returns>
	static CftsPlayer* ftsGetPlayer()
	{
		return ftsPlayer;
	}

	static void RegisterAnimCommands();
};

class CKit
{
public:
	void SetBody(const CZSealBody& body);
private:
	CZSealBody* seal;
};

class CZBodyPart
{
public:
private:
};

class CZSealBody : CEntity
{
public:
	CZSealBody();
	CZSealBody(const zdb::CNode& node, const CCharacterType& character);

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

class CZBombState
{
public:
	enum EnumBombState
	{
		value_00,
		value_01,
		value_02,
		value_03
	};

	static EnumBombState m_FutureBombState;
};