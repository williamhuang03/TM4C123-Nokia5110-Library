#include "Nokia5110.h"
#include "tm4c123gh6pm.h"

// *************************************************
// Initializes LCD
// Uses 24 MHz as max system clock and setting SSI clock
// to 2.67 MHz. Max SSI clock is specifed by LCD as 4 MHz
// Formula for SSI clock is: SSIClk = System Clock / 6
// Inputs:  None
// Outputs: None
// Assumes: System clock is no greater than 24 MHz
// *************************************************
void Nokia5110_Init(void) {
    /* LCD Init */
    volatile uint8_t delay;
    /* SSI Initialization */
    SYSCTL->RCGCSSI |= SSI_MODULE_0;    /* Use SSI Module 0 (SSI0) */
    while(!(SYSCTL->RCGCSSI & SSI_MODULE_0)); /* Wait for module to initialize */
    SYSCTL->RCGCGPIO |= GPIO_A; /* Initialize Port A as SSI0 uses port A */
    while(!(SYSCTL->RCGCGPIO & GPIO_A));    /* Wait for port A to initialize */
    GPIOA->DIR      |= PA6 | PA7;   // PA6, PA7 output
    GPIOA->AFSEL    |= PA2 | PA3 | PA5; // Alternative function select for PA2, PA3, PA5
    GPIOA->PCTL |= (2U << 8) | (2U << 12) | (2U << 20); // Select SSI alternate function for PA2, PA3, PA5
    GPIOA->DEN |= PA2 | PA3 | PA5 | PA6 | PA7;  // Configure pins as digital
    
    /* SSI Configuration */
    SSI0->CR1   &=  ~(1U << 1); // Disable SSI port for configuration
    SSI0->CR1   =   0x00000000; // Master mode 
    
    /* Configure SSI0Clk to 2.6667 MHz = 16 MHz/(2*(1+2)) */
    SSI0->CC    =   0x00;       // System clock as source (16 MHz)
    SSI0->CPSR  =   2;          // CPSR = 2
    SSI0->CR0   &=  0x00;       // Steady state low SSI0Clk when not used, data is captured on rising edge, Freescale frame format
    SSI0->CR0   =   (2U << 8);  // SCR = 2
    SSI0->CR0   |=  (0x7 << 0); // 8 bit data size
    SSI0->CR1   |=  (1U << 1);  // Enable SSI
    
    /* LCD Initialization */
    GPIOA->DATA |= RST;                     // Set reset pin to high
    GPIOA->DATA &= ~RST;                    // Set reset pin to low
    for(delay = 0; delay < 100; delay++);   // Delay for reset pulse
    GPIOA->DATA |= RST;                     // Reset pin back high
    
    LCDWrite(COMMAND, 0x21);                // Enable chip (PD=0), Horizontal addressing (V=0), Extended instructions (H=1)
    LCDWrite(COMMAND, LCD_CONTRAST);
    LCDWrite(COMMAND, 0x04);                // set temp coefficient
    LCDWrite(COMMAND, 0x14);                // LCD bias mode 1:48: try 0x13 or 0x14
    
    LCDWrite(COMMAND, 0x20);                // Switch to basic instruction set
    LCDWrite(COMMAND, DISPLAY_MODE);        // set display control to normal mode: 0x0D for inverse
    Nokia5110_Clear();
}

// *************************************************
// Sends instructions to LCD
// Inputs:  type: either DATA or COMMAND instructions
//          data: 8-bit instruction data to LCD driver
// Outputs: None
// *************************************************
static void LCDWrite(TYPE_OF_WRITE type, uint8_t data) {

    while((SSI0->SR & BSY));    // Wait for SSI0 to be not busy
    GPIOA->DATA &= ~(DC);       // Force D/C to known low state
    GPIOA->DATA |= type << 6;   
    SSI0->DR = data;
    while((SSI0->SR & BSY));
    
}

// *************************************************
// Clears LCD screen and sets cursor bck to 0,0 position
// Inputs:  none
// Outputs: none
// *************************************************
void Nokia5110_Clear(void) {
    int16_t i;
    for(i = 0; i < (MAX_X*MAX_Y/8); i++) {
        LCDWrite(DATA, 0x00);
    }
    
   Nokia5110_SetCursor(0,0);

}
// *************************************************
// Sets cursor at x_pos and y_pos
// Max x_pos is is MAX_X - 1, max y_pos is MAX_Y - 1
// Inputs:  x_pos: new x position on LCD
//          y_pos: new y position on LCD
// Outputs:
// *************************************************
void Nokia5110_SetCursor(uint8_t x_pos, uint8_t y_pos){
    if(x_pos > 83 || y_pos > 5) return; // bad inputs, do nothing and return
    LCDWrite(COMMAND, 0x80|(x_pos));    // setting bit 7 updates X-position
    LCDWrite(COMMAND, 0x40|y_pos);      // setting bit 6 updates Y-position
}

// *************************************************
// Sends a single ASCII character to the LCD screen
// ASCII font based on uint8_t ASCII variable
// Inputs:  c: ASCII character to output
// Outputs: none
// *************************************************
static void OutChar(uint8_t c) {
    uint8_t i;
    for(i = 0; i < 5; i++) {
        LCDWrite(DATA, ASCII[c - 0x20][i]);
    }
}

// *************************************************
// Write a string of ASCII characters to LCD screen
// Inputs:  *s: pointer to string of message to send
// Outputs: none
// *************************************************
void Nokia5110_Printf(uint8_t *s) {
    while(*s) {
        OutChar(*s++);
    }
}

// *************************************************
// Fills whole screen by drawing a 84x48 bitmap image
// Inputs:  *p: pointer to bitmap image of size 504 byte
// Outputs: none
// *************************************************
void Nokia5110_DrawFullMap(uint8_t *p){
    uint16_t i;
    Nokia5110_SetCursor(0,0);
    for(i=0; i < (MAX_X*MAX_Y/8); i++) {
        LCDWrite(DATA, p[i]);
    }
}
