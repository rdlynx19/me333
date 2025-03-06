#include "nu32dip.h"
#include "encoder.h"


void delay(int ms)
{     
    int cycles = NU32DIP_SYS_FREQ/2000;
    cycles = cycles*ms;
    _CP0_SET_COUNT(0);
    while (_CP0_GET_COUNT() < cycles) {}
}

int main()
{
    UART2_Startup();
    NU32DIP_Startup();
    delay(1000);
    WriteUART2("b");
    
    while(1)
    {
        WriteUART2("a");
        while (!get_encoder_flag()) {};
        set_encoder_flag(0);
        char m[50];
        float p = get_encoder_count();
        sprintf(m, "Encoder Angle: %.2f[deg]\r\n", p);
        NU32DIP_WriteUART1(m);

        delay(1000);
    }

    return 0;
}
