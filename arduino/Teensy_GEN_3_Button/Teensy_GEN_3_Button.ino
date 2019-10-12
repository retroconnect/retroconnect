//       | GEN   TEENSY  Genesis  DIRECT  |
const byte PIN_1 = 2; // UP       PORTD0    
const byte PIN_2 = 3; // DOWN     PORTA12   
const byte PIN_3 = 4; // LEFT     PORTA13   
const byte PIN_4 = 5; // RIGHT    PORTD7    
//const byte PIN_5;   // (5V unused)
const byte PIN_6 = 6; // FIRE1    PORTD4    
const byte PIN_7 = 7; // SELECT   PIND2     
const byte PIN_9 = 8; // FIRE2    PORTD3    

//int pulse = -1;
//bool six_button_mode = true;
char data[2];

/*
  Handle mode buton
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
  Serial.write("Started program!\n");
  pinMode(PIN_1, OUTPUT); //UP    | Z
  pinMode(PIN_2, OUTPUT); //DOWN  | Y
  pinMode(PIN_3, OUTPUT); //LEFT  | X
  pinMode(PIN_4, OUTPUT); //RIGHT | MODE
  pinMode(PIN_6, OUTPUT); //B     | A
  pinMode(PIN_9, OUTPUT); //C     | START

  pinMode(PIN_7, INPUT_PULLUP);  //SELECT

  digitalWriteFast(PIN_1, HIGH);
  digitalWriteFast(PIN_2, HIGH);
  digitalWriteFast(PIN_3, HIGH);
  digitalWriteFast(PIN_4, HIGH);
  digitalWriteFast(PIN_6, HIGH);
  digitalWriteFast(PIN_9, HIGH);

  Serial1.begin(115200);
}

FASTRUN void loop() {
  while (1) {
    if (digitalReadFast(PIN_7)) {
      //Serial.print("HIGH\n");
      //if (pulse == 1) {
      digitalWriteFast(PIN_3, data[0] & 4);  //LEFT
      digitalWriteFast(PIN_4, data[0] & 8);  //RIGHT
      digitalWriteFast(PIN_1, data[0] & 1);  //UP
      digitalWriteFast(PIN_2, data[0] & 2);  //DOWN
      digitalWriteFast(PIN_6, data[0] & 16); //B
      digitalWriteFast(PIN_9, data[0] & 32); //C

    /*}
      else if (pulse == 2) {
      //Serial.print("High2\n");
      //digitalWriteFast(PIN_1, ~data[2] & 1);        //Z
      //digitalWriteFast(PIN_2, (~data[2] >> 1) & 1); //Y
      //digitalWriteFast(PIN_3, (~data[2] >> 2) & 1); //X
      //digitalWriteFast(PIN_4, (~data[2] >> 3) & 1); //MODE
      }*/
      
      while (digitalReadFast(PIN_7)) {}
      //pulse = (pulse + 1) % 4;
      //if (pulse == 1) {
      //Serial.print("LOW\n");
      digitalWriteFast(PIN_3, LOW);            //Set low to indicate controller connected
      digitalWriteFast(PIN_4, LOW);            //Set low to indicate controller connected
      digitalWriteFast(PIN_6, data[0] & 64);  //A
      digitalWriteFast(PIN_9, data[0] & 128); //START

      //Serial.print("\n");
      /*Serial.print(((~data[1] >> 1) & 1));
      Serial.print(((~data[1] >> 2) & 1));
      Serial.print(((~data[1] >> 3) & 1));
      Serial.print(((~data[1] >> 4) & 1));
      Serial.print(((~data[1] >> 5) & 1));
      Serial.print(((~data[1] >> 6) & 1));
      Serial.print(((~data[1] >> 7) & 1));
      Serial.print("\n\n");*/
      //}
      /*else if (pulse == 2 && six_button_mode) {
      //Serial.print("Low2\n");
      //digitalWriteFast(PIN_1, LOW);                 //Set low to indicate six button mode
      //digitalWriteFast(PIN_2, LOW);                 //Set low to indicate six button mode
      //digitalWriteFast(PIN_3, HIGH); //CLEAR LEFT
      //digitalWriteFast(PIN_4, HIGH); //CLEAR RIGHT
      //digitalWriteFast(PIN_6, HIGH); //CLEAR B
      //digitalWriteFast(PIN_9, HIGH); //CLEAR C
      }
      else if (pulse == 3) {
      //digitalWriteFast(PIN_1, HIGH); //CLEAR ALL BUTTONS
      //digitalWriteFast(PIN_2, HIGH);
      //digitalWriteFast(PIN_3, HIGH);
      //digitalWriteFast(PIN_4, HIGH);
      //digitalWriteFast(PIN_6, HIGH);
      //digitalWriteFast(PIN_9, HIGH);
      }*/
    }
  
    if (Serial1.available() >= 2) {
      //Serial.print("READ\n");
      Serial1.readBytes(data, 2);
    }
  }
}
