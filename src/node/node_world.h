#pragma once
#include "node_main.h"

namespace zdb
{
	static CNodeUniverse* NodeUniverse;
	static CWorld* theWorld;
	static CAppCamera* appCamera;

	// What a weird naming scheme.
	class CNodeUniverse
	{
	public:
		void AddNode(const CNode& node);
	};

	class CWorld
	{
	public:
		static int GetVersion();

		void Init();
		void Uninit();
		void diTick();
		void Update();

		void AddChild(const CNode& child);
		void AddLandmark(const CNode& landmark);
		void AddTextureAssetCharacter(const CNode& textureAsset);

		void DeleteChildren();
		void DeleteLandmark(const CNode& landmark);

		undefined4 DismemberWorldModel();

		void ClearLightMapList();
		void ClearShadowList();
		void WipeoutTextureAssetCharacters();

		void ComputeLightIntensity(float intensity, const CPnt3D& point, float* lightRef);

		void GetTexHandle() const;
		undefined4 GetTextureByName(const char* name) const;
		int GetModel() const;
	};

	class CWind
	{
	public:
		static void RegisterAnimCommands();
		void CmdParseWind();
	};
}