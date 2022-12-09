#include <IRremote.h>
#include "NewPing.h"
#include <Servo.h>
Servo myservo; 

bool r=0;
bool l= 0;
bool u= 0;
bool d=0;
const int RECV_PIN = 9;
IRrecv irrecv(RECV_PIN);
decode_results results;
unsigned long key_value = 0;
int toggle;
int pos; 
int time = 0;
int steve = 90;
bool stopper = 0;

#define FS 225

 void Base(int x, int y , int z, int a){
  analogWrite (5, x);
  analogWrite (6, y);
  digitalWrite (7, z);
  digitalWrite (8, a);
  digitalWrite (3, 1);
  }
  void STOP(){
  analogWrite (5, 0);
  analogWrite (6, 0);
  digitalWrite (7, 0);
  digitalWrite (8, 0);
  digitalWrite (3, 0);
  }

 void Forward(int x){
  
 Base(x/2, x/2, 1, 1);
 }
  
  
  void Backward(int x){

 Base(x/2, x/2, 0, 0);
}

 void Right_F(int  x){
 Base(x/4, x/2, 1, 1);
 }
void Right_B(int  x){
 Base(x/4, x/2, 0, 0);
 }

void Right(int  x){
  Base(x/2, x/2, 0, 1);
}

void Left(int  x){
  Base(x/2, x/2, 1, 0);
}
 void Left_F(int  x){
 Base(x/2, x/4, 1, 1);
 }
 void Left_B(int  x){
 Base(x/2, x/4, 0, 0);
 }

void Man(){
Serial.print(u);
Serial.print(d);
Serial.print(l);
Serial.print(r);
   if (irrecv.decode(&results)){
     STOP();
 
        if (results.value == 0XFFFFFFFF)
          results.value = key_value;

        switch(results.value){
          case 0xFF629D://if results.value is equal to the signal corresponding to the button, serial print the buttons name &...
          Serial.println("VOL+");
          u= 1;
          d=0;
          l=0;
          r=0;
          break;

case 0xFF22DD://if results.value is equal to the signal corresponding to the button, serial print the buttons name &...
          Serial.println("|<<");
          u= 0;
          d=0;
          l=1;
          r=0;
          break;

 case 0xFFC23D:
          Serial.println(">>|");//if results.value is equal to the signal corresponding to the button, serial print the buttons name &...
         u= 0;
          d=0;
          l=0;
          r=1;
          break ;          

 case 0xFFA857:
          Serial.println("VOL-");//if results.value is equal to the signal corresponding to the button, serial print the buttons name &...
          u= 0;
          d=1;
          l=0;
          r=0;
          break ;  
}

   
   
   if(r == 1){
     Right(100);
   }
   if(u == 1){
     Forward(100);
   }
   if(l == 1){
     Left(100);
   }
   if(d == 1){
     Backward(100);
   }
   }}

  
 void linefollower(){
int nowtime;
unsigned long lasttime = 0;
int right;
int left;
int middle;
middle = analogRead(A1);
right =analogRead(A0);
left = analogRead(A2);
  nowtime = millis();
if (nowtime - lasttime >= 1000){
  lasttime = nowtime;
  Serial.println("working");
Serial.println(right);
Serial.println(middle);
Serial.println(left);}

// if(middle> 950 || right >950 || left >950 || middle<200 && right<200 && left <200){
//   STOP();
// }
// else{

if(middle - right >= 10  && middle - left >= 10){
  Forward(90);
}
if(right - middle >= 10 && right- left>= 10){
Right(90);
}
if(left- middle>= 10 && left - right>=10 ){
  Left(90);
}
// }
}
 
 void Avoider(){

 
#define TRIGGER_PIN  13
#define ECHO_PIN     12
#define MAX_DISTANCE 400
 
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
 
float duration, distance;
 
int iterations = 5;
  duration = sonar.ping_median(iterations);
  distance = (duration / 2) * 0.0343;
  Serial.println(distance);
  
   

  if (distance <= 20){
    stopper = 1;
  
  }
 if (stopper == 1){
       Serial.println (distance);
 Serial.println (steve);
 Serial.println (time);
      STOP();
    for (pos = 0; pos <= 180; pos += 1) {
      Serial.println (distance);
 Serial.println (steve);
 Serial.println (time);
      myservo.write(pos);  
    delay(15);  
    if (distance >= 30){
      steve = pos;}          
  }
  for (pos = 180; pos >= 0; pos -= 1) { 
    Serial.println (distance);
 Serial.println (steve);
 Serial.println (time);
  myservo.write(pos);  
    delay(15); 
    if (distance >= 30){
      steve = pos;
    }}
   
    
if (steve > 100 ){
  Serial.println (distance);
 Serial.println (steve);
 Serial.println (time);
 time = map(steve, 90, 180, 1500, 3500);
 Left(200);
 delay(time);
 steve = 90;
stopper = 0;
 }    
  if (steve< 80){
    Serial.println (distance);
 Serial.println (steve);
 Serial.println (time);
 time = map(steve, 0, 90, 1500, 3500);
 Right(200);
 delay(time);
 steve = 90;
stopper = 0;
 } }  
 
  if (stopper == 0){
  Forward(150);
  myservo.write(90);
   Serial.println (steve);
 Serial.println (time);}
 

 

 }
  

