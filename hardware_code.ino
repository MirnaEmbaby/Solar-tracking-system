#include <SoftwareSerial.h>

#include <Servo.h>
SoftwareSerial bluetooth(5, 6);  // RX, TX
Servo horizontal;
Servo vertical;
String newValue;
int currntAngleV;
int currntAngleH;
int newAngle;
float Amps;
float Volts;

void setup() {
  bluetooth.begin(9600);
  Serial.begin(9600);
  horizontal.attach(9);
  vertical.attach(10);
  currntAngleV = 0;
  currntAngleH = 0;

  horizontal.write(currntAngleH);
  vertical.write(currntAngleV);

  pinMode (A0, INPUT);
  pinMode (A1, INPUT);
}

void loop() {
  while (bluetooth.available() > 0) {
    newValue = bluetooth.readString();
    Serial.println(newValue);

    newAngle = newValue.substring(1, newValue.length()).toInt();

    if (newValue.startsWith("h")) {
      if (newAngle > currntAngleH) {
        increaseAngle(horizontal, currntAngleH, newAngle);
      } else if (newAngle < currntAngleH) {
        decreaseAngle(horizontal, currntAngleH, newAngle);
      }
      currntAngleH = newAngle;

    } else if (newValue.startsWith("v")) {
      if (newAngle > currntAngleV) {
        increaseAngle(vertical, currntAngleV, newAngle);
      } else if (newAngle < currntAngleV) {
        decreaseAngle(vertical, currntAngleV, newAngle);
      }
      currntAngleV = newAngle;
    }

    Serial.println(newAngle);
    bluetooth.println("ok");
  }

  getVCP();
}


void increaseAngle(Servo _Servo, int _currntAngle, int _newAngle) {
  for (int i = _currntAngle + 1; i < _newAngle; i = i + 1) {
    _Servo.write(i);
    delay(50);
   
  }
}
void decreaseAngle(Servo _Servo, int _currntAngle, int _newAngle) {
  for (int i = _currntAngle - 1; i > _newAngle; i = i - 1) {
    _Servo.write(i);
        delay(50);

  }
}

void getVCP()
{
  Volts= analogRead (A1)/41.2;  
  Amps= analogRead (A0)/183.3; 
  Serial.print (Volts);
  Serial.print (",");
  Serial.print (Amps);
  Serial.print(",");
  Serial.print(Volts*Amps);
  Serial.print("\n");
  delay(500);
}
