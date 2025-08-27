//******************************************/
// Universidad del Valle de Guatemala
// BE3029 - Electronica Digital 2
// Juan Pablo Vivas
// 12/08/2025
// Proyecto 1 Electrónica Digital II
// MCU: ESP32 dev kit 1.0
//******************************************/
//******************************************/
// Librerias
//******************************************/
#include <Arduino.h>
#include <stdint.h>
//  Librería para PWM
#include "driver/ledc.h"
//  Librerías especiales para proyecto
//  Inicialización de hardware
#include "init.h"
//  Inicialización de Adafruit IO
#include "config.h"

//******************************************/
// Definiciones
//******************************************/
//  Displays
#define dis1 22
#define dis2 27
#define dis3 12

//******************************************/
// Variables globales
//******************************************/
// Variables de botón
volatile bool btn1Pressed;
volatile uint32_t lastISRbtn1 = 0;
//  Variables de ISR display
volatile uint8_t digito = 0;
volatile uint8_t decena = 0;
volatile uint8_t unidad = 0;
volatile uint8_t decimal = 0;
//Filtro EMA
float adcRawEMA = 0; // Y(0)
float adcFiltrado = adcRawEMA; // S(0) = Y(0)
float alpha = 0.5; // Factor de suavizado (0-1)
//  Conversión a °C
float gradC;
//  Configuración de timer para displays
hw_timer_t *timerMultiplex = NULL; 

//******************************************/
// Prototipos de funciones
//******************************************/
//  Inicializa ISR para displays
void initTimerMultiplex(void);
//  Inicializa ISR para botón
void initbtn(void);
//  Prototipo de filtrado
void getADCEMA(void);

//  Operaciones para desplegar temperatura en displays
void divNum(float num);

void semaforo(void);
//  Prototipos ISR
void IRAM_ATTR btn1_ISR(void);
void IRAM_ATTR TMR_Multiplex_ISR(void);

// Adafruit IO
AdafruitIO_Feed *canalTemperatura = io.feed("temperatura");

//******************************************/
// ISRs Rutinas de Interrupcion
//******************************************/
// ISR para el multiplexeo del display
void IRAM_ATTR TMR_Multiplex_ISR(void) {
  // Apaga todos los transistores para evitar "ghosting"
  digitalWrite(dis1, LOW);
  digitalWrite(dis2, LOW);
  digitalWrite(dis3, LOW);

  switch (digito) {
    case 0: // Muestra la DECENA
      desplegarNumero(decena);
      desplegarPunto(0);
      digitalWrite(dis1, HIGH);
      break;
    case 1: // Muestra la UNIDAD
      desplegarNumero(unidad);
      desplegarPunto(1);
      digitalWrite(dis2, HIGH);
      break;
    case 2: // Muestra el DECIMAL
      desplegarNumero(decimal);
      desplegarPunto(0);
      digitalWrite(dis3, HIGH);
      break;
  }
  digito = (digito + 1) % 3; // Avanza al siguiente dígito 
}

void IRAM_ATTR btn1_ISR(void){
  uint32_t tiempoActual1 = millis();
  if (tiempoActual1 - lastISRbtn1 > delayBounce){
    btn1Pressed = true;
    lastISRbtn1 = tiempoActual1;
  } 
  //  Al tocar el botón, espera 250ms para volver a verificar el estado
}

//******************************************/
// Configuracion
//******************************************/
void setup() {
  //  Comunicación serial para mostrar en pantalla
  Serial.begin(115200);

  // wait for serial monitor to open
  while(! Serial);

  Serial.print("Connecting to Adafruit IO");

  // connect to io.adafruit.com
  io.connect();

  // wait for a connection
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  // we are connected
  Serial.println();
  Serial.println(io.statusText());
  //  Inicializar hardware
  initbtn();
  initleds();
  initPWM();
  initServo();
  configDisplay7();
  
  initTimerMultiplex();   // Configura y arranca el timer del display
  //  Configuración de displays
  pinMode(dis1, OUTPUT);
  pinMode(dis2, OUTPUT);
  pinMode(dis3, OUTPUT);
  //  Toma muestras iniciales para filtro estable
  for (int i = 0; i < 65; i++) {
  getADCEMA();
  }
}
//******************************************/
// Loop Principal
//******************************************/
void loop() {
  // io.run(); is required for all sketches.
  // it should always be present at the top of your loop
  // function. it keeps the client connected to
  // io.adafruit.com, and processes any incoming data.
  io.run();
  // Del número actual desde la última toma de datos, calcula para displays
  divNum(gradC);
  // Se ejecuta solo cuando se presiona el botón una vez
  if (btn1Pressed){
    //  Actualiza estados
    btn1Pressed = false;
    getADCEMA();
    semaforo();
    //  Imprime valores obtenidos
    Serial.println(adcFiltrado);
    Serial.println(gradC);
    // save count to the feed on Adafruit IO
    Serial.print("sending -> ");
    Serial.println(gradC);
    //  Envía datos obtenidos a Adafruit IO
    canalTemperatura-> save(gradC);
  }
}
//******************************************/
// Otras funciones
//******************************************/
void semaforo(void){
  // Apaga todos los LEDs al inicio de la función. Con ánodo común, 1023 apaga.
  ledcWrite(canalA, 1023);
  ledcWrite(canalR, 1023);
  ledcWrite(canalV, 1023);
  
  if(gradC < 21){ // Temperatura Baja
    // Enciende el azul (el valor de 0 es brillo maximo) y actualiza posición de servo
    ledcWrite(canalA, 0);
    ledcWrite(canalServo, 150);
  }
  else if(gradC >= 21 && gradC <= 27){ // Temperatura Media
    // Enciende el verde
    ledcWrite(canalV, 0);
    ledcWrite(canalServo, 285);
  }
  else if(gradC > 27){ // Temperatura Alta
    // Enciende el rojo
    ledcWrite(canalR, 0);
    ledcWrite(canalServo, 465);
  }
}

void divNum(float num){
  decena = num/10;
  unidad = num-(decena*10);
  decimal = (num-((decena*10)+unidad))*10;
}

void getADCEMA(void){
  adcRawEMA = analogRead(temp);
  adcFiltrado = (alpha * adcRawEMA) + ((1.0 - alpha) * adcFiltrado);
  gradC = ((adcFiltrado / 4095.0) * 3300.0 / 10.0)+7;
}

void initbtn(void){
  pinMode(btn1, INPUT_PULLUP);

  attachInterrupt(btn1, &btn1_ISR, FALLING);
}
void initTimerMultiplex(void) {
  // Timer 0, prescaler de 80 (para que cuente en microsegundos), cuenta hacia arriba
  timerMultiplex = timerBegin(0, 80, true);
  // Asocia la ISR al temporizador
  timerAttachInterrupt(timerMultiplex, &TMR_Multiplex_ISR, true);
  // Configura la alarma para que se dispare cada 3000 us (3 ms), y que se recargue automáticamente
  timerAlarmWrite(timerMultiplex, 3000, true);
  // Activa la alarma
  timerAlarmEnable(timerMultiplex);

}
