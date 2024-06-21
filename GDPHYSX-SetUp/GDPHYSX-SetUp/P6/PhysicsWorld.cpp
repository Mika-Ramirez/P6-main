#include "PhysicsWorld.h"

void P6::PhysicsWorld::AddParticle(PhysicsParticle* toAdd)
{
	Particles.push_back(toAdd);

	forceRegistry.Add(toAdd, &Gravity);
}

void P6::PhysicsWorld::Update(float time)
{
	this->UpdateParticleList();

	forceRegistry.UpdateForces(time);
	//Create an iterator that points at the start of the list
	for (std::list<PhysicsParticle*>::iterator p = Particles.begin();
		//Continue looping until the end of the list
		p != Particles.end();
		//Move to the next particle
		p++)
	{
		//Call the particle update
		(*p)->Update(time);
	}
}

void P6::PhysicsWorld::UpdateParticleList()
{
	//Removes ALL Particles in the list that
	//Return true to the function below
	Particles.remove_if(
		[](PhysicsParticle* p) {
			return p->IsDestroyed();
		}
	);
}
