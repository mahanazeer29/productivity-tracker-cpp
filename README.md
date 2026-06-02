Productivity Tracker 📋
A console-based Goal & Productivity Tracking System built in C++ with SQLite database integration. Track your weekly goals, log daily progress, and monitor your completion percentage — all from the terminal.

v1 used file handling (goals.txt)  |  v2 upgraded to a proper SQLite database for persistent, reliable storage.


✨ Features

➕ Add Goals — Set a goal title and weekly target hours
📊 Track Daily Progress — Log hours worked each day (up to 7 days)
👁️ View All Goals — See completion %, days logged, and status at a glance
🔍 Search Goals — Find goals instantly by keyword
✏️ Edit Goals — Update title or target hours anytime
🗑️ Delete Goals — Remove goals you no longer need
💾 Persistent Storage — All data saved in SQLite (productivity.db)


🖥️ Demo
================ Productivity Tracker ================
1. Add Goal
2. Update Daily Progress
3. View All Goals
4. Search Goal
5. Edit Goal
6. Delete Goal
7. Exit
======================================================

ID    Title                          Target(hrs)    Done(hrs)   Days    Completion  Status
=================================================================================================
1     Learn Data Structures          20             14          5       70 %        Incomplete
2     Complete OOP Assignments       10             10          7       100 %       Complete

🗂️ Project Structure
productivity-tracker-cpp/
├── main.cpp          # Entry point & main menu loop
├── database.h        # SQLite initialization, open & close
├── functions1.h      # Goal struct, DB CRUD helpers, utility functions
├── functions2.h      # Add goal, View goals, Update daily progress
├── functions3.h      # Search, Edit, Delete goal
├── Makefile          # Build script
└── README.md

🛠️ Tech Stack
ComponentDetailLanguageC++ 17DatabaseSQLite3 (embedded)Build Toolg++ / MakefileIDEVS CodePlatformWindows / Linux / macOS

⚙️ Setup & Installation
Prerequisites

VS Code
MSYS2 (for g++ and SQLite on Windows)
C/C++ Extension by Microsoft (VS Code)


🪟 Windows (VS Code + MSYS2)
Step 1 — Install MSYS2
Download and install from msys2.org
Step 2 — Install g++ and SQLite
Open MSYS2 UCRT64 terminal and run:
bashpacman -S mingw-w64-ucrt-x86_64-gcc
pacman -S mingw-w64-ucrt-x86_64-sqlite3
Step 3 — Add to PATH
Add this to your System Environment Variables → Path:
C:\msys64\ucrt64\bin
Step 4 — Clone & Run
bashgit clone https://github.com/mahanazeer29/productivity-tracker-cpp.git
cd productivity-tracker-cpp
g++ -std=c++17 -Wall main.cpp -o productivity_tracker -lsqlite3 -LC:/msys64/ucrt64/lib -IC:/msys64/ucrt64/include
.\productivity_tracker.exe

🐧 Linux / macOS
bash# Install SQLite
sudo apt install libsqlite3-dev      # Ubuntu/Debian
brew install sqlite3                  # macOS

# Clone & Build
git clone https://github.com/mahanazeer29/productivity-tracker-cpp.git
cd productivity-tracker-cpp
make
./productivity_tracker

🗄️ Database Schema
SQLite automatically creates productivity.db on first run — no manual setup needed.
Table: goals
ColumnTypeDescriptionidINTEGER PKAuto-increment primary keytitleTEXTGoal nametarget_hoursINTEGERWeekly target hourstotal_progressINTEGERTotal hours logged so fardays_completedINTEGERNumber of days logged (max 7)
