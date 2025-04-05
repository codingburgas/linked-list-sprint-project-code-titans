#include "../include/LinkedList.h"
#include <iostream>
#include <vector>
#include <limits>

using namespace std;

void displayMenu() {
    cout << "\nHistorical Events Management System\n";
    cout << "1. Add new event\n";
    cout << "2. Edit event\n";
    cout << "3. Delete event\n";
    cout << "4. Search by date\n";
    cout << "5. Search by topic\n";
    cout << "6. Display all events\n";
    cout << "7. Display events by topic\n";
    cout << "8. Display Bulgarian victories\n";
    cout << "9. Change sort order\n";
    cout << "0. Exit\n";
    cout << "Enter your choice: ";
}

void addNewEvent(LinkedList& list) {
    int year, month, accessLevel;
    string title, topic, location, leader, result;
    bool isVictory;
    vector<string> participants;
    
    // Year validation
    do {
        cout << "Enter year (1000-9999): ";
        if (!(cin >> year) || year < 1000 || year > 9999) {
            cout << "Invalid year. Please enter a number between 1000 and 9999.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        break;
    } while (true);

    // Month validation
    do {
        cout << "Enter month (1-12): ";
        if (!(cin >> month) || month < 1 || month > 12) {
            cout << "Invalid month. Please enter a number between 1 and 12.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        break;
    } while (true);
    
    cin.ignore();
    
    // Title validation
    do {
        cout << "Enter title: ";
        getline(cin, title);
        if (title.empty()) {
            cout << "Title cannot be empty. Please try again.\n";
            continue;
        }
        break;
    } while (true);

    cout << "Enter topic: ";
    getline(cin, topic);
    cout << "Enter location: ";
    getline(cin, location);
    cout << "Enter leader: ";
    getline(cin, leader);
    
    // Participants validation
    int numParticipants;
    do {
        cout << "Enter number of participants (0-100): ";
        if (!(cin >> numParticipants) || numParticipants < 0 || numParticipants > 100) {
            cout << "Invalid number. Please enter a number between 0 and 100.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        break;
    } while (true);
    
    cin.ignore();
    
    for (int i = 0; i < numParticipants; i++) {
        string participant;
        cout << "Enter participant " << (i + 1) << ": ";
        getline(cin, participant);
        if (!participant.empty()) {
            participants.push_back(participant);
        }
    }
    
    cout << "Enter result: ";
    getline(cin, result);

    // Victory validation
    do {
        cout << "Is it a victory? (1 for yes, 0 for no): ";
        if (!(cin >> isVictory)) {
            cout << "Invalid input. Please enter 1 for yes or 0 for no.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        break;
    } while (true);

    // Access level validation
    do {
        cout << "Enter access level (1-5): ";
        if (!(cin >> accessLevel) || accessLevel < 1 || accessLevel > 5) {
            cout << "Invalid access level. Please enter a number between 1 and 5.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        break;
    } while (true);
    
    Event newEvent(year, month, title, topic, location, leader, participants, result, isVictory, accessLevel);
    list.addByDate(newEvent);
    cout << "Event added successfully!\n";
}

void searchByDate(LinkedList& list) {
    int year, month;
    cout << "Enter year: ";
    cin >> year;
    cout << "Enter month (0 for all months): ";
    cin >> month;
    
    Node* result = list.searchByDate(year, month);
    if (result) {
        result->data.displayFullInfo();
    } else {
        cout << "No events found for the specified date.\n";
    }
}

void searchByTopic(LinkedList& list) {
    string topic;
    cout << "Enter topic: ";
    cin.ignore();
    getline(cin, topic);
    
    Node* result = list.searchByTopic(topic);
    if (result) {
        result->data.displayFullInfo();
    } else {
        cout << "No events found for the specified topic.\n";
    }
}

int main() {
    LinkedList eventList;
    int choice;
    
    do {
        displayMenu();
        cin >> choice;
        
        switch (choice) {
            case 1:
                addNewEvent(eventList);
                break;
            case 2: {
                string title;
                cout << "Enter title of event to edit: ";
                cin.ignore();
                getline(cin, title);
                eventList.editEvent(title);
                break;
            }
            case 3: {
                string title;
                cout << "Enter title of event to delete: ";
                cin.ignore();
                getline(cin, title);
                eventList.deleteEvent(title);
                break;
            }
            case 4:
                searchByDate(eventList);
                break;
            case 5:
                searchByTopic(eventList);
                break;
            case 6:
                cout << "\nAll Events:\n";
                eventList.displayAllTitles();
                break;
            case 7: {
                string topic;
                cout << "Enter topic: ";
                cin.ignore();
                getline(cin, topic);
                eventList.displayEventsByTopic(topic);
                break;
            }
            case 8:
                cout << "\nBulgarian Victories:\n";
                eventList.displayBulgarianVictories();
                break;
            case 9: {
                bool ascending;
                cout << "Enter sort order (1 for ascending, 0 for descending): ";
                cin >> ascending;
                eventList.setSortOrder(ascending);
                break;
            }
            case 0:
                cout << "Exiting program...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
        
        if (choice != 0) {
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
        }
    } while (choice != 0);
    
    return 0;
} 