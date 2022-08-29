//Versión modificada
//1.1

#include <EEPROM.h>
const int analogSensor = 0;
const int ledCount = 10;
const int ledSave = 0;
const int pushButtonSave = 12;
const int pushButtonRead = 13;

int ledPins[] = {2,3,4,5,6,7,8,9,10,11};
int buttonSave = 0;
int buttonRead = 0;
int buttonCount = 0;

void setup() {
  //Serial.begin(9600);
  pinMode(ledSave, OUTPUT);
  pinMode(pushButtonSave, INPUT);
  pinMode(pushButtonRead, INPUT);
  for (int thisLed = 0; thisLed < ledCount; thisLed++) {
    pinMode(ledPins[thisLed], OUTPUT);
  }
}

void guardar(int value) {
  int temp1 = EEPROM.read(0);
  int temp2 = EEPROM.read(1);
  EEPROM.write(0, value);
  EEPROM.write(1, temp1);
  EEPROM.write(2, temp2);
  //Serial.println("guardado");
  delay(2000);
}

void mostrar() {
  while (true) {
    buttonRead = digitalRead(pushButtonRead);
    if (buttonRead == HIGH) {
      if (buttonCount < 3) {
        int dataReaded = EEPROM.read(buttonCount);
        //Serial.print(buttonCount);
        //Serial.print("\t");
        //Serial.println(dataReaded);

        for (int ledHigh = 0; ledHigh < ledCount; ledHigh++) {
          if (ledHigh < dataReaded) {
            digitalWrite(ledPins[ledHigh], HIGH);
          } else {
            digitalWrite(ledPins[ledHigh], LOW);
          }
        }

        buttonCount++;
        delay(500);
      } else {
        break;
      }
    }
  }
  buttonCount = 0;
  delay(500);
}

void loop() {
  int dataLevel = map(analogRead(analogSensor), 700, 900, 0, ledCount);
  if (dataLevel < 0) {
    dataLevel = 0;
  }
  if (dataLevel > 10) {
    dataLevel = 10;
  }
  //Serial.println(dataLevel);

  for (int ledHigh = 0; ledHigh < ledCount; ledHigh++) {
    if (ledHigh < dataLevel) {
      digitalWrite(ledPins[ledHigh], HIGH);
    } else {
      digitalWrite(ledPins[ledHigh], LOW);
    }
  }

  buttonSave = digitalRead(pushButtonSave);
  if (buttonSave == HIGH) {
    digitalWrite(ledSave, HIGH);
    guardar(dataLevel);
  } else {
    digitalWrite(ledSave, LOW);
  }
  
  buttonRead = digitalRead(pushButtonRead);
  if (buttonRead == HIGH) {
    mostrar();
  }
}
