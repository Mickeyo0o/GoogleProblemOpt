#ifndef BOOK_H
#define BOOK_H


class Book
{
    public:
        Book(int baseScore, int id);
        bool operator < (const Book& other) const;
        int getBaseScore();
        int getID();
        virtual ~Book();
    private:
        int baseScore;
        int id;
};

#endif // BOOK_H
