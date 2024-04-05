#include <iostream>
#include<fstream>
#include<sstream>
#include <string>
#include <vector>

using namespace std;

class contact
{

public:
    string first_name;
    string last_name;
    string phone_number;
    string email;


    contact(const string _first_name, const string _last_name, const string _phone_number, const string _email)
        : first_name(_first_name), last_name(_last_name), phone_number(_phone_number), email(_email){};

    void display()
    {
        cout << "\tname : " << first_name + " " + last_name << endl;
        cout << "\tphone number : " << phone_number << endl;
        cout << "\temail : " << email << endl;
    }
};

class Contact_Manager
{

private:
    vector<contact> contacts;
    string filename;

public:

    Contact_Manager(const string &file) : filename(file) {};

    void loadContactsFromFile()
    {
        ifstream file(filename);
        if (!file.is_open())
        {
            cout << "Unable to open file " << filename << endl;
            return;
        }

        string line;
        while (getline(file, line))
        {
            istringstream hello(line);
            string first_name, last_name, phone_number, email;
            if (!(hello >> first_name >> last_name >> phone_number >> email))
            {
                cerr << "Error reading contact from file" << endl;
                continue;
            }
            contacts.push_back(contact(first_name, last_name, phone_number, email));
        }
        file.close();
    }

    void saveContactsToFile()
    {
        ofstream file(filename);
        if (!file.is_open())
        {
            cout << "Unable to open file " << filename << " for writing" << endl;
            return;
        }

        for (const auto c : contacts)
        {
            file << c.first_name << " " << c.last_name << " " << c.phone_number << " " << c.email << endl;
        }
        file.close();
    }

    void add_new()
    {
        string fname, lname, phone_number, email;

        cout << endl
             << "\tenter first name : ";
        cin >> fname;

        cout << endl
             << "\tenter last name : ";
        cin >> lname;

        cout << endl
             << "\tenter phone number : ";
        cin >> phone_number;

        cout << endl
             << "\t* enter email_id (if there is no email_id type NULL) : ";

        cin >> email;

        contacts.push_back(contact(fname, lname, phone_number, email));

        cout << endl
             << "\t\t->  CONTACT ADDED SUCCESSFULLY :) " << endl
             << endl;

        cin.ignore();
    }


    void view()
    {
        if (contacts.empty())
        {
            cout << endl
                 << "\t\t->  OOPS ! contact list is empty :( " << endl
                 << endl;
        }
        else
        {
            cout << endl
                 << endl
                 << "\t\t\t\t----------------- YOUR CONTACTS LIST : -----------------------" << endl
                 << endl;
            for (int i = 0; i < contacts.size(); i++)
            {
                cout << (i + 1) << "->  "
                     << "-------------------------------------------------------------------------------" << endl;
                contacts[i].display();
                cout << endl;
            }
        }
    }

    void edit_contact()
    {

        int index;

        if (contacts.empty())
        {
            cout << endl<<endl
                 << "\t\t -> OOPS ! EMPTY CONTACT LIST CANNOT EDIT " << endl<<endl;
            return;
        }

        cout << endl
             << "\tENTER SERIAL NUMBER TO EDIT : ";
        cin >> index;

        if (index < 1 || index > contacts.size())
        {
            cout << endl
                 << endl
                 << "\t-> INVALID CONTACT INDEX !" << endl;
            return;
        }

        cin.ignore();

        string new_fname, new_lname, new_phone_number, new_email;

        cout << endl
             << "\tenter new first Name (type NULL for previous first Name) : ";
        cin >> new_fname;

        cout << endl
             << "\tenter new last Name (type NULL for previous Last Name ) : ";
        cin >> new_lname;

        cout << endl
             << "\tEnter new phone number  (type NULL for old phone number) : ";
        cin >> new_phone_number;

        cout << endl
             << "\tEnter new email_id (type NULL for old email) : ";
        cin >> new_email;

        if (new_fname != "NULL")
        {
            contacts[index - 1].first_name = new_fname;
        }

        if (new_lname != "NULL")
        {
            contacts[index - 1].last_name = new_lname;
        }
        if (new_phone_number != "NULL")
        {
            contacts[index - 1].phone_number = new_phone_number;
        }

        if (new_email != "NULL")
        {
            contacts[index - 1].email = new_email;
        }

        cout << endl
             << " \t -> Contact Edit Successfully :) " << endl;
    }

    void delete_contact()
    {
        if (contacts.empty())
        {
            cout << endl
                 << "-> OOPS ! Contact List Is Empty :( " << endl
                 << endl;
        }
        else
        {
            int index;
            cout << endl
                 << "\tENTER SERIAL NUMBER : "<<endl;
            cin >> index;

            if (index < 1 || index > contacts.size())
            {
                cout << endl
                     << endl
                     << "\t-> INVALID CONTACT INDEX !!! " << endl;
            }

            cout<<"\t-> deleted contact name : "<<contacts[--index].first_name<<" "<<contacts[index].last_name<<endl<<endl;

            contacts.erase(contacts.begin() + index);

            cout << endl
                 << "\t-> CONTACT DELETED SUCCESSFULLY :) " << endl
                 << endl;
        }
    }

    int mainMenu()
    {
        cout << "\n\t\t************************************** Contact Management System ***************************************" << endl
             << endl;
        cout << "\tNOTE -> (a) CHOOSE 1 TO 5 NUMBER AS PER CHOICE " << endl;
        cout << "\t\t(b) * MEANS NOT MANDATORY TO FILL  " << endl;
        cout << "\t\t(c) YOUR CONTACT IS MAINTAINED IN A SERIAL ORDER " << endl;
        cout << "\t\t(d) CONTACT LIST IS SORTED BY 'OLDEST' " << endl;
        cout << "\t\t(e) 'NULL' MEANS NO INFORMATION PROVIDED " << endl;
        cout << "\t\t(f) TYPE 'NULL' IN UPPER CASE WHEN NEEDED " << endl
             << endl
             << endl;
        cout << "\t1. Add Contact" << endl;
        cout << "\t2. View Contacts" << endl;
        cout << "\t3. Edit Contact" << endl;
        cout << "\t4. Delete Contact" << endl;
        cout << "\t5. Exit" << endl
             << endl;
        cout << "\tEnter your choice: ";

        int choice;
        cin >> choice;

        return choice;
    }
};

int main()
{
    Contact_Manager manager("contacts.txt");

    manager.loadContactsFromFile();

    while (1)
    {

        char choice = manager.mainMenu();

        switch (choice)
        {
        case 1:
            manager.add_new();
            manager.saveContactsToFile();
            break;
        case 2:
            manager.view();
            manager.saveContactsToFile();
            break;
        case 3:
            manager.edit_contact();
            manager.saveContactsToFile();
            break;
        case 4:
            manager.delete_contact();
            manager.saveContactsToFile();
            break;
        case 5:
            cout << endl;
            cout << "\tTHANKS FOR USING :) " << endl;
            cout << "\t\tEXITING...." << endl
                 << endl;
            manager.saveContactsToFile();
            return 0;

        default:
            cout << endl
                 << "\t-> INVALID CHOICE : " << endl
                 << endl;
            break;
        }
    }
}
