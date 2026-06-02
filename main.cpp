#include "functions3.h"

// Global database pointer (declared in database.h as extern)
sqlite3* db = nullptr;

int main() {
    // Initialize SQLite database
    if (!initDatabase()) {
        cerr << "Failed to initialize database. Exiting.\n";
        return 1;
    }

    Goal goals[MAX_GOALS];
    int goalCount = 0;
    loadGoals(goals, goalCount);   // load from SQLite on startup

    int choice;
    do {
        clearScreen();
        cout << "================ Productivity Tracker ================\n";
        cout << "1. Add Goal\n";
        cout << "2. Update Daily Progress\n";
        cout << "3. View All Goals\n";
        cout << "4. Search Goal\n";
        cout << "5. Edit Goal\n";
        cout << "6. Delete Goal\n";
        cout << "7. Exit\n";
        cout << "======================================================\n";

        choice = getIntInput("Enter your choice [1-7]: ", 1, 7);

        switch (choice) {
            case 1: addGoal(goals, goalCount);        break;
            case 2: updateProgress(goals, goalCount); break;
            case 3: viewGoals(goals, goalCount);      break;
            case 4: searchGoal(goals, goalCount);     break;
            case 5: editGoal(goals, goalCount);       break;
            case 6: deleteGoal(goals, goalCount);     break;
        }
    } while (choice != 7);

    cout << "\nExiting program. Goodbye!\n";
    closeDatabase();
    return 0;
}
