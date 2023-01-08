#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <cstdlib>
#include <time.h>
#include <chrono>
#include <math.h>
#include "Book.h"
#include "Library.h"
#include "LibraryAssignment.h"
#include "Assignment.h"

using namespace std;

double calcAnnealingScore(bool* assignment, vector<Library*> libraries, int maxDays, unordered_map<int, int> bookFoundInLibs, int expectedResultSize)
{
    double score = 0;
    int remDays = maxDays;
    int libNum = 0;
    for(unsigned int i = 0; i < libraries.size(); i++)
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
    score -= 1000*abs(expectedResultSize - libNum);
    return score;
}

double getRandomDouble()
{
    return static_cast<double>(rand())/static_cast<double>(RAND_MAX);
}

int main()
{
    auto startTime = std::chrono::high_resolution_clock::now();
    srand(time(NULL));
    int B, L, D;
    cin >> B;
    cin >> L;
    cin >> D;
    int score;
    vector<Book*> books;
    unordered_map<int, int> bookFoundInLibs;
    for (int i = 0; i < B; i++) {
        cin >> score;
        books.push_back(new Book(score, i));
    }
    int n, t, m, bookID;
    long long unsigned int sumOfSignupTimes = 0;
    vector<Library*> libraries;
    for (int i = 0; i < L; i++) {
        cin >> n;
        cin >> t;
        cin >> m;
        libraries.push_back(new Library(i, n, t, m));
        for (int j = 0; j < n; j++) {
            cin >> bookID;
            libraries[i]->addBook(books[bookID]);
            auto it = bookFoundInLibs.find(bookID);
            if(it != bookFoundInLibs.end()) it->second++;
            else bookFoundInLibs.insert(make_pair(bookID, 1));
        }
        libraries[i]->sortBooks();
        sumOfSignupTimes += libraries[i]->getSignupTime();
    }
    double requiredSat = D/(double)sumOfSignupTimes;
    int expectedResultSize = L*requiredSat;
    vector<Library*> librariesToConsider;
    if(expectedResultSize > 10000) //Instance is too big to be processed by the algorithm, size reduction needed
    {
        int noImpr = 0;
        double initTemp = 100000.0;
        bool* currAssignment = new bool[L];
        bool* bestAssignment = new bool[L];
        double bestAnnealingScore = 0;
        double currScore = 0;
        double currTemp = 0;
        double neighbourScore = 0;
        int toChange = 0;
        for(int i = 0; i < L; i++)
        {
            if(requiredSat >= getRandomDouble())
                currAssignment[i] = true;
            bestAssignment[i] = currAssignment[i];
        }
        bestAnnealingScore = calcAnnealingScore(bestAssignment, libraries, D, bookFoundInLibs, requiredSat);
        currScore = bestAnnealingScore;
        auto currTime = std::chrono::high_resolution_clock::now();
        for(int i = 0; i<10000; i++)
        {
            currTime = std::chrono::high_resolution_clock::now();
            if(noImpr > 500 || (std::chrono::duration_cast<std::chrono::seconds>(currTime - startTime).count() > 60))break;
            currTemp = initTemp/(i+1);
            toChange = rand()%(libraries.size());
            currAssignment[toChange] = !currAssignment[toChange];
            neighbourScore = calcAnnealingScore(currAssignment, libraries, D, bookFoundInLibs, requiredSat);
            if(neighbourScore > bestAnnealingScore)
            {
                for(int j = 0; j < L; j++)
                {
                    bestAssignment[j] = currAssignment[j];
                }
                bestAnnealingScore = neighbourScore;
                noImpr = 0;
            }
            else noImpr++;
            if(neighbourScore < currScore)
            {
                if(exp(-(currScore - neighbourScore)/currTemp) < getRandomDouble()) //Return back to previous assignment - i.e. do not choose the neighbour
                {
                    currAssignment[toChange] = !currAssignment[toChange];
                }
                else currScore = neighbourScore;
            }
            else
            {
                currScore = neighbourScore;
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
    Assignment* finalAssignment = new Assignment;
    vector<Library*> librariesNotInOrder(librariesToConsider);
    int daysUsedSoFar = 0;
    Library* bestLibrary = NULL;
    float bestScore = 0;
    float currentScore = 0;
    auto currTime = std::chrono::high_resolution_clock::now();
    while(D > daysUsedSoFar && !librariesNotInOrder.empty() && std::chrono::duration_cast<std::chrono::seconds>(currTime - startTime).count() < 290) //Main optimization algorithm - choose libraries that maximize the heuristic function
    {
        currTime = std::chrono::high_resolution_clock::now();
        for (unsigned int i = 0; i < librariesNotInOrder.size(); i++)
        {
            if (D - daysUsedSoFar < librariesNotInOrder[i]->getSignupTime())
                continue;
            currentScore = librariesNotInOrder[i]->calculateHeuristicScore(D, finalAssignment->getUsedBooks(), bookFoundInLibs);
            if (bestLibrary == NULL || currentScore > bestScore)
            {
                bestScore = currentScore;
                bestLibrary = librariesNotInOrder[i];
            }
        }
        if(bestLibrary == NULL)
            break;
        librariesNotInOrder.erase(std::remove(librariesNotInOrder.begin(), librariesNotInOrder.end(), bestLibrary), librariesNotInOrder.end());
        vector<Book*> booksToUse = bestLibrary->getBooksToUse(D - daysUsedSoFar, finalAssignment->getUsedBooks());
        if(booksToUse.size() != 0)
            finalAssignment->addLibraryAssignment(new LibraryAssignment(bestLibrary->getID(), booksToUse));
        daysUsedSoFar += bestLibrary->getSignupTime();
        bestScore = 0;
        bestLibrary = NULL;
    }
    finalAssignment->displayOutput();
    delete finalAssignment;
    for(Library* library: libraries)
    {
        delete library;
    }
    for(Book* book: books)
    {
        delete book;
    }
    return 0;
}










