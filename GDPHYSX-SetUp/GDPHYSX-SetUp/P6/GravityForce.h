#ifndef FORCE_DEF
#define FORCE_DEF

#include "Force.h"
#endif 


namespace P6 {
    class GravityForce : public Force
    {
    private:
        MyVector gravity;

    public:
        GravityForce(const MyVector& gravity) : gravity(gravity) {}

        void UpdateForce(PhysicsParticle* particle, float time) override;
    };
}

