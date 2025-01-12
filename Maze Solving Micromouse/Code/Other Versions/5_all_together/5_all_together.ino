int ldr1 = 26;
int motor1A = 14;
int motor1B = 15;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(motor1A, OUTPUT);
  pinMode(motor1B, OUTPUT);
  pinMode(ldr1, INPUT);
}

void loop() {
  int raw_value = 0;
  raw_value = analogRead(ldr1);
  int scaled_value = map(raw_value, 0, 1023, 0, 255);
  analogWrite(motor1A, 0);
  analogWrite(motor1B, scaled_value);
  analogWrite(LED_BUILTIN, scaled_value);
}
