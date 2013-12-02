
/*

 Il circuito prevede che i pin 2 3 e 4 siano collegati ai 
 pin di comando dei buffer gate il cui input e' il segnale pwm generato dal timer.
 I 3 gate vanno connessi ai mosfet nella parte superiore.
 I pin 5,6 e 7 devono essere invece collegati direttamente ai mosfet della parte inferiore.
 
 
 */
#include <Arduino.h>
#include "brushless.h"

#ifndef F_CPU
#define F_CPU 8000000.0
#endif

#define NUM_STATES 6
//#define DEBUG

byte states[NUM_STATES] = {
  B01000100,
  B10000100,
  B10001000,
  B00101000,
  B00110000,
  B01010000};

brushless::brushless(){

  //  Serial.print("Entering constructor for: ");
  //  Serial.println(__FUNCTION__);

  DDRD       |= B11111100;  // set pin [2,7] as output
  PORTD       = states[0];  // set up first state on pins 2,6

  frequency   = 800;
  duty        = 50;
  refreshRate = 100;

  cpmCounter  = 0;
  stato       = 0;

  timer1_init();

}

int brushless::timer1_init(){

  pinMode(10,OUTPUT);
  /*
    Prescaler is configged like this:
   
   (1 << CS10): divide by 1, 64, 1024
   (1 << WGM13): 16 bit Phase+Frequency correct, TOP =ICR1
   (1 << COM1B1): non-inverting, and inverting?????
   */

  TCCR1B = (1 << CS10) | (1 << WGM13);
  TCCR1A = (1 << COM1B1);

  TIMSK1 = _BV(OCIE1B);  //signal handler association

  ICR1   = frequency;
  setDuty(duty); 
}

//MODIFICA 01/12
start_values brushless::startupcalc(int temp, int MIN, float dec, float resto, int slow)
{ 
  start_values ritorno;
  int delta= temp - MIN;
  float minus = delta * dec;
  if (minus >= 1)
  {
    temp = temp - floor (minus);
  }
  else
  {
    if (slow == 1)
    {
      resto = resto + minus;
      if (resto >=1)
      {
        temp = temp -floor (resto);
        resto = resto - floor (resto);
      }

    }
    else if ( slow == 0 )
    {
      temp = temp-1;
    }

  }
  ritorno.temp=temp;
  ritorno.resto= resto;
  return ritorno;
}
int brushless::startup(int verbose){ 
  Serial.println("Init. startup");

  int MAX_f = 900;
  int MIN_f = 320;
  float dec_f = 0.1;
  start_values ritorno_f;
  ritorno_f.temp=MAX_f;
  ritorno_f.resto=0;

  int MAX_d = 90;
  int MIN_d = 65;
  float dec_d = 0.1;
  start_values ritorno_d;
  ritorno_d.temp=MAX_d;
  ritorno_d.resto=0;

  int MAX_r = 120;
  int MIN_r = 30;
  float dec_r = 0.1;
  start_values ritorno_r;
  ritorno_r.temp=MAX_r;
  ritorno_r.resto=0;

  int  delta_f;
  int  delta_d;
  int  delta_r;
  float minus_f;
  float minus_d;
  float minus_r;

  while ((ritorno_f.temp > MIN_f) || (ritorno_d.temp > MIN_d)||(ritorno_r.temp > MIN_r))
  {

    if (ritorno_f.temp > MIN_f)
    {
      ritorno_f = this -> startupcalc(ritorno_f.temp, MIN_f, dec_f , ritorno_f.resto, 1);
      ICR1 = ritorno_f.temp;
      setDuty(ritorno_d.temp);
    }

    if (ritorno_d.temp > MIN_d )
    {
      ritorno_d = this -> startupcalc(ritorno_d.temp, MIN_d, dec_d, ritorno_d.resto, 1);
      setDuty(ritorno_d.temp);
    }

    if (ritorno_r.temp > MIN_r )
    {
      ritorno_r = this -> startupcalc(ritorno_r.temp, MIN_r, dec_r, ritorno_r.resto, 1);
      setRefreshRate(ritorno_r.temp);
    }
    if (verbose == 1)  
    {
      Serial.print(ritorno_f.temp );
      Serial.print(",");
      Serial.print(ritorno_d.temp );
      Serial.print(",");
      Serial.println(ritorno_r.temp );
    }
    delay(100);
  }
  //FINE MODIFICA funzioni startup 01/12 

  Serial.println("End startup");
}

int brushless::getFrequency(){ 
  return ICR1;//MODIFICA 01/12
}

int brushless::getDuty(){ 
  int duty = OCR1B;//MODIFICA 01/12
  int freq = ICR1;
  float perc = ((float)duty / (float)freq)*100;
  return perc;//MODIFICA 01/12
}
int brushless::getRefreshRate(){ 
  return refreshRate;
}

int brushless::setFrequency(int val){
  /*
   in questo punto sarebbe bello determinare un range di 
   valori utili e mapparlo su una scala di valori semplici tipo 0 - 100
   
   per ora passiamo tutto
   */


  int diff = val - frequency;

  //    Serial.print(__FUNCTION__);
  //    Serial.print(" :diff is:");
  //    Serial.println(diff);

  if(diff == 0){
    Serial.print("setFrequency exit: same value ");
    Serial.println(frequency);
    return frequency;
  }
  if(diff > 0){
    for(int i=0;i<diff;i++){
      ICR1      = ++frequency;
      setDuty(duty);
      //    Serial.println(frequency);
    }  
  }
  if(diff < 0){
    for(int i=diff;i<0;i++){
      ICR1      = --frequency;
      setDuty(duty);
      //    Serial.println(frequency);
    }  
  }

  //ICR1      = val;
  //frequency = val;

  //setDuty(duty);
  return ICR1;
}

int brushless::setDuty(int val){

  if(val < 0 || val >= 100) return -1;
  duty  = map(val,0,100,0,ICR1);
  OCR1B = duty; 
  return duty;
}

int brushless::setRefreshRate(int val){

  /*
  necessaria un analisi sperimentale di questo valore
   */


  int diff = val - refreshRate;

  if(diff == 0){
    Serial.print("setRefreshRate exit: same value ");
    Serial.println(refreshRate);
    return 0;
  }

  if(diff > 0){
    for(int i=0;i<diff;i++){
      refreshRate = ++refreshRate;
      //      Serial.println(refreshRate);
    }  
  }
  if(diff < 0){
    for(int i=diff;i<0;i++){
      refreshRate = --refreshRate;
      //      Serial.println(refreshRate);
    }  
  }
  return 0;
}


int brushless::eventHandler(){

  cpmCounter++;

  if(cpmCounter >= refreshRate){

    // iterazione attraverso gli stati dell'automa
    stato      = ++stato % NUM_STATES;
    PORTD      = states[stato];

    cpmCounter = 0;  
  }
}








