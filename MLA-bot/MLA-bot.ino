#include <Arduino.h>
//#include "HX711.h"
#include "dsplib.h"

int dataI, dataO, i;

byte line_error_code = 0, sw01 = 0, sw02 = 0, sw03 = 0, sw04 = 0;
byte sensor[8] = {0, 0, 0, 0, 0, 0, 0, 0}, commands[5] = {0, 0, 0, 0, 0};
String table_error_code = "000";
int checkweight = 0, dLoop = 0;

void read_sensor_values(void);
void main_Control(void);
void checkUntrasonic(void);
void waitC(void);

// Line sensor Input
#define sensor01 A1
#define sensor02 A2
#define sensor03 A3
#define sensor04 A4
#define sensor05 A5
// Line sensor Input

// Table sensor Input
#define table_sensor01 A6
#define table_sensor02 A7
#define table_sensor03 A8
// Table sensor Input

//Load cell
//#define loadcell_sensor01 A15
//#define loadcell_sensor02 A14
//HX711 balanza(loadcell_sensor02, loadcell_sensor01);
//Load cell

// select Table  Button
#define table01 10
#define table02 11
#define table03 12
#define table04 9
// select Table  Button

//Untrasonic
#define TriggerPin 14
#define EchoPin 15
long Duration;
int Distance;
//Untrasonic

// Output
#define pwm_2 2
#define motorR 3
#define pwm_1 4
#define motorL 5
// Output
// CheckOnlineCommand 41 output
#define CommandI01 37
#define CommandI02 38
#define CommandI03 39
#define CommandI04 40
#define CommandO04 41
// CheckOnlineCommand

/*dsp Definitions*/
int Max7219_pinCS = 22;
int Max7219_pinCLK = 23;
int Max7219_pinDIN = 24;

void motor_output(int _PWM_1, int _PWM_2, int _MotorL, int _MotorR)
{
  analogWrite(pwm_1, _PWM_1);
  analogWrite(pwm_2, _PWM_2);
  analogWrite(motorL, _MotorL);
  analogWrite(motorR, _MotorR);
}

void sucess(String _code)
{
  sw01 = 0;
  sw02 = 0;
  sw03 = 0;
  sw04 = 0;
  table_error_code = _code;
  motor_output(0, 0, 0, 0);
  digitalWrite(CommandO04, HIGH);
  delay(50);
  digitalWrite(CommandO04, LOW);
  commands[0] = LOW;
  commands[1] = LOW;
  commands[2] = LOW;
  commands[3] = LOW;
}
void check_pr() {
  Serial.print("table_error_code : ");
  Serial.println(table_error_code);
  sensor[5] = digitalRead(table_sensor03);
  sensor[6] = digitalRead(table_sensor02);
  sensor[7] = digitalRead(table_sensor01);
  delay(10);
  Serial.print("sensor[5] : ");
  Serial.print(sensor[5]);
  Serial.print("    sensor[6] : ");
  Serial.print(sensor[6]);
  Serial.print("    sensor[7] : ");
  Serial.println(sensor[7]);

  Serial.print("sw01 : ");
  Serial.print(sw01);
  Serial.print("    sw02 : ");
  Serial.print(sw02);
  Serial.print("    sw03 : ");
  Serial.print(sw03);
  Serial.print("    sw04 : ");
  Serial.println(sw04);

  commands[0] = digitalRead(CommandI01);
  commands[1] = digitalRead(CommandI02);
  commands[2] = digitalRead(CommandI03);
  commands[3] = digitalRead(CommandI04);
  Serial.print("commands[0] : ");
  Serial.println(commands[0]);
  Serial.print("commands[1] : ");
  Serial.println(commands[1]);
  Serial.print("commands[2] : ");
  Serial.println(commands[2]);
  Serial.print("commands[3] : ");
  Serial.println(commands[3]);
}

void Write_Max7219_byte(unsigned char DATA)
{
  unsigned char i;
  digitalWrite(Max7219_pinCS, LOW);
  for (i = 8; i >= 1; i--)
  {
    digitalWrite(Max7219_pinCLK, LOW);
    digitalWrite(Max7219_pinDIN, DATA & 0x80); // Extracting a bit data
    DATA = DATA << 1;
    digitalWrite(Max7219_pinCLK, HIGH);
  }
}


