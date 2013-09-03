// include the library code:
#include <LiquidCrystal.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <PinChangeInt.h>
//#include <JeeLib.h> // https://github.com/jcw/jeelib
#include <avr/sleep.h>

 
// Data wire is plugged into pin 2 on the Arduino
#define ONE_WIRE_BUS 7
#define PIN1 10
 
// Setup a oneWire instance to communicate with any OneWire devices 
// (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
 
// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);
 


// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

uint16_t tipCount = 0;

void tipfunc() {
   tipCount++;
};


void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  sensors.begin();

  pinMode(PIN1, INPUT); digitalWrite(PIN1, HIGH);
  PCintPort::attachInterrupt(PIN1, &tipfunc, FALLING);  // add more attachInterrupt code as required

  set_sleep_mode(SLEEP_MODE_PWR_DOWN);         // Set sleep mode
  sleep_mode();                                // Sleep now

}

void loop() {

  sensors.requestTemperatures(); // Send the command to get temperatures
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.setCursor(5, 0);
  lcd.print(sensors.getTempCByIndex(0)); // Why "byIndex"? 
  
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  lcd.print("Rain: "); // Why "byIndex"? 
  lcd.setCursor(5, 1);
  lcd.print(tipCount*0.3);

  //Sleepy::loseSomeTime(1000); 
  delay(1000);
  set_sleep_mode(SLEEP_MODE_PWR_DOWN); // Set sleep mode
  sleep_mode(); // Sleep now


}

 

