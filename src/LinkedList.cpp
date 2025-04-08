#include "../include/LinkedList.h"
#include <iostream>
#include <fstream>

using namespace std;

LinkedList::LinkedList() : head(nullptr), tail(nullptr), size(0), ascendingOrder(true) {}

LinkedList::~LinkedList() {
    clear();
}

void LinkedList::addFirst(const Event& event) {
    Node* newNode = new Node(event);
    head = tail = newNode;
    size = 1;
}

void LinkedList::addAtBeginning(const Event& event) {
    if (isEmpty()) {
        addFirst(event);
        return;
    }
    
    Node* newNode = new Node(event);
    newNode->next = head;
    head->prev = newNode;
    head = newNode;
    size++;
}

void LinkedList::addAtEnd(const Event& event) {
    if (isEmpty()) {
        addFirst(event);
        return;
    }
    
    Node* newNode = new Node(event);
    tail->next = newNode;
    newNode->prev = tail;
    tail = newNode;
    size++;
}

void LinkedList::addByDate(const Event& event) {
    if (isEmpty()) {
        addFirst(event);
        return;
    }
    
    Node* newNode = new Node(event);
    insertSorted(newNode);
    size++;
}

void LinkedList::insertSorted(Node* newNode) {
    if (!newNode) return;

    // If list is empty
    if (!head) {
        head = tail = newNode;
        newNode->next = newNode->prev = nullptr;
        return;
    }

    Node* current = head;
    
    while (current) {
        bool shouldInsert = ascendingOrder ?
            (newNode->data.year < current->data.year ||
             (newNode->data.year == current->data.year &&
              newNode->data.month < current->data.month)) :
            (newNode->data.year > current->data.year ||
             (newNode->data.year == current->data.year &&
              newNode->data.month > current->data.month));
              
        if (shouldInsert) {
            newNode->next = current;
            newNode->prev = current->prev;
            if (current->prev) {
                current->prev->next = newNode;
            } else {
                head = newNode;
            }
            current->prev = newNode;
            return;
        }
        
        if (!current->next) {
            current->next = newNode;
            newNode->prev = current;
            newNode->next = nullptr;
            tail = newNode;
            return;
        }
        
        current = current->next;
    }
}

void LinkedList::deleteEvent(const  string& title) {
    Node* current = head;
    while (current) {
        if (current->data.title == title) {
            deleteNode(current);
            return;
        }
        current = current->next;
    }
    cout << "Event not found!" << endl;
}

void LinkedList::deleteNode(Node* node) {
    if (node->prev) {
        node->prev->next = node->next;
    } else {
        head = node->next;
    }
    
    if (node->next) {
        node->next->prev = node->prev;
    } else {
        tail = node->prev;
    }
    
    delete node;
    size--;
}

void LinkedList::editEvent(const string& title) {
    Node* current = head;
    while (current) {
        if (current->data.title == title) {
            int year, month;
            string newTitle, topic, location, leader, result;
            bool isVictory;
            int accessLevel;
            vector<string> participants;
            
            cout << "Enter new year: ";
            cin >> year;
            cout << "Enter new month: ";
            cin >> month;
            cin.ignore();
            
            cout << "Enter new title: ";
            getline(cin, newTitle);
            cout << "Enter new topic: ";
            getline(cin, topic);
            cout << "Enter new location: ";
            getline(cin, location);
            cout << "Enter new leader: ";
            getline(cin, leader);
            
            cout << "Enter number of participants: ";
            int numParticipants;
            cin >> numParticipants;
            cin.ignore();
            
            for (int i = 0; i < numParticipants; i++) {
                string participant;
                cout << "Enter participant " << (i + 1) << ": ";
                getline(cin, participant);
                participants.push_back(participant);
            }
            
            cout << "Enter new result: ";
            getline(cin, result);
            cout << "Is it a victory? (1/0): ";
            cin >> isVictory;
            cout << "Enter access level: ";
            cin >> accessLevel;
            
            current->data = Event(year, month, newTitle, topic, location, leader,
                                participants, result, isVictory, accessLevel);
            return;
        }
        current = current->next;
    }
    cout << "Event not found!" << endl;
}

