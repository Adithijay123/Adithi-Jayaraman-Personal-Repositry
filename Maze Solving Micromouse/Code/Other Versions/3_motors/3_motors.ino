int motor1A = 14;
int motor1B = 15;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(motor1A, OUTPUT);
  pinMode(motor1B, OUTPUT);
}

void loop() {
  digitalWrite(LED_BUILTIN, LOW);
  digitalWrite(motor1A, LOW);
  digitalWrite(motor1B, LOW);
  delay(1000);
  digitalWrite(LED_BUILTIN, HIGH);
  digitalWrite(motor1A, LOW);
  digitalWrite(motor1B, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  digitalWrite(motor1A, LOW);
  digitalWrite(motor1B, LOW);
  delay(1000);
  digitalWrite(LED_BUILTIN, HIGH);
  digitalWrite(motor1A, HIGH);
  digitalWrite(motor1B, LOW);
  delay(1000);
}
