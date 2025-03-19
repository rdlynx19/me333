#ifndef HELPER__H__
#define HELPER__H__

#include <stdio.h>
#include "helper.h"

#define MAX_YEARS 100

typedef struct {
    double inv0;
    double growth;
    int years;
    double invarray[MAX_YEARS+1];
} Investment;

int getUserInput(Investment *invp);
void calculateGrowth(Investment *invp);
void sendOutput(double *arr, int years);

#endif