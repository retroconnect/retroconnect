const byte DATA = 2;
const byte CLOCK = 3;
const byte LATCH = 4;
int clock = 0;
char data[2];

void setup() {
  //Serial.write("Started program!\n");
  pinMode(DATA, OUTPUT);
  pinMode(CLOCK, INPUT);
  pinMode(LATCH, INPUT);
  attachInterrupt(digitalPinToInterrupt(CLOCK), clock_isr, RISING);
  attachInterrupt(digitalPinToInterrupt(LATCH), latch_isr, RISING);
  Serial1.begin(115200);
}

void latch_isr() {
  digitalWriteFast(DATA, data[0] & 1);
  clock = 1;
}

void clock_isr() {
  digitalWriteFast(DATA, (data[clock / 8] >> clock % 8) & 1);
  clock++;
}

void loop() {
 while (true) {
    if (Serial1.available() >= 2) {
      Serial1.readBytes(data, 2);
    }
  }
}
