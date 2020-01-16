# Arduino-Timer2
######Libreria che semplifica la configurazione del Timer2 nei dispositivi ATMEGA

La documentazione è in **italiano**

# Uso:

## Importazione
```C
  extern "C++" {
    #include "Timer2.h" //se si trova nella directory del progetto
    #include <Timer2.h> //se si trova nella directory delle librerie di Arduino
  }
```

## Dichiarazione
```C++
  #define True 1
  #define False 0
  Timer2 timer2;
```

## Abilita gli interrupts
`.enableInterrupts(byte) -> void` abilita/disabilita gli interrupts

```C++
  Timer2 t2;
  t2.enableInterrupts(True);
```

## Provenienza del clock
`.hasExternalClock(byte) -> void` imposta la sorgente del clock: 1 per esterno e 0 per interno

```C++
  Timer2 t2;
  t2.hasExternalClock(False); //usa l'oscillatore di Arduino (16 o 8MHz)
```

la funzione va a modificare un bit del registro `ASSR` in particolare `AS2`:

|  AS2  | Descrizione                          |
| :---: | ------------------------------------ |
|   0   | utilizza il clock interno di arduino |
|   1   | utilizza un clock esterno            |

## Divisione del prescaler

`.setPrescaler(byte) -> void` imposta il criterio di divisione del clock

```C++
  Timer2 t2;
  t2.setPrescaler(PRES_NULL);
```

la funzione va a modificare i bit sul registro `TCCR2B`:

|  CS22  |  CS21  |  CS20  | Costante  | Descrizione               |
| :----: | :----: | :----: | :-------: | ------------------------- |
|    0   |    0   |    0   | PRES_NULL | Nessun clock              |
|    0   |    0   |    1   | PRES_1    | Frequenza originale       |
|    0   |    1   |    0   | PRES_8    | Frequenza divisa per 8    |
|    0   |    1   |    1   | PRES_32   | Frequenza divisa per 32   |
|    1   |    0   |    0   | PRES_64   | Frequenza divisa per 64   |
|    1   |    0   |    1   | PRES_128  | Frequenza divisa per 128  |
|    1   |    1   |    0   | PRES_256  | Frequenza divisa per 256  |
|    1   |    1   |    1   | PRES_1024 | Frequenza divisa per 1024 |

## Modalità di funzionamento

`.setMode(byte) -> void` e `.setMode(byte,byte) -> void` sono due funzioni per definire la modalità di conteggio del timer2 e conseguentemente di azzerarlo

```C++
  Timer2 t2;
  t2.setMode(MODE_CTC,124); //chiama un interrupt ogni 1ms
```

la funzione modifica `TCCR2A` e `TCCR2B` per impostare la modalità e `OCR2A` per il valore da raggiungere per riazzerarsi:

| WGM22 | WGM21 | WGM20 |     Sintassi e costanti     |Descrizione|
| :---: | :---: | :---: | :-------------------------: |---|
|   0   |   0   |   0   | setMode(MODE_NORMAL)        | Il contatore si azzera a 0xFF (255) |
|   0   |   0   |   1   | setMode(MODE_PWM1)          |                                     |
|   0   |   1   |   0   | setMode(MODE_CTC,val)       | Quando il contatore raggiunge il valore contenuto in val si azzera|
|   0   |   1   |   1   | setMode(MODE_FAST_PWM1)     |                                     |
|   1   |   0   |   0   | x                           |                                     |
|   1   |   0   |   1   | setMode(MODE_PWM2,val)      |                                     |
|   1   |   1   |   0   | x                           |                                     |
|   1   |   1   |   1   | setMode(MODE_FAST_PWM2,val) |                                     |

## Output

`.setOutput(byte) -> void` imposta se il clock deve usare l'uscita 11

```C++
  Timer2 t2;
  pinMode(11,OUTPUT);
  t2.setOutput(OUT_NORMAL);
```

la funzione va a modificare `COM2A1` e `COM2A0` dentro `TCCR2A`:

| COM2A1 | COM2A0 |  Costanti  | Descrizione                                         |
| :----: | :----: | :--------: | --------------------------------------------------- |
|   0    |    0   | OUT_NORMAL | Non connesso al pin11                               |
|   0    |    1   | OUT_TOGGLE | L'uscita cambia stato al raggiungimento del massimo |
|   1    |    0   | OUT_CLEAR  | L'uscita va a 0 quando raggiunge il massimo         |
|   1    |    1   | OUT_SET    | L'uscita va a 1 quando raggiunge il massimo         |

## Routine dell'interrupt

`.useRoutine(byte) -> void` s/maschera la routine

```C++
  //test.ino
  
  Timer2 t2;
  t2.useRoutine(True);
  
  //func.ino
  ISR(TIMER2_COMPA_vect){
    /* todo */
  }
```

la funzione presente nel file func.ino viene eseguita ogni volta che il timer raggiunge il suo massimo e si riazzera
