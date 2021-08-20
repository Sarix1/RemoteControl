#define INPUT_CENTER            1500
#define INPUT_MAX_DISPLACEMENT  500
#define INPUT_THRESHOLD_MIN     25
#define INPUT_THRESHOLD_MAX     475
#define MAX_MOTOR_SPEED         100
#define TURN_RATE_INVERSE       2
#define INPUT_TO_SPEED_RATIO    5

#define PIN_Y 2
#define PIN_X 3

int input_x, input_y, motor_left, motor_right;
int control_x, control_y;

void setup()
{
  attachInterrupt(digitalPinToInterrupt(PIN_Y), get_axis_y, CHANGE);
  attachInterrupt(digitalPinToInterrupt(PIN_X), get_axis_x, CHANGE);
  pinMode(PIN_Y, INPUT);
  pinMode(PIN_X, INPUT);
  Serial.begin(9600);
}

void get_axis_y()
{
  static int flip = 0;
  static unsigned long time;

  if (flip == 0)
    time = micros();
  else
    input_y = micros() - time - INPUT_CENTER;

  flip ^= 1;
}

void get_axis_x()
{
  static int flip = 0;
  static unsigned long time;

  if (flip == 0)
    time = micros();
  else
    input_x = micros() - time - INPUT_CENTER;

  flip ^= 1;
}

int filter_value(int in_value)
{
  int out_value;
  
  if (in_value > -INPUT_THRESHOLD_MIN && in_value < INPUT_THRESHOLD_MIN)
    out_value = 0;
  else if (in_value > INPUT_THRESHOLD_MAX)
    out_value = INPUT_MAX_DISPLACEMENT;
  else if (in_value < -INPUT_THRESHOLD_MAX)
    out_value = -INPUT_MAX_DISPLACEMENT;
  else
    out_value = in_value;

  return out_value;
}

int cap(int value, int cap)
{
  if (value > cap)
    return cap;
  else if (value < -cap)
    return -cap;
  return value;
}

void loop()
{
  control_x   = filter_value(input_x) / INPUT_TO_SPEED_RATIO;
  control_y   = filter_value(input_y) / INPUT_TO_SPEED_RATIO;
  motor_left  = cap(control_y + (control_x / TURN_RATE_INVERSE), MAX_MOTOR_SPEED);
  motor_right = cap(control_y - (control_x / TURN_RATE_INVERSE), MAX_MOTOR_SPEED);
  
  Serial.print(motor_left);
  Serial.print(" ");
  Serial.print(motor_right);
  Serial.print("\n");
}
