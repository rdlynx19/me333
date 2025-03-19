#include "nu32dip.h"
#include "helper.h"


void calculateGrowth(Investment *invp) {
    int i;

    for (i = 1; i <= invp->years; i= i + 1) { 

    invp->invarray[i] = invp->growth * invp->invarray[i-1];
    }
} 

int getUserInput(Investment *invp) {
    int valid; 
    char message[200];

    // Asking input from the user
    sprintf(message, "Enter investment, growth rate, number of yrs (up to %d): ",MAX_YEARS);
    NU32DIP_WriteUART1(message);
    NU32DIP_WriteUART1("\r\n");
    NU32DIP_ReadUART1(message, 200);

    sscanf(message, "%lf %lf %d", &(invp->inv0), &(invp->growth), &(invp->years));

    valid = (invp->inv0 > 0) && (invp->growth > 0) &&
    (invp->years > 0) && (invp->years <= MAX_YEARS);
    sprintf(message, "Valid input? %d\n",valid);
    NU32DIP_WriteUART1(message);
    NU32DIP_WriteUART1("\r\n");

    if (!valid) { 
    sprintf(message, "Invalid input; exiting.\n");
    NU32DIP_WriteUART1(message);
    NU32DIP_WriteUART1("\r\n");
    }
    return(valid);
} 

void sendOutput(double *arr, int yrs) {
    int i;
    char outstring[100]; 
    char message[100];

    sprintf(message, "\nRESULTS:\n\n");
    NU32DIP_WriteUART1(message);
    for (i=0; i<=yrs; i++) { 
        sprintf(outstring,"Year %3d: %10.2f\n",i,arr[i]);
        NU32DIP_WriteUART1(outstring);
	NU32DIP_WriteUART1("\r\n");
    }
    NU32DIP_WriteUART1("\n");
} 