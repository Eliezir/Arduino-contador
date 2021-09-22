
#include <IRremote.h>
#include <MD_MAX72xx.h>
#include <MD_Parola.h>
#define MAX_DEVICES 3
#define HARDWARE_TYPE MD_MAX72XX::PAROLA_HW
#define PIN_RECEIVER 2
#define SPEED_TIME 55
#define CLK_PIN    13 
#define DATA_PIN   11 
#define CS_PIN     10 
MD_Parola mx = MD_Parola(MD_MAX72XX::PAROLA_HW, CS_PIN, MAX_DEVICES);
IRrecv receiver(PIN_RECEIVER);

int num1 = 0; // numero printado display
boolean ligado = false; // on-off

void setup() {
  receiver.enableIRIn();
  mx.begin();}

void loop(){
  if (receiver.decode()) {
      receptor();
    receiver.resume();}}

void receptor(){  
  switch (receiver.decodedIRData.command) {
      case 152: // menos
      if(num1 > 0){
      num1 -= 1;
      mx.print(num1);}
      break;
      case 2: // mais
      if (ligado == true){
      num1 += 1;
      mx.print(num1);}
      break;
    case 162: //power
      if(ligado == false){ 
        ligado = true;
        mx.displayAnimate();
        mx.displayText("0", PA_CENTER, mx.getSpeed(), mx.getPause(), PA_NO_EFFECT, PA_NO_EFFECT); 
        mx.print(num1);}
      else{ 
        mx.displayClear();
        num1 = 0;
        ligado = false;}
    break;}
}
