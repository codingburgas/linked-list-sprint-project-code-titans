#include "../include/LinkedList.h"
// Small edit to test commit workflow
#include <iostream>
#include <vector>
#include <limits>
#include <fstream>
#include <string>

using namespace std;

LinkedList eventList; // Global variable for the event list

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void displayTitle() {
    ifstream titleFile("title.txt");
    if (!titleFile.is_open()) {
        // Try looking in the HistoricalEvents subdirectory
        titleFile.open("HistoricalEvents/title.txt");
    }
    
    if (titleFile.is_open()) {
        string line;
        while (getline(titleFile, line)) {
            cout << line << endl;
        }
        titleFile.close();
    } else {
        cout << "Failed to open title.txt file." << endl;
    }
}

void displayMenu() {
    clearScreen();
    displayTitle();
    
    ifstream menuFile("menu.txt");
    if (!menuFile.is_open()) {
        // Try looking in the HistoricalEvents subdirectory
        menuFile.open("HistoricalEvents/menu.txt");
    }
    
    if (menuFile.is_open()) {
        string line;
        // Read all lines directly, no need to search for MAIN MENU
        while (getline(menuFile, line)) {
            cout << line << endl;
        }
        menuFile.close();
    } else {
        cout << "Failed to open menu.txt file." << endl;
        cout << "\nMAIN MENU\n";
        cout << "1. Add new event\n";
        cout << "2. Search events\n";
        cout << "3. Generate reports\n";
        cout << "4. Edit event\n";
        cout << "5. Delete event\n";
        cout << "6. Save data to file\n";
        cout << "7. Load data from file\n";
        cout << "8. Exit\n";
    }
    cout << "Enter your choice: ";
}

void addNewEvent(LinkedList& list) {
    clearScreen();
    displayTitle();
    
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
    clearScreen();
    displayTitle();
    
    int year, month;
    
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
        cout << "Enter month (0 for all months, or 1-12): ";
        if (!(cin >> month) || month < 0 || month > 12) {
            cout << "Invalid month. Please enter 0 for all months, or a number between 1 and 12.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        break;
    } while (true);
    
    Node* result = list.searchByDate(year, month);
    if (result) {
        result->data.displayFullInfo();
    } else {
        cout << "No events found for the specified date.\n";
    }
}

void searchByTopic(LinkedList& list) {
    clearScreen();
    displayTitle();
    
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

void searchEvents() {
    clearScreen();
    displayTitle();
    
    cout << "\nSearch Options:\n";
    cout << "1. Search by date\n";
    cout << "2. Search by topic\n";
    cout << "Enter your choice: ";
    
    int searchChoice;
    cin >> searchChoice;
    
    switch (searchChoice) {
        case 1:
            searchByDate(eventList);
            break;
        case 2:
            searchByTopic(eventList);
            break;
        default:
            cout << "Invalid choice.\n";
    }
}

void generateReports() {
    clearScreen();
    displayTitle();
    
    cout << "\nReport Options:\n";
    cout << "1. Display all events\n";
    cout << "2. Display events by topic\n";
    cout << "3. Display Bulgarian victories\n";
    cout << "4. Change sort order\n";
    cout << "Enter your choice: ";
    
    int reportChoice;
    if (!(cin >> reportChoice) || reportChoice < 1 || reportChoice > 4) {
        cout << "Invalid choice. Please enter a number between 1 and 4.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }
    
    switch (reportChoice) {
        case 1:
            clearScreen();
            displayTitle();
            cout << "\nAll Events:\n";
            eventList.displayAllTitles();
            break;
        case 2: {
            clearScreen();
            displayTitle();
            string topic;
            cout << "Enter topic: ";
            cin.ignore();
            getline(cin, topic);
            cout << "\nEvents for topic '" << topic << "':\n";
            eventList.displayEventsByTopic(topic);
            break;
        }
        case 3:
            clearScreen();
            displayTitle();
            cout << "\nBulgarian Victories:\n";
            eventList.displayBulgarianVictories();
            break;
        case 4: {
            clearScreen();
            displayTitle();
            bool ascending;
            do {
                cout << "Enter sort order (1 for ascending, 0 for descending): ";
                if (!(cin >> ascending) && cin.fail()) {
                    cout << "Invalid input. Please enter 0 or 1.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    continue;
                }
                break;
            } while (true);
            eventList.setSortOrder(ascending);
            cout << "Sort order changed to " << (ascending ? "ascending" : "descending") << ".\n";
            break;
        }
    }
}

void handleUserChoice(int choice) {
    string title;
    
    switch (choice) {
        case 1:
            addNewEvent(eventList);
            break;
        case 2:
            searchEvents();
            break;
        case 3:
            generateReports();
            break;
        case 4:
            clearScreen();
            displayTitle();
            cout << "\nEnter event title to edit: ";
            cin.ignore();
            getline(cin, title);
            if (!title.empty()) {
                eventList.editEvent(title);
            } else {
                cout << "Title cannot be empty.\n";
            }
            break;
        case 5:
            clearScreen();
            displayTitle();
            cout << "\nEnter event title to delete: ";
            cin.ignore();
            getline(cin, title);
            if (!title.empty()) {
                eventList.deleteEvent(title);
            } else {
                cout << "Title cannot be empty.\n";
            }
            break;
        case 6:
            clearScreen();
            displayTitle();
            cout << "\nSaving data to file...\n";
            eventList.saveToFile("historical_events.dat");
            cout << "Data saved successfully!\n";
            break;
        case 7:
            clearScreen();
            displayTitle();
            cout << "\nLoading data from file...\n";
            eventList.loadFromFile("historical_events.dat");
            cout << "Data loaded successfully!\n";
            break;
        case 8:
            clearScreen();
            displayTitle();
            cout << "\nSaving data before exit...\n";
            eventList.saveToFile("historical_events.dat");
            cout << "Thank you for using Historical Events Management System!\n";
            break;
    }
    
    if (choice != 8) {
        cout << "\nPress Enter to continue...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
    }
}

int main() {
    // Try to load data at startup
    eventList.loadFromFile("historical_events.dat");
    
    int choice;
    do {
        displayMenu();
        cin >> choice;
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            choice = -1;
        }
        
        handleUserChoice(choice);
    } while (choice != 8);
    
    return 0;
} 