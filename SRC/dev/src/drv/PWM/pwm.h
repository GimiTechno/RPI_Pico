#ifndef __PWM_H__
#define __PWM_H__

#include "hardware/irq.h"
#include "hardware/pwm.h"

#include "../../drv/common.h"

void isr_pwm(void);
void PWM_Init(void);

#endif /* __PWM_H__ */