#include <stdint.h>
#include "tm4c123gh6pm.h"
#include <stdint.h>
#include "tm4c123gh6pm.h"

// LED Macros
#define RED_LED    (1<<1)   // PF1


// Switch Macros
#define SW1        (1<<4)   // PF4
#define SW2        (1<<0)   // PF0

int main(void) {
    SYSCTL_RCGCGPIO_R |= (1<<5);     // Enable clock to Port F
    while((SYSCTL_PRGPIO_R & (1<<5)) == 0); // Wait for Port F ready

    GPIO_PORTF_LOCK_R = 0x4C4F434B;  // Unlock Port F
    GPIO_PORTF_CR_R |= (SW1 | SW2);  // Allow changes to PF0 and PF4
    GPIO_PORTF_DIR_R |= RED_LED;     // Set PF1 (RED) as output
    GPIO_PORTF_DIR_R &= ~(SW1 | SW2);// Set PF0, PF4 as input (switches)
    GPIO_PORTF_DEN_R |= (RED_LED | SW1 | SW2);  // Enable digital I/O

    GPIO_PORTF_PUR_R |= (SW1 | SW2); // Enable pull-up resistors on PF0, PF4

    while(1) {
        if(((GPIO_PORTF_DATA_R & SW1) == 0) || ((GPIO_PORTF_DATA_R & SW2) == 0)) {
            GPIO_PORTF_DATA_R |= RED_LED;   // Turn ON RED LED
        } else {
            GPIO_PORTF_DATA_R &= ~RED_LED;  // Turn OFF RED LED
        }
    }
}
