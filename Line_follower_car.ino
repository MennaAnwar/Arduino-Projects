#define IN1 3
#define IN2 4
#define IN3 5
#define IN4 6
#define speedR 10
#define sensorL 11
#define sensorR 12
#define speedL 9
int sl=0;
int sr=0;

void setup() {
for(int i=3;i<=6;i++)
{
pinMode(i, OUTPUT);
}
pinMode(sensorR, INPUT);
pinMode(sensorL, INPUT);

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
sl=digitalRead(sensorL);
sr=digitalRead(sensorR);
if (sl==0&&sr==0)
forward();
else if (sl==0&&sr==1)
right();
else if (sl==1&&sr==0)
left();
else if (sl==1&&sr==1)
stopp(); }
