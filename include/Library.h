#ifndef LIBRARY_H
#define LIBRARY_H
#include <vector>
#include <algorithm>
#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include "Book.h"


class Library
{
    public:
        Library(int id, int numOfBooks, int signupTime, int booksPerDay);
        float calculateScore(int maxDays, const std::unordered_set<int>& booksUsedSoFar);
        float calculateHeuristicScore(int maxDays, const std::unordered_set<int>& booksUsedSoFar, const std::unordered_map<int, int>& bookFoundInLibs);
        void addBook(Book* book);
        int getID();
        int getSignupTime();
        int getBooksPerDay();
        void sortBooks();
        const std::vector<Book*> getBooksToUse(int remainingDays, const std::unordered_set<int>& booksUsedSoFar);
        const std::vector<Book*> getAllBooks();
        long long unsigned int getSumScoreOfAllBooks();
        virtual ~Library();
    private:
        int id;
        int numOfBooks;
        int signupTime;
        int booksPerDay;
        std::vector<Book*> booksInLibrary;
};

#endif // LIBRARY_H
