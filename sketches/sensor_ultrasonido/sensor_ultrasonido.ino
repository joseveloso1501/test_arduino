/*
  Ping))) Sensor

  This sketch reads a PING))) ultrasonic rangefinder and returns the distance
  to the closest object in range. To do this, it sends a pulse to the sensor to
  initiate a reading, then listens for a pulse to return. The length of the
  returning pulse is proportional to the distance of the object from the sensor.

  The circuit:
	- +V connection of the PING))) attached to +5V
	- GND connection of the PING))) attached to ground
	- SIG connection of the PING))) attached to digital pin 7

  created 3 Nov 2008
  by David A. Mellis
  modified 30 Aug 2011
  by Tom Igoe

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/Ping
*/


const int pingPin = 8; //pin donde se conecta la salida de señal del sensor

void setup() {
  Serial.begin(9600); //inicializar la comunicacion serial
}

void loop() {
  long duration, inches, cm; //definicion de variables: duracion del ping y resultado de la distancia medida en pulgadas y centimentros 

  // PING))) es accionado por un pulso HIGH de 2 o mas milisegundos
  //se da un pulso LOW corto anticipadamente para asegurar un pulso ALTO limpio
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);

  // El mismo pin es usado para leer la señal del PING))): 
  // un pulso ALTO cuya duración es el tiempo (en microsegundos) 
  // desde el envío del ping hasta la recepción de su eco en un objeto.
  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);

  // convertir el tiempo en distancia
  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);
  
    Serial.print("Distancia: ");
    Serial.print(inches);
    Serial.print(" [in] | ");
    Serial.print(cm);
    Serial.print(" [cm]");
    Serial.println();



  delay(1000);
}

long microsecondsToInches(long microseconds) {
   // Según la hoja de datos de Parallax para el PING))), hay 73.746
   // microsegundos por pulgada (es decir, el sonido viaja a 1130 pies por segundo).
   // Esto da la distancia recorrida por el ping, ida y vuelta,
   // así que dividimos por 2 para obtener la distancia del obstáculo.
  // ver: https://www.parallax.com/package/ping-ultrasonic-distance-sensor-downloads/
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
  // la velocidad del sonido es 340 m/s o 29 microsegundos por centimetro.
  // El ping viaja de ida y vuelta, así que para encontrar la distancia del objeto tomamos la mitad de la distancia recorrida.
  return microseconds / 29 / 2;
}
