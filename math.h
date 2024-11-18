#pragma once
#include <cmath>
#include <cstring>

#define PI 3.14159265358979323846

class Vector3f
{
public:
	float x, y, z;

public:
	Vector3f() {}

	Vector3f(float _x, float _y, float _z)
	{
		x = _x;
		y = _y;
		z = _z;
	}

	Vector3f normalize()
	{
		Vector3f out;

		float length = sqrt(x * x + y * y + z * z);
		out.x = x /= length;
		out.y = y /= length;
		out.z = z /= length;

		return out;
	}

	Vector3f negate()
	{
		Vector3f out;
		out.x = -x;
		out.y = -y;
		out.z = -z;

		return out;
	}

	// Multiplication operator

	void operator *= (const Vector3f& vector)
	{
		Vector3f out;

		out.x = x * vector.x;
		out.y = y * vector.y;
		out.z = z * vector.z;

		*this = out;
	}

	Vector3f operator * (const Vector3f& vector)
	{
		Vector3f out;

		out.x = x * vector.x;
		out.y = y * vector.y;
		out.z = z * vector.z;

		return out;
	}

	Vector3f operator * (float scalar)
	{
		Vector3f out;

		out.x = x * scalar;
		out.y = y * scalar;
		out.z = z * scalar;

		return out;
	}

	// Plus operator

	void operator += (const Vector3f& vector)
	{
		Vector3f out;

		out.x = x + vector.x;
		out.y = y + vector.y;
		out.z = z + vector.z;

		*this = out;
	}

	Vector3f operator + (const Vector3f& vector)
	{
		Vector3f out;

		out.x = x + vector.x;
		out.y = y + vector.y;
		out.z = z + vector.z;

		return out;
	}

	// Minus operator

	void operator -= (const Vector3f& vector)
	{
		Vector3f out;

		out.x = x - vector.x;
		out.y = y - vector.y;
		out.z = z - vector.z;

		*this = out;
	}

	// Not equal operator

	bool operator != (const Vector3f& vector)
	{
		bool out = false;

		if (x != vector.x || y != vector.y || z != vector.z)
			out = true;

		return out;
	}

};

class Vector4f
{
public:
	Vector4f(){}

	Vector4f(float _x, float _y, float _z, float _w)
	{
		x = _x;
		y = _y;
		z = _z;
		w = _w;
	}

	void cross(Vector4f& v1, Vector4f& v2, Vector4f& v3)
	{
		this->x = v1.y * (v2.z * v3.w - v3.z * v2.w) - v1.z * (v2.y * v3.w - v3.y * v2.w) + v1.w * (v2.y * v3.z - v2.z * v3.y);
		this->y = -(v1.x * (v2.z * v3.w - v3.z * v2.w) - v1.z * (v2.x * v3.w - v3.x * v2.w) + v1.w * (v2.x * v3.z - v3.x * v2.z));
		this->z = v1.x * (v2.y * v3.w - v3.y * v2.w) - v1.y * (v2.x * v3.w - v3.x * v2.w) + v1.w * (v2.x * v3.y - v3.x * v2.y);
		this->w = -(v1.x * (v2.y * v3.z - v3.y * v2.z) - v1.y * (v2.x * v3.z - v3.x * v2.z) + v1.z * (v2.x * v3.y - v3.x * v2.y));
	}

public:
	float x, y, z, w;
};

class Vector2f
{
public:
	Vector2f() {}

	Vector2f(float _x, float _y)
	{
		x = _x;
		y = _y;
	}

public:
	float x, y;
};



class Matrix4f
{
public:
	float mat[4][4];

public:
	Matrix4f()
	{
		setIdentity();
	}

	Matrix4f(const Matrix4f& matrix) 
	{
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				mat[i][j] = matrix.mat[i][j];
			
	}

	void setIdentity()
	{
		::memset(mat, 0, sizeof(mat));
		mat[0][0] = 1;
		mat[1][1] = 1;
		mat[2][2] = 1;
		mat[3][3] = 1;
	}

	void setScale(const Vector3f& scale)
	{
		mat[0][0] = scale.x;
		mat[1][1] = scale.y;
		mat[2][2] = scale.z;
	}

	void setTranslation(const Vector3f& scale)
	{
		mat[0][3] = scale.x;
		mat[1][3] = scale.y;
		mat[2][3] = scale.z;
		mat[3][3] = 1.0f;
	}

	void setRotationX(float x)
	{
		mat[1][1] = cos(x);
		mat[2][1] = sin(x);
		mat[1][2] = -sin(x);
		mat[2][2] = cos(x);
	}

	void setRotationY(float y)
	{
		mat[0][0] = cos(y);
		mat[2][0] = -sin(y);
		mat[0][2] = sin(y);
		mat[2][2] = cos(y);
	}

	void setRotationZ(float z)
	{
		mat[0][0] = cos(z);
		mat[1][0] = sin(z);
		mat[0][1] = -sin(z);
		mat[1][1] = cos(z);
	}


	Vector3f getZDirection()
	{
		return Vector3f(mat[0][2], mat[1][2], mat[2][2]);
	}

	Vector3f getYDirection()
	{
		return Vector3f(mat[0][1], mat[1][1], mat[2][1]);
	}

	Vector3f getXDirection()
	{
		return Vector3f(mat[0][0], mat[1][0], mat[2][0]);
	}

	Vector3f getTranslation()
	{
		return Vector3f(mat[0][3], mat[1][3], mat[2][3]);
	}

