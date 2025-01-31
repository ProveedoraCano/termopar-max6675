#include <SPI.h>
#include "max6675.h"

// Definición de pines
int thermoDO = 4;   // Pin de datos
int thermoCS = 5;   // Pin de selección de chip
int thermoCLK = 6;  // Pin de reloj

// Crear una instancia del sensor MAX6675
MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);

void setup() {
  // Iniciar comunicación serial
  Serial.begin(9600);
  delay(500); // Esperar medio segundo
  Serial.println("Iniciando lectura del termopar tipo K...");
}

void loop() {
  // Leer y mostrar la temperatura en Celsius
  Serial.print("Temperatura: ");
  Serial.print(thermocouple.readCelsius());
  Serial.println(" °C");
  
  delay(2000); // Esperar 1 segundo antes de la siguiente lectura
}
