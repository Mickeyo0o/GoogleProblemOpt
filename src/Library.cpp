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

float Library::calculateScore(int maxDays, const std::unordered_set<int>& booksUsedSoFar)
{
    int bookScores = 0;
    for (int i = 0; i < booksInLibrary.size(); i++) {
        if(booksUsedSoFar.find(booksInLibrary[i]->getID()) == booksUsedSoFar.cend())
            bookScores += booksInLibrary[i]->getBaseScore();
    }
    return this->booksPerDay * bookScores / (float)(maxDays - this->signupTime);
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
    std::sort(booksNotUsed.begin(), booksNotUsed.end(), compareBooks);
    return std::vector<Book*>(booksNotUsed.begin(), booksNotUsed.begin()+numOfBooksToScan);
}
