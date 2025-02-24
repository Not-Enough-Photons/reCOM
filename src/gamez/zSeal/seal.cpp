#include "zseal.h"

#include "gamez/zAI/zai.h"
#include "gamez/zNode/znode.h"

bool seal_init = false;

CZSealBody::CZSealBody(zdb::CNode* node, CCharacterType* chartype) : CEntity(ENT_TYPE_SEAL, node), CBody()
{
    m_MaxFollowerDistance = 0;
    m_MaxFollowerDistanceNext = 0;

    pa_di = zdb::DiIntersect();

    m_desiredState = SEAL_STATE::stateStand;
    m_desiredPeek = SEAL_PEEK::PEEK_RIGHT;
    
    m_recoilParam = 0.0f;
    m_select = NULL;

    m_snakePath.m_type_bias = 0.0f;
    m_snakePath.m_template = NULL;
    m_snakePath.m_overlay = new CAiPath();

    m_formation_dir = CPnt3D::unit_nz;
    m_saved_formation_dir = CPnt3D::unit_nz;

    m_charType = chartype;

    // m_mp_stats.Reset();
    // m_stats.Reset();

    m_accuracy.Factor = tanf(0.0f) * 0.70f;
    m_accuracy.FactorX = 0.0f;
    m_accuracy.FactorY = 0.0f;

    m_sealEx.m_seal = this;

    m_camera = NULL;

    m_advance_camera = false;
    m_retreat_camera = false;
    m_needs_respawn = false;

    m_inAirHorizVel = CPnt3D::zero;

    m_aim_dir = CPnt3D::unit_nz;
    m_aim_goal = CPnt3D::unit_nz;

    m_action_available_mask = 0;
    m_action_selection_mask = 0;
    m_action_display_on = false;
    m_formation_clock = 0;
    m_follow_params_are_current = false;
    m_saved_formation_dir_is_valid = false;
    
    pa_diIntersectHandle = -999;

    numChords = 0;

    dpos = CPnt3D::zero;

    // BodySetState(0);
    // m_kit.Init();
    // m_kit.SetBody(this);

    m_threatdir[0] = 0;
    m_threatscale[0] = 0.0f;
    m_threatangle[0] = 0.0f;
    m_threatscale[1] = 0.0f;
    m_threatangle[1] = 0.0f;
    m_threatscale[2] = 0.0f;
    m_threatangle[2] = 0.0f;
    m_threatscale[3] = 0.0f;
    m_threatangle[3] = 0.0f;
    m_threatscale[4] = 0.0f;
    m_threatangle[4] = 0.0f;
    m_threatscale[5] = 0.0f;
    m_threatangle[5] = 0.0f;
    m_threatscale[6] = 0.0f;
    m_threatangle[6] = 0.0f;
    m_threatscale[7] = 0.0f;
    m_threatangle[7] = 0.0f;

    m_adrenaline = new CAiDecay();

    zdb::CNode* child = node->FindChild("seal_body", true);

    if (!child)
    {
        child = node->FindChild("skel_root", true);
    }

    if (child)
    {
        m_body_parts.reserve(32);

        // BodySetup(child, NULL);

        m_root = FindPart("skel_root");
        m_lfoot = FindPart("lfoot");
        m_rfoot = FindPart("rfoot");
        m_lhand = FindPart("lhand");
        m_spinelo = FindPart("spinelo");
        m_rhand = FindPart("rhand");
        m_hips = FindPart("hips");
        m_head = FindPart("head");
        m_neck = FindPart("neck");
        m_spinehi = FindPart("spinehi");
        m_lthigh = FindPart("lthigh");
        m_rthigh = FindPart("rthigh");
        m_rcalf = FindPart("rcalf");
        m_rbicep = FindPart("rbicep");
        m_rforearm = FindPart("rforearm");
        m_lbicep = FindPart("lbicep");
        m_lforearm = FindPart("lforearm");
        m_lscap = FindPart("lscap");
        m_rscap = FindPart("rscap");
        m_lshoulder_wgt = FindPart("lshoulder_wgt");
        m_rshoulder_wgt = FindPart("rshoulder_wgt");
        m_lcalf = FindPart("lcalf");
        m_aimnodes = FindPart("aimnodes");
        m_ltoe = FindPart("ltoe");
        m_rtoe = FindPart("rtoe");

        m_leyelid = NULL;
        m_reyelid = NULL;
        m_leyeball = NULL;
        m_reyeball = NULL;

        m_weapons.resize(6);

        m_item = SEAL_ITEM::itemRifle;

        // AddWeapon(SEAL_ITEM::itemRifle);
        // AddWeapon(SEAL_ITEM::itemPistol);
        // AddWeapon(SEAL_ITEM::itemThrowable);

        m_rifle = FindPart("rifle");
        m_pistol = FindPart("pistol");
        m_grenade = FindPart("grenade");

        m_weapon_state = 2;
        zdb::CNode* weaponnode = new zdb::CNode();

        m_deallocList.insert(m_deallocList.begin(), weaponnode);

        weaponnode->SetName("weapon");

        // m_weapon = AddBodyPart(weaponnode);

        m_rifle_as_gear = NULL;
        m_pistol_as_gear = NULL;

        // AddItem("rifle_out");

        m_curr_aimpt = NULL;
        m_curr_firept = NULL;

        m_curr_aimpos = CPnt3D::zero;
        m_curr_firepos = CPnt3D::zero;
        m_aim_norm = CPnt3D::zero;
        m_prev_aim_point = CPnt3D::zero;
        m_prev_aim_norm = CPnt3D::zero;
        m_prev_reticle_pt = CPnt3D::zero;

        m_crouch = new CCrouchedRun();
        m_fire = new CFire();
        m_look = new CLook();
        m_eyelook = new CLook();
        m_blink = new CBlink();
        m_lookitem = new CLookItem();
        m_turnip = new CTurnInPlace();

        //WepWaitOn();

        m_carry = NULL;

        m_skel_root = CPnt3D::zero;
        
        // SetBlendPool(8);

        // bool animSetupSuccess = AnimSetup();
    }

    // Creation of the CZSealBody instance went terribly wrong.
    // End the program.
    zVid_Assert(false, LONG_MAX, __FILE__, __LINE__);
}

void CZSealBody::StopAllHeartbeatSounds()
{
    if (m_heartbeat_sndisnt)
    {
        m_heartbeat_sndisnt->Stop();
        CSndInstance::ReleaseSoundInstance(m_heartbeat_sndisnt);
        m_heartbeat_sndisnt = NULL;
        m_heartbeat_curindex = 0xffffffff;
    }
}
