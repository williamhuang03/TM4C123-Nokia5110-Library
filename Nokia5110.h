#include <stdint.h>
#ifndef __NOKIA_5110_H__
#define __NOKIA_5110_H__

// *************************************************
// User Adjustable Parameters
// *************************************************

// *************************************************
// LCD Contrast
// Adjust LCD contrast. Choose from 0x80 to 0xFF
// *************************************************
#define LCD_CONTRAST 0xA8

// *************************************************
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// DO NOT MAKE CHANGES FROM HERE ON
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// *************************************************

#define MAX_Y 48
#define MAX_X 84

#define SSI_MODULE_0 (1U << 0)
#define GPIO_A (1U << 0)


enum PORT_A_BIT {
    PA7 = (1U << 7),
    PA6 = (1U << 6),    
    PA5 = (1U << 5),    /* AF: SSI0Tx */
    PA3 = (1U << 3),    /* AF: SSI0Fss */
    PA2 = (1U << 2),    /* AF: SSI0Clk */
};

enum LCD_PIN {
    RST = PA7,
    CE  = PA3,
    DC  = PA6,
    DIN = PA5,
    CLK = PA2
};

typedef enum {
    COMMAND = 0,
    DATA = 1
} TYPE_OF_WRITE;

enum SSI_STATUS_RESGITER {
    TFE =   (1U << 0),  // Tx FIFO Empty
    TFF =   (1U << 1),  // Tx Fifo Not Full
    BSY =   (1U << 4)   // SSI Module Busy
    
};

// *************************************************
// Initializes LCD
// Uses 24 MHz as max system clock and setting SSI clock
// to 2.67 MHz. Max SSI clock is specifed by LCD as 4 MHz
// Formula for SSI clock is: SSIClk = System Clock / 6
// Input: None
// Output: None
// Assumes: System clock is no greater than 24 MHz
// *************************************************
void Nokia5110_Init(void);

// *************************************************
// Sends instructions to LCD
// Input: TYPE_OF_WRITE (DATA or COMMAND), u8int_t data
// Output: None
// *************************************************
static void LCDWrite(TYPE_OF_WRITE type, uint8_t data);

// *************************************************
// Clears LCD screen and sets cursor bck to 0,0 position
// Input: none
// Output: none
// *************************************************
void Nokia5110_Clear(void);
void Nokia5110_SetCursor(uint8_t x_pos, uint8_t y_pos);
void OutChar(uint8_t c);

#endif
