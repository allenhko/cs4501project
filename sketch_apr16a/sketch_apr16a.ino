#include <OneWire.h>
#include <DallasTemperature.h>

// Data wire is conntec to the Arduino digital pin 4
#define ONE_WIRE_BUS 4

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature sensor 
DallasTemperature sensors(&oneWire);

int redPin = 11;                // output pin number to Red pin of the LED
int greenPin = 10;              // output pin number to Green pin
int bluePin = 9;                // output pin number to Blue pin

int STBY = 2;   // A Channel STBY Pin
int AIN1 = 3;   // A Channel Input 1
int AIN2 = 7;   // A Channel Input 2
int PWMA = 5;  // A Channel PWM

void setup(void)
{
  // Start serial communication for debugging purposes
  Serial.begin(9600);
  // Start up the library
  sensors.begin();
  pinMode(redPin, OUTPUT);      // sets the pin as output pin
  pinMode(greenPin, OUTPUT);    // sets the pin as output pin
  pinMode(bluePin, OUTPUT); 

  pinMode(STBY, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMA, OUTPUT);
}

void loop(void){ 
  // Call sensors.requestTemperatures() to issue a global temperature and Requests to all devices on the bus
  sensors.requestTemperatures(); 
  
  Serial.print("Celsius temperature: ");
  // Why "byIndex"? You can have more than one IC on the same bus. 0 refers to the first IC on the wire
  Serial.print(sensors.getTempCByIndex(0)); 
  Serial.print(" - Fahrenheit temperature: ");
  float a = sensors.getTempFByIndex(0);
  Serial.println(sensors.getTempFByIndex(0));

  digitalWrite(STBY, HIGH);
  
  if (60 < a < 80) {
    analogWrite(greenPin, 255);
    analogWrite(bluePin, 0);
    analogWrite(redPin, 0);
    analogWrite(PWMA, 0);
  }
  if (a > 80) {
    analogWrite(bluePin, 0);
    analogWrite(greenPin, 0);
    analogWrite(redPin, 255);
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
    analogWrite(PWMA, 170);
  }
  if (a < 60) {
    analogWrite(redPin, 0);
    analogWrite(bluePin, 255);
    analogWrite(greenPin, 0);
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, HIGH);
    analogWrite(PWMA, 170);
  }
  delay(1000);
}