// 281=2
//812=54

#include <Servo.h>

#define ENCODER_A 14
#define ENCODER_B 15
#define ENCODER_PORT PINC
#define SWITCH 13
#define BUTTON 12
#define RGB_RED 11
#define RGB_GREEN 10
#define RGB_BLUE 9
#define LED 6
#define SERVO 5
#define PIEZO 3
#define RELAY 2
#define POT 2
#define HALL 3
#define THERMISTOR 4
#define PHOTOCELL 5 

Servo myservo; // create servo object to control a servo

unsigned long currentMillis = 0; // a storage place called currentMillis and stores a value of zero, also this begins the millis function 

int hours = 0; 
int minutes = 0; // a interger that is named minutes and stores the value of zero
int seconds = 0; // a interger that is named seconds and stores the value of zero
int daylength = 0;
unsigned long daystart = millis();

int temp = THERMISTOR; // a interger that is named Temperature and conains the thermistor pin name

int Magnet = HALL;

int light = PHOTOCELL;

void setup() // sets up things to be able to work in the program and defines things
{
  Serial.begin(9600); // starts communication with the computer and shown in the serial monitor 
    pinMode(THERMISTOR, INPUT); // this pin contains the thermistor and it is defined as an input
     pinMode(PIEZO, OUTPUT); // this pin contains the piezo and it is defined as an output
     pinMode(RGB_BLUE, OUTPUT); // this pin contains the blue light on the RGB LED and it is defined as an output
     pinMode(RGB_RED, OUTPUT); // this pin contains the red light on the RGB LEDn and its is defined as and output
     pinMode(HALL, INPUT);
     pinMode(PHOTOCELL, INPUT);
      pinMode(RGB_GREEN, OUTPUT);
      pinMode(RELAY, OUTPUT);
      myservo.attach(SERVO, 1000, 2000);
}

void loop(){ // the main code will be runned repeatedly 

  digitalWrite(RELAY, digitalRead(BUTTON));

  Magnet = analogRead(HALL);

  myservo.write(map( analogRead(POT), 0, 1023, 0, 179));
   // sets the servo position according to the scaled value
  Serial.print( "pot reading ");
  Serial.println(analogRead (POT));
  
  Serial.print( "servo output ");
Serial.println(map( analogRead(POT), 0, 1023, 0, 179));
Serial.println(" ");

   delay(100);

 daylength = (millis()-daystart)/60000;
 Serial.println("time in minutes to hours "); // the words time in hours will be written in the serial montior 
  Serial.println(daylength); // the serial monitor will read the value of the number of hours

 temp = map(analogRead(THERMISTOR), 281, 812, 2, 54);  
    Serial.print("Celsius "); // the word celsius will be written in the serial monitor
    Serial.println(temp); // the serial monitor will read the value from the variable named temperature
    
    if(temp>30) { // if the value from the varibalbe named temperature rises above 651 then the piezo will create a sound  
      digitalWrite(RGB_BLUE, HIGH);
       digitalWrite(RELAY, HIGH);   
    }
    else{ // and if the value for the variable named temperature goes under 650 then the piezo will go silent
    temp<25;
     digitalWrite(RGB_BLUE, LOW);
     digitalWrite(RELAY, LOW);
   }
   if(temp<11){ // if value from the variable temperature goes below 439 then the peizo will create a sound 
     analogWrite(PIEZO, HIGH);
     digitalWrite(RGB_RED, HIGH);
   }
   else{ // and if the temperature variable value goes above 440 then the peizo will go silent
   temp>11;
     analogWrite(PIEZO, LOW);
     digitalWrite(RGB_RED, LOW);
   }
   
    if (daylength > 24) { // 2 - 2 = 0
    daylength = 0;
    daystart = millis();
    }
    
    if(Magnet>515){
    Serial.print(" Door closed ");
    Serial.println(Magnet);
  }
      else{
    Magnet<514;
    Serial.print(" Door open ");
    Serial.println(Magnet);
  }
   light = analogRead(PHOTOCELL);
 
  Serial.print("Brightness amount");
  Serial.println(light);
  
  if(light<315){
    digitalWrite(RGB_GREEN, HIGH);
  }
  else{
    digitalWrite(RGB_GREEN, LOW);
  }
  
  if(daylength <= 17 && light >= 855){
  digitalWrite(LED, LOW); 
  }
  else{
    digitalWrite(LED, HIGH);
  }
  }
  
    
    

    
