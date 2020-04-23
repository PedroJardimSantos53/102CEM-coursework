#define LDR A0                                        //LDR sensor connected to analog 0 on the arduino

#define RRredLED 8                                    //Rear Right red LED connected to digital pin 8
#define RLredLED 7                                    //Rear Left red LED connected to digital pin 7
#define FRredLED 6                                    //Front Right red LED connected to digital pin 6
#define FLredLED 5                                    //Front Left red LED connected to digital pin 5

#define FRgreenLED 4                                  //Front Right green LED connected to digital pin 4
#define FLgreenLED 3                                  //Front Left green LED connected to digital pin 3

#define RRGB 22                                       //Red component of the RGB LED connected to digital pin 22
#define GRGB 24                                       //Green component of the RGB LED connected to digital pin 24
#define BRGB 26                                       //Blue component of the RGB LED connected to digital pin 26

//-----------fading setup-----------//

unsigned long previousMillis = 0;
unsigned long previousMillis2 = 0;
long IntervalMode1 = 6;
long IntervalMode2 = 5;

int brightness = 0;
int fadeAmount = 5;
int RedBrightness = 0;
int GreenBrightness = 255;

//----------LED Button setup----------//

#define LEDButton 9
int LEDButtonState;
int lastLEDButtonState = LOW;
int LEDMode = 0;
int oldLEDMode = 0;
boolean on = false;

//----------Mode Button setup----------//

#define ModeButton 2 
int ModeButtonState;           
int lastModeButtonState = LOW;  
int Mode = 0;
int oldMode = 0;

//----------Debouncing----------//

unsigned long lastDebounceTime = 0; 
unsigned long debounceDelay = 50;





void setup() {

  //Setting the 6 different LEDs as Outputs//
  pinMode(FLredLED, OUTPUT);
  pinMode(FRredLED, OUTPUT);
  pinMode(RLredLED, OUTPUT);
  pinMode(RRredLED, OUTPUT);
  pinMode(FLgreenLED, OUTPUT);
  pinMode(FRgreenLED, OUTPUT);
  
  //Setting the 3 different components of the RGB LED as Outputs//
  pinMode(RRGB, OUTPUT);
  pinMode(GRGB, OUTPUT);
  pinMode(BRGB, OUTPUT);

  //Setting the 2 buttons as Inputs//
  pinMode(ModeButton, INPUT);
  pinMode(LEDButton, INPUT);

  //Starting the serial monitor to help with debugging//
  Serial.begin(9600);
}

void loop() {

//LDR SETUP//
int val = analogRead(LDR);
Serial.println(val); 

//BUTTON DEBOUNCING ROUTINE//
  int ModeReading = digitalRead(ModeButton);
  
  if (ModeReading != lastModeButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (ModeReading != ModeButtonState) {
      ModeButtonState = ModeReading;
      if (ModeButtonState == HIGH) {
        Mode = oldMode + 1;
      }
    }
  }

  lastModeButtonState = ModeReading;



//MODE SWITCHER//
  switch(Mode){


    
    case 1:         //SURVEILLANCE MODE//
    
                        if (val<750){
                        digitalWrite(RRGB,HIGH);
                        digitalWrite(GRGB,HIGH);
                        digitalWrite(BRGB,HIGH);
                        }else{
                        digitalWrite(RRGB,LOW);
                        digitalWrite(GRGB,LOW);
                        digitalWrite(BRGB,LOW);
                        } 
                         analogWrite(RLredLED, LOW);
                        analogWrite(RRredLED, LOW);
                        analogWrite(FLredLED, LOW);
                        analogWrite(FRredLED, LOW);
                        analogWrite(FLgreenLED, LOW);
                        analogWrite(FRgreenLED, LOW);    
     
     oldMode = Mode;
     break;


     
    case 2:         //SILENT MODE//

                        analogWrite(RLredLED, LOW);
                        analogWrite(RRredLED, LOW);
                        analogWrite(FLredLED, LOW);
                        analogWrite(FRredLED, LOW);
                        analogWrite(FLgreenLED, LOW);
                        analogWrite(FRgreenLED, LOW);
                        digitalWrite(RRGB,LOW);
                        digitalWrite(GRGB,LOW);
                        digitalWrite(BRGB,LOW);
     
     oldMode = Mode;
     break;


     
    default:        //NORMAL MODE//                          
                        
                        if (val<750){
                        digitalWrite(RRGB,HIGH);
                        digitalWrite(GRGB,HIGH);
                        digitalWrite(BRGB,HIGH);
                        }else{
                        digitalWrite(RRGB,LOW);
                        digitalWrite(GRGB,LOW);
                        digitalWrite(BRGB,LOW);
                        }

                        LEDButtonState = digitalRead(LEDButton); // latch switch code for the button on the breadboard to prevent bouncing and bad connections 
                        if (LEDButtonState == HIGH){ 
                          delay(50);
                          LEDButtonState = digitalRead(LEDButton);
                          if(LEDButtonState == LOW){
                              if(on==true){
                          on=false;
                        }  else{
                           on=true;
                             } 
                          }
                        }


                        if(on == false){
                        unsigned long currentMillis = millis(); // grab current time

                        analogWrite(FLredLED, brightness);// set the brightness of ledPin:
                        analogWrite(FRredLED, brightness);
                        analogWrite(RLredLED, brightness);
                        analogWrite(RRredLED, brightness);
                        digitalWrite(FLgreenLED,LOW);
                        digitalWrite(FRgreenLED,LOW);


                        if (currentMillis - previousMillis >= IntervalMode1){
                            brightness = brightness + fadeAmount;     // change the brightness for next time through the loop:
                            previousMillis = millis();
                          }
 
                        if (brightness <= 0 )
                          { // reverse the direction of the fading at the ends of the fade:
                            brightness = 0;
                            fadeAmount = -fadeAmount;
                          }
                            if (brightness >=255 )
                          { // reverse the direction of the fading at the ends of the fade:
                            brightness = 255;
                            fadeAmount = -fadeAmount;
                          }
                         }
                         else if(on == true){
                          // set the brightness of pin 9:
                          analogWrite(RLredLED, RedBrightness);
                          analogWrite(RRredLED, RedBrightness);
                          analogWrite(FLredLED, LOW);
                          analogWrite(FRredLED, LOW);
                          // set the brightness of pin 10:
                          analogWrite(FLgreenLED, GreenBrightness);
                          analogWrite(FRgreenLED, GreenBrightness);

                          // change the brightness for next time through the loop:
                          RedBrightness = RedBrightness + fadeAmount;
                          GreenBrightness = GreenBrightness - fadeAmount;
  
                          // reverse the direction of the fading at the ends of the fade: 
                          // and blink the internal LED on pin 13 at the fade end point
                          if (RedBrightness == 0 || RedBrightness == 255) {
                            fadeAmount = -fadeAmount ; 
                          }     

 
                          // wait for 30 milliseconds to see the dimming effect    

                         delay(8); // physiscal button acts up without this line and wont bridge the connection correctly
                        }

  
  
     oldMode = 0;
     break;
  }
  }
