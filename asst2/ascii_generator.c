#include <stdio.h>

int main(){
    unsigned char c = 33;
    int i = 33, shift = 0;
    for(; i < 128; i++, c++){
        printf("%3d : %c ", i, c);
        shift++;
        if (shift == 5){
            printf("\n");
            shift = 0;
        } 
    }
}
