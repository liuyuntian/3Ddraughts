#ifndef Vector3d_hpp
#define Vector3d_hpp

#include <cmath>

template <class T> class Vector3d
{
public:
	T x;
	T y;
	T z;

	explicit Vector3d(T x = 0, T y = 0, T z = 0) : x(x), y(y), z(z) {}

	void operator+=(const Vector3d<T>& v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
	}
	void operator-=(const Vector3d<T>& v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
	}
	void operator*=(const T& n)
	{
		x *= n;
		y *= n;
		z *= n;
	}
	void operator/=(const T& n)
	{
		x /= n;
		y /= n;
		z /= n;
	}


	// + - * /
	Vector3d<T> operator+(const Vector3d<T>& v) const
	{
		return Vector3d<T>(x + v.x, y + v.y, z + v.z);
	}
	Vector3d<T> operator-(const Vector3d<T>& v) const
	{
		return Vector3d<T>(x - v.x, y - v.y, z - v.z);
	}
	Vector3d<T> operator/(const T& n) const
	{
		return Vector3d<T>(x / n, y / n, z / n);
	}
	Vector3d<T> operator*(const T& n) const
	{
		return Vector3d<T>(x * n, y * n, z * n);
	}

	// dot, cross product
	T dotMultiply(const Vector3d<T>& v) const
	{
		return x * v.x + y * v.y + z * v.z;
	}
	Vector3d<T> crossMultiply(const Vector3d<T>& v) const
	{
		return Vector3d<T>(y * v.z - v.y * z, z * v.x - x * v.z, x * v.y - y * v.x);
	}

	// others
	double getPowerLength() const
	{
		return dotMultiply(*this);
	}
	double getLength() const
	{
		return std::sqrt(getPowerLength());
	}
	Vector3d<T> getUnitVector3d() const
	{
		return *this / getLength();
	}

	double getAngleBetween(const Vector3d<T>& v) const
	{
		return std::acos(dotMultiply(v) / std::sqrt(getPowerLength() * v.getPowerLength())) * 180 / M_PI;
	}

	Vector3d<T> rotateAroundAxis(Vector3d<T> axis, float angle)
	{
		double rotationMatrix[4][4];
		double inputMatrix[4][1] = { x, y, z, 1.0 };
		double outputMatrix[4][1] = { 0.0, 0.0, 0.0, 0.0 };

		double powLenghtOfAxis = axis.getPowerLength();
		double lengthOfAxis = axis.getLength();
		angle = angle * M_PI / 180.0; //converting to radian value
		float x_2 = std::pow(axis.x, 2);
		float y_2 = std::pow(axis.y, 2);
		float z_2 = std::pow(axis.z, 2);

		rotationMatrix[0][0] = (x_2 + (y_2 + z_2) * cos(angle)) / powLenghtOfAxis;
		rotationMatrix[0][1] = (axis.x * axis.y * (1 - cos(angle)) - axis.z * lengthOfAxis * sin(angle)) / powLenghtOfAxis;
		rotationMatrix[0][2] = (axis.x * axis.z * (1 - cos(angle)) + axis.y * lengthOfAxis * sin(angle)) / powLenghtOfAxis;
		rotationMatrix[0][3] = 0.0;

		rotationMatrix[1][0] = (axis.x * axis.y * (1 - cos(angle)) + axis.z * lengthOfAxis * sin(angle)) / powLenghtOfAxis;
		rotationMatrix[1][1] = (y_2 + (x_2 + z_2) * cos(angle)) / powLenghtOfAxis;
		rotationMatrix[1][2] = (axis.y * axis.z * (1 - cos(angle)) - axis.x * lengthOfAxis * sin(angle)) / powLenghtOfAxis;
		rotationMatrix[1][3] = 0.0;

		rotationMatrix[2][0] = (axis.x * axis.z * (1 - cos(angle)) - axis.y * lengthOfAxis * sin(angle)) / powLenghtOfAxis;
		rotationMatrix[2][1] = (axis.y * axis.z * (1 - cos(angle)) + axis.x * lengthOfAxis * sin(angle)) / powLenghtOfAxis;
		rotationMatrix[2][2] = (z_2 + (x_2 + y_2) * cos(angle)) / powLenghtOfAxis;
		rotationMatrix[2][3] = 0.0;

		rotationMatrix[3][0] = 0.0;
		rotationMatrix[3][1] = 0.0;
		rotationMatrix[3][2] = 0.0;
		rotationMatrix[3][3] = 1.0;

		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 1; j++){
				outputMatrix[i][j] = 0;
				for (int k = 0; k < 4; k++)
					outputMatrix[i][j] += rotationMatrix[i][k] * inputMatrix[k][j];
			}
		return Vector3d<T>((T)outputMatrix[0][0], (T)outputMatrix[1][0], (T)outputMatrix[2][0]);
	}

	T* toArray()
	{
		return{ x, y, z };
	}

	static Vector3d<T> ZERO, XAXIS, YAXIS, ZAXIS;
};

template <class T>
Vector3d<T> Vector3d<T>::ZERO(0, 0, 0);
template <class T>
Vector3d<T> Vector3d<T>::XAXIS(1, 0, 0);
template <class T>
Vector3d<T> Vector3d<T>::YAXIS(0, 1, 0);
template <class T>
Vector3d<T> Vector3d<T>::ZAXIS(0, 0, 1);

#endif