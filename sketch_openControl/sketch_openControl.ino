
/*
*  This is the openControl for the remoteQth.com
*  If you need help, feel free to contact DM5XX@gmx.de
*  Sketch is developed with IDE Version 1.6.12 and later
*
*  This is free software. You can redistribute it and/or modify it under
*  the terms of Creative Commons Attribution 3.0 United States License if at least the version information says credits to remoteQTH.com :P
*
*  To view a copy of this license, visit http://creativecommons.org/licenses/by/3.0/us/
*  or send a letter to Creative Commons, 171 Second Street, Suite 300, San Francisco, California, 94105, USA.
*
*    Tribute to OL7M!
*  LLAP!
*
**********************
* Sj2w matrix:
*        a    b    c    k4
*A        1    0    0    1
*B        0    1    0    1
*C        0    0    1    1
*A+B    0    0    1    0
*B+C    1    0    0    0
*A+C    0    1    0    0
*A+B+C    0    0    0    0
***********************
***********************
remoteQth matrix:
*        a    b    c    bal
*A        1    0    0    0
*B        0    1    0    0
*C        0    0    1    0
*A+B    1    1    0    1
*B+C    0    1    1    1
(*A+C    1    0    1    1)
*A+B+C    1    1    1    1
***********************
***************************************************************************************************************/
/*#include <SPI.h>
#include "digitalWriteFast.h"
#include <Ethernet.h>
#include <avr/pgmspace.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>*/

//#define ENABLEWEBSERVER

#include "/home/werkstatt/Arduino/libraries/digitalWriteFast.h"
#include <LiquidCrystal_I2C.h>

#ifdef ENABLEWEBSERVER
	#include <Ethernet.h>
#endif

#include <EEPROM.h>

#define I2C_ADDR    0x20  // Define I2C Address for controller
#define BACKLIGHT_PIN  7
#define En_pin  4
#define Rw_pin  5
#define Rs_pin  6
#define D4_pin  0
#define D5_pin  1
#define D6_pin  2
#define D7_pin  3
#define  LED_OFF  0
#define  LED_ON  1
//#define DEBUG

const byte epromAddresses[] = { 0,1,2,3,4,5,6,7 };
#define SKETCHMODE 5         // 0 = multibeaming / 1 = stack2 / 2 = stack3  / 3 = sj2w_multibeaming / 4 = sj2w stack3  / 5 CN3A => this will enable the needed files for each mode... so choose your mode...


LiquidCrystal_I2C  lcd(I2C_ADDR, En_pin, Rw_pin, Rs_pin, D4_pin, D5_pin, D6_pin, D7_pin);

#ifdef ENABLEWEBSERVER
	byte mac[] = { 0xDE, 0x7D, 0xBE, 0xEF, 0xFE, 0xED };  //**************************************** <-------------------------CHANGE MAC-ADRESS IF YOU HAVE MORE THAN 1 CONTROLLER
														////////////////////////////////   CONFIGURE YOUR DEFAULT DETTINGS HERE   /////////////////////////////////////////////
	byte ip[] = { 192, 168, 1, 179 };           //******** <------------------------CHANGE ARDOINOs IP TO YOUR NEEDs - DONT FORGET TO CHANGE IT EVERYWHERE (see comments WWW Content for PROGMEM) !!!!!!           
	byte gateway[] = { 192, 168, 1, 40 };    //***** Define your routers gateway adress to the internet if needed
	byte subnet[] = { 255, 255, 255, 0 };
	/////////////////////////////// Change only if you know what you re doing....
	EthernetServer server(80);                  //*************************************************** <------------------------CHANGE PORT, IF YOU DONT LIKE PORT 80           
#endif
											////////////////////////////// NO CHANGES HERE!!!!!
boolean registersRx[4] = { 0, 0, 0, 0 };
boolean registersTx[4] = { 0, 0, 0, 0 };
boolean registersRxLed[4] = { 0, 0, 0, 0 };
boolean registersTxLed[4] = { 0, 0, 0, 0 };
boolean registersDisplay[4] = { 0, 0, 0, 0 };

