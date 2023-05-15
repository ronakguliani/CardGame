#ifndef CARD_H
#define CARD_H

#include <iostream>
#include <string>
using namespace std;

class Card {
public:
    Card();
		virtual ~Card();
    void setDescription(const string& description);
    string getDescription() const;
    void setSpaces(int spaces);
    int getSpaces() const;
    virtual void display() const;

    friend ostream& operator<<(ostream& os, const Card& card);

    Card& operator=(const Card& other);
    bool operator==(const Card& other) const;
    bool operator!=(const Card& other) const;

protected:
    int spaces;
    string description;
};

#endif // CARD_H

