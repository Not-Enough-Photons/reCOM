#pragma once
#include "gamez/zAnim/zanim.h"

enum PARTICLE_TYPE
{
	PARTICLE_STANDARD,
	PARTICLE_ROTATED,
	PARTICLE_XZ,
	PARTICLE_STREAKED,
	NUM_PARTICLE_TYPES
};

class Particle
{
public:
	struct Props
	{
		s32 m_refCount;

		Sequence m_textureSeq;
		Sequence m_colorSeq;
		Sequence m_scaleSeq;

		zdb::CModel* m_model;
		f32 m_friction;
		CPnt4D m_accelW;
		f32 m_windFactor;
		f32 m_priority;
		f32 m_nearFade1;
		f32 m_nearFade2;
		f32 m_farFade1;
		f32 m_farFade2;
		f32 m_invNearFade;
		f32 m_invFarFade;
		f32 m_visualDensity;
		bool m_checkFade;
	};
};