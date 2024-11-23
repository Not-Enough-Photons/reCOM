#pragma once
#include "gamez/zAnim/anim_main.h"
#include "gamez/zMath/zmath_main.h"
#include "gamez/zEntity/ent_main.h"
#include "gamez/zNode/node_main.h"
#include "gamez/zSystem/zsys_main.h"

CAppCamera appCamera;

bool camera_tether_intersects_something = false;
float save_short_tether_length = 10000.0f;
float DeltaRot = 0.0f;
float DeltaAim = 0.0f;

// void FirstToThirdPersonTransition(CAppCamera* appCamera);
// void ThirdToFirstPersonTransition(CAppCamera* appCamera);
// void APTeatherCam(CAppCamera* appCamera, CMatrix* transform, float offset);

enum CAMVIEW
{
	FIRSTPERSON,
	THIRDPERSON
};

enum SEAL_PEEK
{
	PEEK_LEFT,
	PEEK_RIGHT
};

enum PLAYER_CAM_STATE
{
	type_00,
	type_01,
	type_02,
	type_03,
	type_04
};

enum CAM_DEATH_STATE
{
	type_00,
	type_01,
	type_02,
	type_03,
	type_04
};

struct cam_wiggle
{
	float amplitude;
	float duration;
	float rate;
};

struct throw_params
{
	float m_abort_threshold;
	float max_distance_stand;
	float max_distance_crouch;
	float toss_power_threshold;
	float toss_aim_threshold;
};

class CCameraParams
{
public:
	CPnt3D m_cam_offset;
	CPnt3D m_cam_aimpoint;
};

namespace zdb
{
	struct tag_CAMERA_PARAMS
	{
		CQuat m_quat;

		CPnt4D m_fog_color;

		float m_hfov;
		float m_vfov;

		float m_near_plane;
		float m_mid_plane;
		float m_far_plane;

		CPnt3D m_px_fog_color;
		CPnt3D m_nx_fog_color;
		CPnt3D m_pz_fog_color;
		CPnt3D m_nz_fog_color;
		float m_fog_near;
		float m_fog_far;
		float m_fog_mid;
		float m_fogA;
		float m_fogB;
		float m_fog_density;
		float m_fog_top;
		float m_fog_bottom;
		float m_landmark_fog_top;
		float m_landmark_fog_bottom;

		unsigned int m_flags_unused : 29;

		bool m_fog_enabled;
		bool m_directional_fog_enabled;
		bool m_fog_alt_enabled;
	};

	struct tag_RECT
	{
		int left;
		int top;
		int right;
		int bottom;
	};

	struct tag_ZCAM_MTX_SET
	{
		float mtxWorldToView[4][4];
		float mtxWorldToClip[4][4];
		float mtxViewToClip[4][4];
		float mtxViewToScreen[4][4];
	};

	struct tag_FrameSetup
	{
		_word128 dmaTag;
		_word128 vifTag;
		float mtxWorldToScreen[4][4];
		float mtxWorldToClip[4][4];
		float mtxClipToScreen[4][4];
		float mtxLightNormal[4][4];
		float mtxLightColor[4][4];
		float fogA[4];
		float fogB[4];
		_word128 shadowGifTag;
	};

	enum tag_ZCAM_TYPE
	{
		type_00,
		type_01,
		type_02
	};

	struct _tag_SAVE_CAMERA_PARAMS
	{
		tag_CAMERA_PARAMS m_CameraParams;
		float m_RangeScale;
	};

	struct ZCAM_CLIP_DATA
	{
		CPnt4D ViewPlanePoint;
		CPnt4D NearPlanePoint;
		CPnt4D NearPlaneNormal;
		CPnt4D LeftPlaneNormal;
		CPnt4D RightPlaneNormal;
		CPnt4D TopPlaneNormal;
		CPnt4D BottompPlaneNormal;
	};

	class CCamera : public CNode, tag_CAMERA_PARAMS
	{
	public:
		static void RegisterAnimCommands();

		static _zanim_cmd_hdr* CmdParseRelease(_zrdr* reader);
		static _zanim_cmd_hdr* CmdParseAcquire(_zrdr* reader);
		static _zanim_cmd_hdr* CmdParseIndoorsTest(_zrdr* reader);
		static _zanim_cmd_hdr* CmdParseSetRegions(_zrdr* reader);
		static _zanim_cmd_hdr* CmdParseGetRegions(_zrdr* reader);
		static _zanim_cmd_hdr* CmdParseParams(_zrdr* reader);

		static void CmdBeginParams(_zanim_cmd_hdr* header);

