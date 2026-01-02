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