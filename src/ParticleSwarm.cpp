#include "ParticleSwarm.h"

ParticleSwarm::ParticleSwarm(float coefficientVelocity, float coefficientGlobal, float coefficientParticle, int n)
    : coefficientGlobal(coefficientGlobal), coefficientVelocity(coefficientVelocity), coefficientParticle(coefficientParticle), n(n)
{
    this->bestGlobalScore = 0;
    this->bestGlobalPos = new int[n];
}

ParticleSwarm::~ParticleSwarm()
{
    for (int i = 0; i < particles.size(); i++) {
        delete particles[i];
    }
    delete bestGlobalPos;
}

void ParticleSwarm::doParticleSwarmIter(int days, const std::vector<Library*>& libraries)
{
    for (int i = 0; i < particles.size(); i++) {
        particles[i]->updateVelocity(coefficientVelocity, coefficientGlobal, coefficientParticle, bestGlobalPos);
        particles[i]->updatePosition();
        int currentScore = particles[i]->calculateScore(days, libraries);
        if (currentScore > bestGlobalScore) {
            bestGlobalScore = currentScore;
            int* bestPosP = particles[i]->getPosition();
            for (int i = 0; i < n; i++) {
                bestGlobalPos[i] = bestPosP[i];
            }
        }
    }
}

void ParticleSwarm::addRandomParticle()
{
    particles.push_back(new Particle(n));
}

void ParticleSwarm::addParticle(int* pos)
{
    particles.push_back(new Particle(n, pos));
}

int ParticleSwarm::getBestScore()
{
    return bestGlobalScore;
}
