#include <stdint.h>
#include "tm4c123gh6pm.h"

// Macros for GPIO Port F
#define PORTF_CLOCK 0x20    // Bit 5
#define UNLOCK_KEY 0x4C4F434B
#define PORTF_PINS_ALL 0x1F    // PF0–PF4
#define PORTF_OUTPUT_PINS 0x0E    // PF1 (Red), PF2 (Blue), PF3 (Green)
#define PORTF_INPUT_PINS 0x11    // PF0 (SW2) and PF4 (SW1)

// Macros for LEDs
#define RED_LED 0x02    // PF1
#define BLUE_LED 0x04    // PF2
#define GREEN_LED 0x08    // PF3

// Macro for switch input mask
#define SWITCHES 0x11    // PF0 | PF4

// Simple delay function to debounce button press
void delay(int time) {
    volatile int i;
    for (i = 0; i < time * 10000; i++);
}

int main(void) {
    SYSCTL_RCGCGPIO_R |= PORTF_CLOCK;        // Enable clock for Port F
    GPIO_PORTF_LOCK_R = UNLOCK_KEY;          // Unlock Port F
    GPIO_PORTF_CR_R = PORTF_PINS_ALL;        // Enable changes to PF0–PF4
    GPIO_PORTF_DIR_R = PORTF_OUTPUT_PINS;    // LEDs as output; switches as input
    GPIO_PORTF_DEN_R = PORTF_PINS_ALL;       // Enable digital function for PF0–PF4
    GPIO_PORTF_PUR_R = PORTF_INPUT_PINS;     // Enable pull-up resistors on PF0 and PF4 (switches)

    int state = 2; // Initialize LED state

    while (1) {
        // Check if either button (PF0 or PF4) is pressed
        if ((GPIO_PORTF_DATA_R & SWITCHES) != SWITCHES) {
            delay(50);
            while ((GPIO_PORTF_DATA_R & SWITCHES) != SWITCHES); // Wait until both buttons released

            state = (state + 1) % 3;

            switch (state) {
                case 0:
                    GPIO_PORTF_DATA_R = RED_LED;
                    break;
                case 1:
                    GPIO_PORTF_DATA_R = GREEN_LED;
                    break;
                case 2:
                    GPIO_PORTF_DATA_R = BLUE_LED;
                    break;
            }
        }
    }
}
