#include "init.h"

//  Desplegar número en display 7 segmentos
void desplegarNumero(uint8_t numero){
    switch (numero)
    {
    case 0:
        digitalWrite(dA, HIGH);
        digitalWrite(dB, HIGH);
        digitalWrite(dC, HIGH);
        digitalWrite(dD, HIGH);
        digitalWrite(dE, HIGH);
        digitalWrite(dF, HIGH);
        digitalWrite(dG, LOW);
        break;
    case 1:
        digitalWrite(dA, LOW);
        digitalWrite(dB, HIGH);
        digitalWrite(dC, HIGH);
        digitalWrite(dD, LOW);
        digitalWrite(dE, LOW);
        digitalWrite(dF, LOW);
        digitalWrite(dG, LOW);
        break;
    case 2:
        digitalWrite(dA, HIGH);
        digitalWrite(dB, HIGH);
        digitalWrite(dC, LOW);
        digitalWrite(dD, HIGH);
        digitalWrite(dE, HIGH);
        digitalWrite(dF, LOW);
        digitalWrite(dG, HIGH);
        break;
    case 3:
        digitalWrite(dA, HIGH);
        digitalWrite(dB, HIGH);
        digitalWrite(dC, HIGH);
        digitalWrite(dD, HIGH);
        digitalWrite(dE, LOW);
        digitalWrite(dF, LOW);
        digitalWrite(dG, HIGH);
        break;
    case 4:
        digitalWrite(dA, LOW);
        digitalWrite(dB, HIGH);
        digitalWrite(dC, HIGH);
        digitalWrite(dD, LOW);
        digitalWrite(dE, LOW);
        digitalWrite(dF, HIGH);
        digitalWrite(dG, HIGH);
        break;
    case 5:
        digitalWrite(dA, HIGH);
        digitalWrite(dB, LOW);
        digitalWrite(dC, HIGH);
        digitalWrite(dD, HIGH);
        digitalWrite(dE, LOW);
        digitalWrite(dF, HIGH);
        digitalWrite(dG, HIGH);
        break;
    case 6:
        digitalWrite(dA, HIGH);
        digitalWrite(dB, LOW);
        digitalWrite(dC, HIGH);
        digitalWrite(dD, HIGH);
        digitalWrite(dE, HIGH);
        digitalWrite(dF, HIGH);
        digitalWrite(dG, HIGH);
        break;
    case 7:
        digitalWrite(dA, HIGH);
        digitalWrite(dB, HIGH);
        digitalWrite(dC, HIGH);
        digitalWrite(dD, LOW);
        digitalWrite(dE, LOW);
        digitalWrite(dF, LOW);
        digitalWrite(dG, LOW);
        break;
    case 8:
        digitalWrite(dA, HIGH);
        digitalWrite(dB, HIGH);
        digitalWrite(dC, HIGH);
        digitalWrite(dD, HIGH);
        digitalWrite(dE, HIGH);
        digitalWrite(dF, HIGH);
        digitalWrite(dG, HIGH);
        break;
    case 9:
        digitalWrite(dA, HIGH);
        digitalWrite(dB, HIGH);
        digitalWrite(dC, HIGH);
        digitalWrite(dD, HIGH);
        digitalWrite(dE, LOW);
        digitalWrite(dF, HIGH);
        digitalWrite(dG, HIGH);
        break;
    default:
        digitalWrite(dA, HIGH);
        digitalWrite(dB, LOW);
        digitalWrite(dC, LOW);
        digitalWrite(dD, LOW);
        digitalWrite(dE, LOW);
        digitalWrite(dF, LOW);
        digitalWrite(dG, LOW);
        break;
    }
}

//  Desplegar punto (1 desplegar, 0 no desplegar)
void desplegarPunto(uint8_t punto){
    if(punto==1){
        digitalWrite(dP, HIGH);
    }else{
        digitalWrite(dP, LOW);
    }
}

//  Función para configurar display de 7 segmentos
void configDisplay7(void){
    //  Configuración de puertos como salidas
    pinMode(dA, OUTPUT);
    pinMode(dB, OUTPUT);
    pinMode(dC, OUTPUT);
    pinMode(dD, OUTPUT);
    pinMode(dE, OUTPUT);
    pinMode(dF, OUTPUT);
    pinMode(dG, OUTPUT);
    pinMode(dP, OUTPUT);

    digitalWrite(dA, LOW);
    digitalWrite(dB, LOW);
    digitalWrite(dC, LOW);
    digitalWrite(dD, LOW);
    digitalWrite(dE, LOW);
    digitalWrite(dF, LOW);
    digitalWrite(dG, LOW);
    digitalWrite(dP, LOW);
}
void inittemp(void){
  pinMode(temp, INPUT);
}
void initPWM(void){
  //    Asignar canales
  ledcSetup(canalR, freqPWM, resPWM);
  ledcSetup(canalV, freqPWM, resPWM);
  ledcSetup(canalA, freqPWM, resPWM);
  //    Asignar GPIO
  ledcAttachPin(LEDr, canalR);
  ledcAttachPin(LEDv, canalV);
  ledcAttachPin(LEDa, canalA);
}
void initleds(void){
  pinMode(LEDr, OUTPUT);
  pinMode(LEDv, OUTPUT);
  pinMode(LEDa, OUTPUT);

  digitalWrite(LEDr, HIGH);
  digitalWrite(LEDv, HIGH);
  digitalWrite(LEDa, HIGH);
}
void initServo(void){
  ledcSetup(canalServo, freqServo, resServo);

  ledcAttachPin(Servo, canalServo);
}