#include <dht.h>`
dht DHT;
#define DHT11_PIN 36

#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 53
#define RST_PIN 5
MFRC522 mfrc522(SS_PIN, RST_PIN);

int redLed = 24; 
int greenLed = 22;
int buzzer = 8;
int yellowLed = 31;

int smokeA0 = A1;
int sensorThres = 500;

//sensor
int sensor = 32;              // the pin that the sensor is atteched to
int state = LOW;             // by default, no motion detected
int val = 0; 

//alam
int buttonPin = 45;     // the number of the pushbutton pin
int buttonState = 0; 
int buttonState1 = 0; 

const int songspeed = 1.5; //Change to 2 for a slower version of the song, the bigger the number the slower the song
//*****************************************
#define NOTE_C4  262   //Defining note frequency
#define NOTE_D4  294
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_G4  392
#define NOTE_A4  440
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_D5  587
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_G5  784
#define NOTE_A5  880
#define NOTE_B5  988
//*****************************************
int notes[] = {       //Note of the song, 0 is a rest/pulse
   NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0, 
   NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0, 
   NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
   NOTE_A4, NOTE_G4, NOTE_A4, 0,
   
   NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0, 
   NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0, 
   NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
   NOTE_A4, NOTE_G4, NOTE_A4, 0,
   
   NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0, 
   NOTE_A4, NOTE_C5, NOTE_D5, NOTE_D5, 0, 
   NOTE_D5, NOTE_E5, NOTE_F5, NOTE_F5, 0,
   NOTE_E5, NOTE_D5, NOTE_E5, NOTE_A4, 0,
   
   NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0, 
   NOTE_D5, NOTE_E5, NOTE_A4, 0, 
   NOTE_A4, NOTE_C5, NOTE_B4, NOTE_B4, 0,
   NOTE_C5, NOTE_A4, NOTE_B4, 0,

   NOTE_A4, NOTE_A4, 
   //Repeat of first part
   NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0, 
   NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
   NOTE_A4, NOTE_G4, NOTE_A4, 0,

   NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0, 
   NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0, 
   NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
   NOTE_A4, NOTE_G4, NOTE_A4, 0,
   
   NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0, 
   NOTE_A4, NOTE_C5, NOTE_D5, NOTE_D5, 0, 
   NOTE_D5, NOTE_E5, NOTE_F5, NOTE_F5, 0,
   NOTE_E5, NOTE_D5, NOTE_E5, NOTE_A4, 0,
   
   NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0, 
   NOTE_D5, NOTE_E5, NOTE_A4, 0, 
   NOTE_A4, NOTE_C5, NOTE_B4, NOTE_B4, 0,
   NOTE_C5, NOTE_A4, NOTE_B4, 0,
   //End of Repeat

   NOTE_E5, 0, 0, NOTE_F5, 0, 0,
   NOTE_E5, NOTE_E5, 0, NOTE_G5, 0, NOTE_E5, NOTE_D5, 0, 0,
   NOTE_D5, 0, 0, NOTE_C5, 0, 0,
   NOTE_B4, NOTE_C5, 0, NOTE_B4, 0, NOTE_A4,

   NOTE_E5, 0, 0, NOTE_F5, 0, 0,
   NOTE_E5, NOTE_E5, 0, NOTE_G5, 0, NOTE_E5, NOTE_D5, 0, 0,
   NOTE_D5, 0, 0, NOTE_C5, 0, 0,
   NOTE_B4, NOTE_C5, 0, NOTE_B4, 0, NOTE_A4
};
//*****************************************
int duration[] = {         //duration of each note (in ms) Quarter Note is set to 250 ms
  125, 125, 250, 125, 125, 
  125, 125, 250, 125, 125,
  125, 125, 250, 125, 125,
  125, 125, 375, 125, 
  
  125, 125, 250, 125, 125, 
  125, 125, 250, 125, 125,
  125, 125, 250, 125, 125,
  125, 125, 375, 125, 
  
  125, 125, 250, 125, 125, 
  125, 125, 250, 125, 125,
  125, 125, 250, 125, 125,
  125, 125, 125, 250, 125,

  125, 125, 250, 125, 125, 
  250, 125, 250, 125, 
  125, 125, 250, 125, 125,
  125, 125, 375, 375,

  250, 125,
  //Rpeat of First Part
  125, 125, 250, 125, 125,
  125, 125, 250, 125, 125,
  125, 125, 375, 125, 
  
  125, 125, 250, 125, 125, 
  125, 125, 250, 125, 125,
  125, 125, 250, 125, 125,
  125, 125, 375, 125, 
  
  125, 125, 250, 125, 125, 
  125, 125, 250, 125, 125,
  125, 125, 250, 125, 125,
  125, 125, 125, 250, 125,

  125, 125, 250, 125, 125, 
  250, 125, 250, 125, 
  125, 125, 250, 125, 125,
  125, 125, 375, 375,
  //End of Repeat
  
  250, 125, 375, 250, 125, 375,
  125, 125, 125, 125, 125, 125, 125, 125, 375,
  250, 125, 375, 250, 125, 375,
  125, 125, 125, 125, 125, 500,

  250, 125, 375, 250, 125, 375,
  125, 125, 125, 125, 125, 125, 125, 125, 375,
  250, 125, 375, 250, 125, 375,
  125, 125, 125, 125, 125, 500
};

