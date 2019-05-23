#include <LiquidCrystal.h>
int votes[4]={0,0,0,0};
char inbyte;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); //LCD connections
  String pwd="VOTE";                         //Default Password
  String inpt="";
  boolean flag=false;
  boolean securitygranted=false;           
  int i;
void setup() {
   lcd.setCursor(0, 1);
  pinMode(A2, INPUT_PULLUP);              //Setting pins as input
  pinMode(A3, INPUT_PULLUP);
  pinMode(A4, INPUT_PULLUP);
  pinMode(A5, INPUT_PULLUP);
  lcd.begin(16, 2);
  lcd.display();
  
  Serial.begin(9600);                    //Begin serial communication
  Serial.println("ENTER PASSWORD");
}
void loop() {
   lcd.setCursor(0, 1);
  while(flag==true)                     //Check flag for "V" command
  {
  if(digitalRead(A2) == LOW) 
  {
  flag=false;
  Serial.println("Mark");
  lcd.print("MARK");                  //Example candidate name
  votes[0]=votes[0]+1;
  }
  else if(digitalRead(A3) == LOW)
  {
  flag=false;
  Serial.println("Jill");
  lcd.print("JILL");
  votes[1]=votes[1]+1;
  }
  else if(digitalRead(A4) == LOW) 
  {
  flag=false;
  Serial.println("Jack");
  lcd.print("JACK");
  votes[2]=votes[2]+1;
  }
  else if(digitalRead(A5) == LOW)
  {
  flag=false;
  Serial.println("Tomy");
  lcd.print("TOMY");
  votes[3]=votes[3]+1;
  }
  }
}
void serialEvent()                     
{
  while(Serial.available())
  {
   inbyte=(char)Serial.read();                   //Reading incoming character
   if(securitygranted==false)
   {
    inpt += inbyte;
    inbyte='\n';
   }   
  }
  commandcheck();
}
void commandcheck()                         
{
  switch (securitygranted)                    //See for the security permissions
  {
    case false: {
      if(inpt==pwd)                          //Checking for password match
        {
          securitygranted=true;
          inbyte='\n';
          inpt="";
          Serial.println("ACCESS GRANTED");
         /* char TestData;
          if(Serial.available())
          {
            TestData=Serial.read();
            lcd.print(TestData);
          }
          lcd.print("hello, world!");*/
        }
       else if((inpt!=pwd)&&(inpt.length()>3))        //Mismatch
       {
          Serial.println(inpt);
          inpt=""; 
          inbyte='\n';
          Serial.println("WRONG PASSWORD");
          Serial.println("ENTER PASSWORD");
          Serial.end();
          delay(100);
          Serial.begin(9600);
       }
       break;
              }
              
   case true: {
      if(inbyte=='V')             
        {
          flag=true;                             //Allowing voter to cast a single vote
          Serial.println("OK");
          lcd.clear();
          inbyte='\n';
        }
      else if(inbyte=='D')
        {
          for(i=0;i<=3;i++)                       //Displaying vote tally
          Serial.println(votes[i]);
          inbyte='\n';
        }
      else
        {Serial.println("UNKNOWN COMMAND");}
        break;
             }
  }
}
