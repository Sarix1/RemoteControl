unsigned long g_time;
int speed, lowest, highest;

void setup()
{
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

void loop()
{
  speed = g_time - 1500;
  Serial.println(speed);
}