void Write_Max7219(unsigned char address, unsigned char dat)
{
  digitalWrite(Max7219_pinCS, LOW);
  Write_Max7219_byte(address);           //address，code of LED
  Write_Max7219_byte(dat);               //data，figure on LED
  digitalWrite(Max7219_pinCS, HIGH);
}

void Init_MAX7219(void)
{
  Write_Max7219(0x09, 0x00);       //decoding ：BCD
  Write_Max7219(0x0a, 0x03);       //brightness
  Write_Max7219(0x0b, 0x07);       //scanlimit；8 LEDs
  Write_Max7219(0x0c, 0x01);       //power-down mode：0，normal mode：1
  Write_Max7219(0x0f, 0x00);       //test display：1；EOT，display：0
}

void setup()
{
  Serial.begin(9600);

  pinMode(pwm_1, OUTPUT);
  pinMode(pwm_2, OUTPUT);
  pinMode(motorL, OUTPUT);
  pinMode(motorR, OUTPUT);
  // Line sensor Input
  pinMode(sensor01, INPUT);
  pinMode(sensor02, INPUT);
  pinMode(sensor03, INPUT);
  pinMode(sensor04, INPUT);
  pinMode(sensor05, INPUT);
  // Line sensor Input

  // Table sensor Input
  pinMode(table_sensor01, INPUT);
  pinMode(table_sensor02, INPUT);
  pinMode(table_sensor03, INPUT);
  // Table sensor Input

  // select Table button
  pinMode(table01, INPUT);
  pinMode(table02, INPUT);
  pinMode(table03, INPUT);
  pinMode(table04, INPUT);
  // select Table button

  //Untrasonic
  pinMode(TriggerPin, OUTPUT);
  pinMode(EchoPin, INPUT);
  //Untrasonic
  // CheckOnlineCommand
  pinMode(CommandI01, INPUT);
  pinMode(CommandI02, INPUT);
  pinMode(CommandI03, INPUT);
  pinMode(CommandI04, INPUT);
  pinMode(CommandO04, OUTPUT);
  // CheckOnlineCommand
  //  Serial.println(balanza.read());
  //  balanza.set_scale(207.5);
  //  balanza.tare(20);
  //  set up dsp 8*8
  pinMode(Max7219_pinCLK, OUTPUT);
  pinMode(Max7219_pinCS, OUTPUT);
  pinMode(Max7219_pinDIN, OUTPUT);
  Init_MAX7219();
}

