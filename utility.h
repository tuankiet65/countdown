#ifndef UTILITY_H
	#define UTILITY_H
	
	#include <Arduino.h>
	#include <avr/sleep.h>

	void avr_init_powersaving();
	void avr_sleep();
	void avr_init_interrupt();
	bool avr_read_pcint20();

#endif