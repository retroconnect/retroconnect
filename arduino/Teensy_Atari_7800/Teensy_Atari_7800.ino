//       | DE-9    TEENSY    Atari 2600     Direct Port |
const byte PIN_1 = 2;     // UP             PORTD0
const byte PIN_2 = 20;    // DOWN           PORTD5
const byte PIN_3 = 21;    // LEFT           PORTD6
const byte PIN_4 = 5;     // RIGHT          PORTD7
const byte PIN_5 = 6;     // Right Button   PORTD2
const byte PIN_6 = 7;     // Both Buttons   PORTD4
//         PIN_7;         // (5V unused)     
//         PIN_8;         // GND
const byte PIN_9 = 8;     // Left Button    PORTD3

char data[2];

//Some games, such as Pole Position II, will disable the Left/Right buttons if the "Both Buttons" button is pressed.
//With compatibility mode on, it will disable this button to prevent accidental disabling of the Left/Right buttons.
bool compatibilityMode = true;

const byte PIN_1_BIT = 0;
const byte PIN_2_BIT = 5;
const byte PIN_3_BIT = 6;
const byte PIN_4_BIT = 7;
const byte PIN_5_BIT = 2;
const byte PIN_6_BIT = 4;
const byte PIN_9_BIT = 3;

const byte PIN_BITMASK = (1 << PIN_1_BIT) | (1 << PIN_2_BIT) | (1 << PIN_3_BIT) | (1 << PIN_4_BIT) | (1 << PIN_5_BIT) | (1 << PIN_6_BIT) | (1 << PIN_9_BIT); // bit mask for PORTD write updates

/*
  Low = pressed

  Pin  Connection
  ---  -------------------------- 
  7   Power: +5 Volts / Potentiometer common
  8   Power: Ground

  Pin  Connection
  ---  -----------------
  1   joypad up signal
  2   joypad down signal
  3   joypad left signal
  4   joypad right signal
  5   Right button signal 
  6   Button signal
  9   Left button signal 
*/

void setup() {
  //Serial.begin(115200);
  //Serial.print("Started program!\n");
  pinMode(PIN_1, OUTPUT); //UP
  pinMode(PIN_2, OUTPUT); //DOWN
  pinMode(PIN_3, OUTPUT); //LEFT
  pinMode(PIN_4, OUTPUT); //RIGHT
  pinMode(PIN_5, OUTPUT); //RIGHT BUTTON
  pinMode(PIN_6, OUTPUT); //BOTH BUTTONS
  pinMode(PIN_9, OUTPUT); //LEFT BUTTON

  data[0] = 255;
  data[1] = 255;

  digitalWriteFast(PIN_1, HIGH);
  digitalWriteFast(PIN_2, HIGH);
  digitalWriteFast(PIN_3, HIGH);
  digitalWriteFast(PIN_4, HIGH);
  digitalWriteFast(PIN_5, LOW);
  digitalWriteFast(PIN_6, HIGH);
  digitalWriteFast(PIN_9, LOW);

  Serial1.begin(921600);
}

FASTRUN void updatePORTD(int pin1, int pin2, int pin3, int pin4, int pin5, int pin6, int pin9)
{
  int newVal = (pin1 << PIN_1_BIT) | (pin2 << PIN_2_BIT) | (pin3 << PIN_3_BIT) | (pin4 << PIN_4_BIT) | ((!pin5) << PIN_5_BIT) | (pin6 << PIN_6_BIT) | ((!pin9) << PIN_9_BIT); // form mask of new values
  GPIOD_PDOR = (GPIOD_PDIR & (~PIN_BITMASK)) | newVal; // clear all of the masked pins by ANDing with the inverted bitmask... then OR in the updated bit data  
}

FASTRUN void loop() {  
  if (compatibilityMode) {
    while (1) {
      if (Serial1.available() >= 2) {
          Serial1.readBytes(data, 2);
          //Serial.println(data[0], BIN);
          //Serial.println(data[1], BIN);
          updatePORTD(data[0] & 1, (data[0] & 2) >> 1, (data[0] & 4) >> 2, (data[0] & 8) >> 3, (data[0] & 32) >> 5, HIGH, (data[0] & 64) >> 6);
      }
    }
  }
  else {
    while (1) {
      if (Serial1.available() >= 2) {
          Serial1.readBytes(data, 2);
          //Serial.println(data[0], BIN);
          //Serial.println(data[1], BIN);
          updatePORTD(data[0] & 1, (data[0] & 2) >> 1, (data[0] & 4) >> 2, (data[0] & 8) >> 3, (data[0] & 32) >> 5, (data[0] & 16) >> 4, (data[0] & 64) >> 6);
      }
    }
  }
}
