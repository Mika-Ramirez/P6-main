#pragma once
#include "PhysicsParticle.h"

namespace P6 {
	class Force {
	public:
		virtual void UpdateForce(PhysicsParticle* p, float time) {
			p->AddForce(MyVector(0, 0, 0));
		}
	};
}