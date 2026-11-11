#ifndef TRIAGE_LOGIC_H
#define TRIAGE_LOGIC_H

#include "Patient.h"

int extractSystolic(const string& bpStr);
void evaluateAgeBasedTriage(Patient& p);
bool comparePatients(const Patient& a, const Patient& b);

#endif