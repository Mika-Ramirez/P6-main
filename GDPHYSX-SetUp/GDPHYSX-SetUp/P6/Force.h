#ifndef P6PARTICLES_DEF
#define P6PARTICLES_DEF

#include "PhysicsParticle.h"
#endif 


namespace P6 {
	class Force
	{
	public:
		virtual void UpdateForce(PhysicsParticle* p, float time) {
			p->AddForce(MyVector(0, 0, 0));
		}
	};
}

