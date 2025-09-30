#include <SPI.h>


const char endMarker = '.';

const int front = 1;
const int rear = 2;
const int right = 3;
const int left = 4;
const int stop = 5;

int desiredDirection = stop;
int currentDirection = stop;

const int motorSwitchAPinLeft = 4;
const int motorSwitchBPinLeft = 3;
const int motorSpeedPinLeft = 2;

const int motorSwitchAPinRight = 7;
const int motorSwitchBPinRight = 6;
const int motorSpeedPinRight = 5;


void setup() {
  // Serial configuration
  Serial.begin(9600);
  // Motor pin configuration
  pinMode(motorSpeedPinLeft, OUTPUT);
  pinMode(motorSpeedPinRight, OUTPUT);
  pinMode(motorSwitchAPinLeft, OUTPUT);
  pinMode(motorSwitchBPinLeft, OUTPUT);
  pinMode(motorSwitchAPinRight, OUTPUT);
  pinMode(motorSwitchBPinRight, OUTPUT);
}

void loop() {
  // Read inputs
  String receivedMessage = readMessageFromSerial();

  // Write outputs
  if((!isEmpty(receivedMessage) && receivedMessage.equals(String("UP_PRESSED")))) {
    desiredDirection = front;
  } else if((!isEmpty(receivedMessage) && receivedMessage.equals(String("DOWN_PRESSED")))) {
    desiredDirection = rear;
  } else if((!isEmpty(receivedMessage) && receivedMessage.equals(String("LEFT_PRESSED")))) {
    desiredDirection = left;
  } else if((!isEmpty(receivedMessage) && receivedMessage.equals(String("RIGHT_PRESSED")))) {
    desiredDirection = right;
  } else {
    desiredDirection = stop;
  }
  move();
}

String readMessageFromSerial() {
  String ret = "";
  char receivedChar =  '-';
  while(receivedChar != endMarker) {
    while(Serial.available() > 0) {
      receivedChar = Serial.read();
      if(receivedChar != endMarker) {
        ret.concat(receivedChar);
      }
    }
  }
  return ret;
}

boolean isEmpty(String message) {
  return message == NULL || message.equals("");
}

void move() {
  if(currentDirection != desiredDirection) {
    if(desiredDirection == front) {
      moveFront();
    } else if(desiredDirection == rear) {
      moveRear();
    } else if(desiredDirection == left) {
      moveLeft();
    } else if(desiredDirection == right) {
      moveRight();
    } else {
      stopMovement();
    }
  }
  currentDirection = desiredDirection;
}

void moveFront() {
	digitalWrite(motorSwitchAPinLeft, HIGH);
	digitalWrite(motorSwitchBPinLeft, LOW);
	digitalWrite(motorSwitchAPinRight, LOW);
	digitalWrite(motorSwitchBPinRight, HIGH);
	
	digitalWrite(motorSpeedPinLeft, HIGH);
	digitalWrite(motorSpeedPinRight, HIGH);
}

void moveRear() {
	digitalWrite(motorSwitchAPinLeft, LOW);
	digitalWrite(motorSwitchBPinLeft, HIGH);
	digitalWrite(motorSwitchAPinRight, HIGH);
	digitalWrite(motorSwitchBPinRight, LOW);
	
	digitalWrite(motorSpeedPinLeft, HIGH);
	digitalWrite(motorSpeedPinRight, HIGH);
}

void moveLeft() {
	digitalWrite(motorSwitchAPinLeft, LOW);
	digitalWrite(motorSwitchBPinLeft, HIGH);
	digitalWrite(motorSwitchAPinRight, LOW);
	digitalWrite(motorSwitchBPinRight, HIGH);
	
	digitalWrite(motorSpeedPinLeft, HIGH);
	digitalWrite(motorSpeedPinRight, HIGH);
}

void moveRight() {
  digitalWrite(motorSwitchAPinLeft, HIGH);
	digitalWrite(motorSwitchBPinLeft, LOW);
	digitalWrite(motorSwitchAPinRight, HIGH);
	digitalWrite(motorSwitchBPinRight, LOW);
	
	digitalWrite(motorSpeedPinLeft, HIGH);
	digitalWrite(motorSpeedPinRight, HIGH);
}

void stopMovement() {
	digitalWrite(motorSpeedPinLeft, LOW);
	digitalWrite(motorSpeedPinRight, LOW);
}