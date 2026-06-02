#ifndef FUNCTIONS3_H
#define FUNCTIONS3_H

#include "functions2.h"

// ─── Search Goals by Keyword ──────────────────────────────────────────────────
void searchGoal(Goal goals[], int count) {
    if (count == 0) {
        cout << "\nNo goals available.\n";
        pauseMessage();
        return;
    }

    string keyword;
    cout << "\nEnter keyword to search: ";
    getline(cin, keyword);

    bool found = false;
    for (int i = 0; i < count; i++) {
        if (goals[i].title.find(keyword) != string::npos) {
            if (!found) {
                cout << "\n--- Matching Goals ---\n";
                cout << left
                     << setw(5)  << "ID"
                     << setw(30) << "Title"
                     << setw(15) << "Target(hrs)"
                     << setw(15) << "Done(hrs)"
                     << setw(8)  << "Days"
                     << setw(12) << "Completion"
                     << "Status\n";
                cout << string(97, '=') << "\n";
                found = true;
            }
            float perc   = calculatePercentage(goals[i].totalProgress, goals[i].targetHours);
            string status = (goals[i].daysCompleted >= 7 || perc >= 100) ? "Complete" : "Incomplete";

            cout << left
                 << setw(5)  << goals[i].id
                 << setw(30) << goals[i].title
                 << setw(15) << goals[i].targetHours
                 << setw(15) << goals[i].totalProgress
                 << setw(8)  << goals[i].daysCompleted
                 << setw(12) << fixed << setprecision(1) << perc << "%"
                 << status   << "\n";
        }
    }

    if (!found) cout << "No matching goals found.\n";
    pauseMessage();
}

// ─── Edit Goal ────────────────────────────────────────────────────────────────
void editGoal(Goal goals[], int count) {
    if (count == 0) {
        cout << "\nNo goals to edit.\n";
        pauseMessage();
        return;
    }

    viewGoals(goals, count);
    int choice = getIntInput("Enter goal ID to edit: ", 1, goals[count - 1].id);

    int index = -1;
    for (int i = 0; i < count; i++) {
        if (goals[i].id == choice) { index = i; break; }
    }
    if (index == -1) { cout << "Goal not found.\n"; pauseMessage(); return; }

    string newTitle;
    cout << "\nEnter new title (leave blank to keep current): ";
    getline(cin, newTitle);
    if (!newTitle.empty())
        goals[index].title = newTitle;

    int newTarget = getIntInput("Enter new target hours (0 to keep same) [0-168]: ", 0, 168);
    if (newTarget != 0)
        goals[index].targetHours = newTarget;

    updateGoalDB(goals[index]);  // <-- save to SQLite
    pauseMessage("Goal updated successfully!");
}

// ─── Delete Goal ──────────────────────────────────────────────────────────────
void deleteGoal(Goal goals[], int &count) {
    if (count == 0) {
        cout << "\n No goals to delete.\n";
        pauseMessage();
        return;
    }

    viewGoals(goals, count);
    int choice = getIntInput("Enter goal ID to delete: ", 1, goals[count - 1].id);

    int index = -1;
    for (int i = 0; i < count; i++) {
        if (goals[i].id == choice) { index = i; break; }
    }
    if (index == -1) { cout << "Goal not found.\n"; pauseMessage(); return; }

    deleteGoalDB(goals[index].id);  // <-- delete from SQLite

    // Shift array
    for (int i = index; i < count - 1; i++)
        goals[i] = goals[i + 1];
    count--;

    pauseMessage("Goal deleted successfully!");
}

#endif // FUNCTIONS3_H
