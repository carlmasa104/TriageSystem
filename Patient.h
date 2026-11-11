#ifndef PATIENT_H
#define PATIENT_H

#include <string>
#include <vector>

using namespace std;

// The colors used in the console output for better visibility.
// These are used to make important text stand out on screen.
// In this project they are left blank, so the app still works but without color.
// If you wanted color, each constant could be set to an ANSI escape sequence.
#define RESET   "\033[0m"
#define RED     "\033[1;31m"
#define YELLOW  "\033[1;33m"
#define GREEN   "\033[1;32m"
#define AMBER   "\033[1;35m"
#define CYAN    "\033[1;36m"
#define BOLD    "\033[1m"

// Structure
// This is a template or blueprint for one patient in the system.
// Each patient has a set of health details captured during registration.
struct Patient {
    string id;            // Example: "P-0101". A unique identifier for each patient.
    string name;          // Patient's name, for example "Dela Cruz, Ana".
    int age;              // Age in years.
    string bp;            // Blood pressure string as typed, like "160/95".
    int systolicBp;       // The top number in the BP reading, used for calculations.
    int hr;               // Heart rate, measured in beats per minute.
    double temp;          // Temperature in Celsius, for example 38.5.
    int deviationScore;    // A number that tells how far the patient is from normal values.
    string complaint;     // Main reason why the patient came to the clinic.
    string triage;        // Final category: RED, YEL, AMB, or GRN.
};

// This vector acts like a filing cabinet that all parts of the program can use.
// Every time a patient is registered, they are added here.
// Every time a patient is discharged, they are removed from here.
extern vector<Patient> patients;

#endif
