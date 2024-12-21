#include <SoftwareSerial.h>
SoftwareSerial BTSerial(2, 3);

#define en1Analog 6
#define en1DigitL 7
#define en1DigitR 8

#define en2Analog 11
#define en2DigitL 12
#define en2DigitR 13

char data = 1;

void setup() {
    Serial.begin(9600);
    BTSerial.begin(9600);

    pinMode(en1Analog, OUTPUT);
    pinMode(en1DigitL, OUTPUT); 
    pinMode(en1DigitR, OUTPUT);

    pinMode(en2Analog, OUTPUT);
    pinMode(en2DigitL, OUTPUT); 
    pinMode(en2DigitR, OUTPUT);
}

void loop() {
    if (BTSerial.available()) {
        String receivedString = BTSerial.readStringUntil('\n');
        data = receivedString.toInt();
        Serial.println(data);
    }

    switch (data) {
        case 1:
            digitalWrite(en1DigitL, LOW);
            digitalWrite(en1DigitR, HIGH);
            sterujPWM(en1Analog);
            break;

        case 2:
            digitalWrite(en1DigitL, HIGH);
            digitalWrite(en1DigitR, LOW);
            sterujPWM(en1Analog);
            break;

        case 3:
            digitalWrite(en2DigitL, LOW);
            digitalWrite(en2DigitR, HIGH);
            sterujPWM(en2Analog);
            break;

        case 4:
            digitalWrite(en2DigitL, HIGH);
            digitalWrite(en2DigitR, LOW);
            sterujPWM(en2Analog);
            break;

        default:
            digitalWrite(en1DigitL, LOW);
            digitalWrite(en1DigitR, LOW);
            digitalWrite(en2DigitL, LOW);
            digitalWrite(en2DigitR, LOW);
            analogWrite(en1Analog, 0);
            analogWrite(en2Analog, 0);
            break;
    }
}

void sterujPWM(int pin) {
    for (int i = 0; i <= 255; i++) {
        analogWrite(pin, i);
        delay(10);
    }
    for (int i = 255; i >= 0; i--) {
        analogWrite(pin, i);
        delay(10);
    }
}
