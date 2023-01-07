#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <fstream>
#include <cstdlib>
#include <time.h>
#include <chrono>
#include "Book.h"
#include "Library.h"
#include "LibraryAssignment.h"
#include "Assignment.h"
#include "ParticleSwarm.h"

using namespace std;

double calcScore(bool* assignment, vector<Library*> libraries, int maxDays, unordered_map<int, int> bookFoundInLibs, double sat)
{
    double score = 0;
    int remDays = maxDays;
    int libNum = 0;
    for(int i = 0; i < libraries.size(); i++)
    {
        if(assignment[i])
        {
            libNum++;
            double libScore = 0;
            for(Book* b: libraries[i]->getAllBooks())
            {
                libScore += b->getBaseScore()/(double)bookFoundInLibs.at(b->getID());
            }
            remDays -= libraries[i]->getSignupTime();
            libScore *= libraries[i]->getBooksPerDay();
            score += libScore;
        }
    }
    score -= 1000*remDays;
    score -= 10000*abs(libraries.size()*sat - libNum);
    return score;
}

int main()
{
    auto startTime = std::chrono::high_resolution_clock::now();
    srand(time(NULL));
    int B, L, D;
// TO DO CHANGE THIS SHIT INPUT AND OUTPUT
    ifstream InputFile("f_libraries_of_the_world.txt");
    InputFile >> B;
    InputFile >> L;
    InputFile >> D;
    int score;
    vector<Book*> books;
    unordered_map<int, int> bookFoundInLibs;
    for (int i = 0; i < B; i++) {
        InputFile >> score;
        books.push_back(new Book(score, i));
    }
    int n, t, m, bookID;
    long long unsigned int sumOfSignupTimes = 0;
    vector<Library*> libraries;
    for (int i = 0; i < L; i++) {
        InputFile >> n;
        InputFile >> t;
        InputFile >> m;
        libraries.push_back(new Library(i, n, t, m));
        for (int j = 0; j < n; j++) {
            InputFile >> bookID;
            libraries[i]->addBook(books[bookID]);
            auto it = bookFoundInLibs.find(bookID);
            if(it != bookFoundInLibs.end()) it->second++;
            else bookFoundInLibs.insert(make_pair(bookID, 1));
        }
        libraries[i]->sortBooks();
        sumOfSignupTimes += libraries[i]->getSignupTime();
    }
    double requiredSat = D/(double)sumOfSignupTimes;
    vector<Library*> librariesToConsider;
    if(requiredSat < 1 && L*requiredSat > 10000)
    {
        int noImpr = 0;
        int initTemp = 100000;
        bool* currAssignment = new bool[L];
        bool* bestAssignment = new bool[L];
        double bestAnnealingScore = 0;
        double currScore = 0;
        for(int i = 0; i < L; i++)
        {
            if(requiredSat >= (static_cast<float>(rand())/static_cast<float>(RAND_MAX)))
                currAssignment[i] = true;
            bestAssignment[i] = currAssignment[i];
        }
        bestAnnealingScore = calcScore(bestAssignment, libraries, D, bookFoundInLibs, requiredSat);
        currScore = bestAnnealingScore;
        auto currTime = std::chrono::high_resolution_clock::now();
        for(int i = 0; i<10000; i++)
        {
            currTime = std::chrono::high_resolution_clock::now();
            if(noImpr > 500 || (std::chrono::duration_cast<std::chrono::seconds>(currTime - startTime).count() > 60))break;
            double currTemp = initTemp/(1+i);
            int toChange = rand()%(libraries.size());
            currAssignment[toChange] = !currAssignment[toChange];
            double nScore = calcScore(currAssignment, libraries, D, bookFoundInLibs, requiredSat);
            if(nScore > bestAnnealingScore)
            {
                for(int j = 0; j < L; j++)
                {
                    bestAssignment[j] = currAssignment[j];
                }
                bestAnnealingScore = nScore;
                noImpr = 0;
            }
            else noImpr++;
            if(nScore < currScore)
            {
                double diff = currScore - nScore;
                if(exp(-diff/currTemp) < static_cast<float>(rand())/static_cast<float>(RAND_MAX))
                {
                    currAssignment[toChange] = !currAssignment[toChange];
                }
            }
        }
        for(int i = 0; i<L; i++)
        {
            if(bestAssignment[i] == 1)
            {
                librariesToConsider.push_back(libraries[i]);
            }
        }
        delete[] bestAssignment;
        delete[] currAssignment;
    }
    else
    {
        librariesToConsider = libraries;
    }
    Assignment* initialAssignment = new Assignment;
    vector<Library*> librariesNotInOrder(librariesToConsider);
    int daysUsedSoFar = 0;
    Library* bestLibrary = NULL;
    float bestScore = 0;
    float currentScore = 0;
    auto currTime = std::chrono::high_resolution_clock::now();
    while(D > daysUsedSoFar && !librariesNotInOrder.empty() && std::chrono::duration_cast<std::chrono::seconds>(currTime - startTime).count() < 290)
    {
        for (unsigned int i = 0; i < librariesNotInOrder.size(); i++)
        {
            if (D - daysUsedSoFar < librariesNotInOrder[i]->getSignupTime())
                continue;
            currentScore = librariesNotInOrder[i]->calculateHeuristicScore(D, initialAssignment->getUsedBooks(), bookFoundInLibs);
            if (bestLibrary == NULL || currentScore > bestScore)
            {
                bestScore = currentScore;
                bestLibrary = librariesNotInOrder[i];
            }
        }
        if(bestLibrary == NULL)
            break;
        librariesNotInOrder.erase(std::remove(librariesNotInOrder.begin(), librariesNotInOrder.end(), bestLibrary), librariesNotInOrder.end());
        vector<Book*> booksToUse = bestLibrary->getBooksToUse(D - daysUsedSoFar, initialAssignment->getUsedBooks());
        if(booksToUse.size() != 0)
            initialAssignment->addLibraryAssignment(new LibraryAssignment(bestLibrary->getID(), booksToUse));
        daysUsedSoFar += bestLibrary->getSignupTime();
        bestScore = 0;
        bestLibrary = NULL;
    }
    initialAssignment->displayOutput();
    return 0;
}










