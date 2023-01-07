#include "Particle.h"


Particle::Particle(int n, double sat) : n(n)
{
    this->pos = new int[n];
    this->bestPos = new int[n];
    this->velocity = new float[n];
    this->bestScore = -std::numeric_limits<double>::infinity();
    fillRandomPos(sat);
    for (int i = 0; i < n; i++) {
        this->bestPos[i] = pos[i];
    }
    fillRandomVel();
}

Particle::Particle(int n, int* pos): n(n)
{
    this->pos = new int[n];
    this->bestPos = new int[n];
    this->velocity = new float[n];
    this->bestScore = -std::numeric_limits<double>::infinity();
    for (int i = 0; i < n; i++) {
        this->pos[i] = pos[i];
        this->bestPos[i] = pos[i];
    }
    fillRandomVel();
}

Particle::~Particle()
{
    delete[] pos;
    delete[] velocity;
}

double Particle::calculateScore(int days, std::vector<Library*> libraries)
{
    double sum = 0;
    std::unordered_set<int> usedBooks;
    long long remainingDays = days;
    int repeatedBooks = 0;
    for(int i = 0; i < n; i++)
    {
        if(pos[i] == 1)
        {
            sum += libraries[i]->getSumScoreOfAllBooks();
            remainingDays -= libraries[i]->getSignupTime();
            std::vector<Book*> booksFromLibrary = libraries[i]->getAllBooks();
            for(Book* book: booksFromLibrary)
            {
                if(usedBooks.find(book->getID()) != usedBooks.end()) repeatedBooks++;
                else usedBooks.insert(book->getID());
            }

        }
    }
    double score = 0;
    if(usedBooks.size() > 0)
    {
        score = sum - 100.0*repeatedBooks;
        if(remainingDays < 0)
        {
            score += 3000.0*remainingDays;
        }
    }
    if(score > bestScore)
    {
        bestScore = score;
        for(int i = 0; i<n; i++)
        {
            bestPos[i] = pos[i];
        }
    }
    return score;
}

void Particle::updateVelocity(float coefficientVelocity, float coefficientGlobal, float coefficientParticle, int* bestGlobalPos)
{
    float randomGlobal = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    float randomParticle = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    float new_velocity;
    for (int i = 0; i < n; i++) {
        new_velocity = coefficientVelocity * velocity[i] +
            randomGlobal * coefficientGlobal * (pos[i] - bestGlobalPos[i]) + randomParticle * coefficientParticle * (pos[i] - bestPos[i]);
        velocity[i] = new_velocity;
    }
}
int sign(float vel)
{
    if(vel > 0) return 1;
    return 0;
}
void Particle::updatePosition()
{
    for(int i = 0; i < n; i++)
    {
        if(sign(velocity[i]) != pos[i])
        {
            if(this->randomDecision(velocity[i]))
            {
                if(pos[i] == 0) pos[i] = 1;
                else if(pos[i] == 1) pos[i] = 0;
            }
        }
    }
}
int* Particle::getPosition()
{
    return pos;
}

void Particle::fillRandomPos(double sat)
{
    for(int i = 0; i<n; i++)
    {
        pos[i] = (sat >= static_cast<float>(rand())/static_cast<float>(RAND_MAX)?1:0);
    }
}

void Particle::fillRandomVel()
{
    for(int i = 0; i < n; i++)
    {
        velocity[i] = 2.f*static_cast<float>(rand())/static_cast<float>(RAND_MAX)-1;
    }
}

bool Particle::randomDecision(float vel)
{
    float p = vel/(vel+10.0);
    if(p < 0)p = -p;
    bool ret = (p >= static_cast<float>(rand())/static_cast<float>(RAND_MAX));
    return ret;
}
