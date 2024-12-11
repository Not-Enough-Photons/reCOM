#pragma once
#include "znode.h"

#include "gamez/zMath/zmath.h"

namespace zdb
{
	class CNode;
	class CNodeUniverse;
	class CWorld;
	class CAppCamera;
	class CGrid;

	static CNodeUniverse* NodeUniverse;
	static CWorld* theWorld;
	static CAppCamera* appCamera;

	// What an interesting naming scheme.
	class CNodeUniverse
	{
	public:
		bool AddNode(CNode* node);
		void RemoveNode(CNode* node);
		CNode* GetElement(int index) const;
		int GetIndex(CNode* node) const;
	private:
		std::vector<CNode*> nodes;
		bool m_locked;
		int capacity;
		CNode** head;
		CNode** tail;
	};

	class CWorld : public CNode
	{
	public:
		CWorld() : CNode() {}
		~CWorld();

		static CWorld* m_world;

		static float m_scale;
		static float m_invscale;

		static int GetVersion();
		static void Init();
	public:
		void Uninit();
		void diTick();
		void Update();

		void AddChild(CNode* child);
		void AddLandmark(CNode* landmark);
		void AddTextureAssetCharacter(const CNode& textureAsset);
		void ReserveChildren(int count);

		void DeleteChildren();
		void DeleteLandmark(const CNode& landmark);

		// undefined4 DismemberWorldModel();

		void ClearLightMapList();
		void ClearShadowList();
		void WipeoutTextureAssetCharacters();

		void ComputeLightIntensity(float intensity, const CPnt3D& point, float* lightRef);

		void GetTexHandle() const;
		// undefined4 GetTextureByName(const char* name) const;
		int GetModel() const;
	private:
		int expandSize;
		std::vector<CNode*> children;
		std::vector<CNode*> landmarks;
		CGrid* grid;
	};

	class CGrid
	{
	public:
		CGrid();
		~CGrid();
	public:
		void Insert(CNode* node);
	};

	class CCell
	{
	public:

	};

	class CWind
	{
	public:
		static void RegisterAnimCommands();
		void CmdParseWind();
	};
}