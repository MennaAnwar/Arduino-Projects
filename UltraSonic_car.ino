#define IN1 3
#define IN2 4
#define IN3 5
#define IN4 6
#define trig 11
#define echo 12
#define speedL 9
#define speedR 10
long duration,distance;
void setup() {
for(int i=3;i<=6;i++)
{
pinMode(i, OUTPUT);
}
pinMode(echo, INPUT);
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


void left()
{
digitalWrite(IN1, LOW);
digitalWrite(IN2, LOW);
digitalWrite(IN3, HIGH);
digitalWrite(IN4, LOW);
analogWrite(speedL,0);
analogWrite(speedR,80);
}

void right()
{
digitalWrite(IN1, HIGH);
digitalWrite(IN2, LOW);
digitalWrite(IN3, LOW);
digitalWrite(IN4, LOW);
analogWrite(speedL,80);
analogWrite(speedR,0);
}

void stopp(){
digitalWrite(IN1, LOW);
digitalWrite(IN2, LOW);
digitalWrite(IN3, LOW);
digitalWrite(IN4, LOW);
analogWrite(speedL,0);
analogWrite(speedR,0);
}

void forward()
{
digitalWrite(IN1, HIGH);
digitalWrite(IN2, LOW);
digitalWrite(IN3, HIGH);
digitalWrite(IN4, LOW);
analogWrite(speedL,80);
analogWrite(speedR,80);
}
void backward()
{
digitalWrite(IN1, LOW);
digitalWrite(IN2, HIGH);
digitalWrite(IN3, LOW);
digitalWrite(IN4, HIGH);
analogWrite(speedL,80);
analogWrite(speedR,80);
}

void loop(){
Ultrasonic();
if(distance<20){
 
stopp();
delay(1000);
right(); //or left 
delay(500);
}
else{
forward();
}
}
