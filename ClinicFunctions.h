#ifndef CLINIC_FUNCTIONS_H
#define CLINIC_FUNCTIONS_H

#include "Patient.h"

// Declaration of helper and CRUD functions
void clearScreen();
void printHeader();
int extractSystolic(const string& bpStr);
void evaluateAgeBasedTriage(Patient& p);
bool comparePatients(const Patient& a, const Patient& b);
void registerPatient();
void updatePatient();
void dischargePatient();
void clinicStatistics();

#endif