///////////////////////////////////////// Change the labels you want to have... there are about 11 chars left. so dont use longer labels than 11 chars...
#if SKETCHMODE == 0
String rxDisplayArray[7] = { "Ant1", "Ant2", "Ant3",  "STACK ALL", "Ant1 + Ant2", "Ant1 + Ant3", "Ant2 + Ant3" };
String txDisplayArray[7] = { "Ant1", "Ant2", "Ant3",  "STACK all", "Ant1 + Ant2", "Ant1 + Ant3", "Ant2 + Ant3" };
#endif
#if SKETCHMODE == 1
String rxDisplayArray[4] = { "Beam TOP", "BEAM BOTTOM", "InPhase",  "OutOfPhase" };
String txDisplayArray[4] = { "beam top", "beam bottom", "inphase",  "outofphase" };
#endif
#if SKETCHMODE == 2
String rxDisplayArray[7] = { "Ant1", "Ant2", "Ant3",  "STACK ALL", "Ant1 + Ant2", "Ant1 + Ant3", "Ant2 + Ant3" };
String txDisplayArray[7] = { "Ant1", "Ant2", "Ant3",  "STACK all", "Ant1 + Ant2", "Ant1 + Ant3", "Ant2 + Ant3" };
#endif
#if SKETCHMODE == 3
String rxDisplayArray[4] = { "SBeam USA", "SBeam AF", "SBeam JA",  "SBeam All" };
String txDisplayArray[7] = { "SUSA", "SAF", "SJA",  "SUSA+AF+JA", "SUSA+AF", "SAF+JA", "SUSA+JA" };
#endif
#if SKETCHMODE == 4
String rxDisplayArray[7] = { "SJ3W TOP", "SJ3W Middle", "SJ3W Bottom",  "STACK ALL", "STOP+SMid", "SMID+SBOT", "STOP+SBOT" };
String txDisplayArray[7] = { "SJ3W tOP", "SJ3W middle", "SJ3W bottom",  "STACK all", "STOP+Smid", "Smid+Sbot", "Stop+Sbot" };
#endif
#if SKETCHMODE == 5
String rxDisplayArray[7] = { "A1", "A2", "A3",  "ALL", "A1 + A2", "A1 + A3", "A2 + A3" };
String txDisplayArray[7] = { "A1", "A2", "A3",  "STACK all", "Ant1 + Ant2", "Ant1 + Ant3", "Ant2 + Ant3" };
#endif

