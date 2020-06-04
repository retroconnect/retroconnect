#include "soc/timer_group_struct.h"
#include "soc/timer_group_reg.h"

static portMUX_TYPE my_mutex;

//       | GEN     ESP32  Genesis    |
const byte PIN_1 = 22; // UP           
const byte PIN_2 = 21; // DOWN        
const byte PIN_3 = 27; // LEFT        
const byte PIN_4 = 25; // RIGHT        
//         PIN_5;      // (5V unused)
const byte PIN_6 = 32; // FIRE1        
const byte PIN_7 = 26; // SELECT   
//         PIN_8;      // GND 
const byte PIN_9 = 18; // FIRE2  
//PIN_RX = 16
//PIN_TX = 17         

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
  Serial.begin(115200);
  Serial.write("Started program!\n");
  
  pinMode(PIN_1, OUTPUT); //UP    | Z
  pinMode(PIN_2, OUTPUT); //DOWN  | Y
  pinMode(PIN_3, OUTPUT); //LEFT  | X
  pinMode(PIN_4, OUTPUT); //RIGHT | MODE
  pinMode(PIN_6, OUTPUT); //B     | A
  pinMode(PIN_9, OUTPUT); //C     | START
  pinMode(PIN_7, INPUT_PULLUP);  // SELECT

  digitalWrite(PIN_1, HIGH);
  digitalWrite(PIN_2, HIGH);
  digitalWrite(PIN_3, HIGH);
  digitalWrite(PIN_4, HIGH);
  digitalWrite(PIN_6, HIGH);
  digitalWrite(PIN_9, HIGH);

  Serial2.begin(921600);
  
  vPortCPUInitializeMutex(&my_mutex);
  
  TaskHandle_t Task1;
  xTaskCreatePinnedToCore(
      SerialHandler,   /* Function to implement the task */
      "SerialHandler", /* Name of the task */
      10000,           /* Stack size in words */
      NULL,            /* Task input parameter */
      1,               /* Priority of the task */
      &Task1,          /* Task handle. */
      0);              /* Core where the task should run */
}

void Feed_Watchdogs(){
  // feed dog 0
  TIMERG0.wdt_wprotect=TIMG_WDT_WKEY_VALUE; // write enable
  TIMERG0.wdt_feed=1;                       // feed dog
  TIMERG0.wdt_wprotect=0;                   // write protect
  // feed dog 1
  TIMERG1.wdt_wprotect=TIMG_WDT_WKEY_VALUE; // write enable
  TIMERG1.wdt_feed=1;                       // feed dog
  TIMERG1.wdt_wprotect=0;                   // write protect
}

void SerialHandler( void * parameter) {
  while(1) {
    if (Serial2.available() >= 2) {
      //Serial.print("READ\n");
      Serial2.readBytes(data, 2);
    }
    Feed_Watchdogs();
  }
}

void loop() {
  while (1) {    
    portENTER_CRITICAL(&my_mutex);

    while((GPIO.in >> PIN_7) & 0x1 == HIGH) {} //Wait for SELECT LOW

    //State 0
    GPIO.out_w1tc = ((uint32_t)1 << PIN_3); //Set low to indicate controller connected
    GPIO.out_w1tc = ((uint32_t)1 << PIN_4); //Set low to indicate controller connected

    if (data[0] & 64) {
      GPIO.out1_w1ts.val = ((uint32_t)1 << PIN_6 - 32); //A
    }
    else {
      GPIO.out1_w1tc.val = ((uint32_t)1 << PIN_6 - 32);
    }
   
    if (data[0] & 128) {
      GPIO.out_w1ts = ((uint32_t)1 << PIN_9); //START
    }
    else {
      GPIO.out_w1tc = ((uint32_t)1 << PIN_9);
    }

    //SELECT is held LOW for many milliseconds; pre-set signals for state 1
    
    delayMicroseconds(1);
    if (data[0] & 4) {
      GPIO.out_w1ts = ((uint32_t)1 << PIN_3); //LEFT
    }
    if (data[0] & 8) {
      GPIO.out_w1ts = ((uint32_t)1 << PIN_4); //RIGHT
    }
    if (data[0] & 1) {
      GPIO.out_w1ts = ((uint32_t)1 << PIN_1); //UP
    }
    else {
      GPIO.out_w1tc = ((uint32_t)1 << PIN_1);
    }
    if (data[0] & 2) {
      GPIO.out_w1ts = ((uint32_t)1 << PIN_2); //DOWN
    }
    else {
      GPIO.out_w1tc = ((uint32_t)1 << PIN_2);
    }
    if (data[0] & 16) {
      GPIO.out1_w1ts.val = ((uint32_t)1 << PIN_6 - 32); //B
    }
    else {
      GPIO.out1_w1tc.val = ((uint32_t)1 << PIN_6 - 32);
    }
    if (data[0] & 32) {
      GPIO.out_w1ts = ((uint32_t)1 << PIN_9); //C
    }
    else {
      GPIO.out_w1tc = ((uint32_t)1 << PIN_9);
    }

    while((GPIO.in >> PIN_7) & 0x1 == LOW) {}  //End State 1, inputs pre-set
    portEXIT_CRITICAL(&my_mutex);
  }
}
