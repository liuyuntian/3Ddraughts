#ifndef _D_Scene_Object3D_h
#define _D_Scene_Object3D_h

#include "Vector3d.hpp"
#include <vector>

class Object3d
{
private:
	Vector3d<float> position;
	Vector3d<float> xVector;
	Vector3d<float> yVector;

public:
	explicit Object3d(Vector3d<float> position = Vector3d<float>(0, 0, 0),
		Vector3d<float> xVector = Vector3d<float>(1, 0, 0),
		Vector3d<float> yVector = Vector3d<float>(0, 1, 0)) :
		position(position), xVector(xVector), yVector(yVector) {}

	Vector3d<float> getPosition() const
	{
		return position;
	}

	Vector3d<float> getXVector() const
	{
		return xVector;
	}
	Vector3d<float> getYVector() const
	{
		return yVector;
	}
	Vector3d<float> getZVector() const
	{
		return xVector.crossMultiply(yVector);
	}

	void setPosition(const Vector3d<float>& position)
	{
		this->position = position;
	}

	void setXVector(const Vector3d<float>& xVector)
	{
		this->xVector = xVector;
	}
	void setYVector(const Vector3d<float>& yVector)
	{
		this->yVector = yVector;
	}
	void setXYVector3ds(const Vector3d<float>& xVector, const Vector3d<float>& yVector)
	{
		setXVector(xVector);
		setYVector(yVector);
	}
	void rotate(const Vector3d<float>& axisVector, float angle)
	{
		xVector = xVector.rotateAroundAxis(axisVector, angle);
		yVector = yVector.rotateAroundAxis(axisVector, angle);
	}

};

#endif