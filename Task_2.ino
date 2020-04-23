#include <Wire.h>
#include <LiquidCrystal.h>

LiquidCrystal LCD(7, 8, 9, 10, 11, 12);                    // the LCD is connected to digital pins 7 through to 12


#define buzzer 5                                           // the buzzer is connected to digital pin 5

#define Rled 22                                            // red portion of RGB led connected to digital pin 22 
#define Gled 24                                            // green portion of RGB led connected to digital pin 24
#define Bled 26                                            // blue portion of RGB led connected to digital pin 26




//---------------Joystick Setup---------------//

#define xPin A1                                            // X axis component on the joystick is connected to analog pin 1
#define yPin A0                                            // Y axis component on the joystick is connected to analog pin 0
#define kPin 13                                            // Button on the joystick is connected to digital pin 13

int Yaxis;
int Xaxis;

int joyRead;
int joyPos;
int lastJoyPos;
long lastDebounceTime = 0;
long debounceDelay = 70;

bool refresh;
bool PQCP;

//---------------LCD Button Setup---------------//

#define Button 4
int lastButtonState = LOW;
int ButtonState;
int LCDmode = 0;
int oldLCDmode = 0;

//---------------Error Button Setup---------------//

#define Error 3
int lastErrorState = LOW;
int ErrorState;

int lastexitKState = LOW;
int exitKState;

//--------------Debouncing Routine--------------//

int lastkState = 0;
int kState = HIGH;

int kMode = 0;
int oldkMode = 0;

int Mode = 0;
int oldMode = 0;

void setup() {

  //Setting the joystick pins to Inputs//
  pinMode(xPin, INPUT);
  pinMode(yPin, INPUT);
  pinMode(kPin, INPUT_PULLUP);

  //Setting the 3 different components of the RGB LED as Outputs//
  pinMode(Rled, OUTPUT);
  pinMode(Gled, OUTPUT);
  pinMode(Bled, OUTPUT);

  //Buzzer is set as an Output//
  pinMode(buzzer, OUTPUT);

  //Letting the arduino know that there is 16 columns and 2 rows//
  LCD.begin(16, 2);

  //Initiating the serial monitor to help with debugging when necessary//
  Serial.begin(9600);

}

void loop() {

  Buttons();
  ONOFF();


}

void ONOFF() {

  switch (LCDmode) {
    case 1:
      LCD.display();
      controlJoystick();
      Menu();
      oldLCDmode = LCDmode;
      break;

    default:
      LCD.noDisplay();
      oldLCDmode = 0;
      break;
  }
}


void Menu() {

  switch (Yaxis) {

    case 1:
      IMUTest();
      break;

    case 2:
      SVTest();
      break;

    case 3:
      MotorTest();
      break;

    case 4:
      WIFITest();
      break;

    case 5:
      Exit();
      break;

    default:
      TestingON();
      break;
  }
}


void LEDBlinking() {
  digitalWrite(Bled, HIGH);
  delay(100);
  digitalWrite(Bled, LOW);
  delay(100);
  Serial.println("Testing...");

}



void Buttons() {

  int ButtonReading = digitalRead(Button);

  if (ButtonReading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (ButtonReading != ButtonState) {
      ButtonState = ButtonReading;
      if (ButtonState == HIGH) {
        LCDmode = oldLCDmode + 1;
      }
    }
  }

  lastButtonState = ButtonReading;



}

void ErrorCheck() {
  int ErrorReading = digitalRead(Error);


  if (ErrorReading == HIGH) {
    tone(buzzer, 3000);
    digitalWrite(Rled, HIGH);
    delay(1000);
    digitalWrite(Rled, LOW);
    noTone(buzzer);
    Serial.println("ERROR");
  }
  else if (ErrorReading == LOW) {
    digitalWrite(Gled, HIGH);
    delay(1000);
    digitalWrite(Gled, LOW);
    Serial.println("SUCCESS");
  }
}


void IMUTest() {

  int k = digitalRead(kPin);
  if (k != lastkState) {
    lastDebounceTime = millis();
  }
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (k != kState) {
      kState = k;
      if (kState == LOW) {
        kMode = oldkMode + 1;
      }
    }
  }

  lastkState = k;
  switch (kMode) {

    case 1:
      if (refresh) {
        LCD.clear();
        refresh = 0;
      }
      LCD.clear();
      LCD.setCursor(0, 0);
      LCD.print("IMU Test");
      delay(10);
      LCD.setCursor(0, 1);
      LCD.print("Testing");
      int counter;
      for (int x = 0; x <= 25; x++) {
        LEDBlinking();
      }
      ErrorCheck();

      kMode = 0;

    default:
      if (refresh) {
        LCD.clear();
        refresh = 0;
      }

      LCD.setCursor(0, 0);
      LCD.print("IMU Test");
      delay(10);
      LCD.setCursor(0, 1);
      LCD.print("press to start");
      oldkMode = 0;

      break;
  }
}

