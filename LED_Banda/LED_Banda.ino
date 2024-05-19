int Sentido = A0;
int OnOff = A1;
int direccion = 3;
int motor = 5;
int verde=2,rojo=4,amarillo=6;
String cadena;
bool cambioDirIzq = true, cambioDirDer = true;

void setup() {
  Serial.begin(9600);
  pinMode(verde,OUTPUT);
  pinMode(rojo,OUTPUT);
  pinMode(amarillo,OUTPUT);
}

int valor1, valor2;
void loop() {
    valor1=analogRead(Sentido);
    valor2=analogRead(OnOff);

    valor2=map(valor2,0,1023,0,3);
    valor1=map(valor1,0,1023,0,3);

    Serial.println(String(valor1)+"<--->"+String(valor2));

    if(valor2<=1){
      digitalWrite(rojo,LOW);
      digitalWrite(verde,HIGH);
      analogWrite(motor,0);
    }else if(valor2>=2){
      digitalWrite(rojo,HIGH);
      digitalWrite(verde,LOW);
      analogWrite(motor,255);
    }

    if(valor1<=1){
      if (cambioDirIzq == true){
        digitalWrite(amarillo,HIGH);        
        delay(1000);
        digitalWrite(amarillo,LOW);
        cambioDirIzq = false;
        cambioDirDer = true;
      }
      analogWrite(direccion,0);
    }else if(valor1>=2){
      if (cambioDirDer == true){
        digitalWrite(amarillo,HIGH);
        delay(1000);
        digitalWrite(amarillo,LOW);
        cambioDirDer = false;
        cambioDirIzq = true;
      }
      analogWrite(direccion,255);
    }
    
  delay(100);
}