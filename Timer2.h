/**
 * Simone Cocco - 14/01/2020
 */

#include <avr/io.h>
#include <Arduino.h>

//per impostare la modalita'
#define MODE_NORMAL    0
#define MODE_PWM1      1
#define MODE_CTC       2
#define MODE_FAST_PWM1 3
#define MODE_PWM2      4
#define MODE_FAST_PWM2 5

//per impostare il prescaler
#define PRES_NULL 0
#define PRES_1    1
#define PRES_8    2
#define PRES_32   3
#define PRES_64   4
#define PRES_128  5
#define PRES_256  6
#define PRES_1024 7

//per impostare l'output
#define OUT_NORMAL 0
#define OUT_TOGGLE 1
#define OUT_CLEAR  2
#define OUT_SET    3

//Timer2.h
#ifndef TIMER_2
#define TIMER_2

class Timer2 {
  public:
    Timer2();

    /**
     * disabilita o abilita gli interrupts
     */
    void enableInterrupts(byte enable);
    /**
     * mi dice se il clock è interno (0)
     * o esterno (1)
     */
    void hasExternalClock(byte external);

    /**
     * imposta di quanto deve scalare la frequenza
     */
    void setPrescaler(byte divisore);

    /**
     * imposta la modalita' di funzionamento
     */
    void setMode(byte mode,byte maxVal);

    /**
     * imposta la modalita' di funzionamento, senza il valore massimo
     */
    void setMode(byte mode);

    /**
     * imposta la modalita' di output
     */
    void setOutput(byte mode);

    /**
     * usa la routine di interrupt
     * ISR(TIMER2_COMPA_vect)
     */
    void useRoutine(byte use);
  private:
  protected:
};

#endif
