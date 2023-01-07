#ifndef ASSIGNMENT_H
#define ASSIGNMENT_H
#include <vector>
#include <iostream>
#include <unordered_set>
#include "LibraryAssignment.h"


class Assignment
{
    public:
        Assignment();
        virtual ~Assignment();
        void addLibraryAssignment(LibraryAssignment* libraryAssignment);
        void displayOutput();
        const std::unordered_set<int>& getUsedBooks();
        std::vector<int> getLibraryIDS();
        long long unsigned int getUpperBound(std::vector<Book*> books, int remainingDays);
        long long unsigned int getLowerBound(std::vector<Book*> books);

    private:
        std::vector<LibraryAssignment*> assignment;
        std::unordered_set<int> usedBooks;
};

#endif // ASSIGNMENT_H
