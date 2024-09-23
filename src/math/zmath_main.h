#pragma once
namespace zdb
{
	typedef union Vector2
	{
		struct
		{
			float x;
			float y;
		};
	};

	typedef union Vector3
	{
		struct
		{
			float x;
			float y;
			float z;
		};
	};

	typedef union Vector4
	{
		struct
		{
			float x;
			float y;
			float z;
			float w;
		};
	};

	typedef union Ray2D
	{
		struct
		{
			Vector2 origin;
			Vector2 direction;
		};
	};

	typedef union Ray3D
	{
		struct
		{
			Vector3 origin;
			Vector3 direction;
		};
	};

	class C2D
	{

	};

	class C2DLine : public C2D
	{
	public:
		C2DLine();
		C2DLine(float x1, float y1, float x2, float y2);
		C2DLine(Vector2 p1, Vector2 p2);

		// Copy constructor
		C2DLine(const C2DLine& other);

		Vector2 GetPointOnLine();
		Vector2 IntersectsWithLine(const Vector2& point, const C2DLine& other);
		float GetLength();

		Vector2 GetFirstPoint() const;
		Vector2 GetSecondPoint() const;
	private:
		Vector2 m_p1;
		Vector2 m_p2;
	};
}