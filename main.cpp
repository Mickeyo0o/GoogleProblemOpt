#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include "Book.h"
#include "Library.h"

using namespace std;

int main()
{
    int B, L, D;
    cin >> B;
    cin >> L;
    cin >> D;
    int score;
    vector<Book*> books;
    for (int i = 0; i < B; i++) {
        cin >> score;
        books.push_back(new Book(score, i));
    }
    int n, t, m, bookID;
    vector<Library*> libraries;
    for (int i = 0; i < L; i++) {
        cin >> n;
        cin >> t;
        cin >> m;
        libraries.push_back(new Library(n, t, m));
        for (int j = 0; j < n; j++) {
            cin >> bookID;
            libraries[i]->addBook(books[bookID]);
        }
    }
    vector<Library*> librariesInOrder;
    vector<Library*> librariesNotInOrder(libraries);
    map<int, bool> booksUsedSoFar;
    for(Book* b: books)
    {
        booksUsedSoFar.insert(pair<int, bool>(b->getID(), false));
    }
    int daysUsedSoFar = 0;
    Library* bestLibrary = NULL;
    float bestScore = 0;
    float currentScore = 0;
    while(D > daysUsedSoFar && !librariesNotInOrder.empty()) {
        for (int i = 0; i < librariesNotInOrder.size(); i++) {
            currentScore = librariesNotInOrder[i]->calculateScore(D, booksUsedSoFar);
            if (bestLibrary == NULL || currentScore > bestScore) {
                bestScore = currentScore;
                bestLibrary = librariesNotInOrder[i];
            }
        }
        daysUsedSoFar += bestLibrary->getSignupTime();
        librariesInOrder.push_back(bestLibrary);
        librariesNotInOrder.erase(std::remove(librariesNotInOrder.begin(), librariesNotInOrder.end(), bestLibrary), librariesNotInOrder.end());
        vector<Book*> booksToUse = bestLibrary->getBooksToUse(D - daysUsedSoFar, booksUsedSoFar);
        for(Book* b: booksToUse)
            cout<<b->getID()<<endl;
        bestScore = 0;
        bestLibrary = NULL;
    }
    cout << "lol" << endl;
    return 0;
}
