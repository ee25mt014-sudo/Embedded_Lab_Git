#include <stdint.h>
#include "tm4c123gh6pm.h"

int main(void) {
    volatile unsigned int i;                  // Declare delay variable

    SYSCTL_RCGCGPIO_R |= 0x20;                // Enable clock to Port F
    while ((SYSCTL_PRGPIO_R & 0x20) == 0);    // Wait until Port F is ready

    GPIO_PORTF_DIR_R |= 0x08;                 // PF1 (Red LED) as output
    GPIO_PORTF_DEN_R |= 0x08;                 // Enable digital on PF1

    while (1) {
        GPIO_PORTF_DATA_R |= 0x08;            // Turn ON Red LED
        for (i = 0; i < 500000; i++);         // Delay

        GPIO_PORTF_DATA_R &= ~0x08;           // Turn OFF Red LED
        for (i = 0; i < 500000; i++);         // Delay
    }
}
