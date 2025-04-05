#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include <string>
#include "Event.h"

using namespace std;

struct Node {
    Event data;
    Node* next;
    Node* prev;
    
    Node(const Event& event) : data(event), next(nullptr), prev(nullptr) {}
};

struct LinkedList {
    Node* head;
    Node* tail;
    int size;
    bool ascendingOrder; // true for ascending, false for descending

    // Constructor and Destructor
    LinkedList();
    ~LinkedList();

    // Basic operations
    void addFirst(const Event& event);
    void addAtBeginning(const Event& event);
    void addAtEnd(const Event& event);
    void addByDate(const Event& event);
    void deleteEvent(const string& title);
    void editEvent(const string& title);
    
    // Search operations
    Node* searchByDate(int year, int month = 0);
    Node* searchByTopic(const string& topic);
    
    // Report generation
    void displayAllTitles();
    void displayEventsByTopic(const string& topic);
    void displayBulgarianVictories();
    
    // Sorting
    void setSortOrder(bool ascending);
    void sortByDate();
    
    // Utility
    bool isEmpty();
    int getSize();
    void clear();

private:
    void insertSorted(Node* newNode);
    void deleteNode(Node* node);
};

#endif // LINKEDLIST_H 