#ifdef ENABLEWEBSERVER
/////////////////////////////////////// WWW Content for PROGMEM  CHANGE ONLY (URLs) IF YOU KNOW WHAT YOU ARE DOING!!! ////////////////////////////////////////////////////////////////////////////////////////////
const char  message0[] PROGMEM = { "<html><head>" };
const char  message1[] PROGMEM = { "<script type=\"text/javascript\" src=\"http://code.jquery.com/jquery-1.11.3.js\">" };      //*************************************************** <------------------------CHANGE to your File-Location URL IF NEEDED !!!!!!
const char  message2[] PROGMEM = { "</script>" };
const char  message3[] PROGMEM = { "<script type='text/javascript' src='http://h.mmmedia-online.de/c.js'></script>" };            //*************************************************** <------------------------CHANGE to your File-Location URL IF NEEDED !!!!!!
#if SKETCHMODE == 0
const char  message4[] PROGMEM = { "<script type='text/javascript' src='http://h.mmmedia-online.de/cm.js'></script>" };         //******** Multibeam ************<------------------------CHANGE to your File-Location URL IF NEEDED !!!!!!
#endif
#if SKETCHMODE == 1
const char  message4[] PROGMEM = { "<script type='text/javascript' src='http://h.mmmedia-online.de/cs2.js'></script>" };        //******** Stack 2 Ant************ <------------------------CHANGE to your File-Location URL IF NEEDED !!!!!!
#endif
#if SKETCHMODE == 2
const char  message4[] PROGMEM = { "<script type='text/javascript' src='http://h.mmmedia-online.de/cs3.js'></script>" };          //******** Stack 3 And************ <------------------------CHANGE to your File-Location URL IF NEEDED !!!!!!
#endif
#if SKETCHMODE == 3
const char  message4[] PROGMEM = { "<script type='text/javascript' src='http://h.mmmedia-online.de/sj2w_cm.js'></script>" };          //******** Stack 3 And************ <------------------------CHANGE to your File-Location URL IF NEEDED !!!!!!
#endif
#if SKETCHMODE == 4
const char  message4[] PROGMEM = { "<script type='text/javascript' src='http://h.mmmedia-online.de/sj2w_cs3.js'></script>" };          //******** Stack 3 And************ <------------------------CHANGE to your File-Location URL IF NEEDED !!!!!!
#endif
#if SKETCHMODE == 5
const char  message4[] PROGMEM = { "<script type='text/javascript' src='http://h.mmmedia-online.de/cn3a.js'></script>" };          //******** Stack 3 And************ <------------------------CHANGE to your File-Location URL IF NEEDED !!!!!!
#endif
const char  message5[] PROGMEM = { "<link href=\"http://h.mmmedia-online.de/c.css\" rel=\"stylesheet\" type=\"text/css\"/>" };    //*************************************************** <------------------------CHANGE to your File-Location URL IF NEEDED !!!!!!
const char  message6[] PROGMEM = { "<link rel = \"shortcut icon\" href=\"http://h.mmmedia-online.de/favicon.ico\">" };
const char  message7[] PROGMEM = { "</head>" };
const char  message8[] PROGMEM = { "<body>" };
const char  message9[] PROGMEM = { "<div id=\"container\">" };
const char  message10[] PROGMEM = { "<div class=\"myTab\">" };
const char  message11[] PROGMEM = { "<table class=\"myTable\">" };
const char  message12[] PROGMEM = { "<tr><td><a id=\"b0\" href=\"#\" class=\"myButton\" onClick=\"clkButton(0)\"> </a></td>" };
const char  message13[] PROGMEM = { "<td><a id=\"b1\" href=\"#\" class=\"myButton\" onClick=\"clkButton(1)\"> </a></td>" };
const char  message14[] PROGMEM = { "<td><a id=\"b2\" href=\"#\" class=\"myButton\" onClick=\"clkButton(2)\"> </a></td>" };
const char  message15[] PROGMEM = { "<td><a id=\"b3\" href=\"#\" class=\"myButton\" onClick=\"clkButton(3)\"> </a></td>" };
const char  message16[] PROGMEM = { "<td align=\"center\"><a id=\"b4\" href=\"#\" class=\"myButton right\" onClick=\"clkButton(4)\"> </a></td>" };
const char  message17[] PROGMEM = { "</tr>" };
const char  message18[] PROGMEM = { "</table>" };
const char  message19[] PROGMEM = { "</div>" };
const char  message20[] PROGMEM = { "<div class=\"myTab2\" id=\"myTabi\"><div id=\"myRxString\"></div><div id=\"myTxString\"></div></div>" };
const char  message21[] PROGMEM = { "</div>" };
const char  message22[] PROGMEM = { " " };
//// DONT FORGET TO CHANGE THE INTERNAL ARDUINO IP....//////////////////////////////////////////////////
#if SKETCHMODE == 0
const char  message23[] PROGMEM = { "<script>var urlToArduino='http://192.168.1.179';\t\n$('#container').css(\"background-image\", \"url(http://h.mmmedia-online.de/multi.png)\"); " }; //********UNCOMMENT/COMMENT NEEDED VERSION: Multibeaming************ <------------------------CHANGE to Arduino AND File-Location URL IF NEEDED !!!!!!
#endif
#if SKETCHMODE == 1
const char  message23[] PROGMEM = { "<script>var urlToArduino='http://192.168.1.179';\t\n$('#container').css(\"background-image\", \"url(http://h.mmmedia-online.de/stack.png)\"); " }; //********UNCOMMENT/COMMENT NEEDED VERSION: Stack***************** <------------------------CHANGE to Arduino AND File-Location URL IF NEEDED !!!!!!
#endif
#if SKETCHMODE == 2
const char  message23[] PROGMEM = { "<script>var urlToArduino='http://192.168.1.179';\t\n$('#container').css(\"background-image\", \"url(http://h.mmmedia-online.de/stack.png)\"); " }; //********UNCOMMENT/COMMENT NEEDED VERSION: Stack***************** <------------------------CHANGE to Arduino AND File-Location URL IF NEEDED !!!!!!
#endif
#if SKETCHMODE == 3
const char  message23[] PROGMEM = { "<script>var urlToArduino='http://192.168.1.179';\t\n$('#container').css(\"background-image\", \"url(http://h.mmmedia-online.de/multi.png)\"); " }; //********UNCOMMENT/COMMENT NEEDED VERSION: Stack***************** <------------------------CHANGE to Arduino AND File-Location URL IF NEEDED !!!!!!
#endif
#if SKETCHMODE == 4
const char  message23[] PROGMEM = { "<script>var urlToArduino='http://192.168.1.179';\t\n$('#container').css(\"background-image\", \"url(http://h.mmmedia-online.de/stack.png)\"); " }; //********UNCOMMENT/COMMENT NEEDED VERSION: Stack***************** <------------------------CHANGE to Arduino AND File-Location URL IF NEEDED !!!!!!
#endif
#if SKETCHMODE == 5
const char  message23[] PROGMEM = { "<script>var urlToArduino='http://192.168.1.179';\t\n$('#container').css(\"background-image\", \"url(http://h.mmmedia-online.de/stack.png)\"); " }; //********UNCOMMENT/COMMENT NEEDED VERSION: Stack***************** <------------------------CHANGE to Arduino AND File-Location URL IF NEEDED !!!!!!
#endif
const char  message24[] PROGMEM = { "init();</script>" };
const char  message25[] PROGMEM = { "</html>" };
const byte webArraySize = 26;
const char * const messages[webArraySize] PROGMEM =
{
	message0,
	message1,
	message2,
	message3,
	message4,
	message5,
	message6,
	message7,
	message8,
	message9,
	message10,
	message11,
	message12,
	message13,
	message14,
	message15,
	message16,
	message17,
	message18,
	message19,
	message20,
	message21,
	message22,
	message23,
	message24,
	message25
};
#endif
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
String requestString;
const int ptt_InPin = 2;
const int ptt_OutPin = 9;
const int txModePin = 6;
const int txModeLedPin = 8;
const int DS_pin = 5;
const int STCP_pin = 3;
const int SHCP_pin = 7;
volatile boolean isTransmitting = false;
volatile boolean wasTransmittingBefore = false;
volatile boolean isTxModeSet = false;
volatile boolean isRxModeSet = false;
volatile boolean isRxModeSet_old = false;
const byte debouncing_timeMicros = 15; // X in Miliseconds * 1000 = microseconds 
volatile unsigned long last_micros;
unsigned long pushDog = 0;
unsigned long eepromDog = 0;
const int leadIn = 50; // dont forget: leadin complete = debouncetime in ms + leadIn!!!!
const int leadOut = 50;

