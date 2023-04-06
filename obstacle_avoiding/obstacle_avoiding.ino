/*obstacle avoiding, Bluetooth control, voice control robot car.
   https://srituhobby.com
*/
#include <Servo.h>
#include <AFMotor.h>
#define Echo A0
#define Trig A1
#define motor 10
#define Speed 170
#define spoint 103
char value;
int distance;
int Left;
int Right;
int L = 0;
int R = 0;
int L1 = 0;
int R1 = 0;
Servo servo;
AF_DCMotor M1(1);
AF_DCMotor M2(2);
AF_DCMotor M3(3);
AF_DCMotor M4(4);
void setup() {
  Serial.begin(9600);
  pinMode(Trig, OUTPUT);
  pinMode(Echo, INPUT);
  servo.attach(motor);
  M1.setSpeed(Speed);
  M2.setSpeed(Speed);
  M3.setSpeed(Speed);
  M4.setSpeed(Speed);
}
void loop() {
  //Obstacle();
  //Bluetoothcontrol();
  voicecontrol();
}
void Bluetoothcontrol() {
  if (Serial.available() > 0) {
    value = Serial.read();
    Serial.println(value);
  }
 if (value == 'F') {
    forward();
  } else if (value == 'B') {
    backward();
  } else if (value == 'R') {
    left();
  } else if (value == 'I'){
    forward_left();
  } else if (value == 'H'){
    backward_left();
  } else if (value == 'L') {
    right();
  } else if (value == 'G'){
    forward_right();
  } else if (value == 'J'){
    backward_right();
  }else if (value == 'S') {
    Stop();
  }
}

void Obstacle() {
  distance = ultrasonic();
  if (distance <= 12) {
    Stop();
    backward();
    delay(100);
    Stop();
    L = leftsee();
    servo.write(spoint);
    delay(800);
    R = rightsee();
    servo.write(spoint);
    if (L < R) {
      right();
      delay(500);
      Stop();
      delay(200);
    } else if (L > R) {
      left();
      delay(500);
      Stop();
      delay(200);
    }
  } else {
    forward();
  }
}
void voicecontrol() {
  if (Serial.available() > 0) {
    value = Serial.read();
    Serial.println(value);
    if (value == '^') {
      forward();
    } else if (value == '-') {
      backward();
    } else if (value == '<') {
      L = leftsee();
      servo.write(spoint);
      if (L >= 10 ) {
        left();
        delay(500);
        Stop();
      } else if (L < 50) {
        Stop();
      }
    } else if (value == '>') {
      R = rightsee();
      servo.write(spoint);
      if (R >= 10 ) {
        right();
        delay(500);
        Stop();
      } else if (R < 50) {
        Stop();
      }
      }else if(value == '>>'){
      R = rightsee();
      servo.write(spoint);
      if (R >= 10 ) {
        right();
        delay(500);
        forward();
      } else if (R < 50) {
        forward();
    }
      }
    else if (value == '<<') {
      L = leftsee();
      servo.write(spoint);
      if (L >= 10 ) {
        left();
        delay(500);
        forward();
      } else if (L < 50) {
        forward();
      }
    }else if(value == '->'){
     L = leftsee();
      servo.write(spoint);
      if (L >= 10 ) {
        left();
        delay(500);
        backward();
      } else if (L < 50) {
        backward();
    }
    }else if(value == '-<'){
       R = rightsee();
      servo.write(spoint);
      if (R >= 10 ) {
        right();
        delay(500);
        backward();
      } else if (R < 50) {
        backward();
    } 
    }else if (value == '*') {
      Stop();
    }
  }
}
// Ultrasonic sensor distance reading function
int ultrasonic() {
  digitalWrite(Trig, LOW);
  delayMicroseconds(4);
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);
  long t = pulseIn(Echo, HIGH);
  long cm = t / 29 / 2; //time convert distance
  return cm;
}
void forward() {
  M1.setSpeed(255);
  M1.run(FORWARD);
  M2.setSpeed(255);
  M2.run(FORWARD);
  M3.setSpeed(255);
  M3.run(FORWARD);
  M4.setSpeed(255);
  M4.run(FORWARD);
}
void forward_left() {
  M1.setSpeed(255);
  M1.run(FORWARD);
  M2.setSpeed(255);
  M2.run(FORWARD);
  M3.setSpeed(255);
  M3.run(FORWARD);
  M4.setSpeed(255);
  M4.run(FORWARD);
  M1.setSpeed(255);
  M1.run(FORWARD);
  M2.setSpeed(255);
  M2.run(FORWARD);
  M3.setSpeed(255);
  M3.run(BACKWARD);
  M4.setSpeed(255);
  M4.run(BACKWARD);
}
 void forward_right() {
   M1.setSpeed(255);
  M1.run(FORWARD);
  M2.setSpeed(255);
  M2.run(FORWARD);
  M3.setSpeed(255);
  M3.run(FORWARD);
  M4.setSpeed(255);
  M4.run(FORWARD);
  M1.setSpeed(255);
  M1.run(BACKWARD);
  M2.setSpeed(255);
  M2.run(BACKWARD);
  M3.setSpeed(255);
  M3.run(FORWARD);
  M4.setSpeed(255);
  M4.run(FORWARD);
 }
