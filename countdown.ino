#include <util/delay.h>
#include <RTClib.h>

#include "digit.h"
#include "utility.h"

#define SECONDS_PER_DAY 86400L

Digit d1(13, A0, A1, A2, A3, 3, 2);
Digit d2(12, 11, 10, 9, 8, 7, 6);

RTC_DS3231 rtc;
const DateTime target_dt(2017, 05, 24);

bool enable_msg, is_high;
int msg_ptr, count;

char msg[9][35] = {
    "", // empty message on the final day
    "Good luck and see you soon",
    "Plz let me know if you enjoy it",
    "Thanks for joining this game",
    "https://fb.me/tuankiet65",
    "https://tuankiet65.moe",
    "A product made by Ho Tuan Kiet",
    "You found the easter egg",
    "Congratulation for decoding this",
};

void setup(){
    d1.turn_off();
    d2.turn_off();

    avr_init_powersaving();
    avr_init_interrupt();

    rtc.begin();
    rtc.writeSqwPinMode(DS3231_SquareWave1Hz);
}

void loop(){
    if (!is_high){
        return;
    }

    DateTime dt = rtc.now();
    int32_t seconds_left = (target_dt - dt).totalseconds();
    if (seconds_left < 0){
        seconds_left = 0;
    }
    int32_t days_left = seconds_left / SECONDS_PER_DAY;
    if (seconds_left % SECONDS_PER_DAY != 0L){
        days_left++;
    } 


    if (enable_msg){
        if (msg_ptr >= strlen(msg[days_left])){
            enable_msg = false;
        } else if (count < 2){
            count++;
        } else {
            d1.turn_off();
            d2.turn_off();

            _delay_ms(200);

            d1.set_digit((uint8_t)msg[days_left][msg_ptr] / 16);
            d2.set_digit((uint8_t)msg[days_left][msg_ptr] % 16);

            msg_ptr++;

            count = 0;
        }
    } else {
        d1.set_digit(days_left / 10);
        d2.set_digit(days_left % 10);

        if (days_left == 0){
            d1.turn_off();
            d2.turn_off();

            _delay_ms(200);

            d1.turn_on();
            d2.turn_on();
        } else {
            if ((dt.minute() == 0 && dt.hour() != 0) || (dt.hour() == 0 && dt.minute() == 15)){
                enable_msg = true;
                msg_ptr = 0;
                count = 0;
            }
        }
    }

    avr_sleep();
}

ISR(PCINT2_vect){
    is_high = avr_read_pcint20();
}
