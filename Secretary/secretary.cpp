#ifndef IOSTREAM
#define IOSTREAM
#include <iostream>
#endif

#ifndef INIT_LIST
#define INIT_LIST
#include <initializer_list>
#endif

#ifndef MAP
#define MAP
#include <map>
#endif

#ifndef SECRETARY
#define SECRETARY
#include "secretary.h"
#endif

#ifndef UTIL
#define UTIL
#include "../Util/util.h"
#endif

using std::cout;
using std::cerr;
using std::cin;
using std::endl;

using std::initializer_list;

Secretary::Secretary() { }
Secretary::Secretary(initializer_list<Person> people) {
    for (const auto &p : people) *this + p; // already overloaded insertion
}

Secretary::Secretary(const Secretary &secretary) {
    for (const auto &p : secretary.people_by_id) {
        people_by_id[p.first] = new Person(*p.second);
        people_by_name[p.first].push_back(people_by_id[p.first]); // point to object created above
    }
}

Secretary::~Secretary() {
    for (auto &p : people_by_id)
        delete p.second;
}

Person *Secretary::findById(const string &id) const {
    auto ptr = people_by_id.find(id); 

    if(ptr != people_by_id.end())
        return ptr->second;

    return nullptr;
        
}

const vector<Person *> *Secretary::findByName(const string &name) const {
    auto ptr = people_by_name.find(name); 

    if(ptr != people_by_name.end())
        return &(ptr->second);

    return nullptr;
}

Person *Secretary::findByObject(const Person &person) const {
    return findById(person.getId());
}


Secretary &Secretary::operator+(const Person &person) {
    Person *p;
    
    if ((p = findByObject(person)))
        cerr << util::RED << "Person with id: " << util::RESET << person.getId() << util::RED <<" already exists! " << util::RESET << "(" << *p << ")" << endl;
    else {
        people_by_id[person.getId()] = new Person(person);
        people_by_name[person.getName()].push_back(people_by_id[person.getId()]); // point to object created above
        cout << "Inserted " << person << endl;
    }

    return *this;
}

Secretary &Secretary::operator=(Secretary other) {
    using std::swap;
    swap(*this, other);

    return *this;
}

void swap(Secretary &lhs, Secretary &rhs) {
    using std::swap;
    swap(lhs.people_by_id, rhs.people_by_id);
    swap(lhs.people_by_name, rhs.people_by_name);
}

ostream &operator<<(ostream &str, const Secretary &secretary) {
    for (const auto &p : secretary.people_by_id)
        str << *p.second << endl;

    return str;
}

istream &operator>>(istream &str, Secretary &secretary) {
    char ans = '\0';
    while (ans != 'n' && ans != 'N') {
        util::clear_screen();

        cout << util::GREEN << "---INSERTION---" << util::RESET << endl; 
        Person p;
        str >> p;

        secretary + p;

        cout << "Do you want to continue? (y/Y/n/N): ";
        str >> ans;
        while (ans != 'y' && ans != 'Y' && ans != 'n' && ans != 'N') {
            util::clear_lines();
            cerr << util::RED << "Invalid input!" << util::RESET << " Try again (y/Y/n/N): ";
            str >> ans;
        }
    }

    return str;
}