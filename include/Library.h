#ifndef LIBRARY_H
#define LIBRARY_H
#include <vector>
#include <algorithm>
#include <iostream>
#include <unordered_set>
#include "Book.h"


class Library
{
    public:
        Library(int id, int numOfBooks, int signupTime, int booksPerDay);
        float calculateScore(int maxDays, std::unordered_set<int>& booksUsedSoFar);
        float calculateHeuristicScore(int maxDays, const std::unordered_set<int>& booksUsedSoFar);
        void addBook(Book* book);
        int getID();
        int getSignupTime();
        void sortBooks();
        const std::vector<Book*> getBooksToUse(int remainingDays, const std::unordered_set<int>& booksUsedSoFar);
        virtual ~Library();
    private:
        int id;
        int numOfBooks;
        int signupTime;
        int booksPerDay;
        std::vector<Book*> booksInLibrary;
};

#endif // LIBRARY_H
