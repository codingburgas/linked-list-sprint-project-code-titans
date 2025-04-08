[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/fMNqOIZ8)

# Historical Events Management System

A C++ project for managing historical events using linked lists.

## Project Structure

```
.
├── src/                    # Source files
│   ├── main.cpp           # Main program file
│   ├── Event.cpp          # Event class implementation
│   └── LinkedList.cpp     # LinkedList class implementation
├── include/               # Header files
│   ├── Event.h           # Event class declaration
│   └── LinkedList.h      # LinkedList class declaration
├── docs/                  # Project documentation
├── presentation/         # Project presentation files
├── HistoricalEvents.sln  # Visual Studio solution file
└── HistoricalEvents.vcxproj  # Visual Studio project file
```

## Recent Improvements

- Enhanced input validation in all user interactions
- Improved error handling for file operations
- Added clear screen functionality for better UI
- Implemented consistent title display across all screens
- Added validation for empty event titles
- Improved user feedback messages
- Added "Press Enter to continue" prompts for better user experience

## Features

1. Add new historical events with:
   - Date (year and month)
   - Title
   - Topic
   - Location
   - Leader
   - Participants
   - Result
   - Victory status
   - Access level

2. Search events by:
   - Date
   - Topic

3. Generate reports:
   - Display all events
   - Display events by topic
   - Display Bulgarian victories
   - Change sort order (ascending/descending)

4. Edit existing events
5. Delete events
6. Save data to file
7. Load data from file

## Building and Running

### Using Visual Studio
1. Open `HistoricalEvents.sln` in Visual Studio
2. Select your preferred configuration (Debug/Release) and platform (x86/x64)
3. Build and run the project (F5)

## Documentation
Project documentation can be found in the `docs` directory.

## Presentation
Project presentation materials are available in the `presentation` directory.
