//       | DE-9    TEENSY    Genesis         DIRECT  |
const byte PIN_1 = 2;     // UP     | Z      PORTD0    
const byte PIN_2 = 20;    // DOWN   | Y      PORTD5
const byte PIN_3 = 21;    // LEFT   | X      PORTD6   
const byte PIN_4 = 5;     // RIGHT  | MODE   PORTD7    
//         PIN_5;         // (5V unused)
const byte PIN_6 = 6;     // B      | A      PORTD4    
const byte PIN_7 = 7;     // SELECT |        PORTD2     
//         PIN_8;         // GND
const byte PIN_9 = 8;     // C      | START  PORTD3        

char data[2];
bool sixButtonMode = true;
int state = 0;
int stateCap = 4;
int timer = 0;

const byte PIN_1_BIT = 0;
const byte PIN_2_BIT = 5;
const byte PIN_3_BIT = 6;
const byte PIN_4_BIT = 7;
const byte PIN_6_BIT = 4;
const byte PIN_7_BIT = 2;
const byte PIN_9_BIT = 3;
const byte PIN_BITMASK = (1 << PIN_1_BIT) | (1 << PIN_2_BIT) |(1 << PIN_3_BIT) |(1 << PIN_4_BIT) |(1 << PIN_6_BIT) |(1 << PIN_9_BIT); // bit mask for PORTD write updates

void setup() {
  ARM_DEMCR |= ARM_DEMCR_TRCENA;
  ARM_DWT_CTRL |= ARM_DWT_CTRL_CYCCNTENA;
  
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

  if (sixButtonMode) {
    stateCap = 8;
  } else {
    stateCap = 4;
  }

  timer = ARM_DWT_CYCCNT;
  
  attachInterrupt(digitalPinToInterrupt(PIN_7), select_isr, CHANGE); //SELECT
  NVIC_SET_PRIORITY(IRQ_PORTD, 0);

  Serial1.begin(921600);
}

FASTRUN void updatePORTD(int pin1, int pin2, int pin3, int pin4, int pin6, int pin9)
{
  int newVal = (pin1 << PIN_1_BIT) | (pin2 << PIN_2_BIT) | (pin3 << PIN_3_BIT) | (pin4 << PIN_4_BIT) | (pin6 << PIN_6_BIT) | (pin9 << PIN_9_BIT); // form mask of new values
  GPIOD_PDOR = (GPIOD_PDIR & (~PIN_BITMASK)) | newVal; // clear all of the masked pins by anding with the inverted bitmask... then or in the updated bit data  
}

FASTRUN void select_isr() {
  if (digitalReadFast(PIN_7)) {
    //Serial.print("HIGH\n");
    switch (state) {
      case 1:
      case 3:
      case 7:
        updatePORTD(data[0] & 1, (data[0] & 2) >> 1, (data[0] & 4) >> 2, (data[0] & 8) >> 3, (data[0] & 16) >> 4, (data[0] & 32) >> 5);
        break;    
      case 5:
        updatePORTD((data[1] & 2) >> 1, (data[1] & 4) >> 2, (data[1] & 8) >> 3, data[1] & 1, (data[0] & 16) >> 4, (data[0] & 32) >> 5);
        break;
      default:
        state++;
        break;
    } 
  }
  else {
    //Serial.print("LOW\n");
    int temp = ARM_DWT_CYCCNT;
    int diff = temp - timer;
    if (sixButtonMode && (diff > 8400 || diff < 0)) {
      state = 0;
      timer = temp;
    }
          
    switch(state) {
      case 0:
      case 2:
        updatePORTD(data[0] & 1, (data[0] & 2) >> 1, LOW, LOW, (data[0] & 64) >> 6, (data[0] & 128) >> 7);
        break;
      case 4:
        updatePORTD(LOW, LOW, LOW, LOW, (data[0] & 64) >> 6, (data[0] & 128) >> 7);
        break;
      case 6:
        updatePORTD(HIGH, HIGH, HIGH, HIGH, (data[0] & 64) >> 6, (data[0] & 128) >> 7);
        break;
      default:
        state++;
        break;
    }
  }
  state = (state+1) % stateCap;
}

FASTRUN void loop() {
  if (Serial1.available() >= 2) {
      Serial1.readBytes(data, 2);
      //Serial.println(data[0], BIN);
      //Serial.println(data[1], BIN);
  }
}
