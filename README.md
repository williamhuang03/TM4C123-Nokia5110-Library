# TM4C123-Nokia5110-Library
TM4C123 Library for the Nokia 5110 LCD (PCD8544 LCD Driver)

Font table is 5 pixels wide, 8 pixels high. Adapted from sparkfun http://cdn.sparkfun.com/datasheets/LCD/Monochrome/Nokia_5110_Example.pde

## Functions

// ************************************************* <br>
// Initializes LCD <br>
// Uses 24 MHz as max system clock and setting SSI clock <br>
// to 2.67 MHz. Max SSI clock is specifed by LCD as 4 MHz <br>
// Formula for SSI clock is: SSIClk = System Clock / 6 <br>
// Inputs:  None <br>
// Outputs: None <br>
// Assumes: System clock is no greater than 24 MHz <br>
// ************************************************* <br>

void Nokia5110_Init(void);

// ************************************************* <br>
// Clears LCD screen and sets cursor bck to 0,0 position <br>
// Inputs:  none <br>
// Outputs: none <br>
// ************************************************* <br>
void Nokia5110_Clear(void);

// ************************************************* <br>
// Sets cursor at x_pos and y_pos <br>
// Max x_pos is is MAX_X - 1, max y_pos is MAX_Y - 1 <br>
// Inputs:  x_pos: new x position on LCD <br>
//          y_pos: new y position on LCD <br>
// Outputs: none <br>
// ************************************************* <br>
void Nokia5110_SetCursor(uint8_t x_pos, uint8_t y_pos);

// ************************************************* <br>
// Write a string of ASCII characters to LCD screen <br>
// Inputs:  *s: pointer to string of message to send <br>
// Outputs: none <br>
// ************************************************* <br>
void Nokia5110_Printf(uint8_t *s);

// ************************************************* <br>
// Fills whole screen by drawing a 84x48 bitmap image <br>
// Inputs:  *p: pointer to bitmap image of size 504 byte <br>
// Outputs: none <br>
// ************************************************* <br>
void Nokia5110_DrawFullMap(uint8_t *p);
