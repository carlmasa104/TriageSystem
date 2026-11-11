#include "PatientManager.h"
#include "TriageLogic.h"
#include "ClinicStats.h"
#include "StorageManager.h" 
#include <iostream>
#include <algorithm>
#include <cstdlib>

using namespace std;

void printHeader();

// OPTION [1]: REGISTER A NEW PATIENT
// This is the CREATE function of the system.
// It collects patient information, calculates urgency, and stores the patient.
void registerPatient() {
    clearScreen();
    printHeader();
    cout << YELLOW << "--- [1] REGISTER PATIENT (Create) ---" << RESET << "\n";

    // Create a temporary patient record.
    Patient p;

    // Create a simple patient ID.
    // Example: first patient gets P-0101, second gets P-0102, and so on.
    p.id = "P-010" + to_string(patients.size() + 1);

    // Important: clear input buffer before reading text with getline.
    cin.ignore();
    cout << "Enter Patient Name (Last, First): ";
    getline(cin, p.name);

    cout << "Enter Age: ";
    cin >> p.age;

    cout << "Enter Blood Pressure (e.g., 160/95): ";
    cin >> p.bp;
    p.systolicBp = extractSystolic(p.bp);

    cout << "Enter Heart Rate (HR): ";
    cin >> p.hr;

    cout << "Enter Temperature (e.g., 38.5): ";
    cin >> p.temp;

    // After reading a number, we should clean the buffer before reading complaint text.
    cin.ignore();
    cout << "Enter Chief Complaint: ";
    getline(cin, p.complaint);

    // This is the heart of triage: use the values to assign a severity score and tag.
    evaluateAgeBasedTriage(p);

    // Save the patient into the global vector.
    patients.push_back(p);

    // [INSERTED]: Instantly save the updated patient list to text storage so it isn't lost.
    savePatientsToFile();

    cout << "\n" << GREEN << "[+] Patient registered! Deviation Score: " << p.deviationScore << " | Triage Assigned: " << p.triage << RESET << "\n";
    cout << "Press Enter to return to Main Menu...";
    cin.get();
}

// OPTION [3]: UPDATE AN EXISTING PATIENT'S VITALS
// This is the update function.
// It finds a patient by ID, asks for new values, then recalculates triage.
void updatePatient() {
    clearScreen();
    printHeader();
    cout << YELLOW << "--- [3] UPDATE VITALS & ACUITY (Update) ---" << RESET << "\n";

    // If there are no patients, stop early and explain the situation.
    if (patients.empty()) {
        cout << "\n" << RED << "[!] No patients available to update." << RESET << "\n\n";
        cout << "Press Enter to return to Main Menu...";
        cin.ignore();
        cin.get();
        return;
    }

    cin.ignore();
    string pid;
    cout << "Enter Patient ID to update (e.g., P-0101): ";
    getline(cin, pid);

    bool found = false;

    // Search the list for the matching patient ID.
    for (auto& p : patients) {
        if (p.id == pid) {
            found = true;
            cout << "\nUpdating record for: " << p.name << " (Age: " << p.age << ")\n";

            // Ask for each field one by one.
            // If the user enters nothing, the original value stays unchanged.
            cout << "New BP [" << p.bp << "]: ";
            string newBp;
            getline(cin, newBp);
            if (!newBp.empty()) {
                p.bp = newBp;
                p.systolicBp = extractSystolic(p.bp);
            }

            cout << "New Heart Rate [" << p.hr << "]: ";
            string newHrStr;
            getline(cin, newHrStr);
            if (!newHrStr.empty()) p.hr = stoi(newHrStr);

            cout << "New Temp [" << p.temp << "]: ";
            string newTempStr;
            getline(cin, newTempStr);
            if (!newTempStr.empty()) p.temp = stod(newTempStr);

            // Recalculate the triage after new values are entered.
            evaluateAgeBasedTriage(p);

            // [INSERTED]: Save changes to the text file immediately after updating vitals.
            savePatientsToFile();

            cout << "\n" << GREEN << "[+] Record updated! New Deviation Score: " << p.deviationScore << " | New Triage: " << p.triage << RESET << "\n";
            break;
        }
    }

    // If no patient matches, tell the user clearly.
    if (!found) {
        cout << "\n" << RED << "[!] Patient not found!" << RESET << "\n";
    }

    cout << "Press Enter to return to Main Menu...";
    cin.get();
}

// OPTION [4]: DISCHARGE A PATIENT
// This is the DELETE function.
// It removes a patient from the queue when they are no longer active.
void dischargePatient() {
    clearScreen();
    printHeader();
    cout << YELLOW << "--- [4] DISCHARGE PATIENT (Delete) ---" << RESET << "\n";

    // If the queue is empty, there is nothing to remove.
    if (patients.empty()) {
        cout << "\n" << RED << "[!] No patients in the queue to discharge." << RESET << "\n\n";
        cout << "Press Enter to return to Main Menu...";
        cin.ignore();
        cin.get();
        return;
    }

    cin.ignore();
    string pid;
    cout << "Enter Patient ID to discharge: ";
    getline(cin, pid);

    // remove_if will remove every patient whose ID matches the entered code.
    auto it = remove_if(patients.begin(), patients.end(), [&pid](const Patient& p) {
        return p.id == pid;
    });

    // If something was removed, show success.
    if (it != patients.end()) {
        patients.erase(it, patients.end());
        
        // [INSERTED]: Update the text file storage to permanently remove the discharged patient.
        savePatientsToFile();

        cout << "\n" << GREEN << "[+] Patient " << pid << " has been discharged." << RESET << "\n";
    } else {
        cout << "\n" << RED << "[!] Patient ID not found." << RESET << "\n";
    }

    cout << "Press Enter to return to Main Menu...";
    cin.get();
}