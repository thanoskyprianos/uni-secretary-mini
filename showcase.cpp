// File used to showcase functions not used in main.cpp

#ifndef IOSTREAM
#define IOSTREAM
#include <iostream>
#endif

#ifndef PERSON
#define PERSON
#include "Person/person.h"
#endif

#ifndef SECRETARY
#define SECRETARY
#include "Secretary/secretary.h"
#endif

using std::cout;
using std::endl;

int main(void) {
    // create some placeholder Person objects
    Person p {"1", "Alice", 25, "123 Main St", "123-456-7890", "alice@example.com"};
    Person p2{"1", "Charlie", 26, "999 Oak St", "999-999-9999", "charlie@example.com"}; // duplicate id ( won't be added )
    Person q {"2", "Bob", 30, "456 Oak St", "234-567-8901", "bob@example.com"};
    Person r {"3", "Charlie", 22, "789 Elm St", "345-678-9012", "charlie2@example.com"};
    Person s {"4", "David", 28, "987 Pine St", "456-789-0123", "david@example.com"};
    Person t {"5", "Eva", 35, "654 Birch St", "567-890-1234", "eva@example.com"};
    Person u {"6", "Frank", 29, "321 Cedar St", "678-901-2345", "frank@example.com"};
    Person v {"7", "Alice", 27, "876 Maple St", "789-012-3456", "alice2@example.com"};
    Person w {"8", "Bob", 31, "543 Fir St", "890-123-4567", "bob2@example.com"};

    // showcase get functions
    cout << "Person p: " << endl;
    cout << p.getId() << ' ' <<
            p.getName() << ' ' <<
            p.getAge() << ' ' <<
            p.getAddress() << ' ' <<
            p.getPhoneNumber() << ' ' <<
            p.getEmail() << endl << endl;

    // showcase static object counter
    cout << "Person objects created: " << Person::getObjectCount() << endl << endl;

    // Create Secretary objects and add above Person objects to it's data stracture
    cout << "Creating new secretary..." << endl;
    Secretary oldSec {p, p2, q, r, s, t, u, v, w};

    // showcase copy constructor
    cout << endl << "Copying secretary into new object..." << endl;
    
    Secretary newSec {oldSec};
    
    cout << "Old Sec: " << endl << oldSec << endl << endl;
    cout << "New Sec: " << endl << newSec << endl << endl;

    // showcase operator=
    cout << "Assigning secretary of two people to old secretary..." << endl;
    oldSec = Secretary {p, q};

    // used to showcase operator+
    cout << "Adding new person to old secretary..." << endl;
    Person x = {"10", "Eva", 36, "111 Pine St", "111-111-1111", "eva2@example.com"};
    oldSec + x;
    cout << endl << endl;

    cout << endl <<  "Old Sec: " << endl << oldSec << endl << endl;
    cout << "New Sec: " << endl << newSec << endl;

    // showcase findByObject
    Person *ptr = oldSec.findByObject(x);
    if (ptr) cout << *ptr << ": IN old secretary." << endl;
    else cout << "NOT IN old secretary." << endl;

    ptr = newSec.findByObject(x);
    if (ptr) cout << *ptr << "IN new secretary." << endl << endl;
    else cout << "NOT IN new secretary." << endl << endl;

    return 0;
}