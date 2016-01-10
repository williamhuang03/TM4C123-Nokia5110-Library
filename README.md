# TM4C123-Nokia5110-Library
TM4C123 Library for the Nokia 5110 LCD (PCD8544 LCD Driver)

Font table is 5 pixels wide, 8 pixels high. Adapted from sparkfun http://cdn.sparkfun.com/datasheets/LCD/Monochrome/Nokia_5110_Example.pde

## Functions


Initializes LCD
Uses 24 MHz as max system clock and setting SSI clock
to 2.67 MHz. Max SSI clock is specifed by LCD as 4 MHz
Formula for SSI clock is: SSIClk = System Clock / 6
Inputs:  None
Outputs: None
Assumes: System clock is no greater than 24 MHz

void Nokia5110_Init(void);

// *************************************************
// Clears LCD screen and sets cursor bck to 0,0 position
// Inputs:  none
// Outputs: none
// *************************************************
void Nokia5110_Clear(void);

// *************************************************
// Sets cursor at x_pos and y_pos
// Max x_pos is is MAX_X - 1, max y_pos is MAX_Y - 1
// Inputs:  x_pos: new x position on LCD
//          y_pos: new y position on LCD
// Outputs: none
// *************************************************
void Nokia5110_SetCursor(uint8_t x_pos, uint8_t y_pos);

// *************************************************
// Write a string of ASCII characters to LCD screen
// Inputs:  *s: pointer to string of message to send
// Outputs: none
// *************************************************
void Nokia5110_Printf(uint8_t *s);

// *************************************************
// Fills whole screen by drawing a 84x48 bitmap image
// Inputs:  *p: pointer to bitmap image of size 504 byte
// Outputs: none
// *************************************************
void Nokia5110_DrawFullMap(uint8_t *p);
