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

float Library::calculateScore(int remainingDays, const std::unordered_set<int>& booksUsedSoFar)
{
    int bookScores = 0;
    long long unsigned int booksToScan = (long long unsigned int)remainingDays * (long long unsigned int)booksPerDay;
    for (int i = 0; i < booksInLibrary.size(); i++) {
        if (booksToScan == 0) {
            break;
        }
        if (booksUsedSoFar.find(booksInLibrary[i]->getID()) == booksUsedSoFar.end()) {
            bookScores += booksInLibrary[i]->getBaseScore();
            booksToScan--;
        }
    }
    return bookScores;
}

float Library::calculateHeuristicScore(int maxDays, const std::unordered_set<int>& booksUsedSoFar, const std::unordered_map<int, int>& bookFoundInLibs)
{
    int bookScores = 0;
    for (int i = 0; i < booksInLibrary.size(); i++) {
        if(booksUsedSoFar.find(booksInLibrary[i]->getID()) == booksUsedSoFar.cend())
        {
            auto it = bookFoundInLibs.find(booksInLibrary[i]->getID());
            bookScores += booksInLibrary[i]->getBaseScore()/(float)it->second;
        }
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
    long long unsigned int numOfBooksToScan = std::min((long long unsigned int)((long long unsigned int)remainingDays*(long long unsigned int)booksPerDay), (long long unsigned int)booksNotUsed.size());
    if(numOfBooksToScan == numOfBooks)
        return booksInLibrary;
    return std::vector<Book*>(booksNotUsed.begin(), booksNotUsed.begin()+numOfBooksToScan);
}

long long unsigned int Library::getSumScoreOfAllBooks()
{
    long long unsigned int sum = 0;
    for(Book* book: booksInLibrary)
    {
        sum += book->getBaseScore();
    }
    return sum;
}

const std::vector<Book*> Library::getAllBooks()
{
    return booksInLibrary;
}

int Library::getBooksPerDay()
{
    return booksPerDay;
}