	void setProjection(float FOV)
	{
		float radFOV = FOV * PI / 180.0;
		float tanHalfFOV = tan((FOV / 2.0f));
		float d = 1 / tanHalfFOV;

		mat[0][0] = d;
		mat[1][1] = d;
		mat[2][2] = 1;
		mat[3][2] = 1;
		mat[3][3] = 0;

	}

	void setProjection(float FOV, float aspectRatio, float nearZ, float farZ)
	{
		float radFOV = (FOV / 2.0f) * PI / 180.0;
		float tanHalfFOV = tan((radFOV));
		float d = 1 / tanHalfFOV;

		float zRange = nearZ - farZ;

		float A = (-farZ - nearZ) / zRange;
		float B = 2.0f * farZ * nearZ / zRange;

		mat[0][0] = d / aspectRatio;
		mat[1][1] = d;
		mat[2][2] = A;
		mat[2][3] = B;
		mat[3][2] = 1;
		mat[3][3] = 0;

	}

	const Matrix4f& transpose()
	{
		Matrix4f out;
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				out.mat[i][j] = mat[j][i];

		return out;
	}

	Vector4f operator* (const Vector4f& vector)
	{
		Vector4f out;

		out.x = mat[0][0] * vector.x + mat[0][1] * vector.y + mat[0][2] * vector.z + mat[0][3] * vector.w;
		out.y = mat[1][0] * vector.x + mat[1][1] * vector.y + mat[1][2] * vector.z + mat[1][3] * vector.w;
		out.z = mat[2][0] * vector.x + mat[2][1] * vector.y + mat[2][2] * vector.z + mat[2][3] * vector.w;
		out.w = mat[3][0] * vector.x + mat[3][1] * vector.y + mat[3][2] * vector.z + mat[3][3] * vector.w;

		return out;
	}

	void operator *= (const Matrix4f& matrix)
	{
		Matrix4f out;

		for (auto i = 0; i < 4; i++)
		{
			for (auto j = 0; j < 4; j++)
			{
				out.mat[i][j] =
					mat[i][0] * matrix.mat[0][j] +
					mat[i][1] * matrix.mat[1][j] +
					mat[i][2] * matrix.mat[2][j] +
					mat[i][3] * matrix.mat[3][j];
			}
		}

		*this = out;
	}

	float getDeterminant()
	{
		Vector4f minor, v1, v2, v3;
		float det;

		v1 = Vector4f(this->mat[0][0], this->mat[1][0], this->mat[2][0], this->mat[3][0]);
		v2 = Vector4f(this->mat[0][1], this->mat[1][1], this->mat[2][1], this->mat[3][1]);
		v3 = Vector4f(this->mat[0][2], this->mat[1][2], this->mat[2][2], this->mat[3][2]);


		minor.cross(v1, v2, v3);
		det = -(this->mat[0][3] * minor.x + this->mat[1][3] * minor.y + this->mat[2][3] * minor.z +
			this->mat[3][3] * minor.w);
		return det;
	}


	void inverse()
	{
		int a, i, j;
		Matrix4f out;
		Vector4f v;
		Vector4f vec[3];
		float det = 0.0f;

		det = this->getDeterminant();
		if (!det) return;
		for (i = 0; i < 4; i++)
		{
			for (j = 0; j < 4; j++)
			{
				if (j != i)
				{
					a = j;
					if (j > i) a = a - 1;
					vec[a].x = (this->mat[j][0]);
					vec[a].y = (this->mat[j][1]);
					vec[a].z = (this->mat[j][2]);
					vec[a].w = (this->mat[j][3]);
				}
			}
			v.cross(vec[0], vec[1], vec[2]);

			out.mat[0][i] = pow(-1.0f, i) * v.x / det;
			out.mat[1][i] = pow(-1.0f, i) * v.y / det;
			out.mat[2][i] = pow(-1.0f, i) * v.z / det;
			out.mat[3][i] = pow(-1.0f, i) * v.w / det;
		}

		*this = out;
	}

	Matrix4f operator * (const Matrix4f& matrix)
	{
		Matrix4f out;

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				out.mat[i][j] =
					mat[i][0] * matrix.mat[0][j] +
					mat[i][1] * matrix.mat[1][j] +
					mat[i][2] * matrix.mat[2][j] +
					mat[i][3] * matrix.mat[3][j];
			}
		}

		return out;
	}
};

class Matrix3f
{
public:
	float mat[3][3];

public:
	Matrix3f()
	{
		setIdentity();
	}

	Matrix3f(const Matrix4f& matrix)
	{
		for (int i = 0; i < 3; ++i)
			for (int j = 0; j < 3; ++j)
				mat[i][j] = matrix.mat[i][j];

	}

	void setIdentity()
	{
		::memset(mat, 0, sizeof(mat));
		mat[0][0] = 1;
		mat[1][1] = 1;
		mat[2][2] = 1;
	}

	const Matrix3f& transpose()
	{
		Matrix3f out;
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				out.mat[i][j] = mat[j][i];

		return out;
	}

	Matrix3f operator* (const Matrix3f& matrix)
	{
		Matrix3f out;

		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				out.mat[i][j] =
					mat[i][0] * matrix.mat[0][j] +
					mat[i][1] * matrix.mat[1][j] +
					mat[i][2] * matrix.mat[2][j];
			}
		}

		return out;
	}

	Vector3f operator* (const Vector3f& vector)
	{
		Vector3f out;

		out.x = mat[0][0] * vector.x + mat[0][1] * vector.y + mat[0][2] * vector.z;
		out.y = mat[1][0] * vector.x + mat[1][1] * vector.y + mat[1][2] * vector.z;
		out.z = mat[2][0] * vector.x + mat[2][1] * vector.y + mat[2][2] * vector.z;

		return out;
	}
};