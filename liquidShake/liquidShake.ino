/*
 *  Kết nối:
 *          Driver              Arduino
 *           5V                   5V
 *           GND                  GND
 *           EN                   A0
 *           INA                  7
 *           INB                  8
 *           PWM                  5
 *           
 *  Cấp nguồn 5.5 - 16V cho Shield.
 *  Mở Serial Monitor:
 *  Gửi '1' dừng động cơ.
 *  Gửi '2' quay 2 động cơ.
 *  Gửi '3' đảo chiều động cơ.
 *  Gửi '+' tăng tốc độ động cơ.
 *  Gửi '-' giảm tốc độ động cơ.
 */

#include "PIDver1.h"
double mySetp = 0;
#define myKp  1000000000
#define myKi  0
#define myKd  0
#define myOutMax  120
#define myOutMin  -120
#define myTime 0.03
PID myPID(myKp, myKi, myKd, myTime, myOutMax, myOutMin,1);

#define CW    1
#define CCW   2

#define MOTOR_A1_PIN 7
#define MOTOR_B1_PIN 8
#define PWM_MOTOR_1 5
#define EN_PIN_1 A0
#define MOTOR_1 0

#define encodPinA1      2                             
#define encodPinB1      3

//variable for position of encoder2
volatile long encoderPos = 0;

 
void setup()                         
{
  pinMode(MOTOR_A1_PIN, OUTPUT);
  pinMode(MOTOR_B1_PIN, OUTPUT);
  pinMode(PWM_MOTOR_1, OUTPUT);
  pinMode(EN_PIN_1, OUTPUT);
  digitalWrite(EN_PIN_1, HIGH);
  attachInterrupt(3, encoder, FALLING);

  Serial.begin(9600);              

}

void loop() 
{
  while(Serial.available())
  {
    motorGo(CW, 150);
    delay(100);
    motorStop();
    delay(20);
    motorGo(CCW, 150);
    delay(100);
    motorStop();
    delay(20);
  }
}

void motorStop()
{
    digitalWrite(MOTOR_A1_PIN, LOW);
    digitalWrite(MOTOR_B1_PIN, LOW);            
}

void motorGo(uint8_t direct, uint8_t pwm) 
{      
    if(direct == CW)
    {
      digitalWrite(MOTOR_A1_PIN, LOW); 
      digitalWrite(MOTOR_B1_PIN, HIGH);
    }
    else if(direct == CCW)
    {
      digitalWrite(MOTOR_A1_PIN, HIGH);
      digitalWrite(MOTOR_B1_PIN, LOW);      
    }
    analogWrite(PWM_MOTOR_1, pwm); 
}

void encoder()  {                                     
 if ((digitalRead(encodPinB1) == 1))    {
   encoderPos++;   
 }      
 else{
   encoderPos--;   
 }     
}
