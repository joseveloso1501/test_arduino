const int sensorPin = 9;

void setup() {
  Serial.begin(9600);   //iniciar puerto serie
  pinMode(sensorPin , INPUT);  //definir pin como entrada
}
 
void loop(){
  int value = 0;
  value = digitalRead(sensorPin);  //lectura digital de pin
 
  if (value == HIGH) {
      Serial.println("Obstaculo detectado");      
  }
  else {
    Serial.println("Sin obstaculo");
  }
  delay(1000);
}
