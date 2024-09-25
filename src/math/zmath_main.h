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

		inline Vector2 operator=(const Vector2 rhs)
		{
			this->x = rhs.x;
			this->y = rhs.y;
		}

		inline Vector2 operator+(const Vector2 rhs)
		{
			this->x += rhs.x;
			this->y += rhs.y;
		}

		inline Vector2 operator-(const Vector2 rhs)
		{
			this->x -= rhs.x;
			this->y -= rhs.y;
		}
	};

	typedef union Vector3
	{
		struct
		{
			float x;
			float y;
			float z;
		};

		inline Vector3 operator=(const Vector3 rhs)
		{
			this->x = rhs.x;
			this->y = rhs.y;
			this->z = rhs.z;
		}

		inline Vector3 operator+(const Vector3 rhs)
		{
			this->x += rhs.x;
			this->y += rhs.y;
			this->z += rhs.z;
		}

		inline Vector3 operator-(const Vector3 rhs)
		{
			this->x -= rhs.x;
			this->y -= rhs.y;
			this->z -= rhs.z;
		}
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

		inline Vector4 operator=(const Vector4 rhs)
		{
			this->x = rhs.x;
			this->y = rhs.y;
			this->z = rhs.z;
			this->w = rhs.w;
		}

		inline Vector4 operator+(const Vector4 rhs)
		{
			this->x += rhs.x;
			this->y += rhs.y;
			this->z += rhs.z;
			this->w += rhs.w;
		}

		inline Vector4 operator-(const Vector4 rhs)
		{
			this->x -= rhs.x;
			this->y -= rhs.y;
			this->z -= rhs.z;
			this->w -= rhs.w;
		}
	};

	typedef union Matrix4x4
	{
		struct
		{
			Vector4 r1;
			Vector4 r2;
			Vector4 r3;
			Vector4 r4;
		};

		float m[];
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

	template<typename T>
	inline static T Lerp(T a, T b, float t)
	{
		return a + t * (b - a);
	}

	template<typename Vector2>
	inline static Vector2 Lerp(Vector2 a, Vector2 b, float t)
	{
		Vector2 vector;
		vector.x = Lerp<float>(a.x, b.x, t);
		vector.y = Lerp<float>(a.y, b.y, t);
		return vector;
	}

	template<typename Vector3>
	inline static Vector3 Lerp(Vector3 a, Vector3 b, float t)
	{
		Vector3 vector;
		vector.x = Lerp<float>(a.x, b.x, t);
		vector.y = Lerp<float>(a.y, b.y, t);
		vector.z = Lerp<float>(a.z, b.z, t);
		return vector;
	}

	template<typename Vector4>
	inline static Vector4 Lerp(Vector4 a, Vector4 b, float t)
	{
		Vector4 vector;
		vector.x = Lerp<float>(a.x, b.x, t);
		vector.y = Lerp<float>(a.y, b.y, t);
		vector.z = Lerp<float>(a.z, b.z, t);
		vector.w = Lerp<float>(a.w, b.w, t);
		return vector;
	}

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