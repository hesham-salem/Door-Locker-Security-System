/*
 * actuators.h
 *
 *  Created on: Jun 23, 2021
 *      Author: hesham
 */

#ifndef ACTUATORS_H_
#define ACTUATORS_H_
#include "timer.h"

//timer configuration
		TIMER_configurationType timer_config;
		uint8 buzzer_flag;
	  uint8 block_buzzer_scope;

	void timer_set(void);
void change_motor_dirction(void);
	void motor_run(void);
	void buzzer_call(void);
	void buzzer(void);


#endif /* ACTUATORS_H_ */
