#pragma once
#include "PhysicsParticle.h"
#include "../Model3D.h"
#include "../Shader.h"
class RenderParticle
{
public:
	P6::PhysicsParticle* PhysicsParticle;
	Model3D* RenderObject;
	P6::MyVector Color;
	P6::MyVector Scale;

	RenderParticle(P6::PhysicsParticle* p, Model3D* obj, P6::MyVector color, P6::MyVector scale) : PhysicsParticle(p),
		RenderObject(obj), Color(color), Scale(scale) {}
	void Draw();

};

