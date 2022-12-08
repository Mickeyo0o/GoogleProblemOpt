#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <fstream>
#include "Book.h"
#include "Library.h"
#include "LibraryAssignment.h"
#include "Assignment.h"

using namespace std;

int main()
{
    int B, L, D;
    ifstream InputFile("f_libraries_of_the_world.txt");
    InputFile >> B;
    InputFile >> L;
    InputFile >> D;
    int score;
    vector<Book*> books;
    for (int i = 0; i < B; i++) {
        InputFile >> score;
        books.push_back(new Book(score, i));
    }
    int n, t, m, bookID;
    vector<Library*> libraries;
    for (int i = 0; i < L; i++) {
        InputFile >> n;
        InputFile >> t;
        InputFile >> m;
        libraries.push_back(new Library(i, n, t, m));
        for (int j = 0; j < n; j++) {
            InputFile >> bookID;
            libraries[i]->addBook(books[bookID]);
        }
    }
// Loading data finished
    Assignment* initialAssignment = new Assignment;
    vector<Library*> librariesNotInOrder(libraries);
    int daysUsedSoFar = 0;
    Library* bestLibrary = NULL;
    float bestScore = 0;
    float currentScore = 0;
    while(D > daysUsedSoFar && !librariesNotInOrder.empty()) {
        for (int i = 0; i < librariesNotInOrder.size(); i++) {
            if (D - daysUsedSoFar < librariesNotInOrder[i]->getSignupTime())
                continue;
            currentScore = librariesNotInOrder[i]->calculateScore(D, initialAssignment->getUsedBooks());
            if (bestLibrary == NULL || currentScore > bestScore) {
                bestScore = currentScore;
                bestLibrary = librariesNotInOrder[i];
            }
        }
        if(bestLibrary == NULL)
            break;
        daysUsedSoFar += bestLibrary->getSignupTime();
        librariesNotInOrder.erase(std::remove(librariesNotInOrder.begin(), librariesNotInOrder.end(), bestLibrary), librariesNotInOrder.end());
        vector<Book*> booksToUse = bestLibrary->getBooksToUse(D - daysUsedSoFar, initialAssignment->getUsedBooks());
        if(booksToUse.size() != 0)
            initialAssignment->addLibraryAssignment(new LibraryAssignment(bestLibrary->getID(), booksToUse));
        bestScore = 0;
        bestLibrary = NULL;
    }
    initialAssignment->displayOutput();
    delete initialAssignment;
    return 0;
}