int buttonPin = 0;
byte oldButton = 0;
boolean isInEditModeTX = true;
boolean oldMode = 1;
byte currentButton;
boolean isCurrentEditModeTX;
boolean isInRelayInvertMode = false;        // set this to true if you want to use hardware with inverted relay out. Normal (false) mode: relays are switched on (0=>1). Inverted mode: relays are switched out (1 => 0);
											//////////////////////////////////////////////// Main Setup //////////////////////////////////////////////////////////////
void setup()
{
	Serial.begin(9600);
	setupPinMode();
	setupDigitalWrites();
	readFromEprom();
	setupLCD();
	setupRegisters();
	#ifdef ENABLEWEBSERVER
		Ethernet.begin(mac, ip); // Client starten
		Serial.print("server is at ");
		Serial.println(Ethernet.localIP());
	#endif
	attachInterrupt(0, setInterruptTxMode, CHANGE);
}
void readFromEprom()
{
	for (byte a = 0; a < 4; a++)
	{
		byte ashift = a + 4;
		byte value = EEPROM.read(epromAddresses[a]);
		byte valueShift = EEPROM.read(epromAddresses[ashift]); // tx values are stored 4 bytes after rx
		registersRx[a] = value;
		registersTx[a] = valueShift;
		registersRxLed[a] = value;
		registersTxLed[a] = valueShift;
		registersDisplay[a] = value;
	}
}
void writeToEprom()
{
	for (byte a = 0; a < 4; a++)
	{
		byte ashift = a + 4;
		EEPROM.write(epromAddresses[a], registersRx[a]);
		EEPROM.write(epromAddresses[ashift], registersTx[a]);
	}
}

