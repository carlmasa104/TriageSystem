#include "TriageLogic.h"
#include <cmath>

// Reads the systolic blood pressure from a string like "160/95".
// A blood pressure reading is usually written like "160/95".
// The first number is the systolic pressure and is the one we care about.
// This function takes a string such as "160/95" and returns 160.
int extractSystolic(const string& bpStr) {
    // Find the symbol that separates the two numbers.
    size_t slashPos = bpStr.find('/');

    // If the slash exists, we can take the text before it.
    if (slashPos != string::npos) {
        try {
            // Convert the part before the slash from text to integer.
            return stoi(bpStr.substr(0, slashPos));
        } catch (...) {
            // If the input is invalid, return a safe default instead of crashing.
            return 120;
        }
    }

    // If there is no slash, we assume a normal default value.
    return 120;
}

// This is the main triage logic function that calculates how urgent a patient is based on their vitals and age.
// Each age group has different normal ranges for blood pressure and heart rate.
// For example, a child and an elderly person do not have the same expected values.
// The program checks how far the patient's values are from those normal values.
void evaluateAgeBasedTriage(Patient& p) {
    // We divide the age by 10 to decide which age bracket the patient fits into.
    // Example: age 24 -> 2 -> bracket 20s.
    int bracket = p.age / 10;

    // These act as the expected values for a healthy person in this age range.
    int normalSystolic = 120;
    int normalHr = 75;
    double normalTemp = 37.0;

    // Different age groups have different "normal" ranges.
    switch (bracket) {
        case 0: normalSystolic = 95; normalHr = 100; normalTemp = 37.0; break; // 0-9 years
        case 1: normalSystolic = 110; normalHr = 80; normalTemp = 37.0; break; // 10-19 years
        case 2: normalSystolic = 115; normalHr = 75; normalTemp = 37.0; break; // 20-29 years
        case 3: normalSystolic = 120; normalHr = 75; normalTemp = 37.0; break; // 30-39 years
        case 4: normalSystolic = 125; normalHr = 78; normalTemp = 37.0; break; // 40-49 years
        case 5: normalSystolic = 130; normalHr = 80; normalTemp = 37.0; break; // 50-59 years
        default: normalSystolic = 135; normalHr = 82; normalTemp = 37.0; break; // 60+ years
    }

    // Calculate how far the patient's vitals are from the expected normal values from each age group.
    // The program measures the difference between the patient value and normal value.
    // A bigger difference means the patient is more abnormal and should be seen sooner.
    int bpDeviation = abs(p.systolicBp - normalSystolic);
    int hrDeviation = abs(p.hr - normalHr);
    int tempDeviation = static_cast<int>(abs(p.temp - normalTemp) * 10);

    // Add all three differences together.
    // This total is the patient’s overall severity score.
    p.deviationScore = bpDeviation + hrDeviation + tempDeviation;

    // Classifies the patients into triage categories based on their deviation score.
    // A high score means the patient is far from healthy and urgent.
    if (p.deviationScore >= 35) {
        p.triage = "RED (1)";   // Highest urgency: immediate attention needed.
    } else if (p.deviationScore >= 22) {
        p.triage = "YEL (2)";   // Urgent but not yet critical.
    } else if (p.deviationScore >= 12) {
        p.triage = "AMB (3)";   // Delayed, but still monitored.
    } else {
        p.triage = "GRN (4)";   // Near normal or routine care.
    }
}

// Sorts the Patients
// The dashboard needs to show the most serious patients first.
// This function is used by the sort() command in main.cpp.
bool comparePatients(const Patient& a, const Patient& b) {
    return a.deviationScore > b.deviationScore;
}