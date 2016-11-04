#ifndef __ROVER__
#define __ROVER__

#include <Arduino.h>

class Rover{

  int fl_, fr_, rl_, rr_; //pins
  int L_, R_; //duty cycles stored for pausing and resuming

  public:

  Rover(int fl, int fr, int rl, int rr):
  fl_(fl), fr_(fr), rl_(rl), rr_(rr) {
    pinMode(fl_, OUTPUT);
    analogWrite(fl_, LOW);
    pinMode(fr_, OUTPUT);
    analogWrite(fr_, LOW);
    pinMode(rl_, OUTPUT);
    analogWrite(rl_, LOW);
    pinMode(rr_, OUTPUT);
    analogWrite(rr_, LOW);
  }

  void drive(int L=PWMRANGE, int R=PWMRANGE){
    if (L<0) {
      analogWrite(fl_, LOW);
      analogWrite(rl_, -L);
    } else {
      analogWrite(rl_, LOW);
      analogWrite(fl_, L);
    }
    if (R<0) {
      analogWrite(fr_, LOW);
      analogWrite(rr_, -R);
    } else {
      analogWrite(rr_, LOW);
      analogWrite(fr_, R);
    }
    L_=L;
    R_=R;
  }

  void pause(){
    analogWrite(fl_, 0);
    analogWrite(fr_, 0);
    analogWrite(rl_, 0);
    analogWrite(rr_, 0);
  }

  void resume(){
    drive(L_, R_);
  }
};


#endif
