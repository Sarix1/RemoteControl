unsigned long g_time;

void setup() {
  // put your setup code here, to run once:
  attachInterrupt(digitalPinToInterrupt(2), get_time, CHANGE);
  pinMode(2, INPUT);
  Serial.begin(9600);
}

void get_time()
{
  static int flip = 0;
  static unsigned long time;

  if (flip == 0)
    time = micros();
  else
    g_time = micros() - time;

  flip ^= 1;
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(g_time);
}
