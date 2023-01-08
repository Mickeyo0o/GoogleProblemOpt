#include "LibraryAssignment.h"

LibraryAssignment::LibraryAssignment(int id, const std::vector<Book*>& books) : libraryID(id)
{
    for (int i = 0; i < books.size(); i ++) {
        booksIDsInOrder.push_back(books[i]->getID());
    }
}

LibraryAssignment::~LibraryAssignment(){}

int LibraryAssignment::getID()
{
    return libraryID;
}

const std::vector<int>& LibraryAssignment::getBooksInOrder()
{
    return booksIDsInOrder;
}
