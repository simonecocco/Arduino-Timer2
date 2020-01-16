/**
 * Simone Cocco - 14/01/2020
 */

#include "Timer2.h"

Timer2::Timer2() { /* todo */ }

/**
 * disabilita o abilita gli interrupts
 */
void Timer2::enableInterrupts(byte enable){
  if(enable){
    interrupts();
  }else{
    noInterrupts();
  }
}

/**
 * mi dice se il clock è interno (0)
 * o esterno (1)
 */
void Timer2::hasExternalClock(byte external){
  if(external){
    ASSR|=(1<<AS2);
  }else{
    ASSR&= ~(1<<AS2);
  }
}

/**
 * imposta di quanto deve scalare la frequenza
 */
void Timer2::setPrescaler(byte divisore){
  switch(divisore){
    case PRES_NULL:
      TCCR2B&= ~((1<<CS20)|(1<<CS21)|(1<<CS22)); //-> 0 0 0
      break;
    case PRES_1:
      TCCR2B|= (1<<CS20);
      TCCR2B&= ~((1<<CS21)|(1<<CS22)); //-> 0 0 1
      break;
    case PRES_8:
      TCCR2B|= (1<<CS21);
      TCCR2B&= ~((1<<CS20)|(1<<CS22)); //-> 0 1 0
      break;
    case PRES_32:
      TCCR2B&= ~(1<<CS22);
      TCCR2B|= ((1<<CS20)|(1<<CS21)); //-> 0 1 1
      break;
    case PRES_64:
      TCCR2B|= (1<<CS22);
      TCCR2B&= ~((1<<CS20)|(1<<CS21)); //-> 1 0 0
      break;
    case PRES_128:
      TCCR2B&= ~(1<<CS21);
      TCCR2B|= ((1<<CS20)|(1<<CS22)); //-> 1 0 1
      break;
    case PRES_256:
      TCCR2B&= ~(1<<CS20);
      TCCR2B|= ((1<<CS21)|(1<<CS22)); //-> 1 1 0
      break;
    case PRES_1024:
      TCCR2B|= ((1<<CS20)|(1<<CS21)|(1<<CS22)); //-> 1 1 1
      break;
    default:
      this->setPrescaler(PRES_NULL);
  }
}

/**
 * imposta la modalita' di funzionamento
 */
void Timer2::setMode(byte mode,byte maxVal){
  if(maxVal<0){
    this->setMode(MODE_NORMAL);
    return;
  }
  switch(mode){
    case MODE_CTC: //-> 0 1 0
      TCCR2A&= ~(1<<WGM20);
      TCCR2A|= (1<<WGM21);
      TCCR2B&= ~(1<<WGM22);
      OCR2A=maxVal;
      break;
    case MODE_PWM2: //-> 1 0 1
      TCCR2A|= (1<<WGM20);
      TCCR2A&= ~(1<<WGM21);
      TCCR2B|= (1<<WGM22);
      OCR2A=maxVal;
      break;
    case MODE_FAST_PWM2: //-> 1 1 1
      TCCR2A|= (1<<WGM20)|(1<<WGM21);
      TCCR2B|= (1<<WGM22);
      OCR2A=maxVal;
      break;
    default:
      this->setMode(MODE_NORMAL);
  }
}

/**
 * imposta la modalita' di funzionamento, senza il valore massimo
 */
void Timer2::setMode(byte mode){
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
    default:
      this->setMode(MODE_NORMAL);
  }
}

void Timer2::setOutput(byte mode){
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
    default:
      this->setOutput(OUT_NORMAL);
  }
}

/**
 * usa la routine di interrupt
 * ISR(TIMER2_COMPA_vect)
 */
void Timer2::useRoutine(byte use){
  if(use){
    TIMSK2|= (1<<OCIE2A);
  }else{
    TIMSK2&= ~(1<<OCIE2A);
  }
}
