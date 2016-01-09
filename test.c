#include "tm4c123gh6pm.h"
#include "Nokia5110.h"

// *****************************************************
// Launchpad to Nokia 5110 LCD Pin Setup
// Use SSI0 module (Port A)
//  TI Pin  (Type)    Nokia 5110 Pin Pin #
//  PA7     (GPIO)        RST           1
//  PA3     (SSI0Fss)     CE            2
//  PA6     (GPIO)        DC            3
//  PA5     (SSI0Tx)      Din           4
//  PA2     (SSI0Clk)     CLK           5
//  -       ()            BL            7
//  +3.3V   ()            VCC           6
//  GND     ()            GND           8
// *****************************************************




int main(void) {
    
    Nokia5110_Init();
    OutChar(0x7F);   //0x14, 0x08, 0x3e, 0x08, 0x14
    OutChar(0x08);
    OutChar(0x08);
    OutChar(0x08);
    OutChar(0x7F);
    OutChar(0x00);
    OutChar(0x7F);   //0x14, 0x08, 0x3e, 0x08, 0x14
    OutChar(0x08);
    OutChar(0x08);
    OutChar(0x08);
    OutChar(0x7F);
    OutChar(0x00);
    
    
    
    for(;;) {
        
    }
    return 0;
}

