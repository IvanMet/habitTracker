```markdown
# Habit Tracker (C Console Application)

A simple console-based habit tracker written in C that allows users to manage daily habits, track completion statistics, and save/load data to a file.

## Features

- **Add Habit**: Create new habits with name, description, category, and automatic ID assignment.
- **Remove Habit**: Delete habits by ID with confirmation prompt.
- **Mark Habit Completed**: Increment completion counters for a specific habit.
- **View Habits**: Display all habits with two sorting options:
  - By name (alphabetical)
  - By completion percentage (descending)
- **Statistics**: Shows completion percentage and total/completed days for each habit.
- **Persistent Storage**: Save and load habit data from a text file (`habits.txt`).
- **Russian Language Interface**: Fully localized for Russian users (supports Cyrillic input/output).

## Project Structure

- `C.cpp` – Main source code file containing all functionality.
- `habits.txt` – Data file created automatically when saving (not included in repo).
- Struct `Habit` – Defines habit attributes (ID, name, description, category, counters).
- Global arrays and counters for managing up to 100 habits.

## How to Compile and Run

### On Windows (using GCC/MinGW):
```bash
gcc -o HabitTracker.exe C.cpp
HabitTracker.exe
```

### On Linux/macOS:
```bash
gcc -o HabitTracker C.cpp
./HabitTracker
```

## Usage Instructions

1. **Launch the program** – You’ll see a Russian-language menu.
2. **Load existing data** – Choose option 6 to load habits from `habits.txt` (if available).
3. **Add a habit** – Choose option 1 and follow prompts.
4. **Mark a habit completed** – Choose option 3 and enter the habit ID.
5. **View habits** – Choose option 4 and select sorting preference.
6. **Save data** – Choose option 5 before exiting to save changes.
7. **Exit** – Choose option 9 to quit.

## File Format (`habits.txt`)

The file stores data in plain text:
- First line: `next_id`
- Second line: `habit_count`
- Then for each habit:
  - `id`
  - `name`
  - `description`
  - `category`
  - `completed_days`
  - `total_days`

## Limitations

- Maximum of 100 habits.
- No date tracking – only total/completed day counts.
- No editing of existing habits (only add/remove/mark).
- Console-based only, no GUI.
- Data is stored in plain text (not encrypted).

## Future Improvements

- Add habit editing functionality.
- Implement date-wise tracking (calendar view).
- Add reminders or notifications.
- Export data to CSV/JSON.
- Multi-user support with login.
- Graphical user interface (GUI).

## Author

Anonymous C developer – academic/learning project.

## License

This project is provided for educational purposes. Feel free to modify and distribute.
```
