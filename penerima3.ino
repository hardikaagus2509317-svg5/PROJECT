#include <DHT.h> // Memanggil library untuk sensor DHT
#include <Wire.h>// Memanggil library untuk komunikasi I2C
#include <LiquidCrystal_I2C.h>// Memanggil library untuk LCD I2C*/
/*#define DHTPIN 2 // Menentukan pin data DHT22 terhubung ke pin 2
#define DHTTYPE DHT11 // Menentukan tipe sensor yang digunakan (DHT22)
// Membuat objek dht dengan pin dan tipe yang sudah ditentukan
DHT dht(DHTPIN, DHTTYPE);*/

void setup() {
    Serial.begin(9600);
}

void loop() {
  String data = "";

  while (Serial.available() > 0) {
    data += char(Serial.read());
    data.trim();
  }
  if (data.length() > 0) {
    Serial.println(data);
   // Serial.print("|");
  }
  delay(500);
}
