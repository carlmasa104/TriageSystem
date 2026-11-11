#include "StorageManager.h"
#include "TriageLogic.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

// Saves the current active patient list into a text file on your computer
void savePatientsToFile() {
    ofstream outFile("patients_database.txt");
    
    if (!outFile.is_open()) {
        cout << "[!] Error: Could not open file for saving.\n";
        return;
    }

    // Loop through every patient and write their attributes to the text file
    for (const auto& p : patients) {
        outFile << p.id << "|" 
                << p.name << "|" 
                << p.age << "|" 
                << p.bp << "|" 
                << p.hr << "|" 
                << p.temp << "|" 
                << p.complaint << "\n";
    }
    
    outFile.close();
}

// Loads saved patient records from the text file into the program when it starts
void loadPatientsFromFile() {
    ifstream inFile("patients_database.txt");
    
    if (!inFile.is_open()) {
        // If the file doesn't exist yet (first time running), just return silently
        return; 
    }

    patients.clear(); // Clear current memory list before loading
    string line;

    while (getline(inFile, line)) {
        stringstream ss(line);
        string segment;
        Patient p;

        // Parse line segments separated by the '|' character
        getline(ss, p.id, '|');
        getline(ss, p.name, '|');
        
        getline(ss, segment, '|');
        p.age = stoi(segment);
        
        getline(ss, p.bp, '|');
        p.systolicBp = extractSystolic(p.bp);
        
        getline(ss, segment, '|');
        p.hr = stoi(segment);
        
        getline(ss, segment, '|');
        p.temp = stod(segment);
        
        getline(ss, p.complaint, '|');

        // Re-calculate their triage score based on their age and vitals
        evaluateAgeBasedTriage(p);

        // Add them back into the active vector queue
        patients.push_back(p);
    }

    inFile.close();
}