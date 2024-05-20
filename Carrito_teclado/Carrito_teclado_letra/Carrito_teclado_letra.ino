#include <SoftwareSerial.h>
SoftwareSerial BT1(10,11); // RX, TX recordar que se cruzan

int inputs[4] = {2, 4, 7, 8};
int enables[2] = {5,6};
int mestados[5][4]={
  {1,0,1,0},
  {0,1,0,1},
  {0,0,0,0},
  {0,1,1,0},
  {1,0,0,1}
  }; //avanzar, reversa, detenerse, izquierda, derecha
int velocidades[5][2]={
  {255,255},
  {255,255},
  {0,0},
  {120,120},
  {120,120}
  };

//IZQUIERDAX
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  //Serial.println("Enter AT commands:");
  BT1.begin(9600);
  BT1.setTimeout(10);
  for(int i = 0; i<4; i++){
    pinMode(inputs[i], OUTPUT);
  }
}

void loop() {
  int estado;
  // Leer datos del módulo Bluetooth
  if (BT1.available() > 0) {
    char receivedChar = BT1.read(); 
    Serial.println(receivedChar);  
    
    switch (receivedChar) {
      case 'W':
        estado = 0;
        Serial.println("AVANZAR");
        for(int i = 0; i<4; i++){
          digitalWrite(inputs[i], mestados[estado][i]);
          Serial.println(String(inputs[i])+" estado :"+String(mestados[estado][i]));
        }

        for(int i = 0; i<2; i++){
          analogWrite(enables[i], velocidades[estado][i]);
          Serial.println(String(enables[i])+" estado: "+ String(velocidades[estado][i]));
        }
        break;

      case 'S':
        estado = 1;
        Serial.println("RETROCEDER");
        for(int i = 0; i<4; i++){
          digitalWrite(inputs[i], mestados[estado][i]);
          Serial.println(String(inputs[i])+" estado :"+String(mestados[estado][i]));
        }

        for(int i = 0; i<2; i++){
          analogWrite(enables[i], velocidades[estado][i]);
          Serial.println(String(enables[i])+" estado: "+ String(velocidades[estado][i]));
        }
        break;

      case 'X':
        estado = 2;
        Serial.println("DETENERSE");
        for(int i = 0; i<4; i++){
          digitalWrite(inputs[i], mestados[estado][i]);
          Serial.println(String(inputs[i])+" estado :"+String(mestados[estado][i]));
        }

        for(int i = 0; i<2; i++){
          analogWrite(enables[i], velocidades[estado][i]);
          Serial.println(String(enables[i])+" estado: "+ String(velocidades[estado][i]));
        }
        break;

      case 'A':
        estado = 3;
        Serial.println("IZQUIERDA");
        for(int i = 0; i<4; i++){
          digitalWrite(inputs[i], mestados[estado][i]);
          Serial.println(String(inputs[i])+" estado :"+String(mestados[estado][i]));
      }

        for(int i = 0; i<2; i++){
          analogWrite(enables[i], velocidades[estado][i]);
          Serial.println(String(enables[i])+" estado: "+ String(velocidades[estado][i]));
        }
        break;

      case 'D':
        estado = 4;
        Serial.println("DERECHA");
        for(int i = 0; i<4; i++){
          digitalWrite(inputs[i], mestados[estado][i]);
          Serial.println(String(inputs[i])+" estado :"+String(mestados[estado][i]));
        }

        for(int i = 0; i<2; i++){
          analogWrite(enables[i], velocidades[estado][i]);
          Serial.println(String(enables[i])+" estado: "+ String(velocidades[estado][i]));
        }
        break;

      default:
        break;
    }
  }
  
  // Leer datos del puerto serial de la computadora
  if (Serial.available() > 0) {
    char commandChar = Serial.read();
    BT1.write(commandChar);       
  }
}