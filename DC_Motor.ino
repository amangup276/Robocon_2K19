// For DC Motor

class DC_Motor 
{ 
  private:
  
  float speed_motor;
  int direction_motor;
  int stop_motor;
  byte speed_motor_pin;
  byte direction_motor_pin;
  byte stop_motor_pin;
  
  public:

  DC_Motor(byte pin1,byte pin2,byte pin3)
  {
     speed_motor_pin=pin1;  //speed_motor_pin is digital output pin for analog output.
     direction_motor_pin=pin2;  //direction_motor_pin is digital output pin for digital output.
     stop_motor_pin=pin3;  //stop_motor_pin is digital output pin for digital output.
  }

   DC_Motor(byte pin1,byte pin2)
  {
     speed_motor_pin=pin1;
     direction_motor_pin=pin2;
     stop_motor_pin=-1;
     stop_motor=0;
  }

 void Initialize()
 {
  pinMode(speed_motor_pin, OUTPUT);
  pinMode(direction_motor_pin, OUTPUT);
   if (stop_motor_pin != -1)
   pinMode(stop_motor_pin, OUTPUT);
   speed_motor=0;
   direction_motor=1; 
   stop_motor=0;
   analogWrite(speed_motor_pin, speed_motor);
   digitalWrite(direction_motor_pin, direction_motor);
   if (stop_motor_pin != -1)
   digitalWrite(stop_motor_pin, stop_motor);
 }

 void Write(float spd_mtr,int dir_mtr)
 {
  if (stop_motor==0)
  {
     speed_motor=spd_mtr;
     direction_motor=dir_mtr;
     analogWrite(speed_motor_pin, speed_motor);
   digitalWrite(direction_motor_pin, direction_motor);
     //digitalWrite(stop_motor_pin, stop_motor);
  }
 }

void Write(float spd_mtr,int dir_mtr,int stop_mtr)
 {
     speed_motor=spd_mtr;
     direction_motor=dir_mtr;
     stop_motor=stop_mtr;
     digitalWrite(direction_motor_pin, direction_motor);
     digitalWrite(stop_motor_pin, stop_motor);
 }

 void Stop_motor()
 {
  if (stop_motor_pin != -1)
  {
  stop_motor=1;
  digitalWrite(stop_motor_pin, stop_motor);
  }
  else
  {
    speed_motor=0;
    analogWrite(speed_motor_pin, speed_motor);
  }
 }

 void Start_motor()
 {
  if (stop_motor_pin != -1)
  {
  stop_motor=0;
  digitalWrite(stop_motor_pin, stop_motor);
  }
  else
  {
    // something to be done.
  }
 }

 void Debug()
 {
  Serial.print(" Speed: ");
  Serial.print(speed_motor);
  Serial.print("\t");
  Serial.print(" Direction: ");
  Serial.print(direction_motor);
  Serial.print("\t");
 }
  
};

DC_Motor D1(6,7,8),D2(6,7);

void setup()
{
  Serial.begin(9600);
  D1.Initialize();
  D2.Initialize();
}

void loop()
{
  D1.Write(102,1,0);
  D2.Write(102,1);
  D1.Debug();
  Serial.print("\n");
  D2.Debug();
  Serial.print("\n");
  delay(500);
  D1.Stop_motor();
  D1.Debug();
  delay(500);
  D1.Start_motor();
  D1.Debug();
  delay(500);
}
