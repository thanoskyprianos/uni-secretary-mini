#ifndef IOSTREAM
#define IOSTREAM
#include <iostream>
#endif

#ifndef PERSON
#define PERSON
#include "person.h"
#endif

#ifndef UTIL
#define UTIL
#include "../Util/util.h"
#endif

using std::cout;
using std::istream;
using std::ostream;
using std::getline;

using  std::string;

unsigned int Person::objectCount = 0;
unsigned int Person::getObjectCount() { return Person::objectCount; }

Person::Person() : age(0) {
    Person::objectCount++;
}

Person::Person(
    const string &id, const string &name, unsigned short age,
    const string &address, const string &phoneNumber, const string &email
): id(id), name(name), age(age),
   address(address), phoneNumber(phoneNumber), email(email)
{
    Person::objectCount++;
}

Person::~Person() {
    Person::objectCount--;
}

string Person::getId() const { return id; }
string Person::getName() const { return name; }
unsigned short Person::getAge() const { return age; }

string Person::getAddress() const { return address; }
void Person::setAddress(const string &address) { this->address = address; }

string Person::getPhoneNumber() const { return phoneNumber; }
void Person::setPhoneNumber(const string &phoneNumber) { this->phoneNumber = phoneNumber; }

string Person::getEmail() const { return email; }
void Person::setEmail(const string &email) { this->email = email; }

ostream &operator<<(ostream &str, const Person &p) {
    str <<
        util::GREEN << p.id << ": " << util::RESET <<
        p.name << ", " <<
        p.age << ", " <<
        p.address  << ", " <<
        p.phoneNumber << ", " <<
        p.email;

    return str;
}

istream &operator>>(istream &str, Person &p) {
    using namespace util;

    cout << "Give" << util::CYAN << " id: " << util::RESET;
    cinWithClear(str, p.id);

    cout << "Give" << util::CYAN << " name: " << util::RESET;
    getline(str, p.name);

    cout << "Give" << util::CYAN << " age: " << util::RESET;
    cinWithClear(str, p.age);

    cout << "Give" << util::CYAN << " address: " << util::RESET;
    getline(str, p.address);

    cout << "Give" << util::CYAN << " phone number: " << util::RESET;
    getline(str, p.phoneNumber);

    cout << "Give" << util::CYAN << " email: " << util::RESET;
    cinWithClear(str, p.email);

    return str;
}