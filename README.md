[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/fMNqOIZ8)

# Historical Events Management System

This C++ application manages historical events using a doubly linked list data structure. It allows users to add, edit, delete, and search for historical events, with a focus on Bulgarian historical events.

## Features

- Add new historical events with detailed information
- Edit existing events
- Delete events
- Search events by date or topic
- Display all events
- Display events by specific topic
- Display Bulgarian victories
- Sort events by date (ascending or descending order)

## Project Structure

```
project/
├── include/           # Header files
│   ├── Event.h
│   └── LinkedList.h
├── src/              # Source files
│   ├── Event.cpp
│   ├── LinkedList.cpp
│   └── main.cpp
└── README.md
```

## How to Compile and Run

1. Make sure you have a C++ compiler installed (g++ or Visual Studio)
2. Navigate to the project directory
3. Compile all source files:
   ```
   g++ src/main.cpp src/Event.cpp src/LinkedList.cpp -o historical_events
   ```
4. Run the program:
   ```
   ./historical_events
   ```

## Data Structure

The program uses a doubly linked list to store historical events. Each event contains:
- Year and month
- Title
- Topic
- Location
- Leader
- Participants
- Result
- Victory status
- Access level

## Example Usage

1. Add a new event:
   - Choose option 1 from the menu
   - Enter the event details when prompted

2. Search for events:
   - Choose option 4 to search by date
   - Choose option 5 to search by topic

3. Generate reports:
   - Choose option 6 to see all events
   - Choose option 7 to see events by topic
   - Choose option 8 to see Bulgarian victories

4. Sort events:
   - Choose option 9 to change the sort order

## Notes

- The program automatically sorts events by date
- Events can be edited or deleted using their titles
- The access level feature allows for different levels of information access
- All data is stored in memory and will be lost when the program exits
