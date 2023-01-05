#include "Particle.h"



void fillRandomPos(int n, int* a);
void fillRandomVel(int n, int* a);
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
    fillRandomVel(n, velocity);
}

Particle::Particle(int n) : n(n)
{
    this->pos = new int[n];
    this->bestPos = new int[n];
    this->velocity = new int[n];
    this->bestScore = 0;
    fillRandomPos(n, pos);
    for (int i = 0; i < n; i++) {
        this->bestPos[i] = pos[i];

    }
    fillRandomVel(n, velocity);
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
            if (bestPriority < pos[i] && usedLibraries.find(i) == usedLibraries.end() && libraries[i]->getSignupTime() <= remainingDays) {
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

void fillRandomPos(int n, int* a)
{
    for(int i = 0; i<n; i++)a[i] = i;
    std::random_shuffle(&a[0], &a[n-1]);
}
void fillRandomVel(int n, int* a)
{
    for(int i = 0; i < n; i++) a[i] = rand()%n;
}


void Particle::updateVelocity(float coefficientVelocity, float coefficientGlobal, float coefficientParticle, int* bestGlobalPos)
{
    float randomGlobal = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    float randomParticle = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    int new_velocity;
    for (int i = 0; i < n; i++) {
        new_velocity = coefficientVelocity * velocity[i] +
            randomGlobal * coefficientGlobal * (pos[i] - bestGlobalPos[i]) + randomParticle * coefficientParticle * (pos[i] - bestPos[i]);
        if (new_velocity < -n ) {
            new_velocity = -n;
        } else if (new_velocity > n) {
            new_velocity = n;
        }
        velocity[i] = new_velocity;
    }
}

void Particle::updatePosition()
{

    for (int i = 0; i < n; i++) {
        int newPos = pos[i] + velocity[i];
        if(newPos >= 0 && newPos < n){
            for(int j = 0; j < n; j++){
                if(pos[j] == newPos){
                    pos[j] = pos[i];
                    break;
                }
            }
            pos[i] = newPos;
        }
    }
}
int* Particle::getPosition()
{
    return pos;
}
