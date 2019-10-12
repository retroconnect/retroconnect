const byte DATA_PIN = 22;  //RED
const byte CLOCK_PIN = 21; //YELLOW
const byte LATCH_PIN = 27; //WHITE
int clock_counter = 0;
char data_arr[2];

void setup() {
  pinMode(DATA_PIN, OUTPUT);
  pinMode(CLOCK_PIN, INPUT);
  pinMode(LATCH_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(CLOCK_PIN), clock_isr, RISING);
  attachInterrupt(digitalPinToInterrupt(LATCH_PIN), latch_isr, RISING);
  Serial2.begin(115200);
}

void latch_isr() {
  if (data_arr[0] & 1) {
    GPIO.out_w1ts = ((uint32_t)1 << 22); //1
  }
  else {
    GPIO.out_w1tc = ((uint32_t)1 << 22); //0
  }
  //digitalWrite(DATA_PIN, data_arr[0] & 1);
  clock_counter = 1;
}

void clock_isr() {
  if ((data_arr[clock_counter / 8] >> clock_counter % 8) & 1) {
      GPIO.out_w1ts = ((uint32_t)1 << 22); //1
  }
  else {
      GPIO.out_w1tc = ((uint32_t)1 << 22); //0
  }
  //digitalWrite(DATA_PIN, (data_arr[0] >> clock_counter % 8) & 1);
  clock_counter++;
}

void loop() {
 while (true) {
    if (Serial2.available() >= 2){
      Serial2.readBytes(data_arr, 2);
    }
}
