int xpin=A0,ypin=A1;  //X and Y pins of the joystick
int x,y;              //Values from X and Y pins
int level=0;          //Current Level
int *arr = (int *) malloc(level * sizeof(int));//Array which will contain sequence
int state=1;          //The state of the user 1=win , 0=loss
int led[5]={8,9,10,11,12};//Display leds 
unsigned long a,b;  //Timestamps
int i,dt;         //i counter //dt delay time
String diff;      //difficulty
String directions[4]={"Up","Right","Down","Left"};//To show user the innput direction
void start(void);
void fail(void);

//////////////////////////////////////////////////////////////////////////////////////////////////////////
void setup() {
Serial.begin(9600);
pinMode(xpin,INPUT);
pinMode(ypin,INPUT);
for(i=0;i<=4;i++)
{
  pinMode(led[i],OUTPUT);
}
start();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////
void loop() {
state=1;
level++;
int ans[level];         //Array with size equal to level which will contain user's inputs
Serial.print("\nLevel = ");
Serial.println(level);   
arr[level-1]=random(0,4); //Insert new random element
Serial.println(" ");

  for(i=0;i<level;i++)     //Diplay the pattern on the leds
{  
  digitalWrite(led[arr[i]],HIGH);
  delay(dt);
  digitalWrite(led[arr[i]],LOW);
  delay(100);
}
  for(i=0;i<level;i++)  //Take the value from user and check it
  {
  Serial.println("Enter Value ");
  a=millis();
  while(1){       //Wait for input from user
  x=analogRead(xpin);
  y=analogRead(ypin);
  b=millis();
  if( y<200 )       //The joystick moves up
  {ans[i]=0;break;}
  else if (x>700)   //The joystick moves right
  {ans[i]=1;break;}
  else if(y>700)    //The joystick moves down
  {ans[i]=2;break;}
  else if (x<200)   //The joystick moves left
  {ans[i]=3;break;}
  if((b-a)>=5000)//If 5 seconds passes and user didn't input any value
  {fail();break;}
            }
  if(state==1){//This statement to check if he lost on time or he input value
  if(ans[i]!=arr[i])// Check wether the input is wrong
  {fail();break;}   }
    
    if(state==1)    //if the input value is true
    {
    Serial.print("you entered ");
    Serial.println(directions[ans[i]]);
    delay(1000);
    }
    else if(state==0) //if he lost exit the loop
    {
      break;
    }
  }
  if(state==1)    //if he wins
    {
  Serial.println("Level passed :) ");
  Serial.print("Your score is ");
  Serial.println(level);
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////
void start(void)
{
Serial.println("Start");
Serial.println("Choose difficulty\n1.Easy\n2.Normal\n3.Hard");
while(Serial.available()==0){}      //Wait for the user to enter value
diff=Serial.readStringUntil('\n');  //Read the diffculty from the user 
if(diff[0]=='1')            //Set the delay time according to Difficulty level which is taken from the user
{dt=4000;}
else if(diff[0]=='2')
{dt=2000;}
else if(diff[0]=='3')
{dt=1000;}
level=0;
Serial.print("Delat time will be ");
Serial.print(dt/1000);
}

void fail(void)
{
  Serial.println("You Lost :( ");
  Serial.print("Your score is ");
  Serial.println(level-1);
  digitalWrite(led[4],HIGH);
  delay(2000);
  digitalWrite(led[4],LOW);
  Serial.println("");
  state=0;
  start();
}
