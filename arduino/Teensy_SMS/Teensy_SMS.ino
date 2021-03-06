//       | DE-9    TEENSY    SMS         DIRECT  |
const byte PIN_1 = 2;     // UP          PORTD0    
const byte PIN_2 = 20;    // DOWN        PORTD5
const byte PIN_3 = 21;    // LEFT        PORTD6   
const byte PIN_4 = 5;     // RIGHT       PORTD7    
//         PIN_5;         // (5V unused)
const byte PIN_6 = 6;     // 1           PORTD4    
//         PIN_7;         // (unused)
//         PIN_8;         // GND     
const byte PIN_9 = 8;     // 2           PORTD3    

char data[2];

const byte PIN_1_BIT = 0;
const byte PIN_2_BIT = 5;
const byte PIN_3_BIT = 6;
const byte PIN_4_BIT = 7;
const byte PIN_6_BIT = 4;
const byte PIN_9_BIT = 3;
const byte PIN_BITMASK = (1 << PIN_1_BIT) | (1 << PIN_2_BIT) |(1 << PIN_3_BIT) |(1 << PIN_4_BIT) |(1 << PIN_6_BIT) |(1 << PIN_9_BIT); // bit mask for PORTD write updates


/*
  Low = pressed

  Pin  Connection
  ---  ---------------
  5   Power: +5 Volts
  8   Power: Ground

  Pin  Connection
  ---  ---------------
  2   joypad up signal
  3   joypad down signal
  4   joypad left signal
  5   joypad right signal
  6   Button 1 signal
  9   Button 2 signal
*/

void setup() {
  //Serial.begin(115200);
  //Serial.print("Started program!\n");
  pinMode(PIN_1, OUTPUT); //UP
  pinMode(PIN_2, OUTPUT); //DOWN
  pinMode(PIN_3, OUTPUT); //LEFT
  pinMode(PIN_4, OUTPUT); //RIGHT
  pinMode(PIN_6, OUTPUT); //1
  pinMode(PIN_9, OUTPUT); //2

  data[0] = 255;
  data[1] = 255;

  digitalWriteFast(PIN_1, HIGH);
  digitalWriteFast(PIN_2, HIGH);
  digitalWriteFast(PIN_3, HIGH);
  digitalWriteFast(PIN_4, HIGH);
  digitalWriteFast(PIN_6, HIGH);
  digitalWriteFast(PIN_9, HIGH);

  Serial1.begin(921600);
}

FASTRUN void updatePORTD(int pin1, int pin2, int pin3, int pin4, int pin6, int pin9)
{
  int newVal = (pin1 << PIN_1_BIT) | (pin2 << PIN_2_BIT) | (pin3 << PIN_3_BIT) | (pin4 << PIN_4_BIT) | (pin6 << PIN_6_BIT) | (pin9 << PIN_9_BIT); // form mask of new values
  GPIOD_PDOR = (GPIOD_PDIR & (~PIN_BITMASK)) | newVal; // clear all of the masked pins by anding with the inverted bitmask... then or in the updated bit data  
}

FASTRUN void loop() {
  while (1) {
    if (Serial1.available() >= 2) {
        Serial1.readBytes(data, 2);
        //Serial.println(data[0], BIN);
        //Serial.println(data[1], BIN);
        updatePORTD(data[0] & 1, (data[0] & 2) >> 1, (data[0] & 4) >> 2, (data[0] & 8) >> 3, (data[0] & 16) >> 4, (data[0] & 32) >> 5);     
    }
  }
}
