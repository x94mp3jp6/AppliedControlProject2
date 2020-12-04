//光耦合計數器設定
int analogPin = A3; // potentiometer wiper (middle terminal) connected to analog pin 3
                    // outside leads to ground and +5V
int val1 = 0;  // motor1
int val2 = 0;  // motor2
float pastTime = 0;
volatile int count1 = 0; //motor1
volatile int count2 = 0; //motor2
bool situation1 = true ;
bool situation2 = true ;
//馬達設定
const byte LEFT1 = 10;
const byte LEFT2 = 9;
const byte LEFT_PWM = 5;
const byte RIGHT1 = 11;
const byte RIGHT2 = 12;
const byte RIGHT_PWM = 6;
int motorSpeed = 60;
int motorTrackSpeed = 0;
double rpm = 0;//馬達1
double rpmTrack = 0;//馬達2(追蹤馬達1)
int setRPM = 30;
//Kp
const float Kp1 = 0.;
const float Kp2 = 0.5;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  //Left Motor
  pinMode(LEFT1, OUTPUT);
  pinMode(LEFT2, OUTPUT);
  pinMode(LEFT_PWM, OUTPUT);
  digitalWrite(LEFT1, HIGH);
  digitalWrite(LEFT2, LOW);
  analogWrite(LEFT_PWM, motorSpeed);
  //Right Motor
  pinMode(RIGHT1, OUTPUT);
  pinMode(RIGHT2, OUTPUT);
  pinMode(RIGHT_PWM, OUTPUT);
  digitalWrite(RIGHT1, HIGH);
  digitalWrite(RIGHT2, LOW);
  analogWrite(RIGHT_PWM, motorTrackSpeed);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  if (Serial.available() > 0) {
    setRPM = Serial.read();
    Serial.write(setRPM);
  }
  
  val1 = digitalRead(3);
  if( val1 != situation1 ) {
    situation1 = val1;
    count1++ ;   
  }
  val2 = digitalRead(4);
  if( val2 != situation2 ) {
    situation2 = val2;
    count2++ ;   
  }
  if(millis()-pastTime > 100)
  {
    //Serial.print("rps:");
    rpm = count1*10.0/12.0;
    rpmTrack = count2*10.0/12.0;
    //Serial.print(motorSpeed);
    //Serial.print(",");
    Serial.print(rpm);
    Serial.print(",");
    //Serial.print("motorTrackSpeed");
    //Serial.print(",");
    Serial.println(rpmTrack);
    count1 =  0;
    count2 =  0;
    pastTime = millis();
    //motorSpeed = motorSpeed + Kp1*(setRPM-rpm);
    motorTrackSpeed = motorTrackSpeed + Kp2*(rpm-rpmTrack);
    //motorSpeed = motorSpeed > 200 ? 200 : motorSpeed ;
    motorTrackSpeed = motorTrackSpeed > 200 ? 200 : motorTrackSpeed ;
    analogWrite(LEFT_PWM, motorSpeed);
    analogWrite(RIGHT_PWM, motorTrackSpeed);
  }
}
