#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include "Patient.h"
#include "TriageLogic.h"
#include "PatientManager.h"
#include "ClinicStats.h"
#include "StorageManager.h" 

using namespace std;

// The entire program uses a single global vector to store all active patients.
// This is the main data container for the entire program.
// It stores every active patient in a list called a vector.
// The program can read from it, add to it, update it, and remove from it.
vector<Patient> patients;

// the main program loop
// This controls the whole application.
// It shows the main dashboard, then lets the user choose what action to do.
int main() {
    // [INSERTED]: Load any previously saved patients from "patients_database.txt" 
    // into the vector memory right when the application boots up.
    loadPatientsFromFile();

    int choice;

    // The program keeps running until the user chooses exit.
    do {
        // Show a fresh screen and the project header.
        clearScreen();
        printHeader();

        // creates a copy and sorts the patients by deviation score for display
        // This makes the most urgent patients appear first.
        vector<Patient> sortedPatients = patients;
        sort(sortedPatients.begin(), sortedPatients.end(), comparePatients);

        cout << BOLD << "Dashboard: [ ACTIVE PATIENT TRIAGE QUEUE ] (Auto-Sorted by Age-Normal Deviation)" << RESET << "\n";

        // The traige table
        // If no patients exist, the program shows a friendly empty state.
        if (sortedPatients.empty()) {
            cout << "+-----+------------------+-----+--------+-----+-------+----------------------+--------+\n";
            cout << "| ID  | PATIENT NAME     | AGE | BP     | HR  | TEMP  | CHIEF COMPLAINT      | TRIAGE |\n";
            cout << "+-----+------------------+-----+--------+-----+-------+----------------------+--------+\n";
            cout << "|                         [!] No active patients in queue.                           |\n";
            cout << "+-----+------------------+-----+--------+-----+-------+----------------------+--------+\n";
        } else {
            cout << "+-----+------------------+-----+--------+-----+-------+----------------------+--------+\n";
            cout << "| ID  | PATIENT NAME     | AGE | BP     | HR  | TEMP  | CHIEF COMPLAINT      | TRIAGE |\n";
            cout << "+-----+------------------+-----+--------+-----+-------+----------------------+--------+\n";

            // Loop through each patient in the sorted list and print one row.
            for (const auto& p : sortedPatients) {
                // Format temperature so it looks nice in the table.
                string tempStr = to_string(p.temp).substr(0, 4) + "C";

                // Assign a simple color based on triage category.
                string coloredTriage = p.triage;
                if (p.triage.find("RED") != string::npos) coloredTriage = RED + p.triage + RESET;
                else if (p.triage.find("YEL") != string::npos) coloredTriage = YELLOW + p.triage + RESET;
                else if (p.triage.find("AMB") != string::npos) coloredTriage = AMBER + p.triage + RESET;
                else if (p.triage.find("GRN") != string::npos) coloredTriage = GREEN + p.triage + RESET;

                // Prints a table row with patient details.
                cout << "| " << left << setw(3) << p.id 
                     << " | " << setw(16) << p.name 
                     << " | " << right << setw(3) << p.age 
                     << " | " << left << setw(6) << p.bp 
                     << " | " << right << setw(3) << p.hr 
                     << " | " << left << setw(5) << tempStr 
                     << " | " << setw(20) << p.complaint 
                     << " | " << setw(15) << coloredTriage << " |\n";
            }
            cout << "+-----+------------------+-----+--------+-----+-------+----------------------+--------+\n";
        }

        // The explanation for the color codes used in the triage column.
        cout << RED << "(*RED = HIGH DEVIATION" << RESET << " | " << YELLOW << "YEL = URGENT" << RESET << " | " << AMBER << "AMB = DELAYED" << RESET << " | " << GREEN << "GRN = NEAR NORMAL)" << RESET << "\n\n";

        // Main menu options for the user to choose from.
        // This menu is the main interface for CRUD operations:
        // Create = Register patient
        // Read = View queue
        // Update = Update vitals
        // Delete = Discharge patient
        cout << CYAN << "MAIN MENU (CRUD Operations)" << RESET << "\n";
        cout << "[1] REGISTER PATIENT (Create - Age-Norm Triage)\n";
        cout << "[2] REFRESH / VIEW QUEUE DETAILS\n";
        cout << "[3] UPDATE VITALS & ACUITY (Update)\n";
        cout << "[4] DISCHARGE PATIENT (Delete)\n";
        cout << "[5] CLINIC STATISTICS\n";
        cout << "[0] EXIT\n\n";
        cout << BOLD << "ENTER CHOSEN OPTION [0-5]: " << RESET;

        // Reads the menu choice from the keyboard.
        // If the user enters invalid text, reset the input and ask again.
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            choice = -1;
        }

        // Handles the user's choice by calling the appropriate function.
        switch(choice) {
            case 1: registerPatient(); break;  // Add a new patient to the queue.
            case 2:
                {
                    // Refresh just means re-display the dashboard and pause before returning.
                    clearScreen();
                    printHeader();
                    cout << "Dashboard: Queue refreshed.\n";
                    cout << "\nPress Enter to return to Main Menu...";
                    cin.ignore();
                    cin.get();
                }
                break;
            case 3: updatePatient(); break;   // Update existing patient details.
            case 4: dischargePatient(); break; // Remove patient from active queue.
            case 5: clinicStatistics(); break; // Show summary counts.
            case 0: cout << "\n" << GREEN << "Exiting Triage System. Stay safe!" << RESET << "\n"; break;
            default:
                // If the user enters a number not on the menu, show a warning.
                cout << "\n" << RED << "Invalid option! Press Enter to try again..." << RESET;
                cin.ignore();
                cin.get();
        }
    } while (choice != 0);

    return 0;
}