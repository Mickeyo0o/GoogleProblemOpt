#include "Library.h"

Library::Library(int id, int numOfBooks, int signupTime, int booksPerDay) : id(id), numOfBooks(numOfBooks), signupTime(signupTime), booksPerDay(booksPerDay)
{
}

Library::~Library()
{
}

void Library::addBook(Book* book)
{
    booksInLibrary.push_back(book);
}

float Library::calculateScore(int remainingDays, std::unordered_set<int>& booksUsedSoFar)
{
    int bookScores = 0;
    int64_t booksToScan = (int64_t)remainingDays * (int64_t)booksPerDay;
    for (int i = 0; i < booksInLibrary.size(); i++) {
        if (booksToScan == 0) {
            break;
        }
        if (booksUsedSoFar.find(booksInLibrary[i]->getID()) == booksUsedSoFar.end()) {
            bookScores += booksInLibrary[i]->getBaseScore();
            booksUsedSoFar.insert(booksInLibrary[i]->getID());
            booksToScan--;
        }
    }
    return bookScores;
}

float Library::calculateHeuristicScore(int maxDays, const std::unordered_set<int>& booksUsedSoFar)
{
    int bookScores = 0;
    for (int i = 0; i < booksInLibrary.size(); i++) {
        if(booksUsedSoFar.find(booksInLibrary[i]->getID()) == booksUsedSoFar.cend())
            bookScores += booksInLibrary[i]->getBaseScore();
    }
    return (bookScores / (float)(maxDays - this->signupTime))/this->signupTime;
}

int Library::getID()
{
    return id;
}

int Library::getSignupTime()
{
    return signupTime;
}

bool compareBooks(const Book* a, const Book* b){return a->getBaseScore()>b->getBaseScore();}

void Library::sortBooks()
{
    std::sort(booksInLibrary.begin(), booksInLibrary.end(), compareBooks);
}

const std::vector<Book*> Library::getBooksToUse(int remainingDays, const std::unordered_set<int>& booksUsedSoFar)
{
    std::vector<Book*> booksNotUsed;
    for(Book* b: booksInLibrary){
        if(booksUsedSoFar.find(b->getID()) == booksUsedSoFar.cend())
            booksNotUsed.push_back(b);
    }
    int numOfBooksToScan = std::min(remainingDays*booksPerDay, (int)booksNotUsed.size());
    if (numOfBooksToScan <= 0) {
        return std::vector<Book*>{};
    }
    if(numOfBooks == numOfBooksToScan)
        return booksInLibrary;
    return std::vector<Book*>(booksNotUsed.begin(), booksNotUsed.begin()+numOfBooksToScan);
}
