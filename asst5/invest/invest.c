#include <stdio.h>
#include "nu32dip.h" 
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

int main(void) {
Investment inv; 

NU32DIP_Startup();

while(getUserInput(&inv)) { 
    inv.invarray[0] = inv.inv0;
    calculateGrowth(&inv); 
    sendOutput(inv.invarray, 
                inv.years); 
}
return 0; 
} 

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
    // storing message to be displayed in a string
    sprintf(message, "Enter investment, growth rate, number of yrs (up to %d): ",MAX_YEARS); 
    // write the message to the screen
    NU32DIP_WriteUART1(message);
    NU32DIP_WriteUART1("\r\n");
    // reading the user input and storing in a string
    NU32DIP_ReadUART1(message, 200);

    // reading from the string and assigning the user entered values to the variables
    sscanf(message, "%lf %lf %d", &(invp->inv0), &(invp->growth), &(invp->years));

    valid = (invp->inv0 > 0) && (invp->growth > 0) &&
    (invp->years > 0) && (invp->years <= MAX_YEARS);
    // printing information about input to the screen
    sprintf(message, "Valid input? %d\n",valid);
    NU32DIP_WriteUART1(message);
    NU32DIP_WriteUART1("\r\n");

    if (!valid) { 
    // printing information about input to the screen
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

    sprintf(message, "\nRESULTS:\n\n"); //
    NU32DIP_WriteUART1(message);
    for (i=0; i<=yrs; i++) { 
        sprintf(outstring,"Year %3d: %10.2f\n",i,arr[i]);
        // writing the results to the screen
        NU32DIP_WriteUART1(outstring);
	NU32DIP_WriteUART1("\r\n");
    }
    NU32DIP_WriteUART1("\n");
} 