void setupDigitalWrites()
{
	digitalWriteFast(ptt_InPin, HIGH);
	digitalWriteFast(ptt_OutPin, LOW);
	digitalWriteFast(txModePin, HIGH);
	digitalWriteFast(txModeLedPin, HIGH);
}
void setupPinMode()
{
	pinModeFast(buttonPin, INPUT_PULLUP);
	pinModeFast(DS_pin, OUTPUT);
	pinModeFast(STCP_pin, OUTPUT);
	pinModeFast(SHCP_pin, OUTPUT);
	pinModeFast(ptt_InPin, INPUT);
	pinModeFast(ptt_OutPin, OUTPUT);
	pinModeFast(txModePin, INPUT);
	pinModeFast(txModeLedPin, OUTPUT);
}
void setupRegisters()
{
	byte checkHowManyOn = 0;
	
	checkHowManyOn = verifyButtons(registersRxLed, 4);
	if(checkHowManyOn == 3)
		registersRxLed[3] = 1;
	
	checkHowManyOn = verifyButtons(registersTxLed, 4);
	if(checkHowManyOn == 3)
		registersTxLed[3] = 1;
	
	specialSetup();
	writeDisplayRegister(registersRxLed);
	writeRelayRegister(registersRx);
	setLabels(registersTxLed, true);
	writeDisplayRegister(registersTxLed);
	writeRelayRegister(registersTx);
}
void setupLCD()
{
	lcd.begin(16, 2); // initialize the lcd
	lcd.setBacklightPin(BACKLIGHT_PIN, NEGATIVE);
	lcd.setBacklight(LED_ON);
	displayWelcomeText();
	betterDelay(2000);
	displayVersion();
	betterDelay(2000);
	displayGreetings();
	betterDelay(3000);
	displayMain();
	setLabels(registersRxLed, false);
}
//////////////////////////////////////////////// Main Loop //////////////////////////////////////////////////////////////
void loop()
{
	if (wasTransmittingBefore == false && isTransmitting)
	{
		pttTriggerTX();
		triggerTXWorkflow();
		wasTransmittingBefore = true;
	}

	if (wasTransmittingBefore && !isTransmitting)
	{
		if (!isRxModeSet)
		{
			receiving(); // set outupt pins
			triggerRXWorkflow(); // handle rx delay
			isRxModeSet = true;
			isTxModeSet = false;
		}

		currentButton = getPressedButton();
		isCurrentEditModeTX = digitalReadFast(txModePin);

		wasTransmittingBefore = false;
	}

	if (!isTransmitting)
	{
		currentButton = getPressedButton();
		isCurrentEditModeTX = !digitalReadFast(txModePin);

		///////////////////// BUTTON SECTION /////////////////////////    
		// here comes the TX-Mode-Button logic
		if (!isCurrentEditModeTX && isCurrentEditModeTX != oldMode)
		{
			if (isInEditModeTX)
			{
				isInEditModeTX = false;
				switchArrow(false);
				digitalWriteFast(txModeLedPin, HIGH);
				writeDisplayRegister(registersRxLed);
				writeRelayRegister(registersRx);
			}
			else                                               // else go to the tx-edit
			{
				isInEditModeTX = true;
				switchArrow(true);
				digitalWriteFast(txModeLedPin, LOW);
				writeDisplayRegister(registersTxLed);
				writeRelayRegister(registersTx);
			}
#ifdef DEBUG
			Serial.println("write to eeprom!");
#endif // DEBUG
			writeToEprom();
		}

		long currentDog = millis() - pushDog;

		// here comes the button logic
		if (currentButton > 0 && currentButton != oldButton && oldButton == 0 && (currentDog < 0 || currentDog >= 200))
		{
			if (isInEditModeTX)
			{
				setRegisterArray(currentButton, registersTx);
				setDisplayAndRelays(true);
			}
			else
			{
				setRegisterArray(currentButton, registersRx);
				setDisplayAndRelays(false);
			}
			pushDog = millis();
		}

		long eepromMillies = millis() - eepromDog;

		if (eepromMillies < 0 || eepromMillies >= 600000)
		{
			writeToEprom();
			eepromDog = millis();
		}
		oldButton = currentButton;
		oldMode = isCurrentEditModeTX;
		
		#ifdef ENABLEWEBSERVER
			webServer();
		#endif
	}
}
/*------------------------------------------------------------------------------------------------------------------------*/
/*---------------------------------------------HELPER METHODS ------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------- LCD Display ---------------------------------------------------------*/
// the version info. Dont change anything here! CC
void displayVersion()
{
	resetDisplay();
	lcd.print("1.96 051119 IP");
	lcd.setCursor(0, 1);
	lcd.print(" OK2ZAW & DM5XX");
}
void displayGreetings()
{
	resetDisplay();
	lcd.print("Hello my Master!");
	lcd.setCursor(0, 1);
	lcd.print("Have fun!");
}
// reset the display and set the cursor to default
void resetDisplay()
{
	lcd.clear();
	lcd.home();
	lcd.backlight();
	lcd.setCursor(0, 0);
}
// swirtch the -> to the needed position
void switchArrow(boolean mode)
{
	byte a = 0;
	byte b = 1;
	if (mode)
	{
		a = 1;
		b = 0;
	}
	lcd.setCursor(0, a);
	lcd.print("->");
	lcd.setCursor(0, b);
	lcd.print("  ");
}
// remove the stars - this is a brute force method.. you do not have to think about which one changed tho' :P
void clearLabels(boolean mode)
{
	byte row = 0;
	if (mode)
		row = 1;
	for (int i = 5; i < 16; i++)
	{
		lcd.setCursor(i, row);
		lcd.print(" ");
	}
}
// calculate the position and set the stars needed to represent the regsiterTx/Rx Array
void setLabels(boolean regArry[], boolean mode)
{
	byte row = 0;
	if (mode) // if 1 => TXMode, second row of the display
		row = 1;
	setDisplay(regArry, row);
}
/*-------------------------------------------------- Register handling --------------------------------------------------------------*/
// my little Register method. Chains the displayregister with the rx/tx register and writes them into the chip.
void writeRelayRegister(boolean registers[])
{
	boolean tempRegisters[8];
	byte inverter = 0;
	byte displayinverter = 0;
	byte counter = 0;
	for (int x = 0; x < 4; x++)
	{
		tempRegisters[x] = registers[x];
		tempRegisters[x + 4] = registersDisplay[x];
		counter += registers[x]; // sum all who are on
	}

#if SKETCHMODE != 1
	if(counter >1) // of more than 1 is on, switch on balun
		tempRegisters[3] = 1; 
#endif

	digitalWriteFast(STCP_pin, LOW);
	for (int i = 7; i >= 0; i--)
	{
		if (i < 4 && isInRelayInvertMode)
		{
			if (tempRegisters[i] == 0)
				inverter = 1;
			else
				inverter = 0;
		}
		else
		{
			inverter = tempRegisters[i];
		}
		digitalWriteFast(SHCP_pin, LOW);
		digitalWriteFast(DS_pin, inverter);
		digitalWriteFast(SHCP_pin, HIGH);
	}
	digitalWriteFast(STCP_pin, HIGH);
}
// write the values of a gioven register into the display register, only needed for showing the button status
void writeDisplayRegister(boolean regA[])
{
	for (int a = 0; a < 4; a++)
		registersDisplay[a] = regA[a];
}
// set the complete Register array to given value
void toggleRegisterArray(boolean regA[], byte v1)
{
	for (int a = 0; a < 4; a++)
		regA[a] = v1;
}
// In some Setups, at least 1 output should be connected
byte verifyButtons(boolean arri[], byte nrOfButtons)
{
	int sum = 0;
	for (int u = 0; u < nrOfButtons; u++)
		sum += arri[u];
	return sum;
}
void setDisplayAndRelays(boolean isTx)
{
	setRegisterLed(isTx);
	if (isTx)
	{
		clearLabels(true);
		setLabels(registersTxLed, true);
		writeDisplayRegister(registersTxLed);
		writeRelayRegister(registersTx);
	}
	else
	{
		clearLabels(false);
		setLabels(registersRxLed, false);
		writeDisplayRegister(registersRxLed);
		writeRelayRegister(registersRx);
	}
}
/*-------------------------------------------------- Fancy Helpers --------------------------------------------------------------*/
// my little string splitting method
String getStringPartByNr(String data, char separator, int index)
{
	int stringData = 0;
	String dataPart = "";
	for (int i = 0; i<data.length(); i++)
	{
		if (data[i] == separator)
			stringData++;
		else if (stringData == index)
			dataPart.concat(data[i]);
		else if (stringData>index)
		{
			return dataPart;
			break;
		}
	}
	return dataPart;
}

