#include "../include/Event.h"
#include <iostream>

Event::Event(int y, int m, const std::string& t, const std::string& top,
             const std::string& loc, const std::string& lead,
             const std::vector<std::string>& parts, const std::string& res,
             bool victory, int access)
    : year(y), month(m), title(t), topic(top), location(loc),
      leader(lead), participants(parts), result(res),
      isVictory(victory), accessLevel(access) {}

// Getters
int Event::getYear() const { return year; }
int Event::getMonth() const { return month; }
std::string Event::getTitle() const { return title; }
std::string Event::getTopic() const { return topic; }
std::string Event::getLocation() const { return location; }
std::string Event::getLeader() const { return leader; }
std::vector<std::string> Event::getParticipants() const { return participants; }
std::string Event::getResult() const { return result; }
bool Event::getIsVictory() const { return isVictory; }
int Event::getAccessLevel() const { return accessLevel; }

// Setters
void Event::setYear(int year) { this->year = year; }
void Event::setMonth(int month) { this->month = month; }
void Event::setTitle(const std::string& title) { this->title = title; }
void Event::setTopic(const std::string& topic) { this->topic = topic; }
void Event::setLocation(const std::string& location) { this->location = location; }
void Event::setLeader(const std::string& leader) { this->leader = leader; }
void Event::setParticipants(const std::vector<std::string>& participants) {
    this->participants = participants;
}
void Event::setResult(const std::string& result) { this->result = result; }
void Event::setIsVictory(bool isVictory) { this->isVictory = isVictory; }
void Event::setAccessLevel(int accessLevel) { this->accessLevel = accessLevel; }

void Event::displayBasicInfo() {
    std::cout << "Title: " << title << std::endl;
    std::cout << "Date: " << month << "/" << year << std::endl;
    std::cout << "Topic: " << topic << std::endl;
    std::cout << "Location: " << location << std::endl;
}

void Event::displayFullInfo() {
    displayBasicInfo();
    std::cout << "Leader: " << leader << std::endl;
    std::cout << "Participants: ";
    for (const auto& participant : participants) {
        std::cout << participant << ", ";
    }
    std::cout << std::endl;
    std::cout << "Result: " << result << std::endl;
    std::cout << "Victory: " << (isVictory ? "Yes" : "No") << std::endl;
    std::cout << "Access Level: " << accessLevel << std::endl;
} 