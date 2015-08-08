#ifndef _D_Scene_Camera_h
#define _D_Scene_Camera_h

#include <SFML/Graphics.hpp>
#include "Object3d.hpp"

class Camera :
	public Object3d
{
public:
	explicit Camera(
		const Vector3d<float>& position,
		const Vector3d<float>& forward,
		const Vector3d<float>& up) :
		Object3d(position, forward, up) {}

	void ViewingTransform()
	{
		auto forward = getXVector();
		auto up = getYVector();
		auto position = getPosition();
		gluLookAt(position.x, position.y, position.z,// camera position
			forward.x, forward.y, forward.z, //look at this point //TODO: BUG here!! what is it ??
			up.x, up.y, up.z); //camera up
	}
};

#endif