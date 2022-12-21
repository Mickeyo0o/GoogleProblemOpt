#ifndef PARTICLESWARM_H
#define PARTICLESWARM_H
#include <vector>
#include "Particle.h"


class ParticleSwarm
{
    public:
        ParticleSwarm(float coefficientVelocity, float coefficientGlobal, float coefficientParticle, int n);
        virtual ~ParticleSwarm();
        void doParticleSwarmIter(int days, const std::vector<Library*>& libraries);
        void addRandomParticle();
        void addParticle(int* pos);
        int getBestScore();

    private:
        std::vector<Particle*> particles;
        float coefficientGlobal;
        float coefficientParticle;
        float coefficientVelocity;
        int* bestGlobalPos;
        int bestGlobalScore;
        int n;
};

#endif // PARTICLESWARM_H
