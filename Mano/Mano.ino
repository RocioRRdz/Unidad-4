// Definición de pines
const int pinMotor1 = 8;    // 28BYJ48 - In1
const int pinMotor2 = 9;    // 28BYJ48 - In2
const int pinMotor3 = 10;   // 28BYJ48 - In3
const int pinMotor4 = 11;   // 28BYJ48 - In4

// Definición de variables
int velocidadMotor = 1000;    // Variable para determinar la velocidad 
int contadorPasos = 0;        // Contador para los pasos
int pasosPorVuelta = 4076;    // Pasos para una vuelta completa
char comando;                 // Variable para almacenar el comando recibido
char estado = '2';            // Estado inicial del motor (detenido)
unsigned long duracionMovimiento = 15000000; // Duración del movimiento en microsegundos (15 segundos)

// Secuencia de media fase
const int cantidadPasos = 8;
const int tablaPasos[8] = { B1000, B1100, B0100, B0110, B0010, B0011, B0001, B1001 };

void setup()
{
    // Declarar pines como salida
    pinMode(pinMotor1, OUTPUT);
    pinMode(pinMotor2, OUTPUT);
    pinMode(pinMotor3, OUTPUT);
    pinMode(pinMotor4, OUTPUT);
    Serial.begin(9600); // Configura la velocidad del puerto serie
}

void loop()
{
    if (Serial.available() > 0)
    {
        comando = Serial.read(); // Lee el comando del puerto serie
        estado = comando; // Actualiza el estado del motor según el comando recibido
    }

    if (estado == '0') // Sentido horario (cerrar pinza)
    {
        cerrarPinza();
    }
    else if (estado == '1') // Sentido antihorario (abrir pinza)
    {
        abrirPinza();
    }
    else if (estado == '2') // Detener
    {
        detenerMotor();
    }
}

void cerrarPinza() // En dirección de las agujas del reloj
{
    unsigned long tiempoInicio = micros();
    while (micros() - tiempoInicio < duracionMovimiento)
    {
      if (Serial.available() > 0)
    {
        comando = Serial.read(); // Lee el comando del puerto serie
        estado = comando; // Actualiza el estado del motor según el comando recibido
    
        if (estado == '2')
        {
            detenerMotor();
            return;
        }
    }
        sentidoHorario();
        delayMicroseconds(velocidadMotor);
    }
    detenerMotor();
}

void abrirPinza() // En dirección contraria a las agujas del reloj
{
    unsigned long tiempoInicio = micros();
    while (micros() - tiempoInicio < duracionMovimiento)
    {
          if (Serial.available() > 0)
    {
        comando = Serial.read(); // Lee el comando del puerto serie
        estado = comando; // Actualiza el estado del motor según el comando recibido
    
        if (estado == '2')
        {
            detenerMotor();
            return;
        }
    }
        sentidoAntihorario();
        delayMicroseconds(velocidadMotor);
    }
    detenerMotor();
}

void sentidoHorario() // En dirección de las agujas del reloj
{
    contadorPasos++;
    if (contadorPasos >= cantidadPasos) contadorPasos = 0;
    escribirSalidas(contadorPasos);
}

void sentidoAntihorario() // En dirección contraria a las agujas del reloj
{
    contadorPasos--;
    if (contadorPasos < 0) contadorPasos = cantidadPasos - 1;
    escribirSalidas(contadorPasos);
}

void escribirSalidas(int paso)
{
    digitalWrite(pinMotor1, bitRead(tablaPasos[paso], 0));
    digitalWrite(pinMotor2, bitRead(tablaPasos[paso], 1));
    digitalWrite(pinMotor3, bitRead(tablaPasos[paso], 2));
    digitalWrite(pinMotor4, bitRead(tablaPasos[paso], 3));
}

void detenerMotor()
{
    // Apaga todas las salidas para detener el motor
    digitalWrite(pinMotor1, LOW);
    digitalWrite(pinMotor2, LOW);
    digitalWrite(pinMotor3, LOW);
    digitalWrite(pinMotor4, LOW);
}