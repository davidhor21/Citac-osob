#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

#define trigPin 2
#define echoPin 3
#define delayBetween 1100

int correction;
long roomWidth;
bool personCaptured;
int personCount;

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x3F, 16, 2);


long measureDistance(){
    digitalWrite(trigPin, LOW); 
    delayMicroseconds(5); 

    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    long duration = pulseIn(echoPin, HIGH);

    return duration/2;
}

void printLcd(int count){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Pocet osob:");
    lcd.setCursor(0,1);
    lcd.print(count);
}

void setup() {
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);

    lcd.begin();
    lcd.backlight();
    printLcd(0);

    roomWidth = measureDistance();
    correction = roomWidth / 100 * 4;
}

void loop() {
    long width = measureDistance();

    if(width < (roomWidth - correction) && !personCaptured){
        personCaptured = true;
        personCount++;
        printLcd(personCount);
        delay(delayBetween);
    }
    else if(abs(roomWidth - width) < correction){
        personCaptured = false;
    }

    delay(5);
}