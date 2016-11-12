//Sketch per evitare gli ostacoli e tenere informati i client in telnet circa
//dove stiamo puntando
#include <Arduino.h>

#include <ESP8266WiFi.h>

#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

#define SSID "Home"
#define PSK "annabel03"

#define HOST "192.168.0.15"
#define PORT 8267

#include <NewPing.h>

#include <../../lib/Rover.h> //Arduino IDE potrebbe non trovarla...

NewPing sonar(D10, D10, 40); //ruba tempo alla CPU
Rover car(D6,D7,D5,D8);
WiFiClient monitor;

bool frontIsClear(){
  int distanza = sonar.convert_cm(sonar.ping_median(5)); // sonar.ping_cm();
  return (distanza>40 || distanza==0); // 0 significa nessun echo
}


void setup() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID, PSK);
  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    ESP.restart();
  }
  ArduinoOTA.begin();

  int attempts = 1;
  while (!monitor.connect(HOST, PORT)){
    if (attempts>5) break;
    delay(500);
  }
}

int lefts = 0;

void loop() {
  car.pause();
  ArduinoOTA.handle();
  car.resume();
  if(frontIsClear())
    car.drive();
  else {
    car.drive(-1024,1024);
    delay(155);
    car.drive(0,0);
    delay(150);
    lefts++;
    //Sarebbe più efficiente accumulare un buffer e inviare dati a blocchi...
    if (monitor.connected()){
      monitor.write('0'+lefts);
      monitor.write('\n');
    }

  }
}
