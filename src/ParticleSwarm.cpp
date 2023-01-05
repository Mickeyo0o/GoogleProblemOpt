#include "ParticleSwarm.h"

ParticleSwarm::ParticleSwarm(float coefficientVelocity, float coefficientGlobal, float coefficientParticle, int n)
    : coefficientGlobal(coefficientGlobal), coefficientVelocity(coefficientVelocity), coefficientParticle(coefficientParticle), n(n)
{
    this->bestGlobalScore = 0;
    this->bestGlobalPos = new int[n];
    for (int i = 0; i < n; i++) {
        bestGlobalPos[i] = 0;
    }
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
    int bestScoreInIter = 0;
    for (int i = 0; i < particles.size(); i++) {
        int currentScore = particles[i]->calculateScore(days, libraries);
        if (currentScore > bestGlobalScore) {
            bestGlobalScore = currentScore;
            int* bestPosP = particles[i]->getPosition();
            for (int i = 0; i < n; i++) {
                bestGlobalPos[i] = bestPosP[i];
            }
        }
        if(currentScore > bestScoreInIter){
            bestScoreInIter = currentScore;
        }
        particles[i]->updatePosition();
        particles[i]->updateVelocity(coefficientVelocity, coefficientGlobal, coefficientParticle, bestGlobalPos);
    }
    std::cout<<"Best in iter: "<<bestScoreInIter<<std::endl;
}

void ParticleSwarm::addRandomParticle()
{
    particles.push_back(new Particle(n));
}

void ParticleSwarm::addParticle(int* pos)
{
    Particle* toAdd = new Particle(n, pos);
    particles.push_back(toAdd);
}

int ParticleSwarm::getBestScore()
{
    return bestGlobalScore;
}
