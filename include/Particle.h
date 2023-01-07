#ifndef PARTICLE_H
#define PARTICLE_H
#include <algorithm>
#include <random>
#include <math.h>
#include "Library.h"
#include <vector>


class Particle
{
    public:
        Particle(int n, double sat);
        Particle(int n, int* pos);
        double calculateScore(int days, std::vector<Library*> libraries);
        virtual ~Particle();
        void updateVelocity(float coefficientVelocity, float coefficientGlobal, float coefficientParticle, int* bestGlobalPos);
        void updatePosition();
        int* getPosition();
    private:
        int n;
        int* pos;
        float* velocity;
        int* bestPos;
        double bestScore;
        void fillRandomPos(double sat);
        void fillRandomVel();
        bool randomDecision(float vel);
};

#endif // PARTICLE_H
