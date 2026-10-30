int sensor_pin = 2;
int Mot_En1 = 3;
int Mot_In1 = 4;
int Mot_In2 = 5;
int Mot_En2 = 6;
int Mot_In3 = 7;
int Mot_In4 = 8;
int buz_pin = 9;
int led_pin1 = 10;
int led_pin2 = 11;

static int cntr;
static bool deb_out, sleep_detect;

void setup() 
{
  Serial.begin(9600);
  pinMode(sensor_pin, INPUT);
  pinMode(Mot_In1, OUTPUT);
  pinMode(Mot_In2, OUTPUT);
  pinMode(Mot_En1, OUTPUT);
  pinMode(Mot_In3, OUTPUT);
  pinMode(Mot_In4, OUTPUT);
  pinMode(Mot_En2, OUTPUT);
  pinMode(led_pin1, OUTPUT);
  pinMode(led_pin2, OUTPUT);
  pinMode(buz_pin, OUTPUT);
  digitalWrite(Mot_In1, LOW);
  digitalWrite(Mot_In2, HIGH);
  analogWrite(Mot_En1, 255);
  digitalWrite(Mot_In3, LOW);
  digitalWrite(Mot_In4, HIGH);
  analogWrite(Mot_En2, 255);
}

void loop() 
{
  int sensor_data = digitalRead(sensor_pin);
  Serial.print(sensor_data);
  Serial.print(" \t");

  sleep_detect = deb_cntr(sensor_data, 1200);
  if(sleep_detect == true)
  {
    Motor_Ctrl();
   
    while(1)
    {
      digitalWrite(Mot_In1, LOW);
      digitalWrite(Mot_In2, LOW);
      digitalWrite(Mot_In3, LOW);
      digitalWrite(Mot_In4, LOW);
      Led_Buzz_Ctrl();
    }
  }
  Serial.println(sleep_detect);
}

//Debounce counter to detect the sleep
bool deb_cntr(bool inp, int count)
{
  if(inp == false)
  {
    cntr+=1;
    if(cntr >= count)
    {
      deb_out = true;
    }
  }
  else
  {
    deb_out = false;
    cntr = 0;
  }
  return deb_out;
}

//Led and Buzzer ctrl
void Led_Buzz_Ctrl()

{
  digitalWrite(led_pin1, HIGH);
  digitalWrite(led_pin2, HIGH);
  digitalWrite(buz_pin, HIGH);
  delay(250);
  digitalWrite(led_pin1, LOW);
  digitalWrite(led_pin2, LOW);
  digitalWrite(buz_pin, LOW);
  delay(250);
}

//Motor ctrl
void Motor_Ctrl()
{
  for(int i=255; i>=0; i--)
  {
    analogWrite(Mot_En1, i);
    analogWrite(Mot_En2, i);
    delay(5);
  }
}