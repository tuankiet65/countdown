#ifndef DIGIT_H
	#define DIGIT_H

	#include <Arduino.h>

	class Digit {
	private:
		const uint8_t DIGITS[17] = {
			// 0b0ABCDEFG
			   0b01111110, // 0
			   0b00110000, // 1
			   0b01101101, // 2
			   0b01111001, // 3
			   0b00110011, // 4
			   0b01011011, // 5
			   0b01011111, // 6
			   0b01110000, // 7
			   0b01111111, // 8
			   0b01111011, // 9
			   0b01110111, // 10 aka A
			   0b00011111, // 11 aka B
			   0b01001110, // 12 aka C
			   0b00111101, // 13 aka D
			   0b01001111, // 14 aka E
			   0b01000111, // 15 aka F
			   0b01001001  // 16 aka ERR
		};
		byte pins[7];
		byte current_digit;

	public:
		Digit(byte s1, byte s2, byte s3, byte s4, byte s5, byte s6, byte s7);
		void set_digit(byte digit);
		void turn_off();
		void turn_on();
	};
#endif