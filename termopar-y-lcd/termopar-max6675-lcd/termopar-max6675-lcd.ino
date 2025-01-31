#include <SPI.h>
#include "max6675.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

int thermoDO = 4;
int thermoCS = 5;
int thermoCLK = 6;

MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);
LiquidCrystal_I2C lcd(0x27, 16, 2);

float temperatura = 0; // Variable para almacenar el promedio
const int numLecturas = 10; // Cantidad de lecturas para promediar
float lecturas[numLecturas];
int indiceLectura = 0;

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  Serial.println("Iniciando lectura...");
  
  for (int i = 0; i < numLecturas; i++) {
    lecturas[i] = 0; // Inicializamos las lecturas en 0
  }
}

void loop() {
  // Leer la temperatura del termopar
  float nuevaLectura = thermocouple.readCelsius();

  // Añadir la nueva lectura al arreglo
  lecturas[indiceLectura] = nuevaLectura;
  indiceLectura++;

  // Volver al inicio si se supera el índice máximo
  if (indiceLectura >= numLecturas) {
    indiceLectura = 0;
  }

  // Calcular el promedio de las lecturas
  float suma = 0;
  for (int i = 0; i < numLecturas; i++) {
    suma += lecturas[i];
  }
  temperatura = suma / numLecturas;

  // Mostrar la temperatura en el monitor serie y en la LCD
  Serial.print("Temperatura Promedio: ");
  Serial.print(temperatura);
  Serial.println(" °C");

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temperatura:");
  lcd.setCursor(0, 1);
  lcd.print(temperatura);
  lcd.print(" C");

  delay(1000);
}
