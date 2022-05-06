#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
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
}
