#ifndef P6PARTICLES_DEF
#define P6PARTICLES_DEF

#include "PhysicsParticle.h"
#endif 

#ifndef FORCE_DEF
#define FORCE_DEF

#include "Force.h"
#endif 

#include "list"
namespace P6 {
    struct ParticleForceRegistry {
        PhysicsParticle* particle;
        Force* generator;
    };

    class ForceRegistry {
    private:
        std::list<ParticleForceRegistry> Registry;
    public:
        void Add(PhysicsParticle* particle, Force* generator);
        void Remove(PhysicsParticle* particle, Force* generator);
        void Clear();
        void UpdateForces(float time);
    };
}
