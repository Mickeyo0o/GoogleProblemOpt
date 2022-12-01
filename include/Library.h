#ifndef LIBRARY_H
#define LIBRARY_H
#include <vector>
#include <algorithm>
#include <map>
#include "Book.h"


class Library
{
    public:
        Library(int numOfBooks, int signupTime, int booksPerDay);
        float calculateScore(int maxDays, const std::map<int, bool>& booksUsedSoFar);
        void addBook(Book* book);
        int getSignupTime();
        const std::vector<Book*> getBooksToUse(int remainingDays, const std::map<int, bool>& booksUsedSoFar);
        virtual ~Library();
    private:
        int numOfBooks;
        int signupTime;
        int booksPerDay;
        std::vector<Book*> booksInLibrary;
};

#endif // LIBRARY_H
