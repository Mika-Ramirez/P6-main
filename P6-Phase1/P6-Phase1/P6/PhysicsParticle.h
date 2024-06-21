#pragma once
#include "MyVector.h"

namespace P6 {

	class PhysicsParticle
	{
	protected:
		bool isDestroyed = false;

	public:
		void AddForce(MyVector force);
		void ResetForce();
		void Destroy();

		bool IsDestroyed() {
			return isDestroyed;
		}

	public:

		float mass = 0;
		float damping = 0.9f;
		float lifespan = 1.f;
		float lifeRemaining = 0.f;

		MyVector Position;
		MyVector Velocity;
		MyVector Acceleration;

		PhysicsParticle();

	protected:
		MyVector accumulatedForce = MyVector(0, 0, 0);

		void UpdatePosition(float time);
		void UpdateVelocity(float time);
		void UpdateLifeSpan(float time);

	public:
		void Update(float time);

	};
}

