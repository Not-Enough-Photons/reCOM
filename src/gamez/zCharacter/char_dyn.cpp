﻿#include "zchar.h"
#include "gamez/zEntity/zentity.h"
#include "gamez/zSeal/zseal.h"

void CharacterDynamics::Load(_zrdr* reader)
{
    if (!m_loaded)
    {
        m_loaded = true;

        zrdr_findreal(reader, "gravity", &m_gravity, 1);
        zrdr_findreal(reader, "DamageToNewtons", &m_DamageToNewtons, 1);
        zrdr_findreal(reader, "jump_factor", &m_jumpFactor, 1);
        zrdr_findreal(reader, "land_fall_rate", &m_landFallRate, 1);
        zrdr_findreal(reader, "land_hard_fall_rate", &m_landHardFallRate, 1);
        zrdr_findreal(reader, "ground_touch_distance", &m_groundTouchDistance, 1);
        zrdr_findreal(reader, "max_slope", &m_maxSlopeCos, 1);
        m_maxSlopeCos = cosf(m_maxSlopeCos * RAD_TO_DEG);
        zrdr_findreal(reader, "step_height", &m_stepHeight, 1);
        zrdr_findreal(reader, "vertical_blast_boost", &m_blastBoostY, 1);
        m_fallDist[0] = 1.3f;
        m_fallDist[1] = 2.6f;
        m_fallDist[2] = 8.0f;
        zrdr_findreal(reader, "FALLING_DAMAGE_LIGHT", &m_fallDist[0], 1);
        zrdr_findreal(reader, "FALLING_DAMAGE_HEAVY", &m_fallDist[1], 1);
        zrdr_findreal(reader, "FALLING_DAMAGE_DEATH", &m_fallDist[2], 1);
        m_fallDist[0] *= zdb::CWorld::m_scale;
        m_fallDist[1] *= zdb::CWorld::m_scale;
        m_fallDist[2] *= zdb::CWorld::m_scale;

        for (u32 i = 0; i < 3; i++)
        {
            m_landSpeed[i] = theCharacterDynamics.m_gravity * sqrtf(m_fallDist[i] * 2.0f / theCharacterDynamics.m_gravity);
        }

        zrdr_findreal(reader, "water_factor_slope", &m_waterFactorSlope, 1);
        zrdr_findreal(reader, "min_water_factor", &m_minWaterFactor, 1);
        zrdr_findreal(reader, "fb_accel", &m_fbStiffness, 1);
        zrdr_findreal(reader, "lr_accel", &m_lrStiffness, 1);
        zrdr_findreal(reader, "throt_exp", &m_throtExp, 1);
        m_throtScale = 1.0f / (m_throtExp - 1.0f);

        f32 stand_turn_factor = 0.0f;
        
        if (zrdr_findreal(reader, "stand_turn_factor", &stand_turn_factor, 1))
        {
            m_standTurnFactor = stand_turn_factor;
        }

        zrdr_findreal(reader, "turn_maxrate", &m_turn_maxRate, 1);
        zrdr_findreal(reader, "lower_x_accel", &m_accelXMin, 1);
        zrdr_findreal(reader, "upper_x_accel", &m_accelXMax, 1);
        zrdr_findreal(reader, "lower_z_accel", &m_accelZMin, 1);
        zrdr_findreal(reader, "upper_z_accel", &m_accelZMax, 1);

        f32 fval = 0.0f;

        if (zrdr_findreal(reader, "init_aim_pitch", &fval, 1))
        {
            m_initAimPitch = fval * RAD_TO_DEG;
        }

        if (zrdr_findreal(reader, "max_aim_pitch", &fval, 1))
        {
            m_maxAimPitch = fval * RAD_TO_DEG;
        }

        if (zrdr_findreal(reader, "max_aim_yaw", &fval, 1))
        {
            m_maxAimYaw = fval * RAD_TO_DEG;
        }

        m_cosProneMaxAimPitch = cosf(m_proneMaxAimPitch);
        m_cosProneMinAimPitch = cosf(m_proneMinAimPitch);
        m_cosProneMaxAimYaw = cosf(m_proneMaxAimYaw);

        if (zrdr_findreal(reader, "max_zoom_aim_pitch", &fval, 1))
        {
            m_maxZoomAimPitch = fval * RAD_TO_DEG;
        }

        if (zrdr_findreal(reader, "min_zoom_aim_pitch", &fval, 1))
        {
            m_minZoomAimPitch = fval * RAD_TO_DEG;
        }

        if (zrdr_findreal(reader, "max_zoom_aim_yaw", &fval, 1))
        {
            m_maxZoomAimYaw = fval * RAD_TO_DEG;
        }

        m_cosMaxZoomAimPitch = cosf(m_maxZoomAimPitch);
        m_cosMinZoomAimPitch = cosf(m_minZoomAimPitch);
        m_cosMaxZoomAimYaw = cosf(m_maxZoomAimYaw);

        if (zrdr_findreal(reader, "prone_max_zoom_aim_pitch", &fval, 1))
        {
            m_proneMaxZoomAimPitch = fval * RAD_TO_DEG;
        }

        if (zrdr_findreal(reader, "prone_min_zoom_aim_pitch", &fval, 1))
        {
            m_cosProneMinZoomAimPitch = fval * RAD_TO_DEG;
        }

        if (zrdr_findreal(reader, "prone_max_zoom_aim_yaw", &fval, 1))
        {
            m_proneMaxZoomAimYaw = fval * RAD_TO_DEG;
        }

        m_cosProneMaxZoomAimPitch = cosf(m_proneMaxZoomAimPitch);
        m_cosProneMinZoomAimPitch = cosf(m_proneMinZoomAimPitch);
        m_cosProneMaxZoomAimYaw = cosf(m_proneMaxZoomAimYaw);

        if (zrdr_findreal(reader, "max_look_pitch", &fval, 1))
        {
            m_maxLookPitch = fval * RAD_TO_DEG;
        }

        if (zrdr_findreal(reader, "min_look_pitch", &fval, 1))
        {
            m_minLookPitch = fval * RAD_TO_DEG;
        }

        if (zrdr_findreal(reader, "max_look_yaw", &fval, 1))
        {
            m_maxLookYaw = fval * RAD_TO_DEG;
        }

        m_cosMaxLookPitch = cosf(m_maxLookPitch);
        m_cosMinLookPitch = cosf(m_minLookPitch);
        m_cosMaxLookYaw = cosf(m_maxLookYaw);

        if (zrdr_findreal(reader, "max_eye_look_pitch", &fval, 1))
        {
            m_maxEyelookPitch = fval * RAD_TO_DEG;
        }

        if (zrdr_findreal(reader, "min_eye_look_pitch", &fval, 1))
        {
            m_minEyelookPitch = fval * RAD_TO_DEG;
        }

        if (zrdr_findreal(reader, "max_eye_look_yaw", &fval, 1))
        {
            m_maxEyelookYaw = fval * RAD_TO_DEG;
        }

        m_cosMaxEyelookPitch = cosf(m_maxEyelookPitch);
        m_cosMinEyelookPitch = cosf(m_minEyelookPitch);
        m_cosMaxEyelookYaw = cosf(m_maxEyelookYaw);
        
        if (zrdr_findreal(reader, "max_blink_rate", &fval, 1))
        {
            m_maxBlinkRate = fval;
        }

        if (zrdr_findreal(reader, "max_blink_angle", &fval, 1))
        {
            m_maxBlinkAngle = fval * RAD_TO_DEG;
        }

        if (zrdr_findreal(reader, "pitch_rate", &fval, 1))
        {
            m_pitchRate = fval;
        }

        if (zrdr_findreal(reader, "turn_throttle_a", &fval, 1))
        {
            m_turnThrottleA = fval;
        }

        if (zrdr_findreal(reader, "turn_throttle_b", &fval, 1))
        {
            m_turnThrottleB = fval;
        }

        if (zrdr_findreal(reader, "pitch_throttle_a", &fval, 1))
        {
            m_pitchThrottleA = fval;
        }

        if (zrdr_findreal(reader, "pitch_throttle_b", &fval, 1))
        {
            m_pitchThrottleB = fval;
        }

        if (zrdr_findreal(reader, "camera_roll", &fval, 1))
        {
            m_cameraRoll = fval;
        }

        auto camera_wiggle = zrdr_findtag(reader, "CAMERA_WIGGLE");

        if (camera_wiggle && camera_wiggle->type == ZRDR_ARRAY)
        {
            zrdr_findreal(camera_wiggle, "Amplitude", &m_cam_wiggle.amplitude, 1);
            zrdr_findreal(camera_wiggle, "Duration", &m_cam_wiggle.duration, 1);
            zrdr_findreal(camera_wiggle, "Rate", &m_cam_wiggle.rate, 1);
        }

        auto bobbing_firstperson = zrdr_findtag(reader, "BOBBING_FIRSTPERSON");

        if (bobbing_firstperson && bobbing_firstperson->type == ZRDR_ARRAY)
        {
            if (zrdr_findreal(bobbing_firstperson, "Walk_Amplitude", &fval, 1))
            {
                CSealCtrl::m_bobbing1stperson_amplitude = fval;
            }

            if (zrdr_findreal(bobbing_firstperson, "Walk_Rate", &fval, 1))
            {
                CSealCtrl::m_bobbing1stperson_rate = fval;
            }

            if (zrdr_findreal(bobbing_firstperson, "Crawl_Amplitude", &fval, 1))
            {
                CSealCtrl::m_crawl1stperson_amplitude = fval;
            }

            if (zrdr_findreal(bobbing_firstperson, "Crawl_Rate", &fval, 1))
            {
                CSealCtrl::m_crawl1stperson_rate = fval;
            }
        }

        auto throw_params = zrdr_findtag(reader, "THROW_PARAMS");

        if (throw_params)
        {
            zrdr_findreal(throw_params, "abort_threshold", &m_throw_params.m_abort_threshold, 1);
            zrdr_findreal(throw_params, "max_distance_stand", &m_throw_params.max_distance_stand, 1);
            zrdr_findreal(throw_params, "max_distance_crouch", &m_throw_params.max_distance_crouch, 1);
            zrdr_findreal(throw_params, "toss_power_threshold", &m_throw_params.toss_power_threshold, 1);

            if (zrdr_findreal(throw_params, "toss_aim_threshold", &m_throw_params.toss_aim_threshold, 1))
            {
                m_throw_params.toss_aim_threshold = sinf(m_throw_params.toss_aim_threshold * RAD_TO_DEG);
            }
        }

        if (zrdr_findreal(reader, "zoom_factor", &fval, 1))
        {
            m_zoomFactor = fval;
        }

        if (zrdr_findreal(reader, "zoom_rate", &fval, 1))
        {
            m_zoomRate = fval;
        }

        m_cam_params.reserve(5);
        
        CCameraParams back;
        CCameraParams side;
        CCameraParams first;
        CCameraParams peekl;
        CCameraParams peekr;

        if (zrdr_findreal(reader, "cam_back_side", &fval, 1))
        {
            back.m_cam_offset.x = fval;
        }

        if (zrdr_findreal(reader, "cam_back_height", &fval, 1))
        {
            back.m_cam_offset.y = fval;
        }

        if (zrdr_findreal(reader, "cam_back_dist", &fval, 1))
        {
            back.m_cam_offset.z = fval;
        }

        if (!zrdr_findPNT3D(reader, "cam_back_aim", &back.m_cam_aimpoint))
        {
            back.m_cam_aimpoint.x = 0.0f;
            back.m_cam_aimpoint.y = 20.0f;
            back.m_cam_aimpoint.z = 0.0f;
        }

        m_cam_params.insert(m_cam_params.begin(), back);

        if (zrdr_findreal(reader, "cam_side_side", &fval, 1))
        {
            side.m_cam_offset.x = fval;
        }

        if (zrdr_findreal(reader, "cam_side_height", &fval, 1))
        {
            side.m_cam_offset.y = fval;
        }

        if (zrdr_findreal(reader, "cam_side_dist", &fval, 1))
        {
            side.m_cam_offset.z = fval;
        }

        if (!zrdr_findPNT3D(reader, "cam_side_aim", &side.m_cam_aimpoint))
        {
            side.m_cam_aimpoint.x = 0.0f;
            side.m_cam_aimpoint.y = 20.0f;
            side.m_cam_aimpoint.z = 0.0f;
        }

        m_cam_params.insert(m_cam_params.begin(), side);

        if (zrdr_findreal(reader, "cam_first_side", &fval, 1))
        {
            first.m_cam_offset.x = fval;
        }

        if (zrdr_findreal(reader, "cam_first_height", &fval, 1))
        {
            first.m_cam_offset.y = fval;
        }

        if (zrdr_findreal(reader, "cam_first_dist", &fval, 1))
        {
            first.m_cam_offset.z = fval;
        }

        if (!zrdr_findPNT3D(reader, "cam_first_aim", &first.m_cam_aimpoint))
        {
            first.m_cam_aimpoint.x = 0.0f;
            first.m_cam_aimpoint.y = 20.0f;
            first.m_cam_aimpoint.z = 0.0f;
        }

        m_cam_params.insert(m_cam_params.begin(), first);

        if (zrdr_findreal(reader, "cam_peekl_side", &fval, 1))
        {
            peekl.m_cam_offset.x = fval;
        }

        if (zrdr_findreal(reader, "cam_peekl_height", &fval, 1))
        {
            peekl.m_cam_offset.y = fval;
        }

        if (zrdr_findreal(reader, "cam_peekl_dist", &fval, 1))
        {
            peekl.m_cam_offset.z = fval;
        }

        if (!zrdr_findPNT3D(reader, "cam_peekl_aim", &peekl.m_cam_aimpoint))
        {
            peekl.m_cam_aimpoint.x = 0.0f;
            peekl.m_cam_aimpoint.y = 20.0f;
            peekl.m_cam_aimpoint.z = 0.0f;
        }

        m_cam_params.insert(m_cam_params.begin(), peekl);

        if (zrdr_findreal(reader, "cam_peekr_side", &fval, 1))
        {
            peekr.m_cam_offset.x = fval;
        }

        if (zrdr_findreal(reader, "cam_peekr_height", &fval, 1))
        {
            peekr.m_cam_offset.y = fval;
        }

        if (zrdr_findreal(reader, "cam_peekr_dist", &fval, 1))
        {
            peekr.m_cam_offset.z = fval;
        }

        if (!zrdr_findPNT3D(reader, "cam_peekr_aim", &peekr.m_cam_aimpoint))
        {
            peekr.m_cam_aimpoint.x = 0.0f;
            peekr.m_cam_aimpoint.y = 20.0f;
            peekr.m_cam_aimpoint.z = 0.0f;
        }

        m_cam_params.insert(m_cam_params.begin(), peekr);

        if (zrdr_findreal(reader, "cam_tether_stiff", &fval, 1))
        {
            m_cameraTetherStiffness = fval;
        }

        if (zrdr_findreal(reader, "cam_look_dwell", &fval, 1))
        {
            m_cameraLookDwell = fval;
        }

        if (zrdr_findreal(reader, "cam_net_pos_smooth", &fval, 1))
        {
            m_cameraNetPosSmooth = fval;
        }

        if (zrdr_findreal(reader, "cam_net_release_rad", &fval, 1))
        {
            m_cameraReleaseRad = fval;
        }

        if (zrdr_findreal(reader, "cam_peek_decay_rate", &fval, 1))
        {
            m_cameraPeekDecayRate = fval;
        }

        zrdr_findreal(reader, "min_running_reload_speed", &fval, 1);
        m_running_reload_speed = fval * zdb::CWorld::m_scale;

        zrdr_findreal(reader, "min_running_chgweapon_speed", &fval, 1);
        m_running_chgweapon_speed = fval * zdb::CWorld::m_scale;

        zrdr_findreal(reader, "low_climb_height", &fval, 1);
        m_lowHeight = fval * zdb::CWorld::m_scale;

        zrdr_findreal(reader, "med_climb_height", &fval, 1);
        m_medHeight = fval * zdb::CWorld::m_scale;

        zrdr_findreal(reader, "high_climb_height", &fval, 1);
        m_highHeight = fval * zdb::CWorld::m_scale;

        zrdr_findreal(reader, "min_stand_height", &fval, 1);
        m_minStandHeight = fval * zdb::CWorld::m_scale;

        zrdr_findreal(reader, "min_jump_height", &fval, 1);
        m_minJumpHeight = fval * zdb::CWorld::m_scale;
    }
}
