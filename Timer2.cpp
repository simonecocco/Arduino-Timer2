//
// Created by Simone Cocco on 10/02/2020.
//

#include "Timer2.h"

void sourceclock(char source){
    if(source) ASSR|=(1<<AS2);
    else ASSR&= ~(1<<AS2);
}

void prescalermode(char divisore){
    switch(divisore) {
        case PRES_NULL:
            TCCR2B &= ~((1 << CS20) | (1 << CS21) | (1 << CS22)); //-> 0 0 0
            break;
        case PRES_1:
            TCCR2B |= (1 << CS20);
            TCCR2B &= ~((1 << CS21) | (1 << CS22)); //-> 0 0 1
            break;
        case PRES_8:
            TCCR2B |= (1 << CS21);
            TCCR2B &= ~((1 << CS20) | (1 << CS22)); //-> 0 1 0
            break;
        case PRES_32:
            TCCR2B &= ~(1 << CS22);
            TCCR2B |= ((1 << CS20) | (1 << CS21)); //-> 0 1 1
            break;
        case PRES_64:
            TCCR2B |= (1 << CS22);
            TCCR2B &= ~((1 << CS20) | (1 << CS21)); //-> 1 0 0
            break;
        case PRES_128:
            TCCR2B &= ~(1 << CS21);
            TCCR2B |= ((1 << CS20) | (1 << CS22)); //-> 1 0 1
            break;
        case PRES_256:
            TCCR2B &= ~(1 << CS20);
            TCCR2B |= ((1 << CS21) | (1 << CS22)); //-> 1 1 0
            break;
        case PRES_1024:
            TCCR2B |= ((1 << CS20) | (1 << CS21) | (1 << CS22)); //-> 1 1 1
            break;
        default: prescalermode(PRES_NULL);
    }
}

void setmode(char mode,unsigned char value){
    if(value<0){
        setmode(MODE_NORMAL);
        return;
    }
    switch(mode){
        case MODE_CTC: //-> 0 1 0
            TCCR2A&= ~(1<<WGM20);
            TCCR2A|= (1<<WGM21);
            TCCR2B&= ~(1<<WGM22);
            OCR2A=value;
            break;
        case MODE_PWM2: //-> 1 0 1
            TCCR2A|= (1<<WGM20);
            TCCR2A&= ~(1<<WGM21);
            TCCR2B|= (1<<WGM22);
            OCR2A=value;
            break;
        case MODE_FAST_PWM2: //-> 1 1 1
            TCCR2A|= (1<<WGM20)|(1<<WGM21);
            TCCR2B|= (1<<WGM22);
            OCR2A=value;
            break;
        default: setmode(MODE_NORMAL);
    }
}

void setmode(char mode){
    switch(mode){
        case MODE_NORMAL: //-> 0 0 0
            TCCR2A&= ~((1<<WGM21)|(1<<WGM20));
            TCCR2B&= ~(1<<WGM22);
            break;
        case MODE_PWM1: //-> 0 0 1
            TCCR2A|= (1<<WGM20);
            TCCR2A&= ~(1<<WGM21);
            TCCR2B&= ~(1<<WGM22);
            break;
        case MODE_FAST_PWM1: //-> 0 1 1
            TCCR2A|= (1<<WGM20)|(1<<WGM21);
            TCCR2B&= ~(1<<WGM22);
            break;
        default: setmode(MODE_NORMAL);
    }
}

void setoutput(char mode){
    switch(mode){
        case OUT_NORMAL: //-> 0 0
            TCCR2A&= ~((1<<COM2A1)|(1<<COM2A0));
            break;
        case OUT_TOGGLE: //-> 0 1
            TCCR2A|= (1<<COM2A0);
            TCCR2A&= ~(1<<COM2A1);
            break;
        case OUT_CLEAR: //-> 1 0
            TCCR2A|= (1<<COM2A1);
            TCCR2A&= ~(1<<COM2A0);
            break;
        case OUT_SET:
            TCCR2A|= ((1<<COM2A1)|(1<<COM2A0));
            break;
        default: setoutput(OUT_NORMAL);
    }
}

void useroutine(char use){
    if(use){
        TIMSK2|= (1<<OCIE2A);
        SREG|=0B1000000;
    }else TIMSK2&= ~(1<<OCIE2A);
}