#include "Nokia5110.h"
#include "tm4c123gh6pm.h"

// *************************************************
// Initializes LCD
// Uses 24 MHz as max system clock and setting SSI clock
// to 2.67 MHz. Max SSI clock is specifed by LCD as 4 MHz
// Formula for SSI clock is: SSIClk = System Clock / 6
// Input: None
// Output: None
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
    LCDWrite(COMMAND, 0x0C);                // set display control to normal mode: 0x0D for inverse
}

// *************************************************
// Sends instructions to LCD
// Input: TYPE_OF_WRITE (DATA or COMMAND), u8int_t data
// Output: None
// *************************************************
static void LCDWrite(TYPE_OF_WRITE type, uint8_t data) {
    while((SSI0->SR & BSY));  // Wait for SSI0 to be not busy
    GPIOA->DATA |= ((DC>>6) & type) << 6;
    SSI0->DR = data;
    while((SSI0->SR & BSY));
    
}

// *************************************************
// Clears LCD screen and sets cursor bck to 0,0 position
// Input: none
// Output: none
// *************************************************
void Nokia5110_Clear(void) {
    
}

void OutChar(uint8_t c) {
    LCDWrite(DATA, c);
}