void setup(){
  Serial.begin(9600);
  irrecv.enableIRIn();
  irrecv.blink13(true);
  myservo.attach(10);  

}

void loop(){









  if (irrecv.decode(&results)){
 
        if (results.value == 0XFFFFFFFF)
          results.value = key_value;

        switch(results.value){//if results.value is equal to the signal corresponding to the button, serial print the buttons name.
           case 0xFFA25D:
          Serial.println("ON/OFF");
          toggle = 0;
          break;
          case 0xFF629D://if results.value is equal to the signal corresponding to the button, serial print the buttons name &...
          Serial.println("VOL+");
          break;
          case 0xFFE21D:
          Serial.println("STOP");
          break;
          case 0xFF22DD://if results.value is equal to the signal corresponding to the button, serial print the buttons name &...
          Serial.println("|<<");
          break;
          case 0xFF02FD:
          Serial.println("PLAY/PAUSE");
          break ;  
          case 0xFFC23D:
          Serial.println(">>|");//if results.value is equal to the signal corresponding to the button, serial print the buttons name &...
          break ;               
          case 0xFFE01F:
          Serial.println("DOWN");
          break ;  
          case 0xFFA857:
          Serial.println("VOL-");//if results.value is equal to the signal corresponding to the button, serial print the buttons name &...
          break ;  
          case 0xFF906F:
          Serial.println("UP");
          break ;  
          case 0xFF6897:
          Serial.println("0");
          break ;  
          case 0xFF9867:
          Serial.println("EQ");
          break ;
          case 0xFFB04F:
          Serial.println("REPT");
          break ;
          case 0xFF30CF:
          Serial.println("1");
          STOP();
          delay(1000);
         toggle = 1;
          break ;
          case 0xFF18E7:
          Serial.println("2");
          STOP();
          delay(1000);
         toggle = 2;
          break ;
          case 0xFF7A85:
          Serial.println("3");
          STOP();
          delay(1000);
          toggle = 3;
          break ;
          case 0xFF10EF:
          Serial.println("4");
          break ;
          case 0xFF38C7:
          Serial.println("5");
          break ;
          case 0xFF5AA5:
          Serial.println("6");
          break ;
          case 0xFF42BD:
          Serial.println("7");
          break ;
          case 0xFF4AB5:
          Serial.println("8");
          break ;
          case 0xFF52AD:
          Serial.println("9");
          break ;      
        }
        key_value = results.value;
        irrecv.resume(); 
  }
if(toggle == 3){
  Man();
}
if(toggle == 2){
  Avoider();
}
if(toggle == 1){
  linefollower();
}
if(toggle == 0){
  STOP();
}
}
