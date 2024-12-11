#ifndef IOSTREAM
#define IOSTREAM
#include <iostream>
#endif

#ifndef VECTOR
#define VECTOR
#include <vector>
#endif

#ifndef INIT_LIST
#define INIT_LIST
#include <initializer_list>
#endif

#ifndef MAP
#define MAP
#include <map>
#endif

#ifndef PERSON
#define PERSON
#include "../Person/person.h"
#endif

using std::vector;
using std::initializer_list;
using std::map;

using std::ostream;
using std::istream;


class Secretary {
private:
    map<string, Person *> people_by_id;
    map<string, vector<Person *>> people_by_name;
    
public:
    Secretary();
    ~Secretary();
    Secretary(initializer_list<Person> people);
    Secretary(const Secretary &secretary);

    Person *findById(const string &id) const;
    const vector<Person *> *findByName(const string &name) const;
    Person *findByObject(const Person &p) const;

    Secretary &operator+(const Person &person);
    
    Secretary &operator=(Secretary other);
    friend void swap(Secretary &lhs, Secretary &rhs);

    friend ostream &operator<<(ostream &str, const Secretary &secretary);
    friend istream &operator>>(istream &str, Secretary &secretary);
};