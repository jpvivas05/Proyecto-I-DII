# Proyecto-I-DII
Proyecto de electrónica digital 2. Sensor de temperatura.
Sensor de temperatura con LM35 implementado. Muestra la temperatura como un semáforo con una luz LED RGB y servo de señalización. Convierte señales analógicas del LM35 en grados centígrados y lo muestra en 3 displays de 7 segmentos. Además, los datos son actualizados en línea con el uso del módulo WIFI del microcontrolador esp32 dev1.0.

Materiales requeridos:
- Esp32
- Servo motor
- Luz led rgb (ánodo común) o 3 luces led
- Push button
- Sensor de temperatura LM35
- 3 displays de 7 segmentos
- 3 transistores NPN (2N2222)
- 11 resistencias de 220 Ohms y 3 de 10K Ohms

Utilizar VSC con librería Adafruit IO Arduino, añadir archivo config.h para inicializar módulo WIFI y alimentar servo motor con 5V (Vin al conectar con computadora).