/*------------------------------------------------- PTT --------------------------------------------------------------------------*/

void setInterruptTxMode()
{
	long currentValue = micros() - last_micros;


	if (currentValue < 0 || currentValue >= debouncing_timeMicros)
	{
		isTransmitting = !digitalReadFast(ptt_InPin);
		last_micros = micros();
	}
}

void triggerTXWorkflow()
{
	betterDelay(leadIn);
	digitalWriteFast(ptt_OutPin, HIGH);
	isRxModeSet = false;
	isTxModeSet = true;
	if (currentButton > 0 && currentButton != oldButton && oldButton == 0)
	{
		clearLabels(true);
		setLabels(registersTxLed, true);
	}
	isRxModeSet_old = false;
}
void pttTriggerTX()
{

#ifdef DEBUG
	Serial.print("isInTXEditMode ");
	Serial.println(isInEditModeTX);
#endif

	isTransmitting = true;
	if (isTransmitting != wasTransmittingBefore)
	{
		if (!isInEditModeTX)
			writeDisplayRegister(registersTxLed);        //////////////////
		writeRelayRegister(registersTx);
	}
	wasTransmittingBefore = isTransmitting;

	// cn3a
	if(isInEditModeTX)
	{
		isInEditModeTX = false;
		switchArrow(false);
		digitalWriteFast(txModeLedPin, HIGH);
	}
}

