#include "utility.h"

void avr_init_powersaving(){
	// Enable "Power down" sleep mode
	// SM[2:0] = 010: "Power down" sleep mode
	SMCR = _BV(SM1);

	// Disable pretty much every features (except TWI/I2C)
	PRR = _BV(PRTIM1) | _BV(PRTIM0) | _BV(PRTIM2) | _BV(PRSPI) | _BV(PRADC) | _BV(PRUSART0);
}

void avr_sleep(){
	// Disable interrupt
	cli();

	// Enable sleep
	sleep_enable();
	sleep_bod_disable();

	// Enabling interrupts before sleeping (to ensure wakeup)
	sei();

	// The actual sleep
	sleep_cpu();

	// Now the MCU is in power down mode
	// It can only be woken up by a interrupt on PCINT20 (D4)
	// connected to the SQW pin on the DS3231
	// The SQW pin is configured to generate square wave every second (1Hz)

	// When it wakes up instruction starts from here

	// After waking up, we disable sleep to ensure that no unintentional
	// sleep command can be executed
	sleep_disable();
}

void avr_init_interrupt(){
	// We need to enable interrupt on PCINT20 (aka D4)

	// put D4 to INPUT mode
	pinMode(4, INPUT);

	// Enable Pin Change Interrupt 2 (PCINT[23:16])
	PCICR = _BV(PCIE2);

	// Unmask Pin Change Interrupt on PCINT20
	PCMSK2 |= _BV(PCINT20);
}

bool avr_read_pcint20(){
	return (PIND & (1 << PIND4)) ? true : false;
}