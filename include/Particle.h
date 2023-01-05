#ifndef PARTICLE_H
#define PARTICLE_H
#include <algorithm>
#include <random>
#include "Library.h"
#include <vector>


class Particle
{
    public:
        Particle(int n, int* pos);
        Particle(int n);
        int calculateScore(int days, std::vector<Library*> libraries);
        virtual ~Particle();
        void updateVelocity(float coefficientVelocity, float coefficientGlobal, float coefficientParticle, int* bestGlobalPos);
        void updatePosition();
        int* getPosition();


    private:
        int n;
        int* pos;
        int* velocity;
        int* bestPos;
        int bestScore;
};

#endif // PARTICLE_H
