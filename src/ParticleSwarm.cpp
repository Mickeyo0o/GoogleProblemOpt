#include "ParticleSwarm.h"

ParticleSwarm::ParticleSwarm(float coefficientVelocity, float coefficientGlobal, float coefficientParticle, int n)
    : coefficientGlobal(coefficientGlobal), coefficientVelocity(coefficientVelocity), coefficientParticle(coefficientParticle), n(n)
{
    itersWithoutImprovement = 0;
    this->bestGlobalScore = -std::numeric_limits<double>::infinity();
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
    bool hasBestScoreImproved = false;
    for (int i = 0; i < particles.size(); i++) {
        double currentScore = particles[i]->calculateScore(days, libraries);
        std::cout<<currentScore<<std::endl;
        if (currentScore > bestGlobalScore) {
            bestGlobalScore = currentScore;
            int* bestPosP = particles[i]->getPosition();
            for (int i = 0; i < n; i++) {
                bestGlobalPos[i] = bestPosP[i];
            }
            hasBestScoreImproved = true;
        }
        particles[i]->updatePosition();
        particles[i]->updateVelocity(coefficientVelocity, coefficientGlobal, coefficientParticle, bestGlobalPos);
    }
    if(hasBestScoreImproved) itersWithoutImprovement = 0;
    else itersWithoutImprovement++;
}


void ParticleSwarm::addRandomParticle(double sat)
{
    particles.push_back(new Particle(n, sat));
}
void ParticleSwarm::addParticle(int* pos)
{
    particles.push_back(new Particle(n, pos));
}
double ParticleSwarm::getBestScore()
{
    return bestGlobalScore;
}
int* ParticleSwarm::getBestPos(){
    return bestGlobalPos;
}
int ParticleSwarm::getItersWithoutImprovement()
{
    return itersWithoutImprovement;
}