/*void pttTriggerRX()
{
	isInEditModeTX = false;
	isTransmitting = false;
	wasTransmittingBefore = false;
	isRxModeSet = false;
	isTxModeSet = false;
	isRxModeSet_old = true; // prevent next debouncePtt call from executing pttTriggerRX, because it was called before..
}*/
// set pins for receiving
void receiving()
{
	digitalWriteFast(ptt_InPin, HIGH); // set intput to high just to be sure.. :P
	digitalWriteFast(ptt_OutPin, LOW);
}
/*------------------------------------------------- RX Setup --------------------------------------------------------------------*/
// set the needed relays and display messages for RX
void triggerRXWorkflow()
{
	if (currentButton > 0 && currentButton != oldButton && oldButton == 0)
	{
		clearLabels(false);
		setLabels(registersRxLed, false);
	}
	if (!isTransmitting)
		writeDisplayRegister(registersRxLed);
	if (!isTransmitting)
		betterDelay(leadOut);            // leadout time - wait to release the releays from tx position to rx position
	if (!isTransmitting)
		writeRelayRegister(registersRx);
}

/*------------------------------------------------- Button handling ---------------------------------------------------------------*/
// return the pressed button depending on the reistor array
byte getPressedButton()
{
	int c = getMyAverageValue();
	if (c < 10 && c >= 0)
		return 1;
	else if (c > 85 && c < 95)
		return 2;
	else if (c > 160 && c < 175)
		return 3;
	else if (c > 200 && c < 240)
		return 4;
	else
		return 0;
}
//calculate the average and except a difference of about 20 to the centervalue
int getMyAverageValue()
{
	int sum = 0;
	for (int i = 0; i < 4; i++)
	{
		int currentV = analogRead(buttonPin);
		sum += currentV;
		betterDelay(5);
	}
	return sum / 4;
}

/*------------------------------------------------------------------------------------------------------------------------*/
/*----------------------------------------------- WEB Server Part --------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------------------------*/
/*---- Example: http://192.168.1.180 for a simple get. -------------------------------------------------------------------*/
/*---- Example: http://192.168.1.180/Set/1/0101 to Set 1 (TX) to 0101 (off-on-off-on), use 0 to set RX -------------------*/
/*------------------------------------------------------------------------------------------------------------------------*/

