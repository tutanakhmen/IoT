// dependencies
#include <MFRC522.h>
#include <MFRC522Extended.h>
#include <deprecated.h>
#include <require_cpp11.h>
#include <Servo.h>

// RFID settings
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);
MFRC522::MIFARE_Key key;
byte allowedUid1[] = { 0x63, 0x44, 0x70, 0xAD };  // Example UID (replace as needed)

// Servo settings
Servo s;
bool servoAt90 = false;

// Sensor pin
#define SENSOR_PIN 7

void setup() {
  Serial.begin(9600);
  // Attach servo
  s.attach(6);
  s.write(0); // Start with servo closed

  // Pin configuration
  pinMode(SENSOR_PIN, INPUT);
  pinMode(4, OUTPUT); // Indicator for RFID detected
  pinMode(8, OUTPUT); // Indicator for RFID not detected
  SPI.begin();
  mfrc522.PCD_Init();
}

void loop() {
  // Check if sensor is detecting something
  bool sensorDetected = digitalRead(SENSOR_PIN) == HIGH;

  // Check if a card is present and read its UID
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    // Read card UID
    MFRC522::PICC_Type piccType = mfrc522.PICC_GetType(mfrc522.uid.sak);
    
    if (piccType == MFRC522::PICC_TYPE_MIFARE_MINI || 
        piccType == MFRC522::PICC_TYPE_MIFARE_1K ||
        piccType == MFRC522::PICC_TYPE_MIFARE_4K) {
      
      if (memcmp(mfrc522.uid.uidByte, allowedUid1, mfrc522.uid.size) == 0) {
        Serial.println("Kartu 1 terdeteksi");
        digitalWrite(4, HIGH); // Turn on indicator for RFID detected

        if (sensorDetected && !servoAt90) {
          s.write(90); // Open servo if sensor detects something
          servoAt90 = true;
        }
      } else {
        Serial.println("Kartu tidak dikenal");
        digitalWrite(8, HIGH); // Turn on indicator for RFID not detected
      }
    } else {
      Serial.println("Kartu tidak didukung.");
      digitalWrite(8, HIGH); // Turn on indicator for RFID not detected
    }
  } else {
    // If no card is detected
    // digitalWrite(4, LOW); // Turn off indicator for RFID detected
    digitalWrite(8, LOW); // Turn off indicator for RFID not detected
  }

  // Close servo if sensor does not detect anything
  if (!sensorDetected && servoAt90) {
    while (digitalRead(7) == 0) {
    servoAt90 = true;
     }
     delay(1000);
    digitalWrite(4, LOW); // Close servo
    s.write(0);
    servoAt90 = false;
  }

  delay(50); // Short delay to stabilize readings
}
