#pragma once
namespace zdb
{
	typedef struct CPnt2D
	{
		float x;
		float y;
	};

	typedef struct CPnt3D
	{
		float x;
		float y;
		float z;
	};

	typedef struct CPnt4D
	{
		float x;
		float y;
		float z;
		float w;
	};

	typedef struct CQuat
	{
		float x;
		float y;
		float z;
		float w;
	};

	typedef union CMatrix
	{
		struct
		{
			CPnt4D r0;
			CPnt4D r1;
			CPnt4D r2;
			CPnt4D r3;
		};

		float m[4][4];
	};
}