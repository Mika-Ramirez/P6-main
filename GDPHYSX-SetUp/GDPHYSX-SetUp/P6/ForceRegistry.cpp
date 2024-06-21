#include "ForceRegistry.h"


void P6::ForceRegistry::Add(PhysicsParticle* particle, Force* generator)
{
	ParticleForceRegistry toAdd;
	toAdd.particle = particle;
	toAdd.generator = generator;

	Registry.push_back(toAdd);
}

void P6::ForceRegistry::Remove(PhysicsParticle* particle, Force* generator)
{
	Registry.remove_if(
		[particle, generator](ParticleForceRegistry reg) {
			return reg.particle == particle && reg.generator == generator;

		}
	);
}

void P6::ForceRegistry::Clear()
{
	Registry.clear();
}

void P6::ForceRegistry::UpdateForces(float time)
{
	for (std::list<ParticleForceRegistry>::iterator i = Registry.begin();
		i != Registry.end();
		i++) {
		i->generator->UpdateForce(i->particle, time);
	}
}
