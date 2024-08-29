#include <iostream>
#include <map>
#include <string>
#include <fstream>

using namespace std;

// Struct and Value of map
struct Details {
    string phoneNumber;
    string email;
};

// Function prototypes
void display();
void addC(map<string, Details>& contacts, const string& filename);
void viewC(const map<string, Details>& contacts);
void editC(map<string, Details>& contacts, const string& filename);
void deleteC(map<string, Details>& contacts, const string& filename);
void saveContactsToFile(const map<string, Details>& contacts, const string& filename);
void loadContactsFromFile(map<string, Details>& contacts, const string& filename);

// Function to display the menu
void display() {
    cout << "Enter a number according to the Menu: " << endl;
    cout << "1. Add Contact" << endl;
    cout << "2. View Contact" << endl;
    cout << "3. Edit Contact" << endl;
    cout << "4. Delete Contact" << endl;
    cout << "5. Exit" << endl;
    cout << "Choose an option: ";
}

// Function to add a contact
void addC(map<string, Details>& contacts, const string& filename) {
    string name;
    Details contactDetails;
    cout << "Enter Name: " << endl;
    cin.ignore();  
    getline(cin, name);

    cout << "Enter Phone Number: " << endl;
    getline(cin, contactDetails.phoneNumber);
    
    cout << "Enter Email Address: " << endl;
    getline(cin, contactDetails.email);
    
    contacts[name] = contactDetails;

    saveContactsToFile(contacts, filename);

    cout << "Contact added successfully." << endl;
}

// Function to view all contacts
void viewC(const map<string, Details>& contacts) {
    if (contacts.empty()) {
        cout << "No Contacts available.\n";
        return;
    }

    map<string, Details>::const_iterator it = contacts.begin();
    while (it != contacts.end()) {
        cout << "Name: " << it->first << endl;
        cout << "Phone Number: " << it->second.phoneNumber << endl;
        cout << "Email Address: " << it->second.email << endl;
        cout << "---------------------------\n";
        ++it;
    }
}

// Function to edit a contact
void editC(map<string, Details>& contacts, const string& filename) {
    string name;
    cout << "Enter the name of the Contact to edit: " << endl;
    cin.ignore();  
    getline(cin, name);

    map<string, Details>::iterator it = contacts.find(name);
    if (it != contacts.end()) {
        cout << "Editing Contact: " << name << endl;
        cout << "Enter new Phone Number: " << endl;
        getline(cin, it->second.phoneNumber);
        
        cout << "Enter new Email Address: " << endl;
        getline(cin, it->second.email);
        
        cout << "Contact updated successfully." << endl;

        saveContactsToFile(contacts, filename);
    } else {
        cout << "Contact not found." << endl;
    }
}

// Function to delete a contact
void deleteC(map<string, Details>& contacts, const string& filename) {
    string name;
    cout << "Enter the name of the Contact to delete: " << endl;
    cin.ignore();  
    getline(cin, name);

    map<string, Details>::iterator it = contacts.find(name);
    if (it != contacts.end()) {
        contacts.erase(it);
        cout << "Contact deleted successfully." << endl;

        saveContactsToFile(contacts, filename);
    } else {
        cout << "Contact not found." << endl;
    }
}

// Function to save contacts to a file
void saveContactsToFile(const map<string, Details>& contacts, const string& filename) {
    ofstream outFile(filename);
    if (!outFile) {
        cerr << "Error opening file for writing." << endl;
        return;
    }

    map<string, Details>::const_iterator it = contacts.begin();
    while (it != contacts.end()) {
        outFile << it->first << endl;
        outFile << it->second.phoneNumber << endl;
        outFile << it->second.email << endl;
        ++it;
    }

    outFile.close();
}

// Function to load contacts from a file
void loadContactsFromFile(map<string, Details>& contacts, const string& filename) {
    ifstream inFile(filename);
    if (!inFile) {
        cerr << "Error opening file for reading." << endl;
        return;
    }

    string name;
    Details contactDetails;
    while (getline(inFile, name)) {
        getline(inFile, contactDetails.phoneNumber);
        getline(inFile, contactDetails.email);
        contacts[name] = contactDetails;
    }

    inFile.close();
}

int main() {
    map<string, Details> contacts; //map for storing all contacts
    
    const string filename = "contacts.txt"; 

    loadContactsFromFile(contacts, filename);

    int choice;

    do {
        display();  
        cin >> choice;  

        switch (choice) {
            case 1:
                addC(contacts, filename);  
                break;
            case 2:
                viewC(contacts); 
                break;
            case 3:
                editC(contacts, filename);  
                break;
            case 4:
                deleteC(contacts, filename);  
                break;
            case 5:
                
                saveContactsToFile(contacts, filename);
                cout << "Exiting the program.\n";
                break;
            default:
                cout << "Invalid option, please try again.\n";
        }
    } while (choice != 5);  

    return 0;
}