void SVTest() {

  int k = digitalRead(kPin);
  if (k != lastkState) {
    lastDebounceTime = millis();
  }
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (k != kState) {
      kState = k;
      if (kState == LOW) {
        kMode = oldkMode + 1;
      }
    }
  }

  lastkState = k;
  switch (kMode) {

    case 1:
      if (refresh) {
        LCD.clear();
        refresh = 0;
      }
      LCD.clear();
      LCD.setCursor(0, 0);
      LCD.print("SV Test");
      delay(10);
      LCD.setCursor(0, 1);
      LCD.print("Testing");
      int counter;
      for (int x = 0; x <= 25; x++) {
        LEDBlinking();
      }
      ErrorCheck();

      kMode = 0;

    default:
      if (refresh) {
        LCD.clear();
        refresh = 0;
      }

      LCD.setCursor(0, 0);
      LCD.print("SV Test");
      delay(10);
      LCD.setCursor(0, 1);
      LCD.print("press to start");
      oldkMode = 0;

      break;
  }
}


void MotorTest() {

  int k = digitalRead(kPin);
  if (k != lastkState) {
    lastDebounceTime = millis();
  }
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (k != kState) {
      kState = k;
      if (kState == LOW) {
        kMode = oldkMode + 1;
      }
    }
  }

  lastkState = k;
  switch (kMode) {

    case 1:
      if (refresh) {
        LCD.clear();
        refresh = 0;
      }
      LCD.clear();
      LCD.setCursor(0, 0);
      LCD.print("Motor Test");
      delay(10);
      LCD.setCursor(0, 1);
      LCD.print("Testing");
      int counter;
      for (int x = 0; x <= 25; x++) {
        LEDBlinking();
      }
      ErrorCheck();

      kMode = 0;

    default:
      if (refresh) {
        LCD.clear();
        refresh = 0;
      }

      LCD.setCursor(0, 0);
      LCD.print("Motor Test");
      delay(10);
      LCD.setCursor(0, 1);
      LCD.print("press to start");
      oldkMode = 0;

      break;
  }
}


void WIFITest() {


  int k = digitalRead(kPin);
  if (k != lastkState) {
    lastDebounceTime = millis();
  }
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (k != kState) {
      kState = k;
      if (kState == LOW) {
        kMode = oldkMode + 1;
      }
    }
  }

  lastkState = k;
  switch (kMode) {

    case 1:
      if (refresh) {
        LCD.clear();
        refresh = 0;
      }
      LCD.clear();
      LCD.setCursor(0, 0);
      LCD.print("WIFI Test");
      delay(10);
      LCD.setCursor(0, 1);
      LCD.print("Testing");
      int counter;
      for (int x = 0; x <= 25; x++) {
        LEDBlinking();
      }
      ErrorCheck();

      kMode = 0;

    default:
      if (refresh) {
        LCD.clear();
        refresh = 0;
      }

      LCD.setCursor(0, 0);
      LCD.print("WIFI Test");
      delay(10);
      LCD.setCursor(0, 1);
      LCD.print("press to start");
      oldkMode = 0;

      break;
  }
}


void Exit() {

  if (refresh) {
    LCD.clear();
    refresh = 0;
  }
  LCD.setCursor(0, 0);
  LCD.print("Testing Mode");
  delay(10);
  LCD.setCursor(0, 1);
  LCD.print("press to exit");


  int exitK = digitalRead(kPin);
  if (exitK != lastexitKState) {
    lastDebounceTime = millis();
  }
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (exitK != exitKState) {
      exitKState = exitK;
      if (exitKState == LOW) {
        LCD.clear();
        Yaxis = 0;
        LCDmode = 0;
      }
    }
  }
  lastexitKState  = exitK;

}

void TestingON() {

  if (refresh) {
    LCD.clear();
    refresh = 0;
  }
  LCD.setCursor(0, 0);
  LCD.print("Testing Mode");
  delay(10);
  LCD.setCursor(0, 1);
  LCD.print("ON");

}


void controlJoystick() {
  leeJoystick();
  if (PQCP) {
    PQCP = 0;
    LCD.noBlink();
    if (Yaxis < 8 && joyPos == 3) {
      Yaxis++;   //Down
      refresh = 1;
      Xaxis = 0;
    }
    if (Yaxis > 0 && joyPos == 4) {
      Yaxis--;   //Up
      Xaxis = 0;
      refresh = 1;
    }
    if (Xaxis < 3 && joyPos == 1) {
      Xaxis++;   //Right
      refresh = 1;
    }
    if (Xaxis > 0 && joyPos == 2) {
      Xaxis--;   //Left
      refresh = 1;
    }

  }
}

int leeJoystick() {
  int x = analogRead(xPin);
  int y = analogRead(yPin);


  if (x > 900) {
    joyRead = 1;      //x+
  } else if (x < 100) {
    joyRead = 2;      //x-
  } else if (y > 900) {
    joyRead = 3;      //y+
  } else if (y < 100) {
    joyRead = 4;      //y-
  } else  {
    joyRead = 0;
  }

  //----------------Deboucing for the Joystick----------------//

  if (joyRead != lastJoyPos) {
    lastDebounceTime = millis();
  }
  if (((millis() - lastDebounceTime) > debounceDelay) && (joyRead != joyPos)) {
    joyPos = joyRead;
    if (!PQCP) {
      PQCP = 1;
    }
  }
  if (((millis() - lastDebounceTime) > (5 * debounceDelay)) && (joyPos == 3 || joyPos == 4)) {
    joyPos = joyRead;                   //repeat time only for UP/DOWN
    if (!PQCP) {
      PQCP = 1;
    }
  }
  lastJoyPos = joyRead;


}
