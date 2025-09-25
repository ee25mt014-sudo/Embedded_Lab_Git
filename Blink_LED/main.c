#include <stdint.h>
#include "tm4c123gh6pm.h"

void GPIO_INIT(void);

int main(void) {
    GPIO_INIT();

    // Configure SysTick for 0.5s delay
    NVIC_ST_RELOAD_R = 25000000 - 1;    // 0.5s delay at 50MHz
    NVIC_ST_CTRL_R = 0x05;              // Enable SysTick, use system clock

    while (1) {
        // Wait for COUNT flag
        while ((NVIC_ST_CTRL_R & (1 << 16)) == 0);

        GPIO_PORTF_DATA_R ^= 0x02;      // Toggle Red LED (PF1)
    }
}

void GPIO_INIT(void) {
    SYSCTL_RCGCGPIO_R |= 0x20;               // Enable clock to Port F
    while ((SYSCTL_PRGPIO_R & 0x20) == 0);   // Wait until Port F is ready

    GPIO_PORTF_DIR_R |= 0x02;                // PF1 (Red LED) as output
    GPIO_PORTF_DEN_R |= 0x02;                // Enable digital function on PF1
}
