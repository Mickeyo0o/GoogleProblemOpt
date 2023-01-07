#ifndef PARTICLESWARM_H
#define PARTICLESWARM_H
#include <vector>
#include <random>
#include "Particle.h"


class ParticleSwarm
{
    public:
        ParticleSwarm(float coefficientVelocity, float coefficientGlobal, float coefficientParticle, int n);
        virtual ~ParticleSwarm();
        void doParticleSwarmIter(int days, const std::vector<Library*>& libraries);
        void addRandomParticle(double sat);
        void addParticle(int* pos);
        double getBestScore();
        int getItersWithoutImprovement();
        int* getBestPos();
    private:
        std::vector<Particle*> particles;
        float coefficientGlobal;
        float coefficientParticle;
        float coefficientVelocity;
        int* bestGlobalPos;
        int itersWithoutImprovement;
        double bestGlobalScore;
        int n;
};

#endif // PARTICLESWARM_H