void loop()
{
  sw01 = digitalRead(table01);
  sw02 = digitalRead(table02);
  sw03 = digitalRead(table03);
  sw04 = digitalRead(table04);
  check_pr();

  //  checkweight = balanza.get_units(1), 0;

  while (sw01 == HIGH || commands[0] == HIGH)
  {
    Serial.println("Table01 ");
    check_pr();
    checkUntrasonic();
    if (Distance <= 50)
    {

      for (i = 1; i < 9; i++)
      {
        Write_Max7219(i, disp1[15][i - 1]);
      }

      motor_output(0, 0, 0, 0);
      Serial.println("error ");
    }
    else
    {
      if (table_error_code == "000")
      {
        if (sensor[5] == HIGH && sensor[6] == LOW && sensor[7] == LOW)
        {
          Serial.println("true 0001 ");
          table_error_code = "001";
          motor_output(0, 0, 0, 0);
          waitC();
        } else {
          for (i = 1; i < 9; i++)
          {
            Write_Max7219(i, disp1[1][i - 1]);
          }
          read_sensor_values();
          main_Control();
        }
      }
      if (table_error_code == "001")
      {
        if (sensor[5] == HIGH && sensor[6] == HIGH && sensor[7] == HIGH)
        {
          sucess("000");
          break;
        } else {
          for (i = 1; i < 9; i++)
          {
            Write_Max7219(i, disp1[14][i - 1]);
          }
          read_sensor_values();
          main_Control();
        }
      }
    }
  }
  while (sw02 == HIGH || commands[1] == HIGH)
  {
    check_pr();
    checkUntrasonic();
    if (Distance <= 50)
    { for (i = 1; i < 9; i++)
      {
        Write_Max7219(i, disp1[15][i - 1]);
      }
      motor_output(0, 0, 0, 0);
    }
    else
    {
      if (table_error_code == "000")
      {
        if (sensor[5] == LOW && sensor[6] == HIGH  && sensor[7] == LOW)
        {
          table_error_code = "010";
          motor_output(0, 0, 0, 0);
          waitC();
        } else {
          for (i = 1; i < 9; i++)
          {
            Write_Max7219(i, disp1[2][i - 1]);
          }
          read_sensor_values();
          main_Control();
        }
      }
      if (table_error_code == "010")
      {
        if (sensor[5] == HIGH && sensor[6] == HIGH  && sensor[7] == HIGH)
        {
          sucess("000");
          break;
        } else {
          for (i = 1; i < 9; i++)
          {
            Write_Max7219(i, disp1[14][i - 1]);
          }
          read_sensor_values();
          main_Control();
        }
      }
    }
  }
  while (sw03 == HIGH || commands[1] == HIGH)
  {
    check_pr();
    checkUntrasonic();
    if (Distance <= 50)
    { for (i = 1; i < 9; i++)
      {
        Write_Max7219(i, disp1[15][i - 1]);
      }
      motor_output(0, 0, 0, 0);
    }
    else
    {
      if (table_error_code == "000")
      {
        if (sensor[5] == LOW && sensor[6] == HIGH  && sensor[6] == HIGH)
        {
          table_error_code = "011";
          motor_output(0, 0, 0, 0);
          waitC();
        } else {
          for (i = 1; i < 9; i++)
          {
            Write_Max7219(i, disp1[3][i - 1]);
          }
          read_sensor_values();
          main_Control();
        }
      }
      if (table_error_code == "011")
      {
        if (sensor[5] == HIGH && sensor[6] == HIGH  && sensor[6] == HIGH)
        {
          sucess("000");
          break;
        } else {
          for (i = 1; i < 9; i++)
          {
            Write_Max7219(i, disp1[14][i - 1]);
          }
          read_sensor_values();
          main_Control();
        }
      }
    }
  }
  while (sw04 == HIGH || commands[1] == HIGH)
  {
    check_pr();
    checkUntrasonic();
    if (Distance <= 50)
    {
      for (i = 1; i < 9; i++)
      {
        Write_Max7219(i, disp1[15][i - 1]);
      }
      motor_output(0, 0, 0, 0);
    }
    else
    {
      if (table_error_code == "000")
      {
        if (sensor[5] == HIGH && sensor[6] == LOW  && sensor[6] == LOW)
        {
          table_error_code = "100";
          motor_output(0, 0, 0, 0);
          waitC();
        } else {
          for (i = 1; i < 9; i++)
          {
            Write_Max7219(i, disp1[4][i - 1]);
          }
          read_sensor_values();
          main_Control();
        }
      }
      if (table_error_code == "100")
      {
        if (sensor[5] == HIGH && sensor[6] == HIGH && sensor[7] == HIGH)
        {
          sucess("000");
          break;
        } else {
          for (i = 1; i < 9; i++)
          {
            Write_Max7219(i, disp1[14][i - 1]);
          }
          read_sensor_values();
          main_Control();
        }
      }
    }
  }
}
void read_sensor_values()
{
  sensor[0] = digitalRead(sensor01);
  sensor[1] = digitalRead(sensor02);
  sensor[2] = digitalRead(sensor03);
  sensor[3] = digitalRead(sensor04);
  sensor[4] = digitalRead(sensor05);

  if ((sensor[4] == 0) && (sensor[3] == 0) && (sensor[2] == 0) && (sensor[1] == 0) && (sensor[0] == 0))
  {
    line_error_code = 31;
  }
  else if ((sensor[4] == 0) && (sensor[3] == 1) && (sensor[2] == 1) && (sensor[1] == 1) && (sensor[0] == 0))
  {
    line_error_code = 17;
  }
  else if ((sensor[4] == 1) && (sensor[3] == 1) && (sensor[2] == 1) && (sensor[1] == 1) && (sensor[0] == 1))
  {
    line_error_code = 0;
  }
  else if ((sensor[4] == 0) && (sensor[3] == 1) && (sensor[2] == 1) && (sensor[1] == 0) && (sensor[0] == 0))
  {
    line_error_code = 19;
  }
  else if ((sensor[4] == 1) && (sensor[3] == 1) && (sensor[2] == 1) && (sensor[1] == 0) && (sensor[0] == 0))
  {
    line_error_code = 3;
  }
  else if ((sensor[4] == 1) && (sensor[3] == 1) && (sensor[2] == 0) && (sensor[1] == 0) && (sensor[0] == 0))
  {
    line_error_code = 7;
  }
  else if ((sensor[4] == 1) && (sensor[3] == 0) && (sensor[2] == 0) && (sensor[1] == 0) && (sensor[0] == 0))
  {
    line_error_code = 15;
  }
  else if ((sensor[4] == 0) && (sensor[3] == 0) && (sensor[2] == 1) && (sensor[1] == 1) && (sensor[0] == 0))
  {
    line_error_code = 25;
  }
  else if ((sensor[4] == 0) && (sensor[3] == 0) && (sensor[2] == 1) && (sensor[1] == 1) && (sensor[0] == 1))
  {
    line_error_code = 24;
  }
  else if ((sensor[4] == 0) && (sensor[3] == 0) && (sensor[2] == 0) && (sensor[1] == 1) && (sensor[0] == 1))
  {
    line_error_code = 28;
  }
  else if ((sensor[4] == 0) && (sensor[3] == 0) && (sensor[2] == 0) && (sensor[1] == 0) && (sensor[0] == 1))
  {
    line_error_code = 30;
  }
  else if ((sensor[4] == 0) && (sensor[3] == 1) && (sensor[2] == 1) && (sensor[1] == 1) && (sensor[0] == 1))
  {
    line_error_code = 16;
  }
  else if ((sensor[4] == 1) && (sensor[3] == 1) && (sensor[2] == 1) && (sensor[1] == 1) && (sensor[0] == 0))
  {
    line_error_code = 1;
  }
  else if ((sensor[4] == 0) && (sensor[3] == 0) && (sensor[2] == 1) && (sensor[1] == 0) && (sensor[0] == 0))
  {
    line_error_code = 4;
  }
}
void main_Control()
{
  if (line_error_code == 17)         // straight
  {
    motor_output(160, 160, 255, 255);
  }
  else if (line_error_code == 4)      // straight
  {
    motor_output(160, 160, 255, 255);
  }
  else if (line_error_code == 3)      // Turn left(2)
  {
    motor_output(160, 140, 255, 255);
  }
  else if (line_error_code == 7)      // Turn left(3)
  {
    motor_output(160, 120, 255, 255);
  }
  else if (line_error_code == 15)     // Turn left(4)
  {
    motor_output(160, 120, 255, 0);
  }
  else if (line_error_code == 19)     // Turn left(1)
  {
    motor_output(160, 150, 255, 255);
  }
  else if (line_error_code == 24)     // Turn right(2)
  {
    motor_output(140, 160, 255, 255);
  }
  else if (line_error_code == 25)     // Turn right(1)
  {
    motor_output(150, 160, 255, 255);
  }
  else if (line_error_code == 28)     // Turn right(3)
  {
    motor_output(120, 160, 255, 255);
  }
  else if (line_error_code == 30)     // Turn right(4)
  {
    motor_output(120, 160, 0, 255);
  }
  else if (line_error_code == 31)     // Back
  {
    motor_output(155, 155, 0, 0);
  }
  else if (line_error_code == 1)      // Turn right
  {
    motor_output(155, 160, 0, 255);
  }
  else if (line_error_code == 16)     // Turn left
  {
    motor_output(160, 155, 255, 0);
  }
  else if (line_error_code == 0)      // line_error_code code:Stop
  {
    motor_output(0, 0, 0, 0);
  }
}

void waitC() {
  Serial.print("in waitC");

  //  checkweight = balanza.get_units(1), 0;
  //  Serial.print("checkweight---------------------------------------------------------------- : ");
  //  Serial.println(checkweight);
  //  while (checkweight > 22) {
  //    dLoop += 1;
  //    delay(5000);
  //    if (dLoop == 2) {
  //      dLoop = 0;
  //      break;
  //    }
  //  }
  delay(10000);
}

void checkUntrasonic()
{
  digitalWrite(TriggerPin, HIGH);
  digitalWrite(TriggerPin, LOW);
  Duration = pulseIn(EchoPin, HIGH);
  Distance = Duration * 0.034 / 2;
}
