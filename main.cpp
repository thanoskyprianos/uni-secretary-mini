#ifndef IOSTREAM
#define IOSTREAM
#include <iostream>
#endif

#ifndef SECRETARY
#define SECRETARY
#include "Secretary/secretary.h"
#endif

#ifndef PERSON
#define PERSON
#include "Person/person.h"
#endif

#ifndef VECTOR
#define VECTOR
#include <vector>
#endif

#ifndef UTIL
#define UTIL
#include "Util/util.h"
#endif

#define LINE_SIZE 5

using std::cout;
using std::cin;
using util::cinWithClear;
using std::endl;

using util::clear_screen;
using util::clear_lines;
using util::wait_for_enter;

// Main menu
unsigned short main_menu() {
    clear_screen();

    cout << "---" << util::CYAN << "OPTIONS" << util::RESET << "---" << endl;

    cout << util::GREEN << "1. " << util::RESET << "View" << endl;
    cout << util::GREEN << "2. " << util::RESET << "Search" << endl;
    cout << util::GREEN << "3. " << util::RESET << "Edit Person" << endl;
    cout << util::GREEN << "4. " << util::RESET << "Add Person" << endl;
    cout << util::GREEN << "0. " << util::RESET << "Quit" << endl;

    unsigned short choice;
    cout << "Enter choice: ";
    cinWithClear(cin, choice);

    while (choice > 4) {
        clear_lines();

        cout << util::RED << "Invalid choice!" << util::RESET << "Try again: ";
        cinWithClear(cin, choice);
    }

    return choice;
}

// Menu that displays s' saved Person objects
void view_menu(const Secretary &s) {
    clear_screen();

    cout << "---" << util::CYAN << "PEOPLE" << util::RESET << "---" << endl;
    cout << s << endl;

    wait_for_enter();
}

// Menu used to edit selected Person p
void edit_menu(Person *p) {
    unsigned short choice;
    string buf;

    while (true) {
        clear_screen();

        cout << "---" << util::CYAN << "EDIT" << util::RESET << "--- (" << *p << ")" << endl;

        cout << util::GREEN << "1. " << util::RESET << "Address" << endl;
        cout << util::GREEN << "2. " << util::RESET << "Phone number" << endl;
        cout << util::GREEN << "3. " << util::RESET << "Email" << endl;
        cout << util::GREEN << "0. " << util::RESET << "Back" << endl;

        cout << "Enter choice: ";
        cinWithClear(cin, choice);

        while (choice > 3) {
            clear_lines();

            cout << util::RED << "Invalid choice!" << util::RESET << "Try again: ";
            cinWithClear(cin, choice);
        }

        switch (choice) {
            case 1:
                cout << "Give new address: ";
                getline(cin, buf);
                p->setAddress(buf);
                break;
            case 2:
                cout << "Give new phone number: ";
                getline(cin, buf);
                p->setPhoneNumber(buf);
                break;
            case 3:
                cout << "Give new email: ";
                getline(cin, buf);
                p->setEmail(buf);
                break;
            case 0:
                return;
        }
    }
}

// Menu used for cycling through a vector of Person objects; used by search_menu
Person *multi_choice_menu(const vector<Person *> *ps, bool edit) {
    if (!ps)
        return nullptr;

    unsigned short page_num = 0;
    while (true) {
        clear_screen();

        cout << "---" << util::CYAN << "PAGE " << page_num + 1 << util::RESET << "---" << endl;

        long unsigned int i = 0;
        for (; page_num * LINE_SIZE + i < ps->size() && i < LINE_SIZE; i++)
            cout << util::CYAN << "(" << i + 1 << ") " << util::RESET << *ps->at(page_num * LINE_SIZE + i) << endl;
            
        unsigned short choice, upper_bound = 1;
        cout << util::CYAN << "0. " << util::RESET << "Back / " << util::RESET;
        cout << util::CYAN << "1. " << util::RESET << "Next page" << util::RESET;

        if (edit) {
            cout << " / " << util::CYAN << "2. " << util :: RESET << "Edit" << util::RESET;
            upper_bound = 2;
        }

        cout << " | Choice: ";
        
        cinWithClear(cin, choice);
        while (choice > upper_bound) {
            cout << util::RED << "Invalid choice!" << util::RESET << "Try again: ";
            cinWithClear(cin, choice);
            clear_lines();
        }

        switch (choice) {
            case 0: return nullptr;
            case 1: page_num = (page_num + 1) % (ps->size() / LINE_SIZE + 1); break;
            case 2:
                cout << "Enter choice: (1 - " << i << "): ";
                cinWithClear(cin, choice);

                while (0 == choice || choice > i) {
                    cout << util::RED << "Invalid choice!" << util::RESET << "Try again: ";
                    cinWithClear(cin, choice);
                    clear_lines();
                }

                return ps->at(LINE_SIZE * page_num + choice - 1);
        }
    }
}

// Men used to search (and edit if edit == true) for a person by id, or people by name.
void search_menu(const Secretary &s, bool edit) {
    clear_screen();

    cout << "---" << util::CYAN << "SEARCH" << util::RESET << "---" << endl;
    cout << util::GREEN << "1." << util::RESET << " By" << util::CYAN << " id" << util::RESET << endl;
    cout << util::GREEN << "2." << util::RESET << " By" << util::CYAN << " name" << util::RESET << endl;
    cout << util::GREEN << "0." << util::RESET << " Back" << endl;

    unsigned short choice;
    cout << "Enter choice: ";
    cinWithClear(cin, choice);

    while (choice > 2) {
        clear_lines();

        cout << util::RED << "Invalid choice!" << util::RESET << "Try again: ";
        cinWithClear(cin, choice);
    }

    Person *p;
    string buf;

    switch (choice) {
        case 1:
            cout << "Give id: ";
            util::cinWithClear(cin, buf);
            p = s.findById(buf);

            if (p) 
                cout << util::GREEN << "Found! " << util::RESET << *p << endl;
            else
                cout << util::RED << "Not found!" << util::RESET << endl;

            break;
        case 2:
            cout << "Give name: ";
            getline(cin, buf);

            const vector<Person *> *ps;
            ps = s.findByName(buf);

            if (!ps)
                cout << util::RED << "Not found!" << util::RESET << endl;

            p = multi_choice_menu(ps, edit);

            break;
        case 0:
            return;
    }

    if (!edit || !p) {
        wait_for_enter();
        return;
    }

    edit_menu(p);
}

// Menu used to add a new Pesron to Secretary s.
void add_person_menu(Secretary &s) {
    clear_screen();

    cin >> s;

    wait_for_enter();
}

int main(void) {
    clear_screen();

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


    // Create Secretary object with above Person objects
    Secretary sec {p, p2, q, r, s, t, u, v, w};

    bool running = true;
    while (running) {
        unsigned short choice = main_menu();
        clear_screen();

        switch (choice) {
            case 1: view_menu(sec); break;          // showcases operator<<
            case 2: search_menu(sec, false); break; // showcases findById, findByName, iterating over people_by_name vector
            case 3: search_menu(sec, true); break;  // showcases setAdress, setPhoneNumber, setEmail
            case 4: add_person_menu(sec); break;    // showcases operator>>
            case 0: running = false; break;
        }
    }

    return 0;
}