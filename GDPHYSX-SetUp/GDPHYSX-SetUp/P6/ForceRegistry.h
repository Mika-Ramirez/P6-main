#ifndef P6PARTICLES_DEF
#define P6PARTICLES_DEF

#include "PhysicsParticle.h"
#endif 

#ifndef FORCEGENERATOR_DEF
#define FORCEGENERATOR_DEF

#include "Force.h"
#endif 

#include "list"
namespace P6 {
	class ForceRegistry
	{
	public:
		void Add(PhysicsParticle* p, Force* generator);
		void Remove(PhysicsParticle* p, Force* generator);
		void Clear();
		void UpdateForces(float time);

	protected:

		struct ParticleForceRegistry {
			PhysicsParticle* particle;
			Force* generator;
		};

		std::list<ParticleForceRegistry> Registry;
	};
}

