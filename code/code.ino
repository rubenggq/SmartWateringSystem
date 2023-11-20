const int moisturePin = A0;
const int relayPin = 2;

int sensorValue;
int moistureThreshold = 300;
bool isWatering = false;

void setup() {
  pinMode(relayPin, OUTPUT); // Establecemos el pin del relayPin como Salida
  digitalWrite(relayPin, LOW); // Establecemos el valor por defecto del relé a 0v para que no pase corriente
  Serial.begin(9600);
}

void loop() {
  sensorValue = analogRead(moisturePin); // Leemos la humedad del sensor de humedad (moisturePin)
  Serial.print("Valor de humedad: "); // Mostramos mensaje de la humedad del sensor en pantalla
  Serial.println(sensorValue); // Mostramos valor de la humedad del sensor en pantalla a continuación del mensaje anterior

  if (sensorValue < moistureThreshold && !isWatering) { // Si la humedad está por debajo del umbral y no está regando
    digitalWrite(relayPin, LOW);
    Serial.println("Humedad suficiente, riego desactivado");
    isWatering = false;
  } else if (sensorValue >= moistureThreshold && !isWatering) { // Si la humedad está por encima del umbral y no está regando
    isWatering = true;
    // Riego intermitente por intervalos de 4 segundos (2 segundos de riego, 2 segundos de descanso)
    for (int i = 0; i < 5; i++) { // Cambiar 5 por el número de ciclos deseados
      digitalWrite(relayPin, HIGH);
      Serial.println("Regando un poco...");
      delay(2000); // Riego durante 2 segundos
      digitalWrite(relayPin, LOW);
      Serial.println("Midiendo humedad de nuevo");
      delay(2000); // Espera 2 segundos antes de comenzar el siguiente ciclo
    }
    isWatering = false;
  }

  delay(1000);
}
