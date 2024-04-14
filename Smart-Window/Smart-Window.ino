#include <Servo.h>
int potpin=A1;  //potentiometer pin
int pos=0;      //position of the servo(angle)
int servopin=9; //control pin of the servo
Servo myservo;

int sw=2;       //switch pin which control the mode

int LDR=A0;     //LDR pin
int intensity;  //light intensity
int led[4]={3,5,6,11};
int i,j;    //counters

float floatmap(float x,float in_min,float in_max,float out_min,float out_max)
{return (x-in_min)*(out_max-out_min)/(in_max-in_min)+out_min;}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  myservo.attach(servopin);
  pinMode(potpin,INPUT);
  pinMode(LDR,INPUT);
  pinMode(sw,INPUT_PULLUP);
  for(i=0;i<=3;i++)
  {pinMode(led[i],OUTPUT);}
}

void loop() {
  // put your main code here, to run repeatedly:
  pos=map(analogRead(potpin),0,1023,0,180); //read the potentiometer value then calculate the position
  myservo.write(pos);              //Update the angle of the servo
  Serial.println(pos);

  if(digitalRead(sw)==0)          //check the mode wether it's manual using potentiometer or automatic from the LDR
  intensity=analogRead(potpin);   //if its manual read the voltage from potentiometer
  else if(digitalRead(sw)==1)
  intensity=analogRead(LDR);      //if its manual read the voltage from LDR
   
for(i=1;i<=4;i++)
{//check four regions of light intensity { (0~255) , (256~511) , (512,767) , (768,1023) }
if( (intensity>=(1024-256*i)) && (intensity<=(256*(5-i)-1)) ) //check region
{ 
  analogWrite(led[4-i],intensity-(1024-256*i));      //update brightness of the led of the current region
  for(j=0;j<=3-i;j++)
  {
  digitalWrite(led[j],HIGH);              // turn on first leds
  }
}
else if(intensity<(1024-256*i))
{ 
  digitalWrite(led[4-i],LOW);}          //turn off the led if the current region is less than its region
}
  
}
