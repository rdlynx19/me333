#ifndef IO__H__
#define IO__H__

#include <stdio.h>
#include "nu32dip.h"
#include "investment.h"

int getUserInput(Investment *invp);
void sendOutput(double *arr, int years);

#endif