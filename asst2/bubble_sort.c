#include <stdio.h>
#include <string.h>
#define MAXLENGTH 100       // max length of string input

void getString(char *str);  // helper prototypes
void printResult(char *str);
int greaterThan(char ch1, char ch2);
void swap(char *str, int index1, int index2);

int main(void){
    int len;                // length of entered string
    char str[MAXLENGTH];    // input should be no longer than MAXLENGTH
    // here, any other variables you need


    getString(str);         // get length of the string, from string.h
    len = strlen(str);
    // put nested loops here to put the string in sorted order
    for (int i = 0; i < len; i++){
        for(int j = 0; j < len - i - 1; j++){
            if(greaterThan(str[j], str[j+1])){
                swap(str, j, j+1);
            }
        }
    }
    printResult(str);
    return(0);
}

// helper functions go here
void getString(char *str){
    printf("Enter the string you would like to sort: ");
    scanf("%s", str);
}

void printResult(char *str){
    printf("Here is the sorted string: %s\n", str);
}

int greaterThan(char ch1, char ch2){
    if((int)ch1 > (int)ch2){
        return 1;
    } 
    else {
        return 0;
    }
}

void swap(char *str, int index1, int index2){
    char temp = str[index1];
    str[index1] = str[index2];
    str[index2] = temp;
}