void setup() {
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(yellowLed, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(smokeA0, INPUT);
  pinMode(sensor, INPUT);    // initialize sensor as an input
  pinMode(buttonPin, INPUT);
  Serial.begin(9600);
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Approximate your card to the reader...");
  Serial.println();
}
void loop() {
 
  buttonState = digitalRead(buttonPin);
  Serial.print("ButtonState = ");
  Serial.println(buttonState);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    // turn LED on:
    for (int i=0;i<203;i++){              //203 is the total number of music notes in the song
       digitalWrite(greenLed, LOW);
       digitalWrite(redLed, HIGH);
    delay(10);
    digitalWrite(redLed, LOW);
    delay(10);
  int wait = duration[i] * songspeed;
  tone(buzzer,notes[i],wait);          //tone(pin,frequency,duration)
  delay(wait);}            

     digitalWrite(redLed, LOW);
     digitalWrite(greenLed, LOW);
     delay(10000);
    buttonState1=1;
  } else {
    // turn LED off:
    digitalWrite(redLed, HIGH);
  }
  int analogSensor = analogRead(smokeA0);

  Serial.print("Pin A0: ");
  Serial.println(analogSensor);
  // Checks if it has reached the threshold value
  if (analogSensor > sensorThres)
  {
    int i=0;
    for(i=700;i<800;i++){
      tone(buzzer,i);
      delay(15);
    }
    for(i=800;i>700;i--){
      tone(buzzer,i);
      delay(15);
    }
  }
  else
  {
    noTone(buzzer);
  }
  delay(100);


  val = digitalRead(sensor);   // read sensor value
  if (val == HIGH) {           // check if the sensor is HIGH
    digitalWrite(greenLed, HIGH);   // turn LED ON
    digitalWrite(redLed, LOW); 
    digitalWrite(yellowLed, LOW);
    delay(100);                // delay 100 milliseconds 
    
    if (state == LOW) {
      Serial.println("Motion detected!"); 
      state = HIGH;       // update variable state to HIGH
    }
  } 
  else {
      digitalWrite(redLed, HIGH);   // turn LED ON
      digitalWrite(greenLed, LOW);
      delay(200);             // delay 200 milliseconds 
      
      if (state == HIGH){
        Serial.println("Motion stopped!");
        state = LOW;       // update variable state to LOW
      }
  }

  int chk = DHT.read11(DHT11_PIN);
  Serial.print("Temperature = ");
  Serial.println(DHT.temperature);
  Serial.print("Humidity = ");
  Serial.println(DHT.humidity);
  
  if (DHT.humidity > 50 || DHT.temperature > 30 ) 
  {
  int i=0;
  for(i=700;i<800;i++){
    tone(buzzer,i);
    delay(15);
  }
  for(i=800;i>700;i--){
    tone(buzzer,i);
    delay(15);
  }
  }
  
  else
  {
    noTone(buzzer);
  }
  delay(1000);


  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "75 E7 29 E2" || content.substring(1) == "86 1D A3 B9") //the UID of the cards that have access
  {
    Serial.println("Authorized access");
    Serial.println();
    digitalWrite(greenLed, HIGH);   // turn LED ON, indicating that door is open
    digitalWrite(redLed, LOW);
    delay(3000);
    digitalWrite(yellowLed, HIGH);
  }
 
 else   {
    Serial.println(" Access denied");
    digitalWrite(redLed, HIGH);   // turn LED ON
    digitalWrite(greenLed, LOW);
    delay(3000);
  }
}