Node* LinkedList::searchByDate(int year, int month) {
    Node* current = head;
    while (current) {
        if (current->data.year == year && 
            (month == 0 || current->data.month == month)) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

Node* LinkedList::searchByTopic(const string& topic) {
    Node* current = head;
    while (current) {
        if (current->data.topic == topic) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

void LinkedList::displayAllTitles() {
    Node* current = head;
    while (current) {
        cout << current->data.title << endl;
        current = current->next;
    }
}

void LinkedList::displayEventsByTopic(const string& topic) {
    Node* current = head;
    while (current) {
        if (current->data.topic == topic) {
            current->data.displayBasicInfo();
            cout << endl;
        }
        current = current->next;
    }
}

void LinkedList::displayBulgarianVictories() {
    Node* current = head;
    while (current) {
        if (current->data.isVictory) {
            current->data.displayBasicInfo();
            cout << endl;
        }
        current = current->next;
    }
}

void LinkedList::setSortOrder(bool ascending) {
    if (ascendingOrder != ascending) {
        ascendingOrder = ascending;
        sortByDate();
    }
}

void LinkedList::sortByDate() {
    if (size <= 1) return;
    
    vector<Event> events;
    Node* current = head;
    
    // Store all events
    while (current) {
        events.push_back(current->data);
        current = current->next;
    }
    
    // Clear the list
    clear();
    
    // Re-add events in sorted order
    for (const Event& event : events) {
        addByDate(event);
    }
}

bool LinkedList::isEmpty() {
    return size == 0;
}

int LinkedList::getSize() {
    return size;
}

void LinkedList::clear() {
    while (head) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    tail = nullptr;
    size = 0;
}

bool LinkedList::saveToFile(const string& filename) {
    ofstream file(filename, ios::binary);
    if (!file) {
        cout << "Error: Could not open file for writing." << endl;
        return false;
    }

    Node* current = head;
    while (current != nullptr) {
        // Write year and month
        file.write(reinterpret_cast<char*>(&current->data.year), sizeof(int));
        file.write(reinterpret_cast<char*>(&current->data.month), sizeof(int));
        
        // Write strings
        int length;
        
        // Write title
        length = current->data.title.length();
        file.write(reinterpret_cast<char*>(&length), sizeof(int));
        file.write(current->data.title.c_str(), length);
        
        // Write topic
        length = current->data.topic.length();
        file.write(reinterpret_cast<char*>(&length), sizeof(int));
        file.write(current->data.topic.c_str(), length);
        
        // Write location
        length = current->data.location.length();
        file.write(reinterpret_cast<char*>(&length), sizeof(int));
        file.write(current->data.location.c_str(), length);
        
        // Write leader
        length = current->data.leader.length();
        file.write(reinterpret_cast<char*>(&length), sizeof(int));
        file.write(current->data.leader.c_str(), length);
        
        // Write participants
        int participantsCount = current->data.participants.size();
        file.write(reinterpret_cast<char*>(&participantsCount), sizeof(int));
        for (const string& participant : current->data.participants) {
            length = participant.length();
            file.write(reinterpret_cast<char*>(&length), sizeof(int));
            file.write(participant.c_str(), length);
        }
        
        // Write result
        length = current->data.result.length();
        file.write(reinterpret_cast<char*>(&length), sizeof(int));
        file.write(current->data.result.c_str(), length);
        
        // Write isVictory and accessLevel
        file.write(reinterpret_cast<char*>(&current->data.isVictory), sizeof(bool));
        file.write(reinterpret_cast<char*>(&current->data.accessLevel), sizeof(int));
        
        current = current->next;
    }
    
    file.close();
    cout << "Data saved successfully to " << filename << endl;
    return true;
}

bool LinkedList::loadFromFile(const string& filename) {
    ifstream file(filename, ios::binary);
    if (!file) {
        cout << "Error: Could not open file for reading." << endl;
        return false;
    }
    
    // Clear existing list
    clear();
    
    while (file.peek() != EOF) {
        int year, month, length, accessLevel;
        string title, topic, location, leader, result;
        vector<string> participants;
        bool isVictory;
        
        // Read year and month
        file.read(reinterpret_cast<char*>(&year), sizeof(int));
        file.read(reinterpret_cast<char*>(&month), sizeof(int));
        
        // Read title
        file.read(reinterpret_cast<char*>(&length), sizeof(int));
        char* buffer = new char[length + 1];
        file.read(buffer, length);
        buffer[length] = '\0';
        title = string(buffer);
        delete[] buffer;
        
        // Read topic
        file.read(reinterpret_cast<char*>(&length), sizeof(int));
        buffer = new char[length + 1];
        file.read(buffer, length);
        buffer[length] = '\0';
        topic = string(buffer);
        delete[] buffer;
        
        // Read location
        file.read(reinterpret_cast<char*>(&length), sizeof(int));
        buffer = new char[length + 1];
        file.read(buffer, length);
        buffer[length] = '\0';
        location = string(buffer);
        delete[] buffer;
        
        // Read leader
        file.read(reinterpret_cast<char*>(&length), sizeof(int));
        buffer = new char[length + 1];
        file.read(buffer, length);
        buffer[length] = '\0';
        leader = string(buffer);
        delete[] buffer;
        
        // Read participants
        int participantsCount;
        file.read(reinterpret_cast<char*>(&participantsCount), sizeof(int));
        for (int i = 0; i < participantsCount; i++) {
            file.read(reinterpret_cast<char*>(&length), sizeof(int));
            buffer = new char[length + 1];
            file.read(buffer, length);
            buffer[length] = '\0';
            participants.push_back(string(buffer));
            delete[] buffer;
        }
        
        // Read result
        file.read(reinterpret_cast<char*>(&length), sizeof(int));
        buffer = new char[length + 1];
        file.read(buffer, length);
        buffer[length] = '\0';
        result = string(buffer);
        delete[] buffer;
        
        // Read isVictory and accessLevel
        file.read(reinterpret_cast<char*>(&isVictory), sizeof(bool));
        file.read(reinterpret_cast<char*>(&accessLevel), sizeof(int));
        
        // Create and add new event
        Event event(year, month, title, topic, location, leader, participants, result, isVictory, accessLevel);
        addByDate(event);
    }
    
    file.close();
    cout << "Data loaded successfully from " << filename << endl;
    return true;
} 