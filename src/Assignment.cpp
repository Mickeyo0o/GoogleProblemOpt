#include "Assignment.h"

Assignment::Assignment()
{
    //ctor
}

Assignment::~Assignment()
{
    for (int i = 0; i < assignment.size(); i++) {
        delete assignment[i];
    }
}

void Assignment::addLibraryAssignment(LibraryAssignment* libraryAssignment)
{
    assignment.push_back(libraryAssignment);
    std::vector<int> booksAssignment = libraryAssignment->getBooksInOrder();
    for (int i = 0; i < booksAssignment.size(); i++) {
        usedBooks.insert(booksAssignment[i]);
    }
}

void Assignment::displayOutput()
{
    std::cout << assignment.size() << std::endl;
    for (int i = 0; i < assignment.size(); i++) {
        std::vector<int> books = assignment[i]->getBooksInOrder();
        std::cout << assignment[i]->getID() << " " << books.size() << std::endl;
        for (int j = 0; j < books.size(); j++) {
            std::cout << books[j] << " ";
        }
        std::cout << std::endl;
    }
}

const std::unordered_set<int>& Assignment::getUsedBooks()
{
    return usedBooks;
}

std::vector<int> Assignment::getLibraryIDS()
{
    std::vector<int> libraryIDS;
    for (int i = 0; i < assignment.size(); i++) {
        libraryIDS.push_back(assignment[i]->getID());
    }
    return libraryIDS;
}

long long unsigned int Assignment::getUpperBound(std::vector<Book*> books, int remainingDays)
{
    int upper = 0;
    for(Book* book: books)
    {
        if(usedBooks.find(book->getID()) == usedBooks.end())
            upper += book->getBaseScore();
    }
    return upper*remainingDays;
}

long long unsigned int Assignment::getLowerBound(std::vector<Book*> books)
{
    int lower = 0;
    for(int bookId: usedBooks)
    {
        lower += books[bookId]->getBaseScore();
    }
    return lower;
}
