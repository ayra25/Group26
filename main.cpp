#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <fstream>
#include <sstream>

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
//
// Task Distribution:
// - Ayra  : Core data structures, insert/view/update logic, Main Program & Menu
// - Kadee : Delete attendance record, File Operations
// - Irfan : Save & Exit feature, Count rows
// *********************************************************

/////////////////////////////////////////////////////////////
// DATA STRUCTURES & UTILITY FUNCTIONS
/////////////////////////////////////////////////////////////

enum DataType { INT, TEXT };

struct Column {
    string name;
    DataType type;
};

// Global containers for table structure and data
vector<Column> columns;
vector<vector<string>> rows;

// Global variables for file handling
string termName;
string sheetName;
string dataFileName;

/////////////////////////////////////////////////////////////
// UTILITY FUNCTIONS
/////////////////////////////////////////////////////////////

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

/////////////////////////////////////////////////////////////
// FILE OPERATIONS
/////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////
// CORE FEATURES (FROM MILESTONE 1, EXTENDED)
/////////////////////////////////////////////////////////////

// Insert a new attendance record
void insertRow() {
    vector<string> newRow(columns.size());
    string value;

    cout << "\n-------------------------------------------\n";
    cout << "Insert New Attendance Row\n";
    cout << "-------------------------------------------\n";

    for (size_t i = 0; i < columns.size(); i++) {
        string colNameLower = toLowerStr(columns[i].name);

        while (true) {
            cout << "Enter " << columns[i].name << ": ";
            getline(cin, value);
            value = trim(value);

            // Special validation for Status column
            if (colNameLower == "status") {
                if (value != "0" && value != "1") {
                    cout << "Error: Status must be 0 (Absent) or 1 (Present).\n";
                    continue;
                }
            }
            // Integer validation
            else if (columns[i].type == INT) {
                if (!isInteger(value)) {
                    cout << "Error: Invalid INT value.\n";
                    continue;
                }
            }
            // Text validation
            else {
                if (value.empty()) {
                    cout << "Error: TEXT value cannot be empty.\n";
                    continue;
                }
            }

            newRow[i] = value;
            break;
        }
    }

    rows.push_back(newRow);
    cout << "Row inserted successfully.\n";
}

// Display attendance sheet in CSV format
void viewSheet() {
    cout << "\n-------------------------------------------\n";
    cout << "Attendance Sheet (CSV Mode)\n";
    cout << "-------------------------------------------\n";

    // Display column headers
    for (size_t i = 0; i < columns.size(); i++) {
        cout << columns[i].name;
        if (i != columns.size() - 1) cout << ", ";
    }
    cout << endl;

    // Display records
    for (const auto& row : rows) {
        for (size_t j = 0; j < row.size(); j++) {
            cout << row[j];
            if (j != row.size() - 1) cout << ", ";
        }
        cout << endl;
    }
}

/////////////////////////////////////////////////////////////
// UPDATE ROW FEATURE
/////////////////////////////////////////////////////////////

// Update an existing attendance record
void updateRow() {
    string keyValue;
    cout << "Enter " << columns[0].name << " to update: ";
    getline(cin, keyValue);

    for (size_t i = 0; i < rows.size(); i++) {
        if (rows[i][0] == keyValue) {

            for (size_t j = 1; j < columns.size(); j++) {
                string newValue;
                cout << "Enter new value for " << columns[j].name
                     << " (leave blank to keep current): ";
                getline(cin, newValue);
                newValue = trim(newValue);

                if (!newValue.empty()) {
                    string colNameLower = toLowerStr(columns[j].name);

                    // Status validation
                    if (colNameLower == "status") {
                        if (newValue != "0" && newValue != "1") {
                            cout << "Error: Status must be 0 or 1.\n";
                            continue;
                        }
                    }
                    // Integer validation
                    else if (columns[j].type == INT && !isInteger(newValue)) {
                        cout << "Error: Invalid INT value.\n";
                        continue;
                    }

                    rows[i][j] = newValue;
                }
            }

            cout << "Row updated successfully.\n";
            return;
        }
    }

    cout << "Error: Record not found.\n";
}

/////////////////////////////////////////////////////////////
// DELETE ROW FEATURE
/////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////
// SAVE & EXIT FEATURE
/////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////
// MAIN PROGRAM
/////////////////////////////////////////////////////////////

int main() {
    cout << "===========================================\n";
    cout << "   STUDENT ATTENDANCE TRACKER - MILESTONE 2\n";
    cout << "===========================================\n\n";

    // Input term and sheet names
    cout << "Enter school term name: ";
    getline(cin, termName);

    cout << "Enter attendance sheet name: ";
    getline(cin, sheetName);

    // Generate file name
    dataFileName = termName + "_" + sheetName + ".csv";

    // Load existing data or create new sheet
    if (fileExists(dataFileName)) {
        cout << "Previous data found. Loading...\n";
        loadFromFile(dataFileName);
    } else {
        cout << "No existing data found. Creating new sheet.\n";

        int colCount;
        do {
            cout << "Define number of columns (1-10): ";
            cin >> colCount;
            cin.ignore();
        } while (colCount < 1 || colCount > 10);

        for (int i = 0; i < colCount; i++) {
            Column col;
            string input;

            while (true) {
                cout << "Enter column " << i + 1
                     << " name with (INT) or (TEXT): ";
                getline(cin, input);

                if (!parseColumn(input, col))
                    cout << "Error: Invalid column format.\n";
                else {
                    columns.push_back(col);
                    break;
                }
            }
        }
    }

    // Menu-driven program loop
    int choice;
    do {
        cout << "\n-------------------------------------------\n";
        cout << "1. Insert New Attendance Row\n";
        cout << "2. View Attendance Sheet\n";
        cout << "3. Update Attendance Row\n";
        cout << "4. Delete Attendance Row\n";
        cout << "5. Count Rows\n";
        cout << "6. Save & Exit\n";
        cout << "-------------------------------------------\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1: insertRow(); break;
        case 2: viewSheet(); break;
        case 3: updateRow(); break;
        case 4: deleteRow(); break;
        case 5: countRows(); break;
        case 6:
            saveToFile(dataFileName);
            cout << "Data saved successfully.\n";
            break;
        default:
            cout << "Invalid choice.\n";
        }
    } while (choice != 6);

    return 0;
}


