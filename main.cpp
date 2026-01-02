#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <algorithm>

using namespace std;

// *********************************************************
// Program: main.cpp
// Course: CCP6114 Programming Fundamentals
// Lecture Class: TC1L
// Tutorial Class: TT2L
// Trimester: 2530
// Member_1: 252UC24259 | AYRA ADEENA BINTI AZRIN | ayra.adeena.azrin1@student.mmu.edu.my | 0192242006 
// Member_2: 252UC242PE | KADEESYA ALYA BINTI KAMARUDDIN | kadeesya.alya.kamaruddin1@student.mmu.edu.my | 0178982711
// Member_3: 252UC242RA | MUHAMMAD IRFAN ZIKRY BIN NORHESHAM | MUHAMMAD.IRFAN.ZIKRY1@student.mmu.edu.my | 0133965497
// *********************************************************
// Task Distribution
// Member_1: DATA STRUCTURES & UTILITY FUNCTIONS
// Member_2: ROW OPERATIONS & CSV VIEW MODE
// Member_3: MAIN PROGRAM & MENU
// *********************************************************

/////////////////////////////////////////////////////////////
// DATA STRUCTURES & UTILITY FUNCTIONS
/////////////////////////////////////////////////////////////

enum DataType { INT, TEXT };

struct Column {
    string name;
    DataType type;
};

vector<Column> columns;
vector<vector<string>> rows;

bool isInteger(const string& s) {
    if (s.empty()) return false;
    for (char c : s) {
        if (!isdigit(c)) return false;
    }
    return true;
}

string toLowerStr(string s) {
    for (char &c : s) c = tolower(c);
    return s;
}

string trim(const string& s) {
    size_t first = s.find_first_not_of(" \t\n\r");
    if (string::npos == first) return "";
    size_t last = s.find_last_not_of(" \t\n\r");
    return s.substr(first, (last - first + 1));
}

bool parseColumn(const string& input, Column& col) {
    size_t pos = input.find('(');
    size_t end = input.find(')');
    if (pos == string::npos || end == string::npos || end <= pos) return false;

    string typeStr = input.substr(pos + 1, end - pos - 1);
    string namePart = input.substr(0, pos);
    col.name = trim(namePart);

    if (typeStr == "INT") col.type = INT;
    else if (typeStr == "TEXT") col.type = TEXT;
    else return false;

    return true;
}

// Handles the logic for adding a new entry to the attendance sheet
void insertRow() {
    vector<string> newRow(columns.size());
    string v;

    cout << "-------------------------------------------\n";
    cout << "Insert New Attendance Row\n";
    cout << "-------------------------------------------\n";

// Loop through each defined column to get data for the new row
    for (size_t i = 0; i < columns.size(); i++) {
        string colNameLower = toLowerStr(columns[i].name);

        while (true) { // Loop until valid input is provided for the current column
            // Special validation for ID/StudentID columns (must be numbers)
            if (colNameLower == "studentid" || colNameLower == "id") {
                cout << "Enter " << columns[i].name << ": ";
                getline(cin, v);
                v = trim(v);
                if (!isInteger(v) || v.empty()) {
                    cout << "Error: Invalid INT value. Please enter a number.\n";
                    continue;
                }
            } 
             // Special validation for 'Status' (must be 0 or 1)
            else if (colNameLower == "status") {
                cout << "Enter Status (1:Present, 0:Absent) : ";
                getline(cin, v);
                v = trim(v);
                if (v != "0" && v != "1") {
                    cout << "Error: Status must be 0 or 1.\n";
                    continue;
        }
    }
        
 // Generic validation based on the data type (INT or TEXT)
            else {
                cout << "Enter " << columns[i].name << ": ";
                getline(cin, v);
                v = trim(v);
                if (columns[i].type == INT) {
                    if (!isInteger(v) || v.empty()) {
                        cout << "Error: Invalid INT value.\n";
                        continue;
                    }
                } else {
                    if (v.empty()) {
                        cout << "Error: TEXT value cannot be empty.\n";
                        continue;
                    }
                }
            }
            newRow[i] = v; // Save valid input to the row
            break; 
        }
    }
    rows.push_back(newRow); // Add the completed row to the global data storage
    cout << "Row inserted successfully.\n";
}

// Displays all data in the table in a comma-separated format
void viewSheet() {
    cout << "-------------------------------------------\n";
    cout << "View Attendance Sheet (CSV Mode)\n";
    cout << "-------------------------------------------\n";
    
    // Print column headers
    for (size_t i = 0; i < columns.size(); i++) {
        cout << columns[i].name << (i == columns.size() - 1 ? "" : ", ");
    }
    cout << endl;

    // Print each row of data
    for (const auto& row : rows) {
        for (size_t i = 0; i < row.size(); i++) {
            cout << row[i] << (i == row.size() - 1 ? "" : ", ");
        }
        cout << endl;
    }
}

/////////////////////////////////////////////////////////////
// MAIN PROGRAM & MENU
/////////////////////////////////////////////////////////////

int main() {
    string sheetName;
    int colCount;
    
    // Display
    cout << "===========================================\n";
    cout << "   STUDENT ATTENDANCE TRACKER - MILESTONE 1\n";
    cout << "===========================================\n\n";

     // Get the name of the sheet
    cout << "Enter attendance sheet name: ";
    getline(cin, sheetName);

    // Display the sheet name
    cout << "Attendance sheet \"" << sheetName << "\" created successfully.\n"; 

    // Column Setup: Ask how many columns the user wants (1-10)
    while (true) {
        cout << "Define number of columns (1-10): ";
        if (cin >> colCount && colCount >= 1 && colCount <= 10) {
            cin.ignore(); // Clear the newline character from the buffer
            break;
        } else {
            cout << "Invalid input. Please enter a number between 1 and 10.\n";
            cin.clear(); // Clear error flags
            cin.ignore(1000, '\n'); // Discard invalid input
        }
    }

     // Column Definition: Define the name and data type for each column
    for (int i = 0; i < colCount; i++) {
        Column col;
        string input;
        while (true) {
            cout << "Enter column " << i + 1 << " name with (TEXT) or (INT): ";
            getline(cin, input);
            if (!parseColumn(input, col)) {
                cout << "Error: Column must include (INT) or (TEXT).\n";
            } else {
                columns.push_back(col);
                break;
            }
        }
    }