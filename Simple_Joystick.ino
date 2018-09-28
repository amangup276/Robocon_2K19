// For Simple Joystick
// speed_joystick is in range of 1 to 1024 if input for the arduino if from 1 to 1024 ,not 1 to 5.

# include<math.h>
const float pi=3.14159;
class Joystick
{
  private:
  
  float x_value,initial_x_value;
  float y_value,initial_y_value;
  float horizontal_value,vertical_value;
  float speed_joystick;
  float angle_joystick; // Angle is in degree.
  // x_pin and y_pin are analog input pins for analog input. 
  byte x_pin;
  byte y_pin;
  // speed_joystick_pin and angle_joystick_pin are digital output pins for analog output.
  byte speed_joystick_pin;
  byte angle_joystick_pin;
  
  public:

  Joystick (byte pin1,byte pin2)
  {
    x_pin=pin1;
    y_pin=pin2;
  }

  void Joystick_output_pins (byte pin3,byte pin4)
  {
    speed_joystick_pin=pin3;
    angle_joystick_pin=pin4;
  }

 void Initialize()
 {
  pinMode(x_pin,INPUT);
  pinMode(y_pin,INPUT);
  pinMode(speed_joystick_pin, OUTPUT);
  pinMode(angle_joystick_pin, OUTPUT);
  initial_x_value=analogRead(x_pin);
  initial_y_value=analogRead(y_pin);
 }

 void Read()
 {
     x_value=analogRead(x_pin);
     y_value=analogRead(y_pin);
 }

 void Calculate()
 {
  
    horizontal_value=x_value-initial_x_value;
    vertical_value=y_value-initial_y_value;
    
    if ( horizontal_value==0 && vertical_value==0)
    {
      angle_joystick=0;
    }
    
    // The range of atan(x) is from -pi to pi.

    else 
    {
      angle_joystick=atan(vertical_value/horizontal_value)*360.0/pi;
      if (horizontal_value>=0)
      {
        if (vertical_value>=0)
        {
          angle_joystick=angle_joystick;
        }
        else
        {
          angle_joystick=360.0+angle_joystick;
        }
      } 
      else 
      {
        if (vertical_value>=0)
        {
          angle_joystick=90.0-angle_joystick;
        }
        else
        {
          angle_joystick=180.0+angle_joystick;
        }
      }
    }

    if (horizontal_value==0 && vertical_value==0)
    {
      speed_joystick=0;
    } 
    
    else
    {
      speed_joystick=sqrt((horizontal_value*horizontal_value)+(vertical_value*vertical_value));
       if ( abs(horizontal_value) >= abs(vertical_value) )
         {
           //speed_joystick=(speed_joystick)*(512.0)*sqrt(2)/(speed_joystick)*(512/horizontal_value);
           speed_joystick=sqrt(2)*horizontal_value;
         }
       else
         {
           speed_joystick=sqrt(2)*vertical_value;
         }
    }
 }

 void Update()
 {
     Calculate();
     analogWrite(speed_joystick_pin, speed_joystick);
     analogWrite(angle_joystick_pin, angle_joystick);
 }

 void Debug()
 {
  
  Serial.print(" Initial_X: ");
  Serial.print(initial_x_value);
  Serial.print("\t");
  
  Serial.print(" Initial_Y: ");
  Serial.print(initial_y_value);
  Serial.print("\t");
  
  Serial.print(" X: ");
  Serial.print(x_value);
  Serial.print("y_value");
  
  Serial.print(" Y: ");
  Serial.print(speed_joystick);
  Serial.print("\t");
  
  Serial.print(" Speed: ");
  Serial.print(speed_joystick);
  Serial.print("\t");
  
  Serial.print(" Angle: ");
  Serial.print(angle_joystick);
  Serial.print("\t");
  
 }
  
};
Joystick J1(A0,A1);
void setup()
{
  Serial.begin(9600);
  J1.Joystick_output_pins(5,6);
  J1.Initialize();
}

void loop()
{
  J1.Read();
  J1.Update();
  J1.Debug();
  Serial.print("\n");
  delay(100);
}
