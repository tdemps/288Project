
#include <inc/tm4c123gh6pm.h>
#include <stdint.h>


#ifndef IR_H_
#define IR_H_


void ADC_init(void);
unsigned ADC_read(void);
int ir_getDist(void);


#endif /* SERVO_H_ */
