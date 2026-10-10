#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>

#define SS_PIN 10
#define RST_PIN 9

MFRC522 rfid(SS_PIN, RST_PIN);
Servo doorLock;

const int servoPin = 3;

// Replace this with your RFID card UID
byte authorizedUID[] = {0xDE, 0xAD, 0xBE, 0xEF};

void setup() {
  Serial.begin(9600);
  SPI.begin();
  rfid.PCD_Init();

  doorLock.attach(servoPin);
  doorLock.write(0);  // Door locked

  Serial.println("RFID Door Lock System Ready");
  Serial.println("Scan your RFID card");
}

void loop() {
  if (!rfid.PICC_IsNewCardPresent()) {
    return;
  }

  if (!rfid.PICC_ReadCardSerial()) {
    return;
  }

  bool accessGranted = true;

  if (rfid.uid.size != sizeof(authorizedUID)) {
    accessGranted = false;
  } else {
    for (byte i = 0; i < rfid.uid.size; i++) {
      if (rfid.uid.uidByte[i] != authorizedUID[i]) {
        accessGranted = false;
        break;
      }
    }
  }

  if (accessGranted) {
    Serial.println("Access Granted!");
    doorLock.write(90);  // Unlock door
    delay(3000);
    doorLock.write(0);   // Lock door again
    Serial.println("Door Locked");
  } else {
    Serial.println("Access Denied!");
  }

  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
}
