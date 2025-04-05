#ifndef EVENT_H
#define EVENT_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Event {
    int year;
    int month;
    string title;
    string topic;
    string location;
    string leader;
    vector<string> participants;
    string result;
    bool isVictory;  // For Bulgarian victories
    int accessLevel; // For access control

    // Constructor
    Event(int y, int m, const string& t, const string& top,
          const string& loc, const string& lead,
          const vector<string>& parts, const string& res,
          bool victory, int access = 1);

    // Getters
    int getYear() const;
    int getMonth() const;
    string getTitle() const;
    string getTopic() const;
    string getLocation() const;
    string getLeader() const;
    vector<string> getParticipants() const;
    string getResult() const;
    bool getIsVictory() const;
    int getAccessLevel() const;

    // Setters
    void setYear(int year);
    void setMonth(int month);
    void setTitle(const string& title);
    void setTopic(const string& topic);
    void setLocation(const string& location);
    void setLeader(const string& leader);
    void setParticipants(const vector<string>& participants);
    void setResult(const string& result);
    void setIsVictory(bool isVictory);
    void setAccessLevel(int accessLevel);

    // Display methods
    void displayBasicInfo();
    void displayFullInfo();
};

#endif // EVENT_H 