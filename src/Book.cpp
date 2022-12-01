#include "Book.h"

Book::Book(int baseScore, int id) : baseScore(baseScore), id(id)
{
}

Book::~Book()
{
    //dtor
}

bool Book::operator<(const Book& other) const
{
    return baseScore < other.baseScore;
}

int Book::getBaseScore()
{
    return baseScore;
}

int Book::getID()
{
    return id;
}