void backward() {
  M1.setSpeed(255);
  M1.run(BACKWARD);
  M2.setSpeed(255);
  M2.run(BACKWARD);
  M3.setSpeed(255);
  M3.run(BACKWARD);
  M4.setSpeed(255);
  M4.run(BACKWARD);
}
void backward_right() {
  M1.setSpeed(255);
  M1.run(BACKWARD);
  M2.setSpeed(255);
  M2.run(BACKWARD);
  M3.setSpeed(255);
  M3.run(BACKWARD);
  M4.setSpeed(255);
  M4.run(BACKWARD);
  M1.setSpeed(255);
  M1.run(BACKWARD);
  M2.setSpeed(255);
  M2.run(BACKWARD);
  M3.setSpeed(255);
  M3.run(FORWARD);
  M4.setSpeed(255);
  M4.run(FORWARD);
}
void backward_left() {
  M1.setSpeed(255);
  M1.run(BACKWARD);
  M2.setSpeed(255);
  M2.run(BACKWARD);
  M3.setSpeed(255);
  M3.run(BACKWARD);
  M4.setSpeed(255);
  M4.run(BACKWARD);
  M1.setSpeed(255);
  M1.run(FORWARD);
  M2.setSpeed(255);
  M2.run(FORWARD);
  M3.setSpeed(255);
  M3.run(BACKWARD);
  M4.setSpeed(255);
  M4.run(BACKWARD);
}
void right() {
  M1.setSpeed(255);
  M1.run(BACKWARD);
  M2.setSpeed(255);
  M2.run(BACKWARD);
  M3.setSpeed(255);
  M3.run(FORWARD);
  M4.setSpeed(255);
  M4.run(FORWARD);
}
void left() {
  M1.setSpeed(255);
  M1.run(FORWARD);
  M2.setSpeed(255);
  M2.run(FORWARD);
  M3.setSpeed(255);
  M3.run(BACKWARD);
  M4.setSpeed(255);
  M4.run(BACKWARD);
}
void Stop() {
  M1.setSpeed(0);
  M1.run(RELEASE);
  M2.setSpeed(0);
  M2.run(RELEASE);
  M3.setSpeed(0);
  M3.run(RELEASE);
  M4.setSpeed(0);
  M4.run(RELEASE);
}
int rightsee() {
  servo.write(20);
  delay(800);
  Left = ultrasonic();
  return Left;
}
int leftsee() {
  servo.write(180);
  delay(800);
  Right = ultrasonic();
  return Right;
}