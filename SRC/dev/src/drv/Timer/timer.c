#include "timer.h"

/// \tag::get_time[]
// Simplest form of getting 64 bit time from the timer.
// It isn't safe when called from 2 cores because of the latching
// so isn't implemented this way in the sdk
static uint64_t get_time(void) {
    // Reading low latches the high value
    uint32_t lo = timer_hw->timelr;
    uint32_t hi = timer_hw->timehr;
    return ((uint64_t) hi << 32u) | lo;
}
/// \end::get_time[]

/// \tag::alarm_standalone[]
// Use alarm 0
#define ALARM_NUM 0
#define ALARM_IRQ TIMER_IRQ_0

static void alarm_in_us(uint32_t delay_us);

// Alarm interrupt handler
static volatile bool g_timer_alarm_flg = FALSE;
// APP Set Time(us)
static uint32_t s_timer_us = 0;

// Timer ISR
__ISR static void isr_timer0_irq(void)
{
    // Clear the alarm irq
    hw_clear_bits(&timer_hw->intr, 1u << ALARM_NUM);
    printf("%dms OneShot Timer Alarm!!!\n",s_timer_us / 1000);
    g_timer_alarm_flg = TRUE;
}

static void alarm_in_us(uint32_t delay_us)
{
    // Enable the interrupt for our alarm (the timer outputs 4 alarm irqs)
    hw_set_bits(&timer_hw->inte, 1u << ALARM_NUM);
    // Set irq handler for alarm irq
    irq_set_exclusive_handler(ALARM_IRQ, isr_timer0_irq);
    // Enable the alarm irq
    irq_set_enabled(ALARM_IRQ, TRUE);
    // Enable interrupt in block and at processor

    // Alarm is only 32 bits so if trying to delay more
    // than that need to be careful and keep track of the upper
    // bits
    uint64_t target = timer_hw->timerawl + delay_us;

    // Write the lower 32 bits of the target time to the alarm which
    // will arm it
    timer_hw->alarm[ALARM_NUM] = (uint32_t) target;
}

// us Oder OneShot Timer Set
void Timer_Set_us(uint32_t ovf_us)
{
    // Set us Timer
    s_timer_us = ovf_us;
    g_timer_alarm_flg != FALSE;
}

void APP_Timer_Main(void)
{
    if(s_timer_us != 0)
    {
        // Wait for alarm to fire
        if(g_timer_alarm_flg != FALSE)
        {
            printf("%dms OneShot Timer Alarm!!!\n",s_timer_us / 1000);
            g_timer_alarm_flg = FALSE;
            // restart OneShort Timer
            alarm_in_us(s_timer_us);
            printf("OneShot Timer Start!!!\n");
        }
    }
}
