#ifndef FUNCTIONS2_H
#define FUNCTIONS2_H

#include "functions1.h"

// ─── Add New Goal ─────────────────────────────────────────────────────────────
void addGoal(Goal goals[], int &count) {
    if (count >= MAX_GOALS) {
        cout << "\n Goal limit reached!\n";
        pauseMessage();
        return;
    }

    Goal g;
    g.id             = 0; // will be set by SQLite AUTOINCREMENT
    g.totalProgress  = 0;
    g.daysCompleted  = 0;

    cout << "\nEnter goal title: ";
    getline(cin, g.title);
    g.targetHours = getIntInput("Enter weekly target hours [1-168]: ", 1, 168);

    insertGoal(g);          // <-- saves to SQLite, sets g.id
    goals[count++] = g;     // also keep in memory array

    pauseMessage("Goal added successfully!");
}

// ─── View All Goals ───────────────────────────────────────────────────────────
void viewGoals(Goal goals[], int count) {
    if (count == 0) {
        cout << "\nNo goals found.\n";
        pauseMessage();
        return;
    }

    cout << "\n=================== GOALS ===================\n";
    cout << left
         << setw(5)  << "ID"
         << setw(30) << "Title"
         << setw(15) << "Target(hrs)"
         << setw(15) << "Done(hrs)"
         << setw(8)  << "Days"
         << setw(12) << "Completion"
         << "Status\n";
    cout << string(97, '=') << "\n";

    for (int i = 0; i < count; i++) {
        float perc   = calculatePercentage(goals[i].totalProgress, goals[i].targetHours);
        string status = (goals[i].daysCompleted >= 7 || perc >= 100) ? "Complete" : "Incomplete";
        string percStr = to_string((int)perc) + " %";

        cout << left
             << setw(5)  << goals[i].id
             << setw(30) << goals[i].title
             << setw(15) << goals[i].targetHours
             << setw(15) << goals[i].totalProgress
             << setw(8)  << goals[i].daysCompleted
             << setw(12) << percStr
             << status   << "\n";
    }
    cout << string(97, '=') << "\n";
    pauseMessage();
}

// ─── Update Daily Progress ────────────────────────────────────────────────────
void updateProgress(Goal goals[], int count) {
    if (count == 0) {
        cout << "\nNo goals available.\n";
        pauseMessage();
        return;
    }

    viewGoals(goals, count);
    int choice = getIntInput("Enter goal ID to update progress: ", 1, goals[count - 1].id);

    // Find goal index by ID
    int index = -1;
    for (int i = 0; i < count; i++) {
        if (goals[i].id == choice) { index = i; break; }
    }
    if (index == -1) { cout << "Goal not found.\n"; pauseMessage(); return; }

    if (goals[index].daysCompleted >= 7) {
        cout << "\n7-day entries already completed for this goal.\n";
        pauseMessage();
        return;
    }

    int hours = getIntInput("Enter hours for today [0-24]: ", 0, 24);
    goals[index].totalProgress += hours;
    goals[index].daysCompleted++;

    updateGoalDB(goals[index]);  // <-- save to SQLite

    cout << "\nProgress updated successfully!\n";
    if (goals[index].daysCompleted >= 7)
        cout << "7 entries completed for this goal!\n";
    if (calculatePercentage(goals[index].totalProgress, goals[index].targetHours) >= 100)
        cout << "Goal Completed! Great work!\n";

    pauseMessage();
}

#endif // FUNCTIONS2_H
