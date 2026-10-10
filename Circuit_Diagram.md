Circuit Diagram and Connections

Components

- Arduino UNO
- RC522 RFID Reader
- SG90 Servo Motor

RFID Reader Connections

RC522 Pin| Arduino UNO
SDA| 10
SCK| 13
MOSI| 11
MISO| 12
RST| 9
GND| GND
3.3V| 3.3V

Servo Motor Connections

Servo Wire| Connection
Signal| Pin 3
VCC| Suitable 5V supply
GND| Common GND

Working

The RFID reader scans the card and sends its UID to the Arduino. If the card is authorized, the servo motor rotates to unlock the door.