		static bool CmdTickControlSwitch(_zanim_cmd_hdr* header, float* delta);
		static bool CmdTickIndoorsTest(_zanim_cmd_hdr* header, float* delta);
		static bool CmdTickSetRegions(_zanim_cmd_hdr* header, float* delta);
		static bool CmdTickGetRegions(_zanim_cmd_hdr* header, float* delta);
		static bool CmdTickParams(_zanim_cmd_hdr* header, float* delta);
	public:
		float GetScaledRangeSquared(const CPnt3D& point);
	public:
		float m_Zmin;
		float m_Zmax;
		float m_RangeScale;
	private:
		CPnt3D m_frustum[3];
		CPnt3D m_fullfrustum[6];
		int m_full_frustum_points;

		PNT2D m_sin;
		PNT2D m_cos;
		PNT2D m_tan;
		PNT2D m_cot;

		std::vector<void*> m_LensFlareList;

		_tag_SAVE_CAMERA_PARAMS m_saveParams;

		float m_scrZ;

		std::vector<void*> m_lensflare_vec;

		bool m_PlayerCanSeeRegions;
		bool m_CameraCanSeeRegions;
		bool m_SeeRegions;
		bool m_IsInside;
		
		int m_AboveMaterial;

		float m_landmark_far_plane;

		tag_ZCAM_MTX_SET m_mtxSet;
		ZCAM_CLIP_DATA m_ClipSet;
		
		PNT2D m_screenAspect;
		PNT2D m_screenCenter;
		PNT2D m_screenOffset;
		tag_RECT m_screen;
		PNT2D m_screenConstant;

		float m_guardBand_min[4];
		float m_guardBand_max[4];

		float m_vecClipVolume[4];
		float m_farCorner[2][4];
		CPnt4D m_fog_alt[2];
		CPnt4D m_landmark_fog_alt[2];

		tag_ZCAM_TYPE m_type;

		unsigned int m_fovMask;
	};
}

class CAppCamera
{
public:
	CAppCamera(zdb::CWorld* world, zdb::CCamera* camera);
	~CAppCamera();

	static void GetThirdPersonCameraPos(CPnt3D* out, float* partPosition);
	static _zanim_cmd_hdr* CmdParse3rdPersonTest(_zrdr* reader);
	static bool CmdTick3rdPersonTest(_zanim_cmd_hdr* header, float* delta);
	static void RegisterAnimCommands();
public:
	bool AttachTo(CZSealBody* seal);

	void LookAt(const CPnt3D* origin, const CPnt3D* direction, CMatrix* mat);

	void FTSTick(float delta) const;
	void Tick(float delta);

	void UpdateDeathCamState();
	void ResetDeathCam();
	void TickCameraWiggle(float delta, zdb::CCamera* camera);

	void SetZoom(float zoom);

	void WiggleScalar(float wiggle);
	void WiggleEcho(bool echo);
public:
	PLAYER_CAM_STATE m_camera_mode;
	PLAYER_CAM_STATE m_camera_last_mode;
private:
	CPnt3D m_cameraAim;
	CPnt3D m_cameraTie;
	CPnt3D m_camGoalPos;

	float m_goal_t_len;
	float m_short_tether_timer;
	unsigned int m_padid;

	zdb::CCamera* m_camera;
	zdb::CNode* m_camera_effects;
	CZSealBody* m_entity;
	CZBodyPart* m_skel_root;

	CPnt3D m_rPos;
	CPnt3D m_wPos;

	CAMVIEW m_ctrl_view;

	float m_view_delay;
	float m_z_nominal;

	float m_switch_time;
	float m_wiggle_amp;
	float m_wiggle_duration;
	float m_wiggle_inv_duration;
	float m_wiggle_rate;
	float m_wiggle_inv_rate;
	float m_wiggle_cur_time;
	float m_wiggle_scalar;
	bool m_wiggle_echo;

	CEntity* m_track;

	SEAL_PEEK m_save_peek;
	CAMVIEW m_save_view;

	bool m_auto_death_cam;
	bool m_allow_player_death_cam_control;
	CAM_DEATH_STATE m_cam_death_state;
	float m_death_state_timer;
	CZSealBody* m_killed;
	CZSealBody* m_killer;

	int m_flashcounter;

	float m_death_fade_out_time;
	float m_death_faded_time;
	float m_death_fade_in_time;

	float m_next_rumble_time;
	float m_next_rumble_time_scaler;
	int m_rumble_counter;
	float m_rumble_timer;
	float m_rumble_time;
	float m_rumble_time_scaler;
	float m_rumble_power;
	float m_rumble_power_scaler;
};