#ifndef FUNCTIONS1_H
#define FUNCTIONS1_H

#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <sqlite3.h>
#include "database.h"

using namespace std;

// ─── Goal Struct (same as before) ────────────────────────────────────────────
struct Goal {
    int    id;
    string title;
    int    targetHours;
    int    totalProgress;
    int    daysCompleted;
};

const int MAX_GOALS = 100;  // max goals we hold in memory at once

// ─── Utility Functions ────────────────────────────────────────────────────────

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pauseMessage(string message = "") {
    if (!message.empty())
        cout << "\n" << message << endl;
    cout << "Press Enter to continue...";
    cin.ignore();
    cin.get();
}

float calculatePercentage(int totalProgress, int targetHours) {
    if (targetHours == 0) return 0;
    float percent = (float)totalProgress / targetHours * 100;
    if (percent > 100) percent = 100;
    return percent;
}

int getIntInput(string prompt, int min, int max) {
    int input;
    while (true) {
        cout << prompt;
        if (cin >> input) {
            if (input >= min && input <= max) {
                cin.ignore();
                return input;
            } else {
                cout << "Please enter a number between " << min << " and " << max << ".\n";
            }
        } else {
            cout << "Invalid input! Please enter an integer.\n";
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }
}

// ─── SQLite: Load all goals into array ───────────────────────────────────────
void loadGoals(Goal goals[], int &count) {
    count = 0;
    const char* sql = "SELECT id, title, target_hours, total_progress, days_completed FROM goals ORDER BY id;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << "Failed to load goals: " << sqlite3_errmsg(db) << endl;
        return;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW && count < MAX_GOALS) {
        goals[count].id            = sqlite3_column_int(stmt, 0);
        goals[count].title         = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        goals[count].targetHours   = sqlite3_column_int(stmt, 2);
        goals[count].totalProgress = sqlite3_column_int(stmt, 3);
        goals[count].daysCompleted = sqlite3_column_int(stmt, 4);
        count++;
    }
    sqlite3_finalize(stmt);
}

// ─── SQLite: Save ONE goal (INSERT) ──────────────────────────────────────────
void insertGoal(Goal &g) {
    const char* sql = "INSERT INTO goals (title, target_hours, total_progress, days_completed) VALUES (?, ?, ?, ?);";
    sqlite3_stmt* stmt;

    sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    sqlite3_bind_text(stmt, 1, g.title.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int (stmt, 2, g.targetHours);
    sqlite3_bind_int (stmt, 3, g.totalProgress);
    sqlite3_bind_int (stmt, 4, g.daysCompleted);

    if (sqlite3_step(stmt) != SQLITE_DONE)
        cerr << "Insert error: " << sqlite3_errmsg(db) << endl;
    else
        g.id = (int)sqlite3_last_insert_rowid(db);

    sqlite3_finalize(stmt);
}

// ─── SQLite: Update one goal by ID ───────────────────────────────────────────
void updateGoalDB(const Goal &g) {
    const char* sql = "UPDATE goals SET title=?, target_hours=?, total_progress=?, days_completed=? WHERE id=?;";
    sqlite3_stmt* stmt;

    sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    sqlite3_bind_text(stmt, 1, g.title.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int (stmt, 2, g.targetHours);
    sqlite3_bind_int (stmt, 3, g.totalProgress);
    sqlite3_bind_int (stmt, 4, g.daysCompleted);
    sqlite3_bind_int (stmt, 5, g.id);

    if (sqlite3_step(stmt) != SQLITE_DONE)
        cerr << "Update error: " << sqlite3_errmsg(db) << endl;

    sqlite3_finalize(stmt);
}

// ─── SQLite: Delete goal by ID ───────────────────────────────────────────────
void deleteGoalDB(int id) {
    const char* sql = "DELETE FROM goals WHERE id=?;";
    sqlite3_stmt* stmt;

    sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    sqlite3_bind_int(stmt, 1, id);

    if (sqlite3_step(stmt) != SQLITE_DONE)
        cerr << "Delete error: " << sqlite3_errmsg(db) << endl;

    sqlite3_finalize(stmt);
}

#endif // FUNCTIONS1_H