#ifdef ENABLEWEBSERVER
void webServer()
{
	EthernetClient client = server.available();
	if (client) {
		while (client.connected()) {
			if (client.available()) {
				char c = client.read();
				if (requestString.length() < 100) {
					requestString += c;
				}
				//if HTTP request has ended
				if (c == '\n') {
					int cmdSet = requestString.indexOf("Set/"); // see if its a set request
					int cmdGet = requestString.indexOf("Get/"); // see if its a set request
					if (cmdSet >= 0)
					{
						byte currentBank = getStringPartByNr(requestString, '/', 2).toInt(); // the 2nd part is the bank-number
#ifdef DEBUG
						Serial.println(currentBank);
#endif // DEBUG
						String currentPinString = getStringPartByNr(requestString, '/', 3); // the 3nd part is the decimal-value to react on
#ifdef DEBUG
						Serial.println(currentPinString);
#endif // DEBUG
						String myString = currentPinString.substring(0, currentPinString.indexOf(" HTT")); // remove the _HTTP... and convert to int
#ifdef DEBUG
						Serial.println(myString);
#endif // DEBUG
						if (!isTransmitting)
						{
							if (currentBank == 1)
							{
#ifdef DEBUG
								Serial.println("set to txmode");
#endif // DEBUG
								isInEditModeTX = true;
								switchArrow(true);
								digitalWriteFast(txModeLedPin, LOW);
								writeToTheRegister(registersTx, myString);
								setDisplayAndRelays(true);
							}
							else
							{
#ifdef DEBUG
								Serial.println("set to rxmode");
#endif // DEBUG
								isInEditModeTX = false;
								switchArrow(false);
								digitalWriteFast(txModeLedPin, HIGH);
								writeToTheRegister(registersRx, myString);
								setDisplayAndRelays(false);
							}
#ifdef DEBUG
							Serial.println("write to eprom");
#endif // DEBUG
							writeToEprom();
						}
						getStatus(client);
					}
					else if (cmdGet >= 0)
						getStatus(client);
					else
						getPage(client);
					requestString = "";
					betterDelay(1);
					client.stop();
				}
			}
		}
	}
}
// A simple cors safe webserver response
void getStatus(EthernetClient client)
{
	String arrTx = convertArrayToString(registersTx);
	String arrRx = convertArrayToString(registersRx);
	client.println("HTTP/1.1 200 OK"); //send new page
	client.println("Content-Type: text/html");
	client.println("Access-Control-Allow-Origin: *");
	client.println("Access-Control-Allow-Methods: POST, GET, OPTIONS");
	client.println("Access-Control-Allow-Headers: Authorization");
	client.println();isInEditModeTX
	client.print("xx({\"v\": \"");
	client.print(arrRx);
	client.print("|");
	client.print(arrTx);
	client.print("\"})");
}
void getPage(EthernetClient client)
{
	client.println("HTTP/1.1 200 OK"); //send new page
	client.println("Content-Type: text/html");
	client.println("Access-Control-Allow-Origin: *");
	client.println("Access-Control-Allow-Methods: POST, GET, OPTIONS");
	client.println("Access-Control-Allow-Headers: Authorization");
	client.println();
	for (int i = 0; i < webArraySize; i++)
	{
		printProgStr((const char *)pgm_read_word(&messages[i]), client);
		client.println();
	}
}
void printProgStr(const char * str, EthernetClient client)
{
	char c;
	if (!str)
		return;
	while ((c = pgm_read_byte(str++)))
		client.print(c);
}
#endif


// Writes to both of the registers directly - Remember: If you are calling the webserverm you have to take care about urself about button-switching logic and restrictions
void writeToTheRegister(boolean regiA[], String theString)
{
	for (int d = 0; d < 4; d++)
	{
		boolean val = true;
		if (theString[d] == '0')
			val = false;
		regiA[d] = val;
		registersDisplay[d] = val;
	}
}
// convert an array into the string for the response method
String convertArrayToString(boolean ri[])
{
	String mytemp;
	for (int f = 0; f < 4; f++)
	{
		if (ri[f] == true)
			mytemp += "1";
		else
			mytemp += "0";
	}
	return mytemp;
}
void betterDelay(uint32_t ms)
{
	uint32_t start = micros();
	uint32_t mi = ms * 1000;
	while (micros() - start < mi) {
		// do nothing
		//        if (!wasTransmittingBefore && isTransmitting)
		//            break;
	}
}
