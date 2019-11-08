/*------ Arduino Fire Fighting Robot Code----- */

#include <Servo.h>
Servo myservo;

int pos = 0;
boolean fire = false;

/*-------defining Inputs------*/
#define Left_S 2      // left sensor
#define Right_S 4      // right sensor
#define Forward_S 3 //forward sensor

/*-------defining Outputs------*/

#define EnA  8
#define LM1  9     // left motor
#define LM2 10      // left motor
#define RM1 11     // right motor
#define RM2 12    // right motor
#define EnB 7
#define pump 13



void setup()
{
  pinMode(Left_S, INPUT);
  pinMode(Right_S, INPUT);
  pinMode(Forward_S, INPUT);
  pinMode(EnA, OUTPUT);
  pinMode(EnB, OUTPUT);
  pinMode(LM1, OUTPUT);
  pinMode(LM2, OUTPUT);
  pinMode(RM1, OUTPUT);
  pinMode(RM2, OUTPUT);
  pinMode(pump, OUTPUT);

  myservo.attach(5);
  myservo.write(90);
}

void put_off_fire()
{
  delay (500);

  digitalWrite(LM1, HIGH);
  digitalWrite(LM2, HIGH);
  digitalWrite(RM1, HIGH);
  digitalWrite(RM2, HIGH);
  digitalWrite(pump, HIGH);
  delay(500);


  for (pos = 50; pos <= 130; pos += 1) {
    myservo.write(pos);
    delay(5);
  }
  for (pos = 130; pos >= 50; pos -= 1) {
    myservo.write(pos);
    delay(5);
  }

  for (pos = 50; pos <= 130; pos += 1) {
    myservo.write(pos);
    delay(5);
  }

  for (pos = 130; pos >= 50; pos -= 1) {
    myservo.write(pos);
    delay(5);
  }

  digitalWrite(pump, LOW);
  myservo.write(90);

  fire = false;
}

void loop()
{
  myservo.write(90); //Sweep_Servo();

  if (digitalRead(Left_S) == 1 && digitalRead(Right_S) == 1 && digitalRead(Forward_S) == 1) //If Fire not detected all sensors are zero
  {
    //Do not move the robot
    digitalWrite(LM1, HIGH);
    digitalWrite(LM2, HIGH);
    digitalWrite(RM1, HIGH);
    digitalWrite(RM2, HIGH);
  }

  else if (digitalRead(Forward_S) == 0) //If Fire is straight ahead
  {
    //Move the robot forward
    digitalWrite(LM1, HIGH);
    digitalWrite(LM2, LOW);
    analogWrite(EnA, 255);
    digitalWrite(RM1, LOW);
    digitalWrite(RM2, HIGH);
    analogWrite(EnB, 255);

    fire = true;
    while (fire == true)
    {
      put_off_fire();
    }

  }

  else if (digitalRead(Left_S) == 0) //If Fire is to the left
  {
    //Move the robot left
    digitalWrite(LM1, HIGH);
    digitalWrite(LM2, HIGH);
    digitalWrite(RM1, LOW);
    digitalWrite(RM2, HIGH);
    analogWrite(EnB, 255);
    fire = true;


  }

  else if (digitalRead(Right_S) == 0) //If Fire is to the right
  {
    //Move the robot right
    digitalWrite(LM1, HIGH);
    digitalWrite(LM2, LOW);
    analogWrite(EnA, 255);
    digitalWrite(RM1, HIGH);
    digitalWrite(RM2, HIGH);
    fire = true;


  }

  if (digitalRead(Left_S) == 0 && digitalRead(Right_S) == 0 && digitalRead(Forward_S) == 0)
  {
    //Move the robot right
    digitalWrite(LM1, HIGH);
    digitalWrite(LM2, HIGH);
    analogWrite(EnA, 255);
    digitalWrite(RM1, HIGH);
    digitalWrite(RM2, HIGH);
    fire = true;
    while (fire == true)
    {
      put_off_fire();
    }
  }





}
