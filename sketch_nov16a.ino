#include <Servo.h>
Servo ss;
int pos = 180;
int temp = 5;
//MOTOR1 PINS
#define IN1 13 
#define IN2 12
#define IN3 11
#define IN4 10
#define trig 6
#define echo 5
long duration,distance;

const int BUZZER_PIN = 2; 
int smokeA0 = A2;
int sensorThreshold = 400;

int tempPin = 3;

void setup()
{
  Serial.begin(9600);
  ss.attach(3);
  for(int i=4;i<=8;i++)
{
pinMode(i, OUTPUT); 
} 
pinMode(echo, INPUT);

  pinMode(BUZZER_PIN, OUTPUT);       
  pinMode(smokeA0, INPUT);

  pinMode(8,OUTPUT);
}


void loop()
{
Serial.print("distance =");
Serial.println(distance);
Ultrasonic();
if(distance<20){ 
stopp();
delay(250);
right(); //or left as you like
delay(500);
}
else{
forward();
}
  float temp = analogRead(tempPin);
   // read analog volt from sensor and save to variable temp
   temp = temp * 0.48828125;
   // convert the analog volt to its temperature equivalent
   Serial.print("TEMPERATURE = ");
   Serial.print(temp); // display temperature value
   Serial.println("*C");
   
  int analogSensor = analogRead(smokeA0);
  int gas = map(analogSensor,0,1023,0,255);
  Serial.print("Gas amount: ");
  Serial.println(gas);
  
if(temp > 48 && gas>50) //+ detecting the fire by using camera
//if(distance <20) //to test it
{
  digitalWrite(IN1, LOW);
 digitalWrite(IN2, LOW); 
digitalWrite(IN3, LOW); 
digitalWrite(IN4, LOW);
  digitalWrite(BUZZER_PIN, 1);
  digitalWrite(8,1); //water pump
  Serial.println(" pump on");
  ss.write(180);
  delay(1000);
  ss.write(90);
  delay(1);  
}
else{
  //forward();
  digitalWrite(BUZZER_PIN, 0);
  Serial.println("pump off");
  digitalWrite(8,0);
  ss.write(180);
}


/*digitalWrite(in1, 0); //Making car go straight
digitalWrite(in2, 0);
digitalWrite(in4, 0);
digitalWrite(in3, 0);*/
//digitalWrite(BUZZER_PIN, 0);
//digitalWrite(BUZZER_PIN, 0);}

/*if(distance < 30)  

{

  Serial.println(" pump on");

  digitalWrite(4,1);

}

if(distance >30)

{

  Serial.println("pump off");

  digitalWrite(4,0);
}



   /*for(pos = 0; pos <= 180; pos +=1)
  {
    ss.write(pos);
    delay(10);
    }

  for(pos = 0; pos >= 180; pos -=1){
    ss.write(pos);
    delay(10);}
    //Serial.print(pos);*/
  

}


void backword(){
digitalWrite(IN1, LOW);
digitalWrite(IN2, HIGH); 
digitalWrite(IN3, LOW); 
digitalWrite(IN4, HIGH); 
}
void left(){
digitalWrite(IN1, LOW);
digitalWrite(IN2, LOW); 
digitalWrite(IN3, HIGH); 
digitalWrite(IN4, LOW); 
}
void right()
{
digitalWrite(IN1, HIGH);
digitalWrite(IN2, LOW); 
digitalWrite(IN3, LOW); 
digitalWrite(IN4, LOW); 
}
void stopp(){
digitalWrite(IN1, LOW);
digitalWrite(IN2, LOW); 
digitalWrite(IN3, LOW); 
digitalWrite(IN4, LOW); 
} 
void Ultrasonic(){
digitalWrite(trig, LOW);
delayMicroseconds(2); 
digitalWrite(trig, HIGH);
delayMicroseconds(10); 
digitalWrite(trig, LOW);
duration = pulseIn(echo, HIGH);
distance = (duration/2) * 0.0343; 
}
void forward()
{
digitalWrite(IN1, LOW);
digitalWrite(IN2, HIGH); 
digitalWrite(IN3, HIGH); 
digitalWrite(IN4, LOW); 
}
