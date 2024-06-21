#include "GravityForce.h"

namespace P6 {
	void GravityForce::UpdateForce(PhysicsParticle* particle, float time) {
		if (particle->mass <= 0) return;

		MyVector force = this->Gravity * particle->mass;
		particle->AddForce(force);

	}
}
