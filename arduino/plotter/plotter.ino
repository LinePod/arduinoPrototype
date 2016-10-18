// Motor (C)ontroller one
const int C1_enA = 10; //Needs to be PWM
const int C1_enB = 11; //Needs to be PWM
const int C1_in1 = 2;
const int C1_in2 = 3;
const int C1_in3 = 4;
const int C1_in4 = 5;
const int X_PIN = A1;
const int Y_PIN = A0;
const int BUTTON_PIN = 13;

const int MAX_SPEED = 150;
const int MIN_SPEED = 30;

// Motor (C)ontroller two
int C2_in1 = 8;
int C2_in2 = 9;

int xPosition;
int yPosition;

int xSpeed;
int ySpeed;

int prevButtonState = LOW;
int newButtonState = LOW;

int laserState = LOW;

void turnOff(int speed, int motor)
{
	if(motor == 0) {
		digitalWrite(C1_in1, LOW);
		digitalWrite(C1_in2, LOW);
	}
	else {
		digitalWrite(C1_in3, LOW);
		digitalWrite(C1_in4, LOW);
	}
}

void toggleLaser() {
	if(laserState == LOW) {
		laserState = HIGH;
		digitalWrite(C2_in1, HIGH);
		digitalWrite(C2_in2, LOW);
	}
	else {
		laserState = LOW;
		digitalWrite(C2_in1, LOW);
		digitalWrite(C2_in2, LOW);
	}
}

void goForward(int speed, int motor)
{
	if(motor == 0) {
		digitalWrite(C1_in1, HIGH);
		digitalWrite(C1_in2, LOW);
		analogWrite(C1_enA, speed);
	}
	else {
		digitalWrite(C1_in3, HIGH);
		digitalWrite(C1_in4, LOW);
		analogWrite(C1_enB, speed);
	}
}

void goBackward(int speed, int motor)
{
	if(motor == 0) {
		digitalWrite(C1_in1, LOW);
		digitalWrite(C1_in2, HIGH);
		analogWrite(C1_enA, speed);
	}
	else {
		digitalWrite(C1_in3, LOW);
		digitalWrite(C1_in4, HIGH);
		analogWrite(C1_enB, speed);
	}
}

void setup() {
	Serial.begin(9600);
	pinMode(C1_enA, OUTPUT);
	pinMode(C1_in1, OUTPUT);
	pinMode(C1_in2, OUTPUT);
	pinMode(C1_in3, OUTPUT);
	pinMode(C1_in4, OUTPUT);
	pinMode(C1_enB, OUTPUT);
	pinMode(C2_in1, OUTPUT);
	pinMode(C2_in2, OUTPUT);

	pinMode(X_PIN, INPUT);
	pinMode(Y_PIN, INPUT);
	pinMode(BUTTON_PIN, INPUT);
}

void loop() {
	xPosition = analogRead(X_PIN);
	yPosition = analogRead(Y_PIN);
	Serial.println("");
	Serial.println("XPos: ");
	Serial.println(xPosition);
	Serial.println("YPos: ");
	Serial.println(yPosition);
	xPosition -= 512;
	yPosition -= 512;
	Serial.println("XPosAdj: ");
	Serial.println(xPosition);
	Serial.println("YPosAdj: ");
	Serial.println(yPosition);

	xSpeed = (float)xPosition/512 * MAX_SPEED;
	ySpeed = (float)yPosition/512 * MAX_SPEED;

	if(xSpeed > MIN_SPEED) {
		goForward(xSpeed, 0);
	}
	if(xSpeed < -MIN_SPEED) {
		goBackward(abs(xSpeed), 0);
	}
	if(abs(xSpeed) < MIN_SPEED) {
		turnOff(0, 0);
	}

	if(ySpeed > MIN_SPEED) {
		goForward(ySpeed, 1);
	}
	if(ySpeed < -MIN_SPEED) {
		goBackward(abs(ySpeed), 1);
	}
	if(abs(ySpeed) < MIN_SPEED) {
		turnOff(0, 1);
	}

	newButtonState = digitalRead(BUTTON_PIN);

	if(newButtonState != prevButtonState) {
		toggleLaser();	
	}
	prevButtonState = newButtonState;
}
