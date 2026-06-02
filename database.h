#ifndef DATABASE_H
#define DATABASE_H

#include <sqlite3.h>
#include <iostream>
#include <string>
using namespace std;

// SQLite database pointer (global)
extern sqlite3* db;

// Open/create database and initialize tables
bool initDatabase() {
    int rc = sqlite3_open("productivity.db", &db);
    if (rc != SQLITE_OK) {
        cerr << "Cannot open database: " << sqlite3_errmsg(db) << endl;
        return false;
    }

    // Create goals table if it doesn't exist
    const char* createTable = 
        "CREATE TABLE IF NOT EXISTS goals ("
        "id            INTEGER PRIMARY KEY AUTOINCREMENT,"
        "title         TEXT    NOT NULL,"
        "target_hours  INTEGER NOT NULL,"
        "total_progress INTEGER DEFAULT 0,"
        "days_completed INTEGER DEFAULT 0"
        ");";

    char* errMsg = nullptr;
    rc = sqlite3_exec(db, createTable, nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        cerr << "SQL error: " << errMsg << endl;
        sqlite3_free(errMsg);
        return false;
    }
    return true;
}

// Close database connection
void closeDatabase() {
    if (db) {
        sqlite3_close(db);
        db = nullptr;
    }
}

#endif // DATABASE_H
