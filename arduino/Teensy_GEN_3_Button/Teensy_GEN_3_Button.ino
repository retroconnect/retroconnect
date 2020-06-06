//       | DE-9    TEENSY    Genesis  DIRECT  |
const byte PIN_1 = 2;     // UP       PORTD0    
const byte PIN_2 = 3;     // DOWN     PORTA12   
const byte PIN_3 = 4;     // LEFT     PORTA13   
const byte PIN_4 = 5;     // RIGHT    PORTD7    
//         PIN_5;         // (5V unused)
const byte PIN_6 = 6;     // FIRE1    PORTD4    
const byte PIN_7 = 7;     // SELECT   PORTD2  
//         PIN_8;         // GND
const byte PIN_9 = 8;     // FIRE2    PORTD3    

char data[2];

/*
  Low = pressed

  Pin  Connection
  ---  ---------------
  5   Power: +5 Volts
  7   Select signal
  8   Power: Ground

  Pin  Connection with select low  Connection with select high
  ---  --------------------------  ---------------------------
  2   joypad up signal            joypad up signal
  3   joypad down signal          joypad down signal
  4   logic low (ground)          joypad left signal
  5   logic low (ground)          joypad right signal
  6   Button A signal             Button B signal
  9   Start button signal         Button C signal
*/

void setup() {
  //Serial.begin(115200);
  //Serial.print("Started program!\n");
  pinMode(PIN_1, OUTPUT); //UP    | Z
  pinMode(PIN_2, OUTPUT); //DOWN  | Y
  pinMode(PIN_3, OUTPUT); //LEFT  | X
  pinMode(PIN_4, OUTPUT); //RIGHT | MODE
  pinMode(PIN_6, OUTPUT); //B     | A
  pinMode(PIN_9, OUTPUT); //C     | START

  pinMode(PIN_7, INPUT_PULLUP);  //SELECT
  
  data[0] = 255;
  data[1] = 255;

  digitalWriteFast(PIN_1, HIGH);
  digitalWriteFast(PIN_2, HIGH);
  digitalWriteFast(PIN_3, HIGH);
  digitalWriteFast(PIN_4, HIGH);
  digitalWriteFast(PIN_6, HIGH);
  digitalWriteFast(PIN_9, HIGH);

  attachInterrupt(digitalPinToInterrupt(PIN_7), select_isr, CHANGE); //SELECT
  NVIC_SET_PRIORITY(IRQ_PORTD, 0);

  Serial1.begin(921600);
}

FASTRUN void select_isr() {
  if (digitalReadFast(PIN_7)) {
    //Serial.print("HIGH\n");
    digitalWriteFast(PIN_3, data[0] & 4);  //LEFT
    digitalWriteFast(PIN_4, data[0] & 8);  //RIGHT
    digitalWriteFast(PIN_1, data[0] & 1);  //UP
    digitalWriteFast(PIN_2, data[0] & 2);  //DOWN
    digitalWriteFast(PIN_6, data[0] & 16); //B
    digitalWriteFast(PIN_9, data[0] & 32); //C
  }
  else {
    //Serial.print("LOW\n");
    digitalWriteFast(PIN_3, LOW);            //Set low to indicate controller connected
    digitalWriteFast(PIN_4, LOW);            //Set low to indicate controller connected
    digitalWriteFast(PIN_6, data[0] & 64);  //A
    digitalWriteFast(PIN_9, data[0] & 128); //START
  }
}

FASTRUN void loop() {
  if (Serial1.available() >= 2) {
      Serial1.readBytes(data, 2);
      //Serial.println(data[0], BIN);
      //Serial.println(data[1], BIN);
  }
}
