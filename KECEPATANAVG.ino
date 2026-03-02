#include <Simpletimer.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include <math.h>
LiquidCrystal_I2C lcd (0x27, 16, 2);

//SENSOR KECEPATAN
const int IRSensorPin = 2;       // Pin sensor VSS (terhubung ke interrupt 0)
int inputState;
int lastInputState    = LOW;
long lastDebounceTime = 0;
long debounceDelay    = 50;
double kkbanspd = 0.00039878; //proto baru
//double kkbanspd = 0.0002658533; //urban magnet 6 ring 16
long endTime;
long startTime;
int RPM         = 0;
double trip     = 0;
double jarak    = 0;
int    banter   = 0;
float lnTime    = 0.5;

// ===== Moving Average Settings =====
const int N = 5; // jumlah data untuk rata-rata

float bufferBanter[N] = {0};
float totalBanter = 0;
int indexBanter = 0;

void setup() {
  Serial.begin(9600);
  pinMode(IRSensorPin, INPUT);
  endTime = 0;
}

void loop() {
  timer1.run(500);
  time = millis();
  int currentSwitchState = digitalRead(IRSensorPin);

  if (currentSwitchState != lastInputState) 
  {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (currentSwitchState != inputState) {
      inputState = currentSwitchState;
      if (inputState == HIGH) {
        calculateRPM(); // Real RPM from sensor
      }
    }
  }
  lastInputState = currentSwitchState;
  int banter  = ((RPM * kkbanspd) *60);//kecepatan
  Serial.print(banter);

totalBanter -= bufferBanter[indexBanter];   // kurangi data lama
bufferBanter[indexBanter] = banter; // simpan data baru
totalBanter += banter;            // tambahkan data baru
indexBanter = (indexBanter + 1) % N;     // geser index
float avgBanter = totalBanter/ N;       // hitung rata-rata

Serial.print("Kecepatan: ");
Serial.print(banter);
Serial.print("  AVG: ");
Serial.println(avgBanter);

lcd.setCursor(0, 0);
lcd.print("Speed: ");
lcd.print(avgBanter);

RPM = 0;
delay(1000);
}
