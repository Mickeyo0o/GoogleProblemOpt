#ifndef LIBRARYASSIGNMENT_H
#define LIBRARYASSIGNMENT_H
#include <vector>
#include "Book.h"


class LibraryAssignment
{
    public:
        LibraryAssignment(int id, const std::vector<Book*>& books);
        virtual ~LibraryAssignment();
        int getID();
        const std::vector<int>& getBooksInOrder();
        int getScore();

    private:
        int libraryID;
        std::vector<int> booksIDsInOrder;
};

#endif // LIBRARYASSIGNMENT_H
