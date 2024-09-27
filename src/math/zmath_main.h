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
			Vector2 o = *this;
			o.x = rhs.x;
			o.y = rhs.y;
			return o;
		}

		inline Vector2 operator+(const Vector2 rhs)
		{
			Vector2 o = *this;
			o.x += rhs.x;
			o.y += rhs.y;
			return o;
		}

		inline Vector2 operator-(const Vector2 rhs)
		{
			Vector2 o = *this;
			o.x -= rhs.x;
			o.y -= rhs.y;
			return o;
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
			Vector3 o = *this;
			o.x = rhs.x;
			o.y = rhs.y;
			o.z = rhs.z;
			return o;
		}

		inline Vector3 operator+(const Vector3 rhs)
		{
			Vector3 o = *this;
			o.x += rhs.x;
			o.y += rhs.y;
			o.z += rhs.z;
			return o;
		}

		inline Vector3 operator-(const Vector3 rhs)
		{
			Vector3 o = *this;
			o.x -= rhs.x;
			o.y -= rhs.y;
			o.z -= rhs.z;
			return o;
		}

		inline Vector3 operator*(const float rhs)
		{
			Vector3 o = *this;
			o.x *= rhs;
			o.y *= rhs;
			o.z *= rhs;
			return o;
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
			Vector4 o = *this;
			o.x = rhs.x;
			o.y = rhs.y;
			o.z = rhs.z;
			o.w = rhs.w;
			return o;
		}

		inline Vector4 operator+(const Vector4 rhs)
		{
			Vector4 o = *this;
			o.x += rhs.x;
			o.y += rhs.y;
			o.z += rhs.z;
			o.w += rhs.w;
			return o;
		}

		inline Vector4 operator-(const Vector4 rhs)
		{
			Vector4 o = *this;
			o.x -= rhs.x;
			o.y -= rhs.y;
			o.z -= rhs.z;
			o.w -= rhs.w;
			return o;
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

		float m[4][4];

		Matrix4x4 operator*(float rhs)
		{
			Matrix4x4 o = *this;
			o.m[0][0] *= rhs;
			o.m[0][1] *= rhs;
			o.m[0][2] *= rhs;
			o.m[0][3] *= rhs;

			o.m[1][0] *= rhs;
			o.m[1][1] *= rhs;
			o.m[1][2] *= rhs;
			o.m[1][3] *= rhs;

			o.m[2][0] *= rhs;
			o.m[2][1] *= rhs;
			o.m[2][2] *= rhs;
			o.m[2][3] *= rhs;

			o.m[3][0] *= rhs;
			o.m[3][1] *= rhs;
			o.m[3][2] *= rhs;
			o.m[3][3] *= rhs;
			return o;
		}

		Matrix4x4 operator*(const Vector2 rhs)
		{
			Matrix4x4 o = *this;
			o.m[0][0] *= rhs.x;
			o.m[1][1] *= rhs.y;
			return o;
		}

		Matrix4x4 operator*(const Vector3 rhs)
		{
			Matrix4x4 o = *this;
			o.m[0][0] =
				o.m[0][0] * rhs.x +
				o.m[0][1] * rhs.y +
				o.m[0][2] * rhs.z +
				o.m[0][3] * 1.0f;

			o.m[0][1] =
				o.m[0][0] * rhs.x +
				o.m[0][1] * rhs.y +
				o.m[0][2] * rhs.z +
				o.m[0][3] * 1.0f;

			o.m[0][2] =
				o.m[0][0] * rhs.x +
				o.m[0][1] * rhs.y +
				o.m[0][2] * rhs.z +
				o.m[0][3] * 1.0f;

			o.m[0][3] =
				o.m[0][0] * rhs.x +
				o.m[0][1] * rhs.y +
				o.m[0][2] * rhs.z +
				o.m[0][3] * 1.0f;

			o.m[1][0] =
				o.m[1][0] * rhs.x +
				o.m[1][1] * rhs.y +
				o.m[1][2] * rhs.z +
				o.m[1][3] * 1.0f;

			o.m[1][1] =
				o.m[1][0] * rhs.x +
				o.m[1][1] * rhs.y +
				o.m[1][2] * rhs.z +
				o.m[1][3] * 1.0f;

			o.m[1][2] =
				o.m[1][0] * rhs.x +
				o.m[1][1] * rhs.y +
				o.m[1][2] * rhs.z +
				o.m[1][3] * 1.0f;

			o.m[1][3] =
				o.m[1][0] * rhs.x +
				o.m[1][1] * rhs.y +
				o.m[1][2] * rhs.z +
				o.m[1][3] * 1.0f;

			o.m[2][0] =
				o.m[2][0] * rhs.x +
				o.m[2][1] * rhs.y +
				o.m[2][2] * rhs.z +
				o.m[2][3] * 1.0f;

			o.m[2][1] =
				o.m[2][0] * rhs.x +
				o.m[2][1] * rhs.y +
				o.m[2][2] * rhs.z +
				o.m[2][3] * 1.0f;

			o.m[2][2] =
				o.m[2][0] * rhs.x +
				o.m[2][1] * rhs.y +
				o.m[2][2] * rhs.z +
				o.m[2][3] * 1.0f;

			o.m[2][3] =
				o.m[2][0] * rhs.x +
				o.m[2][1] * rhs.y +
				o.m[2][2] * rhs.z +
				o.m[2][3] * 1.0f;

			o.m[3][0] =
				o.m[3][0] * rhs.x +
				o.m[3][1] * rhs.y +
				o.m[3][2] * rhs.z +
				o.m[3][3] * 1.0f;

			o.m[3][1] =
				o.m[3][0] * rhs.x +
				o.m[3][1] * rhs.y +
				o.m[3][2] * rhs.z +
				o.m[3][3] * 1.0f;

			o.m[3][2] =
				o.m[3][0] * rhs.x +
				o.m[3][1] * rhs.y +
				o.m[3][2] * rhs.z +
				o.m[3][3] * 1.0f;

			o.m[3][3] =
				o.m[3][0] * rhs.x +
				o.m[3][1] * rhs.y +
				o.m[3][2] * rhs.z +
				o.m[3][3] * 1.0f;
			return o;
		}

		Matrix4x4 operator*(const Vector4 rhs)
		{
			Matrix4x4 o = *this;
			o.m[0][0] *= rhs.x;
			o.m[1][1] *= rhs.y;
			o.m[2][2] *= rhs.z;
			o.m[3][3] *= rhs.w;
			return o;
		}

		Matrix4x4& operator=(const Matrix4x4 rhs)
		{
			m[0][0] = rhs.m[0][0];
			m[0][1] = rhs.m[0][1];
			m[0][2] = rhs.m[0][2];
			m[0][3] = rhs.m[0][3];

			m[1][0] = rhs.m[1][0];
			m[1][1] = rhs.m[1][1];
			m[1][2] = rhs.m[1][2];
			m[1][3] = rhs.m[1][3];

			m[2][0] = rhs.m[2][0];
			m[2][1] = rhs.m[2][1];
			m[2][2] = rhs.m[2][2];
			m[2][3] = rhs.m[2][3];

			m[3][0] = rhs.m[3][0];
			m[3][1] = rhs.m[3][1];
			m[3][2] = rhs.m[3][2];
			m[3][3] = rhs.m[3][3];
			return *this;
		}

		inline Matrix4x4 operator*(const Matrix4x4 rhs)
		{
			/*
			* [ a0 a1 a2 a3 ]   [ a0 a1 a2 a3 ]
			* [ b0 b1 b2 b3 ]   [ b0 b1 b2 b3 ]
			* [ c0 c1 c2 c3 ] x [ c0 c1 c2 c3 ]
			* [ d0 d1 d2 d3 ]   [ d0 d1 d2 d3 ]
			*/

			Matrix4x4 o = *this;
			o.m[0][0] =
				o.m[0][0] * rhs.m[0][0] +
				o.m[0][1] * rhs.m[1][0] +
				o.m[0][2] * rhs.m[2][0] +
				o.m[0][3] * rhs.m[3][0];

			o.m[0][1] =
				o.m[0][0] * rhs.m[0][1] +
				o.m[0][1] * rhs.m[1][1] +
				o.m[0][2] * rhs.m[2][1] +
				o.m[0][3] * rhs.m[3][1];

			o.m[0][2] =
				o.m[0][0] * rhs.m[0][2] +
				o.m[0][1] * rhs.m[1][2] +
				o.m[0][2] * rhs.m[2][2] +
				o.m[0][3] * rhs.m[3][2];

			o.m[0][3] =
				o.m[0][0] * rhs.m[0][3] +
				o.m[0][1] * rhs.m[1][3] +
				o.m[0][2] * rhs.m[2][3] +
				o.m[0][3] * rhs.m[3][3];

			o.m[1][0] =
				o.m[1][0] * rhs.m[0][0] +
				o.m[1][1] * rhs.m[1][0] +
				o.m[1][2] * rhs.m[2][0] +
				o.m[1][3] * rhs.m[3][0];

			o.m[1][1] =
				o.m[1][0] * rhs.m[0][1] +
				o.m[1][1] * rhs.m[1][1] +
				o.m[1][2] * rhs.m[2][1] +
				o.m[1][3] * rhs.m[3][1];

			o.m[1][2] =
				o.m[1][0] * rhs.m[0][2] +
				o.m[1][1] * rhs.m[1][2] +
				o.m[1][2] * rhs.m[2][2] +
				o.m[1][3] * rhs.m[3][2];

			o.m[1][3] =
				o.m[1][0] * rhs.m[0][3] +
				o.m[1][1] * rhs.m[1][3] +
				o.m[1][2] * rhs.m[2][3] +
				o.m[1][3] * rhs.m[3][3];

			o.m[2][0] =
				o.m[2][0] * rhs.m[0][0] +
				o.m[2][1] * rhs.m[1][0] +
				o.m[2][2] * rhs.m[2][0] +
				o.m[2][3] * rhs.m[3][0];

			o.m[2][1] =
				o.m[2][0] * rhs.m[0][1] +
				o.m[2][1] * rhs.m[1][1] +
				o.m[2][2] * rhs.m[2][1] +
				o.m[2][3] * rhs.m[3][1];

			o.m[2][2] =
				o.m[2][0] * rhs.m[0][2] +
				o.m[2][1] * rhs.m[1][2] +
				o.m[2][2] * rhs.m[2][2] +
				o.m[2][3] * rhs.m[3][2];

			o.m[2][3] =
				o.m[2][0] * rhs.m[0][3] +
				o.m[2][1] * rhs.m[1][3] +
				o.m[2][2] * rhs.m[2][3] +
				o.m[2][3] * rhs.m[3][3];

			o.m[3][0] =
				o.m[3][0] * rhs.m[0][0] +
				o.m[3][1] * rhs.m[1][0] +
				o.m[3][2] * rhs.m[2][0] +
				o.m[3][3] * rhs.m[3][0];

			o.m[3][1] =
				o.m[3][0] * rhs.m[0][1] +
				o.m[3][1] * rhs.m[1][1] +
				o.m[3][2] * rhs.m[2][1] +
				o.m[3][3] * rhs.m[3][1];

			o.m[3][2] =
				o.m[3][0] * rhs.m[0][2] +
				o.m[3][1] * rhs.m[1][2] +
				o.m[3][2] * rhs.m[2][2] +
				o.m[3][3] * rhs.m[3][2];

			o.m[3][3] =
				o.m[3][0] * rhs.m[0][3] +
				o.m[3][1] * rhs.m[1][3] +
				o.m[3][2] * rhs.m[2][3] +
				o.m[3][3] * rhs.m[3][3];

			return o;
		}
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

	static constexpr Matrix4x4& Identity()
	{
		Matrix4x4 mat =
		{
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f,
		};

		return mat;
	}

	inline static float Lerp(float a, float b, float t)
	{
		return a + t * (b - a);
	}

	inline static Vector2 Lerp(Vector2 a, Vector2 b, float t)
	{
		Vector2 vector;
		vector.x = Lerp(a.x, b.x, t);
		vector.y = Lerp(a.y, b.y, t);
		return vector;
	}

	inline static Vector3 Lerp(Vector3& a, Vector3& b, float t)
	{
		Vector3 vector;
		vector.x = Lerp(a.x, b.x, t);
		vector.y = Lerp(a.y, b.y, t);
		vector.z = Lerp(a.z, b.z, t);
		return vector;
	}

	inline static Vector4 Lerp(Vector4 a, Vector4 b, float t)
	{
		Vector4 vector;
		vector.x = Lerp(a.x, b.x, t);
		vector.y = Lerp(a.y, b.y, t);
		vector.z = Lerp(a.z, b.z, t);
		vector.w = Lerp(a.w, b.w, t);
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