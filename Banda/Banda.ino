int Sentido = A0;
int OnOff = A1;
int direccion = 3;
int motor = 5;
String cadena;

void setup() {
  Serial.begin(9600);
}

int valor1, valor2;
void loop() {
    valor1=analogRead(Sentido);
    valor2=analogRead(OnOff);

    valor2=map(valor2,0,1023,0,3);
    valor1=map(valor1,0,1023,0,3);

    Serial.println(String(valor1)+"<--->"+String(valor2));

    if(valor2<=1){
      analogWrite(motor,0);
    }else if(valor2>=2){
      analogWrite(motor,255);
    }

    if(valor1<=1){
      analogWrite(direccion,0);
    }else if(valor1>=2){
      analogWrite(direccion,255);
    }
    
  delay(100);
}
