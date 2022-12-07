#include "Library.h"

Library::Library(int numOfBooks, int signupTime, int booksPerDay) : numOfBooks(numOfBooks), signupTime(signupTime), booksPerDay(booksPerDay)
{
}

Library::~Library()
{
}

void Library::addBook(Book* book)
{
    booksInLibrary.push_back(book);
}

float Library::calculateScore(int maxDays, const std::map<int, bool>& booksUsedSoFar)
{
    int bookScores = 0;
    for (int i = 0; i < booksInLibrary.size(); i++) {
        if(!booksUsedSoFar.at(booksInLibrary[i]->getID()))
            bookScores += booksInLibrary[i]->getBaseScore();
    }
    return this->booksPerDay * bookScores / (float)(maxDays - this->signupTime);
}

int Library::getSignupTime()
{
    return signupTime;
}

bool compareBooks(const Book* a, const Book* b){return a->getBaseScore()>b->getBaseScore();}

const std::vector<Book*> Library::getBooksToUse(int remainingDays, const std::map<int, bool>& booksUsedSoFar)
{
    std::vector<Book*> booksNotUsed;
    for(Book* b: booksInLibrary){
        if(!booksUsedSoFar.at(b->getID()))
            booksNotUsed.push_back(b);
    }
    int numOfBooksToScan = std::min(remainingDays*booksPerDay, (int)booksNotUsed.size());
    if(numOfBooks == numOfBooksToScan)
        return booksInLibrary;
    std::sort(booksNotUsed.begin(), booksNotUsed.end(), compareBooks);
    return std::vector<Book*>(booksNotUsed.begin(), booksNotUsed.begin()+numOfBooksToScan);
}
