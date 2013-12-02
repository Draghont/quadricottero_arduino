/*

 
 */

#ifndef BRUSHLESS_h
#define BRUSHLESS_h

typedef struct{
  int temp;
  float resto; 
}
start_values;


class brushless {

public:

  brushless();
  start_values startupcalc(int temp, int MIN, float dec, float resto, int slow);
  int startup(int verbose);//MODIFICA 01/12
  int setFrequency(int val);
  int setRefreshRate(int val);
  int setDuty(int val);
  int getFrequency();
  int getRefreshRate();
  int getDuty();
  int eventHandler();
  //void iterate();

private:

  volatile unsigned int cpmCounter;
  volatile int          stato;
  volatile unsigned int frequency;//holds register value
  volatile unsigned int refreshRate;
  volatile unsigned int duty;//holds register value

  int timer1_init();
};

#endif

