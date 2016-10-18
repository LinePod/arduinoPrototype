// Motor (C)ontroller one
const int C1_enA = 10; //Needs to be PWM
const int C1_enB = 11; //Needs to be PWM
const int C1_in1 = 2;
const int C1_in2 = 3;
const int C1_in3 = 4;
const int C1_in4 = 5;
const int X_PIN = A0;
const int Y_PIN = A1;
const int BUTTON_PIN = 13;

//const int MAX_SPEED_HZ = 150; //(H)ori(z)ontal
//const int MAX_SPEED_VT = 255; //(V)er(t)ical
//const int MIN_SPEED_HZ = 40;
//const int MIN_SPEED_VT = 30;
const int SPEED_LASER_HZ = 125;
const int SPEED_LASER_VT = 120;
const int SPEED_HZ = 165;
const int SPEED_VT = 155;
const int TH = 120;

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

void turnOff(int motor)
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
		return;
	}
	if(laserState == HIGH) {
		laserState = LOW;
		digitalWrite(C2_in1, LOW);
		digitalWrite(C2_in2, LOW);
	}
}

void goForward(int motor)
{
	if(motor == 0) {
		digitalWrite(C1_in1, HIGH);
		digitalWrite(C1_in2, LOW);
		if(laserState == HIGH) {
			analogWrite(C1_enA, SPEED_LASER_HZ);
		}
		else {
			analogWrite(C1_enA, SPEED_HZ);
		}
	}
	else {
		digitalWrite(C1_in3, HIGH);
		digitalWrite(C1_in4, LOW);
		if(laserState == HIGH) {
			analogWrite(C1_enB, SPEED_LASER_VT);
		}
		else {
			analogWrite(C1_enB, SPEED_VT);
		}
	}
}

void goBackward(int motor) {
	if(motor == 0) {
		digitalWrite(C1_in1, LOW);
		digitalWrite(C1_in2, HIGH);
		if(laserState == HIGH) {
			analogWrite(C1_enA, SPEED_LASER_HZ);
		}
		else {
			analogWrite(C1_enA, SPEED_HZ);
		}
	}
	else {
		digitalWrite(C1_in3, LOW);
		digitalWrite(C1_in4, HIGH);
		if(laserState == HIGH) {
			analogWrite(C1_enB, SPEED_LASER_VT);
		}
		else {
			analogWrite(C1_enB, SPEED_VT);
		}
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

	newButtonState = digitalRead(BUTTON_PIN);

	if(newButtonState != prevButtonState) {
		toggleLaser();	
	}

	prevButtonState = newButtonState;
	xPosition = analogRead(X_PIN);
	yPosition = analogRead(Y_PIN);
	xPosition -= 512;
	yPosition -= 512;

	if(xPosition > TH){
		goForward(0);
	}
	else if(xPosition < -TH){
		goBackward(0);
	}
	else {
		turnOff(0);
	}

	if(yPosition > TH){
		goForward(1);
	}
	else if(yPosition < -TH){
		goBackward(1);
	}
	else {
		turnOff(1);
	}
	
}
