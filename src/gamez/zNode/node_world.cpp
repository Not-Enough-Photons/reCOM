#include "znode.h"

#include "gamez/zAssetLib/zassetlib.h"
#include "gamez/zCamera/zcam.h"
#include "gamez/zVisual/zvis.h"
#include "gamez/zTexture/ztex.h"

#define MIN_POOL_SIZE 3000
#define POOL_INCREMENT 100

namespace zdb
{
	CNodeUniverse* NodeUniverse = NULL;

	CWorld* CWorld::m_world = NULL;
	f32 CWorld::m_scale = 1.0f;
	f32 CWorld::m_invscale = 1.0f / CWorld::m_scale;

	bool CNodeUniverse::AddNode(CNode* node)
	{
		bool success = false;

		if (!m_locked)
		{
			CNode* universeNode = node;
			int universeSize = size();

			if (universeSize == capacity())
			{
				if (capacity() < MIN_POOL_SIZE)
				{
					reserve(MIN_POOL_SIZE);
				}
				else
				{
					reserve(capacity() + POOL_INCREMENT);
				}
			}

			insert(begin(), universeNode);
			success = true;
		}
		else
		{
			success = false;
		}

		return success;
	}

	void CNodeUniverse::RemoveNode(CNode* node)
	{
		auto it = begin();
		while (it != end())
		{
			if (*it == node)
			{
				break;
			}

			it++;
		}

		*it = NULL;
	}

	CNode* CNodeUniverse::GetElement(s32 index) const
	{
		CNode* node;

		if (index < 0)
		{
			node = NULL;
		}
		else
		{
			node = NULL;

			if (index <= size())
			{
				node = at(index);
			}
		}

		return node;
	}

	int CNodeUniverse::GetIndex(CNode* node) const
	{
		int index = 0;
		auto it = begin();
		while (it != end())
		{
			if (*it == node)
			{
				break;
			}

			it++;
			index++;
		}

		return index;
	}

	CWorld::CWorld(const char* name)
	{
		m_camera = NULL;
		m_diInt = NULL;
		m_Wind.Reset();

		m_cellData = NULL;

		m_maxOverlap = 2;

		m_grid = new CGrid();

		SetName(name);

		m_scale = 10.0f;
		m_invscale = 0.1f;
		m_world = this;

		m_diInt = new DiIntersect(1024);
		m_diIntDelayCnt = 0.0f;

		m_gLightDirUpdate = true;
		m_gLightColUpdate = true;

		m_default_soiltype = 0;
		m_default_soiltype_name = NULL;
	}
	
	s32 CWorld::GetVersion()
	{
		return 0x10001;
	}

	CModel* CWorld::GetModel(const char* name)
	{
		return CAssetMgr::m_assets.GetModel(name);
	}

	bool CWorld::Initalize()
	{
		CCamera* camera = new CCamera();

		if (m_camera != camera)
		{
			m_camera = camera;
			CVisual::m_camera = camera;
		}

		m_camera->SetName("camera");
		m_camera->SetPosition(CPnt3D::zero.x, CPnt3D::zero.y, CPnt3D::zero.z);

		m_world->m_gLightColUpdate = true;
		m_world->m_gLightDirUpdate = true;

		// CTexHandle* handle = CTexHandle::Create(m_shadowTex[0]);
		// m_shadowTexH = handle;

		// CTexManager::m_texmanager->front()->Add(handle, true);

		return true;
	}

	void CWorld::ReserveChildren(s32 count)
	{
		m_child.reserve(count + m_child.capacity());
	}

	void CWorld::AddChild(CNode* child)
	{
		CWorld* parent = static_cast<CWorld*>(child->m_parent);

		if (parent != this)
		{
			CNode* node = child;

			if (parent != NULL && parent != this)
			{
				parent->DeleteChild(node);
			}

			// m_grid->Insert(node);

			node->m_parent = static_cast<CNode*>(this);

			if (m_child.capacity() == m_child.size())
			{
				m_child.reserve(m_child.capacity() + 100);
			}

			m_child.insert(m_child.begin(), node);

			CNode* temp = node;
			if (node->m_type != 2)
			{
				temp = NULL;
			}

			if (temp != NULL)
			{

			}

			// TODO:
			// Finish the part of this function that inserts "render maps", so the world can
			// dispatch them to the zRenderer.
		}
	}

	void CWorld::AddLandmark(CNode* landmark)
	{
		if (landmark->m_landmark)
		{

		}

		// landmark->RemoveFromParent();
	}

	bool CWorld::DismemberWorldModel()
	{
		CModel* worldmodel = CAssetMgr::m_assets.GetModel("worldmodel");

		if (!worldmodel)
		{
			return false;
		}

		// ReserveChildren(worldmodel->m_reflist.size());

		auto it = worldmodel->m_child.begin();

		while (it != worldmodel->m_child.end())
		{
			CNode* child = *it;
			m_child.insert(m_child.begin(), child);
			child->m_parent = this;
			// m_grid->Update();
			++it;
		}

		return true;
	}

	s32 CWorld::GenerateLandmarkList()
	{
		CNodeVector landmarks;
		CStack stack;
		
		CStack::m_pointer++;
		CStack::m_top++;

		// *CStack::m_top = CMatrix::identity;

		m_numNoFarClipNodes = 0;
		LandmarkList_Search(this, stack, landmarks);

		auto it = landmarks.begin();
		while (it != landmarks.end())
		{
			AddChild(*it);
			++it;
		}
		
		return 1;
	}

	void CWorld::LandmarkList_Search(CNode* node, CStack& matstack, CNodeVector& landmarks)
	{
		
	}

	void CWind::Reset()
	{
		m_ZenithGoal = 0.0f;
		m_AzimuthGoal = 0.0f;
		m_SpeedGoal = 0.0f;
		m_TickGoal = false;

		m_Zenith = 0.0f;
		m_Azimuth = 0.0f;
		m_Speed = 8.0f;

		m_AzimuthOffset = 0.0f;
		m_MinAzimuthOffset = -0.7853982f;
		m_MaxAzimuthOffset = 0.7853982f;
		
		m_ZenithOffset = 0.0f;
		m_MinZenithOffset = -0.7853982f;
		m_MaxZenithOffset = 0.7853982f;

		m_AzimuthOffsetVelocity = 0.2617994f;
		m_ZenithOffsetVelocity = 0.08726646f;

		m_SpeedOffset = 3.0f;
		m_MinSpeedOffset = -7.5f;
		m_MaxSpeedOffset = 9.0f;
		m_SpeedOffsetVelocity = 3.0f;
	}

}