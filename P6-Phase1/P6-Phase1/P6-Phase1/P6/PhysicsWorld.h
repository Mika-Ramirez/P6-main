#pragma once
#include <list>
#include "PhysicsParticle.h"
#include "ForceRegistry.h"
#include "GravityForce.h"

namespace P6 {
	class PhysicsWorld {
		public:
			ForceRegistry forceRegistry;
			std::list<PhysicsParticle*> Particles;
			void AddParticle(PhysicsParticle* toAdd);
			void Update(float time);

		private:
			void UpdateParticleList();
			GravityForce Gravity = GravityForce(MyVector(0, -9.8, 0));
	};
}