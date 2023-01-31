#include <NewPing.h> //boilerplate, loads dependencies
#include <Servo.h> //boilerplate, loads dependencies


int servoPin = 9; //Sets servo pin to 9
int sonarPower = 7; //Sets sonar 5V pin to 7
int sonarGround = 6; //Sets sonar ground pin to 6
int sonarTransmitter = 4; //Sets sonar transmitter pin to 4
int sonarReciever = 5; //Sets sonar reciever pin to 5
int sonarMaxPingDistance = 200; //Sets radar max distance to 200cm
int pingDistance; //Variable that stores input from sonarReciever
int LED1 = 13; //Sets LED1 to control onboard LED

Servo servo1; //Initialises servo module
NewPing sonar1(sonarTransmitter, sonarReciever, sonarMaxPingDistance); //Initialises sonar module with given parameters


void setup() {
  
  Serial.begin(9600); //sets serial data rate in baud
  servo1.attach(servoPin); //attaches servo object to pin
  pinMode(sonarGround, OUTPUT); //sets pin as output
  pinMode(sonarPower, OUTPUT); //sets pin as output
  pinMode(sonarReciever, INPUT); //sets pin as input
  pinMode(sonarTransmitter, OUTPUT); //sets pin as output
  pinMode (LED1, OUTPUT); //sets onboard LED to output
  digitalWrite(sonarGround, LOW); //sets pin to ground
  digitalWrite(sonarPower, HIGH); //sets pin to +5V

}

void loop() {

  delay(50); //50ms delay before each loop runs
  pingDistance = sonar1.ping_cm(); //sets variable to distance reported by sonar
  Serial.println(pingDistance); //prints distance in console

  if (pingDistance < 10 && pingDistance != 0) { //when distance is less than 10, and not equal to 0, execute the following
      delay(1000); //waits 1 second
      servo1.write(130); //move servo to 90 degree position, claw closes
      Serial.println("HIGH"); //print HIGH in console
      digitalWrite(LED1, HIGH); //sets LED to high
      delay(6000); //waits 6 seconds
      servo1.write(0); //moves servo back to 0 degree position, claw opens
  }
  else { 

      servo1.write(40); //move servo to 0 degree position, claw opens
      Serial.println("LOW"); //print LOW in console
      digitalWrite(LED1, LOW); //sets LED to low
      delay(250); //waits 250ms for servo
    }
}
