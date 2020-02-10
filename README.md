# Arduino-Timer2
######Libreria che semplifica la configurazione del Timer2 nei dispositivi ATMEGA

### La documentazione è in italiano

# Uso:

### Importazione
###### Dopo aver installato la libreria in zip è possibile utilizzarla importandola
* Sintassi
```c
#include <Timer2.h>
```
***

### Provenienza del clock
###### Il segnale di clock può provenire dall'esterno o dall'interno
* Sintassi
```c
void sourceclock(char source);
```
Costante|Valore|Descrizione
---|:---:|---
CLOCK_INTERNAL|0|Utilizza il clock predefinito
CLOCK_EXTERNAL|1|Utilizza un segnale esterno
* Codice
```c
sourceclock(CLOCK_INTERNAL);
```
***

### Divisione del prescaler
###### Indica quanto deve dividere la frequenza
* Sintassi
```c
void prescalermode(char divisore);
```
Costante|Valore|Fattore di divisione
---|:---:|:---:
PRES_NULL|0|Nulla
PRES_1|1|x1
PRES_8|2|x8
PRES_32|3|x32
PRES_64|4|x64
PRES_128|5|x128
PRES_256|6|x256
PRES_1024|7|x1024
* Codice
```c
prescalermode(PRES_128);
```
***

### Modalità di funzionamento
* Sintassi
```c
void setmode(char mode,unsigned char value);
void setmode(char mode);
```
Costante|Valore|Codice|Descrizione
---|:---:|---|---
MODE_NORMAL|0|`setmode(MODE_NORMAL)`|Il contatore si azzera una volta arrivato a 255
MODE_PWM1|1|`setmode(MODE_PWM1)`|
MODE_CTC|2|`setmode(MODE_CTC,x)`|Quando il valore del contatore raggiunge il valore di x, questo si azzera
MODE_FAST_PWM1|3|`setmode(MODE_FAST_PWM1)`|
MODE_PWM2|4|`setmode(MODE_PWM2,x)`|
MODE_FAST_PWM2|5|`setmode(MODE_FAST_PWM2,x)`|
***

### Output
###### Comportamento dei pin collegati all'interrupt
* Sintassi
```c
void setoutput(char mode);
```
Costante|Valore|Descrizione
---|:---:|---
OUT_NORMAL|0|Non connesso al pin11
OUT_TOGGLE|1|L'uscita cambia stato ogni volta
OUT_CLEAR|2|L'uscita va a 0 quando raggiunge il massimo
OUT_SET|3|L'uscita va a 1 quando raggiunge il massimo
* Codice
```c
setoutput(OUT_NORMAL);
```
***

### Routine dell'interrupt
###### Per attivare la routine che verrà chiamata ogni volta che il contatore raggiunge il massimo
* Sintassi
```c
void useroutine(char use);
```
* Codice `main.ino`
```C++
#include <Timer2.h>

void setup(){
    useroutine(True);
}
```
`timerroutine.ino`
```c
ISR(TIMER2_COMPA_vect){
    //some code
}
```
