#pragma once
#include "stdafx.h"

#define M_PI	3.14159265358979323846264338327950288419716939937510
#define M_RADPI		57.295779513082f
#define M_PI_F		((float)(M_PI))	// Shouldn't collide with anything.
#define RAD2DEG( x  )  ( (float)(x) * (float)(180.f / M_PI_F) )
#define DEG2RAD( x  )  ( (float)(x) * (float)(M_PI_F / 180.f) )

template <typename t> static  t clamp_value(t value, t min, t max) {
	if (value > max) {
		return max;
	}
	if (value < min) {
		return min;
	}
	return value;
}
struct Matrix
{
	float member[16];
}mat;
Matrix matrixx;
//Vector2
class Vector2
{
public:
	Vector2() : x(0.f), y(0.f)
	{

	}

	Vector2(float _x, float _y) : x(_x), y(_y)
	{

	}
	~Vector2()
	{

	}

	bool operator==(Vector2& in) {
		return (this->x == in.x && this->y == in.y);
	}
	

	float x;
	float y;
	Vector2 operator * (const float& rhs) const { return Vector2(x * rhs, y * rhs); }
	Vector2& operator *= (const float& rhs) { return *this = *this * rhs; }
	Vector2 operator + (const Vector2& rhs) const { return Vector2(x + rhs.x, y + rhs.y); }
	Vector2& operator += (const Vector2& rhs) { return *this = *this + rhs; }
	Vector2 operator + (const float& rhs) const { return Vector2(x + rhs, y + rhs); }
	Vector2& operator += (const float& rhs) { return *this = *this + rhs; }
	Vector2 operator - (const Vector2& rhs) const { return Vector2(x - rhs.x, y - rhs.y); }
	Vector2& operator -= (const Vector2& rhs) { return *this = *this - rhs; }
	Vector2 operator - (const float& rhs) const { return Vector2(x - rhs, y - rhs); }
	Vector2& operator -= (const float& rhs) { return *this = *this - rhs; }

	float dot(const Vector2& other) const {
		return x * other.x + y * other.y;
	}

	// Cross product in 2D
	float cross(const Vector2& other) const {
		return x * other.y - y * other.x;
	}

	// Magnitude of the vector
	float magnitude() const {
		return std::sqrt(x * x + y * y);
	}

	// Normalization
	Vector2 normalized() const {
		float mag = magnitude();
		return Vector2(x / mag, y / mag);
	}
};


class Vector4 {
public:
	float x, y, z, w;

	Vector4() : x(0.f), y(0.f), z(0.f), w(0.f)
	{

	}

	Vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

	// Function to apply a 4x4 rotation matrix to the vector
	void applyRotationMatrix(const std::vector<std::vector<float>>& rotationMatrix) {
		if (rotationMatrix.size() != 4 || rotationMatrix[0].size() != 4) {
			return;
		}

		float result[4] = { 0.0f };

		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j) {
				result[i] += rotationMatrix[i][j] * (*this)[j];
			}
		}

		// Update the vector with the rotated values
		x = result[0];
		y = result[1];
		z = result[2];
		w = result[3];
	}

	float& operator[](int index) {
		if (index == 0) return x;
		if (index == 1) return y;
		if (index == 2) return z;
		if (index == 3) return w;
		throw std::out_of_range("Index out of range.");
	}

	

	// Overload the *= operator to apply the matrix transformation to a vector
	Vector4& operator*=(const Matrix& matrix) {
		// Perform the matrix-vector multiplication
		float resultX = x * matrix.member[0] + y * matrix.member[4] + z * matrix.member[8] + w * matrix.member[12];
		float resultY = x * matrix.member[1] + y * matrix.member[5] + z * matrix.member[9] + w * matrix.member[13];
		float resultZ = x * matrix.member[2] + y * matrix.member[6] + z * matrix.member[10] + w * matrix.member[14];
		float resultW = x * matrix.member[3] + y * matrix.member[7] + z * matrix.member[11] + w * matrix.member[15];
		x = resultX;
		y = resultY;
		z = resultZ;
		w = resultW;

		return *this;
	}
};

class vec3
{
public:

	float x, y, z;

	vec3() { x = y = z = 0; }
	vec3(const float x, const float y, const float z) : x(x), y(y), z(z) {}
	vec3 operator + (const vec3& rhs) const { return vec3(x + rhs.x, y + rhs.y, z + rhs.z); }
	vec3 operator - (const vec3& rhs) const { return vec3(x - rhs.x, y - rhs.y, z - rhs.z); }
	vec3 operator * (const float& rhs) const { return vec3(x * rhs, y * rhs, z * rhs); }
	vec3 operator * (const vec3& rhs) const { return vec3(x * rhs.x, y * rhs.y, z * rhs.z); }
	vec3 operator / (const float& rhs) const { return vec3(x / rhs, y / rhs, z / rhs); }
	bool operator == (vec3& in) {return (x == in.x && y == in.y && z == in.z);}
	vec3& operator += (const vec3& rhs) { return *this = *this + rhs; }
	vec3& operator -= (const vec3& rhs) { return *this = *this - rhs; }
	vec3& operator *= (const float& rhs) { return *this = *this * rhs; }
	vec3& operator /= (const float& rhs) { return *this = *this / rhs; }
	float operator[](int i) const {
		return ((float*)this)[i];
	}
	float& operator[](int i);
	float dot() const { return x * x + y * y + z * z; }
	float dot(const vec3& other) const {return x * other.x + y * other.y + z * other.z;}
	float Length() const { return sqrtf(dot()); }
	vec3 cross(const vec3& other) const { return vec3{ y * other.z - z * other.y,z * other.x - x * other.z,x * other.y - y * other.x };}
	vec3 Normalize() const { return *this * (1 / Length()); }
	float Distance(const vec3& rhs) const { return (*this - rhs).Length(); }
	float calcAngle(vec3& vec1, vec3& vec2) {
		return acos((vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z) / (vec1.Length() * vec2.Length()));
	}
};

using Vector3 = vec3;

bool RotateDot(float* rotationMatrix, Vector3 originDot, Vector3& rotatedDot) {
	rotatedDot.x = originDot.x * rotationMatrix[0] + originDot.y * rotationMatrix[3] + originDot.z * rotationMatrix[6];
	rotatedDot.y = originDot.x * rotationMatrix[1] + originDot.y * rotationMatrix[4] + originDot.z * rotationMatrix[7];
	rotatedDot.z = originDot.x * rotationMatrix[2] + originDot.y * rotationMatrix[5] + originDot.z * rotationMatrix[8];

	return true;
}

bool RotateDotvec4(float* rotationMatrix, Vector4 originDot, Vector4& rotatedDot) {
	rotatedDot.x = originDot.x * rotationMatrix[0] + originDot.y * rotationMatrix[4] + originDot.z * rotationMatrix[8] + originDot.w * rotationMatrix[12];
	rotatedDot.y = originDot.x * rotationMatrix[1] + originDot.y * rotationMatrix[5] + originDot.z * rotationMatrix[9] + originDot.w * rotationMatrix[13];
	rotatedDot.z = originDot.x * rotationMatrix[2] + originDot.y * rotationMatrix[6] + originDot.z * rotationMatrix[10] + originDot.w * rotationMatrix[14];
	rotatedDot.w = originDot.x * rotationMatrix[3] + originDot.y * rotationMatrix[7] + originDot.z * rotationMatrix[11] + originDot.w * rotationMatrix[15];

	return true;
}

struct Matrix3x3 
{
	float data[3][3];
};




