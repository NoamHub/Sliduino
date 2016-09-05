#pragma once

// MotorControl.h

// Written by NoamHub 3.9.16
// A driver for EasyDriver stepper motor driver

#define NUM_OF_BUTTON_SAMPLES	(3)
#define MIN_INTERVAL						(5)
#define MAX_INTERVAL						(1000)
#define MAX_SLEEP_TIME					(86400000)

enum MicrostepMode
{
	FULL_STEP,
	HALF_STEP,
	QUARTER_STEP,
	EIGHTH_STEP
};

enum MotorDirection
{
	TO_MOTOR 		= 0,
	TO_NO_MOTOR 	= 1
};

enum OperationMode
{
	IDLE,
	MOVE,
	SLEEP
};

class CMotorControl
{
public:
	
	void Init (MicrostepMode Mode, int StepPin, int DirPin, int MS1Pin, int MS2Pin, 
				  int EnablePin, int MotorButtonPin, int NoMotorButtonPin);
	
	bool Set(MotorDirection Direction, unsigned int Interval, unsigned int SleepTime);
	
	bool Start();
	
	void Stop();
	
	void RegisterTimerInterrupt();
	
private:
	
	void Enable();
	void Disable();
	
	bool DidReachEnd();
	
	void ToggleStepPin();
	
	int StepPin;
	int DirPin;
	int MS1Pin;
	int MS2Pin;
	int MotorButtonPin;
	int NoMotorButtonPin;
	int EnablePin;
	//int SleepPin;
	
	bool IsSet;
	unsigned int   Steps;
	unsigned int   Interval;
	unsigned int   Countdown;
	unsigned int   SleepCountdown;
	
	bool CurrentStepStatus;
	
	OperationMode OpMode;
	MotorDirection  Direction;
};

void CMotorControl::RegisterTimerInterrupt()
{
	switch(OpMode)
	{
		case(IDLE):
			// Do nothing
		break;
		
		case(MOVE):
			Countdown--;
			
			// Sets the step pin back to low
			if (Countdown == Interval / 2)
			{
				// Toggle the step pin
				ToggleStepPin();
			}
			else if (Countdown == 0)
			{
				// Ensure the camera did not reach the end
				if (DidReachEnd())
					Stop();
				else
				{
					// Toggle the step pin to HIGH
					ToggleStepPin();
					// Re-arm the countdown variable
					Countdown = Interval;
				}
			}
		break;
		
		case(SLEEP):
			if (--SleepCountdown == 0)
			{
				OpMode = MOVE;
				Enable();
			}
		break;
	}
}

void CMotorControl::Init (MicrostepMode MSMode, int StepPin, int DirPin, int MS1Pin, 
									int MS2Pin, int EnablePin, int MotorButtonPin, int NoMotorButtonPin)
{
	// Don't start before the direction and interval are set for the first time
	bool IsSet = false;
	OpMode = IDLE;
	
	// Disable the board first
	pinMode(this->EnablePin = EnablePin, OUTPUT);
	Disable();
	delay(1);
	
	// Initialize the pins
	pinMode(this->StepPin = StepPin, OUTPUT);
	pinMode(this->DirPin = DirPin, OUTPUT);
	pinMode(this->MS1Pin = MS1Pin, OUTPUT);
	pinMode(this->MS2Pin = MS2Pin, OUTPUT);
	//pinMode(this->SleepPin = SleepPin, OUTPUT);
	pinMode(this->MotorButtonPin = MotorButtonPin, INPUT);
	pinMode(this->NoMotorButtonPin = NoMotorButtonPin, INPUT);
	
	// Set the step pin to LOW ***************************** questionable
	CurrentStepStatus = LOW;
	digitalWrite(StepPin, CurrentStepStatus);
	
	
	// Set the mode pins
	switch(MSMode)
	{
		case(FULL_STEP):
			digitalWrite(MS1Pin, LOW);
			digitalWrite(MS2Pin, LOW);
		break;
		
		case(HALF_STEP):
			digitalWrite(MS1Pin, HIGH);
			digitalWrite(MS2Pin, LOW);
		break;
		
		case(QUARTER_STEP):
			digitalWrite(MS1Pin, LOW);
			digitalWrite(MS2Pin, HIGH);
		break;
		
		case(EIGHTH_STEP):
			digitalWrite(MS1Pin, HIGH);
			digitalWrite(MS2Pin, HIGH);
		break;
	}
}

bool CMotorControl::Set(MotorDirection Direction, unsigned int Interval, unsigned int SleepTime)
{
	// Check bounderies and current operation mode
	if ((OpMode != IDLE) || 
		(Interval < MIN_INTERVAL) || (Interval > MAX_INTERVAL) ||
		(SleepTime > MAX_SLEEP_TIME))
	{
		IsSet = false;
		return false;
	}
	
	digitalWrite(DirPin, Direction);
	this->Interval = Interval;
	this->SleepCountdown = SleepTime;
	this->Direction = Direction;
	
	IsSet = true;
}

bool CMotorControl::Start()
{
	if (!IsSet || DidReachEnd())
		return false;
	
	Countdown = Interval;

	if (SleepCountdown == 0)
	{
		OpMode = MOVE;
		Enable();
		delay(1);
		CurrentStepStatus = HIGH;
		digitalWrite(StepPin, CurrentStepStatus);
	}
	else
	{
		CurrentStepStatus = LOW;
		digitalWrite(StepPin, CurrentStepStatus);
		OpMode = SLEEP;
		Disable();
	}
	
	return true;
}

void CMotorControl::Stop()
{
	OpMode = IDLE;
	Disable();
	
	CurrentStepStatus = LOW;
	digitalWrite(StepPin, CurrentStepStatus);
}

bool CMotorControl::DidReachEnd()
{
	int Button;
	
	if (Direction == TO_MOTOR)
		Button = MotorButtonPin;
	else if (Direction == TO_NO_MOTOR)
		Button = NoMotorButtonPin;
	
	int Counter = 0;
	for (int i = 0; i < NUM_OF_BUTTON_SAMPLES; i++)
		if (digitalRead(Button))
			Counter++;
			
	return (Counter >= (NUM_OF_BUTTON_SAMPLES + 1) / 2);
}

void CMotorControl::ToggleStepPin()
{
	CurrentStepStatus ^= 1;
	digitalWrite(StepPin, CurrentStepStatus);
}

void CMotorControl::Enable()
{
	digitalWrite(EnablePin, LOW);
}

void CMotorControl::Disable()
{
	digitalWrite(EnablePin, HIGH);
}




CMotorControl MotorControl;




























