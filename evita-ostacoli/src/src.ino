//Sketch per evitare gli ostacoli

#include <Arduino.h>
#include <NewPing.h>
#include <../../lib/Rover.h> //Arduino IDE potrebbe non trovarla...

NewPing sonar(D10, D10, 50); //ruba tempo alla CPU
Rover car(D6,D7,D5,D8);

bool frontIsClear(){
  int distanza = sonar.convert_cm(sonar.ping_median()); // sonar.ping_cm();
  return (distanza>40 || distanza==0); // 0 significa nessun echo
}

void turnLeft(){
  car.drive(0,0);
  delay(300); // per fermarsi e essere certi di girare sul posto
  car.drive(-1024,1024);
  delay(164); // per girarsi di ~90°
  car.drive(0,0);
  delay(80); // per smettere di girare
}

void setup() {}

void loop() {
  if(frontIsClear())
    car.drive();
  else
    turnLeft();
}
