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

		inline Vector2 operator*(const float rhs)
		{
			Vector2 o = *this;
			o.x *= rhs;
			o.y *= rhs;
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

	typedef union Quaternion
	{
		struct
		{
			float x;
			float y;
			float z;
			float w;
		};

		inline static void Identity(Quaternion* quat)
		{
			quat->x = 0.0f;
			quat->y = 0.0f;
			quat->z = 0.0f;
			quat->w = 1.0f;
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

	inline static Vector3 Lerp(Vector3 a, Vector3 b, float t)
	{
		Vector3 vector;
		vector.x = Lerp(a.x, b.x, t);
		vector.y = Lerp(a.y, b.y, t);
		vector.z = Lerp(a.z, b.z, t);
		return vector;
	}
}