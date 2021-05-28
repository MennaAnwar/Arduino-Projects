#define IN1 3
#define IN2 4
#define IN3 5
#define IN4 6
#define speedL 9
#define speedR 10
char Reading;

void setup() {
Serial.begin (9600);
pinMode(IN1, OUTPUT);
pinMode(IN2, OUTPUT);
pinMode(IN3, OUTPUT);
pinMode(IN4, OUTPUT);
}

void left()
{
digitalWrite(IN1, LOW);
digitalWrite(IN2, LOW);
digitalWrite(IN3, HIGH);
digitalWrite(IN4, LOW);
analogWrite(speedL,0);
analogWrite(speedR,120);
}

void right()
{
digitalWrite(IN1, HIGH);
digitalWrite(IN2, LOW);
digitalWrite(IN3, LOW);
digitalWrite(IN4, LOW);
analogWrite(speedL,120);
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
analogWrite(speedL,120);
analogWrite(speedR,120);
}
void backward()
{
digitalWrite(IN1, LOW);
digitalWrite(IN2, HIGH);
digitalWrite(IN3, LOW);
digitalWrite(IN4, HIGH);
analogWrite(speedL,120);
analogWrite(speedR,120);
}
void loop(){
if(Serial.available()>0){
Reading=Serial.read();
switch(Reading){
case 'F':  forward();  break;
case 'B':  backward(); break;
case 'R':  right();    break;
case 'L':  left();     break;
case 'S':  stopp();   break;
}// end switch
}// end if
}// end void loop
