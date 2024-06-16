#define INT_A 2    // control the left motor direction pin to D2
#define INT_B 4    // control the right motor direction pin to D4
#define left_A 9    // define the left motor speed as pin D9
#define right_B 5   // define the right motor speed as pin D5
// Ultrasonic 
int servopin=3;// digital 3 is connected to servo signal pin
int myangle;// define the angle
int pulsewidth;// define the pulsewidth 
#include <SR04.h>    // add the ultrasonic libraries 
#define TRIG_PIN 12   // define the pin ting of ultrasonic as D12
#define ECHO_PIN 13   //define the pin echo of ultrasonic as D13
SR04 sr04 = SR04(ECHO_PIN,TRIG_PIN);    // build the ultrasonic object to control the ultrasonic 
long a,a1,a2;      // used to receive the distance measured by ultrasonic 
void setup() 
{
  Serial.begin(9600);  // set the monitor baud rate to 9600
  delay(100);     // delay 100ms
  pinMode(INT_A,OUTPUT);     // set the motor control pin as OUTPUT 
  pinMode(INT_B,OUTPUT);
  pinMode(left_A,OUTPUT);
  pinMode(right_B,OUTPUT); 
  pinMode(servopin,OUTPUT);// set the servo pin as OUTPUT 
  servopulse(servopin,90);  // call the pulse function, make the ultrasonic keep front.
}

void loop() 
{
   a=sr04.Distance();    // assign the front distance measured by ultrasonic to a
   Serial.print(a);     // print a value on the monitor 
   Serial.println("cm");   // print cm and line wrap 
   delay(100);    // delay
   if(a<15)    // whether the distance a is less than 15cm, if yes, then perform the program in the brace.
   {
    Stop();    // car stops
    delay(100);   // delay 100ms
    servopulse(servopin,160);// call the pulse function to make ultrasonic sensor turn left in 90 degrees
    a1=sr04.Distance();  // assign the left obstacle distance measured by ultrasonic to a1
    Serial.print("a1 = ");  // print out the a1 = on the serial monitor
    Serial.print(a1);      //print a1 value 
    Serial.println("cm");   // print cm and line wrap
    delay(100);    // delay 100ms
    servopulse(servopin,20);// call the pulse function to make ultrasonic sensor turn right in 90 degrees
    a2=sr04.Distance();      // assign the right obstacle distance measured by ultrasonic to a2
    Serial.print("a2 = ");
    Serial.print(a2);
    Serial.println("cm");
    delay(100);
    if(a1>a2)     // whether a1 is greater than a2（whether left distance is greater than that measured on the right side.）
    {
      servopulse(servopin,90);// call the pulse function, make the ultrasonic keep front.
      left();    //turn left
      delay(370);   // delay370ms，the time for car to turn left in 90 degrees as much as possible.
      front();  // go front
    }
    else     // if a1<a2
    {
      servopulse(servopin,90);  // call the pulse function, make the ultrasonic keep front.
      right();  // turn right 
      delay(370);  // delay 370ms，the time for car to turn right in 90 degrees as much as possible. 
      front();   // the car goes forward 
    }
   }
   else   // if a>15cm
   {
    front();   //the car goes forward
   }

}

// forward
void front()
{
  digitalWrite(INT_A,LOW);    // control the left motor turn forward
  digitalWrite(INT_B,LOW);   // control the right motor turn forward
  analogWrite(left_A,200);   // set the motor speed（PWM=200)
  analogWrite(right_B,200); 
}
// backward
void back()  
{
  digitalWrite(INT_A,HIGH);   // control the left motor turn backward 
  digitalWrite(INT_B,HIGH);    //control the right motor turn backward 
  analogWrite(left_A,200);   
  analogWrite(right_B,200);
}
// turn left
void left()
{
  digitalWrite(INT_A,HIGH);    //control the left motor turn backward 
  digitalWrite(INT_B,LOW);    // control the right motor turn forward
  analogWrite(left_A,150);    // two motors’ speed（PWM为150）
  analogWrite(right_B,150);
}
// turn right 
void right()
{
  digitalWrite(INT_A,LOW);     // control the left motor turn forward
  digitalWrite(INT_B,HIGH);     // control the right motor turn backward 
  analogWrite(left_A,150);
  analogWrite(right_B,150);
}
// stop
void Stop()
{
  digitalWrite(INT_A,LOW);   
  digitalWrite(INT_B,LOW);   
  analogWrite(left_A,0);     // PWM of both left and right is 0
  analogWrite(right_B,0);
}
// servo
void servopulse(int servopin,int myangle)// define a pulse function
{
  for(int i=0;i<50;i++)
  {
    pulsewidth=(myangle*11)+500;// convert the angle into the pulsewidth of 500-2480 
    digitalWrite(servopin,HIGH);// servo pin to HIGH 
    delayMicroseconds(pulsewidth);// delay the microseconds of pulsewidth 
    digitalWrite(servopin,LOW);// servo pin to LOW
    delay(20-pulsewidth/1000); // delay the rest circle time to LOW level（20ms circle ）
  }
}