#ifndef FORCEGENERATOR_DEF
#define FORCEGENERATOR_DEF

#include "Force.h"
#endif 


namespace P6 {
	class GravityForce : public Force
	{
	private:
		MyVector Gravity = MyVector(0, -9.8, 0);

	public:
		GravityForce(const MyVector gravity) : Gravity(gravity){}

		void UpdateForce(PhysicsParticle* particle, float time) override;
	};

}

