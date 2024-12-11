#ifndef IOSTREAM
#include <iostream>
#define IOSTREAM
#endif

#ifndef STRING
#include <string>
#define STRING
#endif

using std::ostream;
using std::istream;

using std::string;

class Person {
private:
    static unsigned int objectCount;

    string id;
    string name;
    unsigned short age;

    string address;
    string phoneNumber;
    string email;
public:
    static unsigned int getObjectCount();

    Person();
    Person(
        const string &id,
        const string &name,
        unsigned short age,
        const string &address,
        const string &phoneNumber,
        const string &email
    );

    ~Person();

    string getId() const;
    string getName() const;
    unsigned short getAge() const;
    
    string getAddress() const;
    void setAddress(const string &address);

    string getPhoneNumber() const;
    void setPhoneNumber(const string &phoneNumber);

    string getEmail() const;
    void setEmail(const string &email);

    friend std::ostream &operator<<(std::ostream &str, const Person &p);
    friend std::istream &operator>>(std::istream &str, Person &p);
};