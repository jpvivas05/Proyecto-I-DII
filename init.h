#ifndef __INIT_H__
#define __INIT_H__
//  Incluir mismas librerías que en main
#include <Arduino.h>
#include <stdint.h>
#include "driver/ledc.h"

//      Variables globales
//  Definición de pines en segmentos
#define dA 2
#define dB 15
#define dC 18
#define dD 19
#define dE 21
#define dF 4
#define dG 16
#define dP 17

//  Definición LED RGB
#define LEDr 32
#define LEDv 33
#define LEDa 25
#define Servo 13
//  Pre configuración de canales y especificaciones para PWM
//  Canales utilizados
#define canalR 0
#define canalV 1
#define canalA 4
#define canalServo 3
//  Frecuencia definida
#define freqPWM 100
#define freqServo 50
//  Resolución recomendada
#define resPWM 10
#define resServo 12

//  Definición de GPIO sensor y botón
#define btn1 23
#define temp 36
//  Debounce para botón
#define delayBounce 250
//  Ciclo para display
#define delayDisplay 5

//      Prototipos de funciones
//  Funciones de inicialización
void initleds(void);
void initPWM(void);
void inittemp(void);
void initServo(void);

//  Función para configurar display de 7 segmentos
void configDisplay7(void);

//  Desplegar número en display 7 segmentos
void desplegarNumero(uint8_t numero);

//  Desplegar punto (1 desplegar, 0 no desplegar)
void desplegarPunto(uint8_t punto);



#endif // __INIT_H__
