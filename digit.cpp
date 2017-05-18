#include "digit.h"

Digit::Digit(byte s1, byte s2, byte s3, byte s4, byte s5, byte s6, byte s7){
	pins[0] = s1;
	pins[1] = s2;
	pins[2] = s3;
	pins[3] = s4;
	pins[4] = s5;
	pins[5] = s6;
	pins[6] = s7;

	byte i;
	for (i = 0; i < 7; i++){
		pinMode(pins[i], OUTPUT);
	}
}

void Digit::set_digit(byte digit){
	if (digit < 0 || digit > 15){
		digit = 16;
	}

	current_digit = digit;

	byte i;
	for (i = 0; i < 7; i++){
		digitalWrite(pins[i], ((DIGITS[digit] & (1 << (6-i))) > 0) ? LOW : HIGH);
	}
}

void Digit::turn_off(){
	byte i;
	for (i = 0; i < 7; i++){
		digitalWrite(pins[i], HIGH);
	}
}

void Digit::turn_on(){
	set_digit(current_digit);
}
