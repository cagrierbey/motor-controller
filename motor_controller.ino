#include <AFMotor.h>

int button_one = 42;
int button_two = 44;
int button_one_state=0;
int button_two_state=0;
int speed_ratio = 256/4;
int speed_value = 0;
boolean motor_direction = true;//true clockwise
int seven_segment_output = 0;

// 7segmentPinleri tanımlıyoruz
int a = 51; 
int b = 50;
int c = 47;
int d = 48;
int e = 49;
int f = 52;
int g = 53;//kahverengi

AF_DCMotor motor(1);

void setup() {
  // put your setup code here, to run once:
  //Set initial speed of the motor & stop
  motor.setSpeed(speed_value);
  motor.run(RELEASE);
  pinMode(button_one, INPUT);
  pinMode(button_two, INPUT);
  motor.run(FORWARD);
  display_seven_segment(0);
  Serial.begin(9600);
}

void loop() {
  //display_seven_segment(4);
  button_one_state = digitalRead(button_one);
  
  if(button_one_state == HIGH)
  {
    delay(500);
    Serial.println("button111bastım");
    if(motor_direction)
    {
      speed_value += speed_ratio;
      if(seven_segment_output < 4)
      {
        seven_segment_output++;
        display_seven_segment(seven_segment_output);
      }

      if(speed_value >=255)
      {
        
        speed_value = 255;
      }
      
      
      motor.setSpeed(speed_value);
      delay(20);
    }
    else
    {    
    
      speed_value -= speed_ratio;
      if(speed_value <= 0)
      {
        speed_value = 0;
        motor.run(RELEASE);
        motor.setSpeed(speed_value);
        motor.run(BACKWARD);
        motor_direction = true;
        seven_segment_output = 0;
        display_seven_segment(seven_segment_output);
        delay(20);
      }

      else if(speed_value > 0)
      {
        seven_segment_output--;   
        display_seven_segment(seven_segment_output);    
        motor.setSpeed(speed_value);
        delay(20);
      }
      
    }
  }

  button_two_state = digitalRead(button_two);
  
  if(button_two_state == HIGH)
  {
    delay(500);
    Serial.println("button2bastım");
    if(!motor_direction)
    {
      speed_value += speed_ratio;
      if(speed_value >=255)
      {
        speed_value = 255;
      }
      
      if(seven_segment_output < 4)
      {
        seven_segment_output++;
        display_seven_segment(seven_segment_output);
      }
      motor.setSpeed(speed_value);
      delay(20);
    }
    else
    {
      speed_value -= speed_ratio;
      if(speed_value <= 0)
      {
        seven_segment_output = 0;
        display_seven_segment(seven_segment_output);
        speed_value = 0;
        motor.run(RELEASE);
        motor.setSpeed(speed_value);
        motor.run(FORWARD);
        motor_direction = false;
        delay(20);
      }

      else if(speed_value > 0)
      {
        seven_segment_output--;
        display_seven_segment(seven_segment_output);
        motor.setSpeed(speed_value);
        delay(20);
      }
      
    }
  }
}
void display_seven_segment(int display_count)
{
  if(display_count == 1)
  {
    // "1" Sayısını yazar.
    digitalWrite(a, LOW);
    digitalWrite(b,HIGH);
    digitalWrite(c,HIGH);
    digitalWrite(d,LOW);
    digitalWrite(e,LOW);
    digitalWrite(f,LOW);
    digitalWrite(g,LOW);
  }
  else if(display_count == 4)
  {
    digitalWrite(a, LOW);
    digitalWrite(b,HIGH);
    digitalWrite(c,HIGH);
    digitalWrite(d,LOW);
    digitalWrite(e,LOW);
    digitalWrite(f,HIGH);
    digitalWrite(g,HIGH);
  }
  else if(display_count == 3)
  {
    digitalWrite(a, HIGH);
    digitalWrite(b,HIGH);
    digitalWrite(c,HIGH);
    digitalWrite(d,HIGH);
    digitalWrite(e,LOW);
    digitalWrite(f,LOW);
    digitalWrite(g,HIGH);
  }
  else if(display_count == 2)
  {
    digitalWrite(a, HIGH);
    digitalWrite(b,HIGH);
    digitalWrite(c,LOW);
    digitalWrite(d,HIGH);
    digitalWrite(e,HIGH);
    digitalWrite(f,LOW);
    digitalWrite(g,HIGH);
  }

  else if(display_count == 0)
  {
    digitalWrite(a,HIGH);
    digitalWrite(b,HIGH);
    digitalWrite(c,HIGH);
    digitalWrite(d,HIGH);
    digitalWrite(e,HIGH);
    digitalWrite(f,HIGH);
    digitalWrite(g,LOW);
  }
  
}
