/*Librería requerida para usar sensor de humedad */
#include <DHT11.h>

/*Instancia del sensor en el pin que está conectado*/
int pin=7;
DHT11 dht11(pin);

/* Definimos la velocidad de lectura en el setup*/
void setup()
   {
       Serial.begin(9600);
   }

/*Para leerlo basta con hacer dht11.read pasándole las variables donde queremos el resultado, y comprobamos que no haya errors (Siempre es buena idea comprobar que no hay error cuando hacemos una llamada). El programa completo seria más o menos algo así: */

void loop()
   {
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
}
