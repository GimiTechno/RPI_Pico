#ifndef __PWM_H__
#define __PWM_H__

// SDK
#include "hardware/irq.h"
#include "hardware/pwm.h"

// APP
#include "../../drv/common.h"

void isr_pwm(void);
void PWM_Init(void);

#endif /* __PWM_H__ */