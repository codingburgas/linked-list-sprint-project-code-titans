#include "../include/Event.h"
#include <iostream>

using namespace std;

Event::Event(int y, int m, const string& t, const string& top,
             const string& loc, const string& lead,
             const vector<string>& parts, const string& res,
             bool victory, int access)
    : year(y), month(m), title(t), topic(top), location(loc),
      leader(lead), participants(parts), result(res),
      isVictory(victory), accessLevel(access) {}

// Getters
int Event::getYear() const { return year; }
int Event::getMonth() const { return month; }
string Event::getTitle() const { return title; }
string Event::getTopic() const { return topic; }
string Event::getLocation() const { return location; }
string Event::getLeader() const { return leader; }
vector<string> Event::getParticipants() const { return participants; }
string Event::getResult() const { return result; }
bool Event::getIsVictory() const { return isVictory; }
int Event::getAccessLevel() const { return accessLevel; }

// Setters
void Event::setYear(int year) { this->year = year; }
void Event::setMonth(int month) { this->month = month; }
void Event::setTitle(const string& title) { this->title = title; }
void Event::setTopic(const string& topic) { this->topic = topic; }
void Event::setLocation(const string& location) { this->location = location; }
void Event::setLeader(const string& leader) { this->leader = leader; }
void Event::setParticipants(const vector<string>& participants) {
    this->participants = participants;
}
void Event::setResult(const string& result) { this->result = result; }
void Event::setIsVictory(bool isVictory) { this->isVictory = isVictory; }
void Event::setAccessLevel(int accessLevel) { this->accessLevel = accessLevel; }

void Event::displayBasicInfo() {
    cout << "Title: " << title << endl;
    cout << "Date: " << month << "/" << year << endl;
    cout << "Topic: " << topic << endl;
    cout << "Location: " << location << endl;
}

void Event::displayFullInfo() {
    displayBasicInfo();
    cout << "Leader: " << leader << endl;
    cout << "Participants: ";
    for (const auto& participant : participants) {
        cout << participant << ", ";
    }
    cout << endl;
    cout << "Result: " << result << endl;
    cout << "Victory: " << (isVictory ? "Yes" : "No") << endl;
    cout << "Access Level: " << accessLevel << endl;
} 