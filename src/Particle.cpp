#include "Particle.h"


void fillArrayRandom(int n, int* a);
Particle::Particle(int n, int* pos) : n(n)
{
    this->pos = new int[n];
    this->bestPos = new int[n];
    this->velocity = new int[n];
    for (int i = 0; i < n; i++) {
        this->pos[i] = pos[i];
    }
    this->bestScore = 0;
    for (int i = 0; i < n; i++) {
        this->bestPos[i] = pos[i];
    }
    fillArrayRandom(n, velocity);
}

Particle::Particle(int n) : n(n)
{
    this->pos = new int[n];
    this->bestPos = new int[n];
    this->velocity = new int[n];
    this->bestScore = 0;
    fillArrayRandom(n, pos);
    for (int i = 0; i < n; i++) {
        this->bestPos[i] = pos[i];
    }
    fillArrayRandom(n, velocity);
}

Particle::~Particle()
{
    delete[] pos;
    delete[] velocity;
}

int Particle::calculateScore(int days, std::vector<Library*> libraries)
{
    int sum = 0;
    int remainingDays = days;
    std::unordered_set<int> booksUsedSoFar;
    std::unordered_set<int> usedLibraries;
    while(remainingDays > 0) {
        int bestLibrary = 0;
        int bestPriority = pos[0];
        for (int i = 1; i < n; i++) {
            if (bestPriority < pos[i] && usedLibraries.find(i) == usedLibraries.end()) {
                bestLibrary = i;
                bestPriority = pos[i];
            }
        }
        usedLibraries.insert(bestLibrary);
        remainingDays -= libraries[bestLibrary]->getSignupTime();
        sum += libraries[bestLibrary]->calculateScore(remainingDays, booksUsedSoFar);
    }
    if (sum > bestScore) {
        for (int i = 0; i < n; i++) {
            bestPos[i] = pos[i];
        }
        bestScore = sum;
    }
    return sum;
}

void fillArrayRandom(int n, int* a)
{
    for (int i = 0; i < n; i++) {
        a[i] = rand() % n;
    }
}

void Particle::updateVelocity(float coefficientVelocity, float coefficientGlobal, float coefficientParticle, int* bestGlobalPos)
{
    float randomGlobal = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    float randomParticle = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    for (int i = 0; i < n; i++) {
        velocity[i] = coefficientVelocity * velocity[i] +
            randomGlobal * coefficientGlobal * (pos[i] - bestGlobalPos[i]) + randomParticle * coefficientParticle * (pos[i] - bestPos[i]);
    }
}

void Particle::updatePosition()
{
    for (int i = 0; i < n; i++) {
        pos[i] += velocity[i];
    }
}
int* Particle::getPosition()
{
    return pos;
}
