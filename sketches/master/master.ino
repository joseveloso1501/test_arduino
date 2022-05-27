#include <DHT11.h>
#include <Servo.h>

const int sensorPin = 10; //pin del sensor de infrarrojo
const int pingPin = 8; //pin del sensor de ultrasonido 

const int pin;

void setup() {
  Serial.begin(9600);
  pinMode(sensorPin , INPUT);  //definir pin como entrada
}

void loop() {

  pin = Serial.read();
  Servo myservo; 

  switch (pin) {
    case 7: //sensor temperatura humedad
       //Para sensor DHT11
      int err;
      float temp, humi;
      if((err=dht11.read(humi, temp))==0)
      {
        Serial.print("Temperatura Superficie: ");
        Serial.print(temp);
        Serial.print("C");
        Serial.println();
        Serial.print("Humedad Superficie: ");
        Serial.print(humi);
        Serial.print("%");
        Serial.println();          
      }
      else
      {
        Serial.println();
        Serial.print("Error No :");
        Serial.print(err);
        Serial.println();    
      }  
      delay(5000);            //solo lee una vez cada 10 segundos

      break;

    case 8: //sensor ultrasonido
  
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

      break;
    case 9: //servo motor 
      myservo.attach(9); // Asocia la variable al pin donde está conectado el servo.
      char dato = Serial.read();
      if(dato == 'a'){
        Serial.println("Movimiento a: giro de 180");
        myservo.write(180); // Gira lentamente en una dirección durante 4 segundos.
        delay(3000);
      }
      if(dato =='b'){
        Serial.println("Movimiento b: giro de 94");
        myservo.write(94); 
        delay(3000);
      }
      if(dato =='c'){
        Serial.println("Movimiento c: giro de 20");
        myservo.write(20); 
        delay(3000);
      }
      if(dato =='d'){
        Serial.println("Movimiento d: giro de 120");
        myservo.write(120); 
        delay(3000);
      }
      if(dato =='e'){
        Serial.println("Movimiento e: giro de 98");
        myservo.write(98); 
        delay(3000);
      }
      myservo.detach(); // Desasocia la variable Servo de su pin
      break;

    case 10: //sensor infrarrojo

        int value = 0;
        value = digitalRead(sensorPin);  //lectura digital de pin
       
        if (value == HIGH) {
            Serial.println("Obstaculo detectado");      
        }
        else {
          Serial.println("Sin obstaculo");
        }
        delay(1000);
      break;

    default:
      Serial.print("Pin incorrecto");
      break;
  }
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