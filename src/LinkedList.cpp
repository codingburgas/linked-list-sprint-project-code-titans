#include "../include/LinkedList.h"
#include <iostream>

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
        current = current->next;
    }
    
    addAtEnd(newNode->data);
    delete newNode;
}

void LinkedList::deleteEvent(const std::string& title) {
    Node* current = head;
    while (current) {
        if (current->data.title == title) {
            deleteNode(current);
            return;
        }
        current = current->next;
    }
    std::cout << "Event not found!" << std::endl;
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

void LinkedList::editEvent(const std::string& title) {
    Node* current = head;
    while (current) {
        if (current->data.title == title) {
            int year, month;
            std::string newTitle, topic, location, leader, result;
            bool isVictory;
            int accessLevel;
            std::vector<std::string> participants;
            
            std::cout << "Enter new year: ";
            std::cin >> year;
            std::cout << "Enter new month: ";
            std::cin >> month;
            std::cin.ignore();
            
            std::cout << "Enter new title: ";
            std::getline(std::cin, newTitle);
            std::cout << "Enter new topic: ";
            std::getline(std::cin, topic);
            std::cout << "Enter new location: ";
            std::getline(std::cin, location);
            std::cout << "Enter new leader: ";
            std::getline(std::cin, leader);
            
            std::cout << "Enter number of participants: ";
            int numParticipants;
            std::cin >> numParticipants;
            std::cin.ignore();
            
            for (int i = 0; i < numParticipants; i++) {
                std::string participant;
                std::cout << "Enter participant " << (i + 1) << ": ";
                std::getline(std::cin, participant);
                participants.push_back(participant);
            }
            
            std::cout << "Enter new result: ";
            std::getline(std::cin, result);
            std::cout << "Is it a victory? (1/0): ";
            std::cin >> isVictory;
            std::cout << "Enter access level: ";
            std::cin >> accessLevel;
            
            current->data = Event(year, month, newTitle, topic, location, leader,
                                participants, result, isVictory, accessLevel);
            return;
        }
        current = current->next;
    }
    std::cout << "Event not found!" << std::endl;
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

Node* LinkedList::searchByTopic(const std::string& topic) {
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
        std::cout << current->data.title << std::endl;
        current = current->next;
    }
}

void LinkedList::displayEventsByTopic(const std::string& topic) {
    Node* current = head;
    while (current) {
        if (current->data.topic == topic) {
            current->data.displayBasicInfo();
            std::cout << std::endl;
        }
        current = current->next;
    }
}

void LinkedList::displayBulgarianVictories() {
    Node* current = head;
    while (current) {
        if (current->data.isVictory) {
            current->data.displayBasicInfo();
            std::cout << std::endl;
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
    
    LinkedList tempList;
    tempList.ascendingOrder = ascendingOrder;
    
    Node* current = head;
    while (current) {
        Node* next = current->next;
        current->next = current->prev = nullptr;
        tempList.insertSorted(current);
        current = next;
    }
    
    head = tempList.head;
    tail = tempList.tail;
    tempList.head = tempList.tail = nullptr;
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