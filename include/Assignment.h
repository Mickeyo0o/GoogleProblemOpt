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
    private:
        std::vector<LibraryAssignment*> assignment;
        std::unordered_set<int> usedBooks;
};

#endif // ASSIGNMENT_H
