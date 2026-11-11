#include "ClinicStats.h"
#include "Patient.h"
#include <iostream>

using namespace std;


// clears the screen
// This function removes the current terminal display so the user sees a fresh page.
// It works differently depending on the operating system.
void clearScreen() {
    #ifdef _WIN32
        system("cls");   
    #else
        system("clear"); 
    #endif
}


// Shows the Program Header
// This prints the school and project title at the top of the screen.
// It makes the program look organized and professional.
void printHeader() {
    cout << CYAN << string(85, '=') << RESET << "\n";
    cout << BOLD << "WEST VISAYAS STATE UNIVERSITY - CLINIC INTAKE\n";
    cout << "COLLEGE OF INFORMATION AND COMMUNICATIONS TECHNOLOGY (CICT)\n";
    cout << "CC 202 - FINAL PROJECT: ACUITY TRIAGE SYSTEM\n" << RESET;
    cout << CYAN << string(85, '=') << RESET << "\n\n";
}

// This is Option 5 in the main menu. It shows how many patients are in each triage category.
// This screen counts how many patients are in each triage category.
// It helps staff quickly see how busy the clinic is and how critical the queue is.
void clinicStatistics() {
    clearScreen();
    printHeader();
    cout << YELLOW << "--- [5] CLINIC STATISTICS ---" << RESET << "\n";

    // Total number of active patients currently in the queue.
    int total = patients.size();

    // Count each patient according to their triage state.
    int red = 0, yel = 0, amb = 0, grn = 0;
    for (const auto& p : patients) {
        if (p.triage.find("RED") != string::npos) red++;
        else if (p.triage.find("YEL") != string::npos) yel++;
        else if (p.triage.find("AMB") != string::npos) amb++;
        else if (p.triage.find("GRN") != string::npos) grn++;
    }

    // Display the counts clearly for easy reading.
    cout << "Total Active Patients in Queue : " << total << "\n";
    cout << RED << "Critical Cases (RED)           : " << red << RESET << "\n";
    cout << YELLOW << "Urgent Cases (YEL)             : " << yel << RESET << "\n";
    cout << AMBER << "Delayed Cases (AMB)            : " << amb << RESET << "\n";
    cout << GREEN << "Routine Cases (GRN)            : " << grn << RESET << "\n\n";

    cout << "Press Enter to return to Main Menu...";
    cin.ignore();
    cin.get();
}