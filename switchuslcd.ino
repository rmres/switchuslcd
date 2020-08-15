#include <LiquidCrystal.h>

const int triggerPin = 12;
const int echoPin = 11;
const int switcher = 10;
const int vibra = 13;
int swstatus = 0;
int distancia = 0; // Distance
long duracao = 0; // Duration

LiquidCrystal lcd(2, 3, 7, 6, 5, 4);

void setup() {
    Serial.begin(9600);
    pinMode(triggerPin, OUTPUT);
    pinMode(echoPin, INPUT);
    pinMode(vibra, OUTPUT);
    pinMode(switcher, INPUT);

    lcd.begin(16, 2);
}

void loop() {
    swstatus = digitalRead(switcher);

    if (swstatus == HIGH) {
        digitalWrite(triggerPin, LOW);
        delayMicroseconds(2);

        digitalWrite(triggerPin, HIGH);
        delayMicroseconds(10);
        digitalWrite(triggerPin, LOW);

        duracao = pulseIn(echoPin, HIGH);
        distancia = duracao * 0.01723; // centimeter

        if (distancia < 80) {
            digitalWrite(vibra, HIGH);
        }
        else {
            digitalWrite(vibra, LOW);
        }
        lcd.setCursor(0, 0);
        lcd.print("Distancia:");
        delay(500);
        lcd.setCursor(0, 1);
        lcd.print(distancia);
        delay(500);
        lcd.clear();

        Serial.print("Distancia em cm: "); // Distance in cm:
        Serial.println(distancia);
    }

    else {
        digitalWrite(triggerPin, LOW);
        digitalWrite(vibra, LOW);
        digitalWrite(echoPin, LOW);
    }
}
