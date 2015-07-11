
/*
 *  This is the openStackmatchControl for the remoteQth.com Stackmatch-Version
 *  If you need help, feel free to contact DM5XX@gmx.de
 *  Sketch is developed with IDE Version 1.6.4 and later
 *
 *  This is free software. You can redistribute it and/or modify it under
 *  the terms of Creative Commons Attribution 3.0 United States License if at least the version information says credits to remoteQTH.com :P
 *
 *  To view a copy of this license, visit http://creativecommons.org/licenses/by/3.0/us/ 
 *  or send a letter to Creative Commons, 171 Second Street, Suite 300, San Francisco, California, 94105, USA.
 *  
 *	Tribute to OL7M!
 *  LLAP!
 */


#include <SPI.h>
#include <Ethernet.h>
#include <avr/pgmspace.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>  // F Malpartida's NewLiquidCrystal library

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
LiquidCrystal_I2C  lcd(I2C_ADDR, En_pin, Rw_pin, Rs_pin, D4_pin, D5_pin, D6_pin, D7_pin);
byte mac[] = { 0xDE, 0x7D, 0xBE, 0xEF, 0xFE, 0xED };  //**************************************** <-------------------------CHANGE MAC-ADRESS IF YOU HAVE MORE THAN 1 CONTROLLER


////////////////////////////////   CONFIGURE YOUR DEFAULT DETTINGS HERE   /////////////////////////////////////////////

byte ip[] = { 192, 168, 1, 180 };           //*************************************************** <------------------------CHANGE ARDOINOs IP TO YOUR NEEDs - DONT FORGET TO CHANGE IT EVERYWHERE (see comments WWW Content for PROGMEM) !!!!!!           
byte gateway[] = { 192, 168, 1, 190 };                   
byte subnet[] = { 255, 255, 255, 0 };                  
EthernetServer server(80);                  //*************************************************** <------------------------CHANGE PORT, IF YOU DONT LIKE PORT 80           

boolean registersRx[4] = {1, 0, 0, 0};
boolean registersTx[4] = {1, 0, 0, 0};
boolean registersDisplay[4] = {1, 0, 0, 0};

/////////////////////////////////////// WWW Content for PROGMEM ////////////////////////////////////////////////////////////////////////////////////////////

const char  message0[] PROGMEM = { "<html><head>"};
const char  message1[] PROGMEM  = {"<script type=\"text/javascript\" src=\"http://code.jquery.com/jquery-1.11.3.js\">"};      //*************************************************** <------------------------CHANGE to your File-Location URL IF NEEDED !!!!!!
//const char  message1[] PROGMEM = { "<script type=\"text/javascript\" src=\"http://192.168.1.190/oc/jquery-1.11.3.js\">" };      //*************************************************** <------------------------CHANGE to your File-Location URL IF NEEDED !!!!!!
const char  message2[] PROGMEM = { "</script>" };
//const char  message3[] PROGMEM  = {"<script type='text/javascript' src='http://192.168.1.190/oc/c.js'></script>"};            //*************************************************** <------------------------CHANGE to your File-Location URL IF NEEDED !!!!!!
const char  message3[] PROGMEM = { "<script type='text/javascript' src='http://h.mmmedia-online.de/c.js'></script>" };            //*************************************************** <------------------------CHANGE to your File-Location URL IF NEEDED !!!!!!
//const char  message3[] PROGMEM = { "<script type='text/javascript' src='http://h.mmmedia-online.de/c.js'></script>" };            //*************************************************** <------------------------CHANGE to your File-Location URL IF NEEDED !!!!!!
const char  message4[] PROGMEM  = {"<script type='text/javascript' src='http://h.mmmedia-online.de/cm.js'></script>"};         //********UNCOMMENT/COMMENT NEEDED VERSION: Multibeaming*********** <------------------------CHANGE to your File-Location URL IF NEEDED !!!!!!
//const char  message4[] PROGMEM  = {"<script type='text/javascript' src='http://h.mmmedia-online.de/cs2.js'></script>"};        //********UNCOMMENT/COMMENT NEEDED VERSION: Stack 2 Ant************ <------------------------CHANGE to your File-Location URL IF NEEDED !!!!!!
//const char  message4[] PROGMEM  = {"<script type='text/javascript' src='http://h.mmmedia-online.de/cs3.js'></script>"};          //********UNCOMMENT/COMMENT NEEDED VERSION: Stack 3 And************ <------------------------CHANGE to your File-Location URL IF NEEDED !!!!!!
//const char  message4[] PROGMEM = { "<script type='text/javascript' src='http://192.168.1.190/oc/cs3.js'></script>" };          //********UNCOMMENT/COMMENT NEEDED VERSION: Stack 3 And************ <------------------------CHANGE to your File-Location URL IF NEEDED !!!!!!
const char  message5[] PROGMEM = { "<link href=\"http://h.mmmedia-online.de/c.css\" rel=\"stylesheet\" type=\"text/css\"/>" };    //*************************************************** <------------------------CHANGE to your File-Location URL IF NEEDED !!!!!!
//const char  message5[] PROGMEM = { "<link href=\"http://192.168.1.190/oc/c.css\" rel=\"stylesheet\" type=\"text/css\"/>" };    //*************************************************** <------------------------CHANGE to your File-Location URL IF NEEDED !!!!!!
const char  message6[] PROGMEM = { "<link rel = \"shortcut icon\" href=\"http://h.mmmedia-online.de/favicon.ico\">" };
//const char  message6[] PROGMEM = { "<link rel = \"shortcut icon\" href=\"http://192.168.1.190/oc/favicon.ico\">" };
const char  message7[] PROGMEM = { "</head>" };
const char  message8[] PROGMEM  = {"<body>"};
const char  message9[] PROGMEM  = {"<div id=\"container\">"};
const char  message10[] PROGMEM  = {"<div class=\"myTab\">"};
const char  message11[] PROGMEM  = {"<table class=\"myTable\">"};
const char  message12[] PROGMEM  = {"<tr><td><a id=\"b0\" href=\"#\" class=\"myButton\" onClick=\"clkButton(0)\"> </a></td>"};
const char  message13[] PROGMEM  = {"<td><a id=\"b1\" href=\"#\" class=\"myButton\" onClick=\"clkButton(1)\"> </a></td>"};
const char  message14[] PROGMEM  = {"<td><a id=\"b2\" href=\"#\" class=\"myButton\" onClick=\"clkButton(2)\"> </a></td>"};
const char  message15[] PROGMEM  = {"<td><a id=\"b3\" href=\"#\" class=\"myButton\" onClick=\"clkButton(3)\"> </a></td>"};
const char  message16[] PROGMEM  = {"<td align=\"center\"><a id=\"b4\" href=\"#\" class=\"myButton right\" onClick=\"clkButton(4)\"> </a></td>"};
const char  message17[] PROGMEM  = {"</tr>"};
const char  message18[] PROGMEM  = {"</table>"};
const char  message19[] PROGMEM  = {"</div>"};
const char  message20[] PROGMEM  = {"<div class=\"myTab2\" id=\"myTabi\"><div id=\"myRxString\"></div><div id=\"myTxString\"></div></div>"};
const char  message21[] PROGMEM  = {"</div>"};
const char  message22[] PROGMEM  = {"</body>"};
//const char  message23[] PROGMEM  = {"<script>var urlToArduino='http://192.168.1.180';$('#container').css(\"background-image\", \"url(http://h.mmmedia-online.de/stack.png)\"); "}; //********UNCOMMENT/COMMENT NEEDED VERSION: Stack***************** <------------------------CHANGE to Arduino AND File-Location URL IF NEEDED !!!!!!
const char  message23[] PROGMEM  = {"<script>var urlToArduino='http://192.168.1.180';$('#container').css(\"background-image\", \"url(http://h.mmmedia-online.de/multi.png)\"); "}; //********UNCOMMENT/COMMENT NEEDED VERSION: Multibeaming************ <------------------------CHANGE to Arduino AND File-Location URL IF NEEDED !!!!!!
//const char  message23[] PROGMEM = { "<script>var urlToArduino='http://192.168.1.180';$('#container').css(\"background-image\", \"url(http://192.168.1.190/oc/stack.png)\"); " }; //********UNCOMMENT/COMMENT NEEDED VERSION: Multibeaming************ <------------------------CHANGE to Arduino AND File-Location URL IF NEEDED !!!!!!
const char  message24[] PROGMEM = { "getAllContent();window.setTimeout(updateLCD,150);</script>" };
const char  message25[] PROGMEM  = {"</html>"};

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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

String requestString;
const int ptt_InPin = 2;
const int ptt_OutPin = 9;
const int txModePin = 6;
const int txModeLedPin = 8;
int DS_pin = 5;
int STCP_pin = 3;
int SHCP_pin = 7;
volatile boolean isTxMode = false;
volatile boolean isTxModeSet = false;
volatile boolean isRxModeSet = false;
long debouncing_time = 10;
volatile unsigned long last_millis;
unsigned long pushDog = 0;
volatile unsigned long pttDog = 0;
volatile unsigned long pttDogTime = 0; // this is sort of anti-qsk-logic... the lower the value, the faster the response. Set you value for the threshold only if ur txrx has not threshold time for anti-qsk.

int buttonPin = 0;
byte oldButton = 0;
boolean inTxEditMode = false;
byte oldTxEditMode = 0;

int leadIn = 15;
int leadOut = 20;

byte currentButton;
byte readTxEditMode;

//////////////////////////////////////////////// Main Setup //////////////////////////////////////////////////////////////

void setup()
{
  //Serial.begin(9600);
  setupPinMode();
  setupDigitalWrites();
  setupLCD();
  setupRegisters();
  Ethernet.begin(mac, ip); // Client starten
  //Serial.print("server is at ");
  //Serial.println(Ethernet.localIP());  
}

void setupDigitalWrites()
{
  digitalWrite(ptt_InPin, HIGH);
  digitalWrite(ptt_OutPin, LOW);
  digitalWrite(txModePin, HIGH);
  digitalWrite(txModeLedPin, HIGH);
}

void setupPinMode()
{
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(DS_pin, OUTPUT);
  pinMode(STCP_pin, OUTPUT);
  pinMode(SHCP_pin, OUTPUT);
  pinMode(ptt_InPin, INPUT);
  pinMode(ptt_OutPin, OUTPUT);
  pinMode(txModePin, INPUT);
  pinMode(txModeLedPin, OUTPUT);
}

void setupRegisters()
{
  writeDisplayRegister(registersRx);
  writeRelayRegister(registersRx);
  setStar(registersTx, true);
  writeDisplayRegister(registersTx);
  writeRelayRegister(registersTx);
}

void setupLCD()
{
  lcd.begin (16, 2); // initialize the lcd
  lcd.setBacklightPin(BACKLIGHT_PIN, NEGATIVE);
  lcd.setBacklight(LED_ON);
  displayWelcomeText();
  delay(2000);
  displayVersion();
  delay(2000);
  displayMain();
  setStar(registersRx, false);
}

//////////////////////////////////////////////// Main Loop //////////////////////////////////////////////////////////////
void loop()
{
  ///////////////////// PTT CONTROL SECTION /////////////////////////
  debouncePtt();

  // this is handling the status change from tx to rx and from rx to tx... The setup methods contain the switching delays and logic
  if (isTxMode)
  {
	  if (!isTxModeSet)
	  {
		  delay(leadIn); // this is leadin - comment it out and see 100us
		  digitalWrite(ptt_OutPin, HIGH);

		  isRxModeSet = false;
		  isTxModeSet = true;
		  if (currentButton > 0 && currentButton != oldButton && oldButton == 0)
		  {
			  removeStars(true);
			  setStar(registersTx, true);
		  }
	  }
  }
  else
  {
	if (!isRxModeSet && millis() - pttDog > pttDogTime)
    {
      receiving(); // set outupt pins
      setRxSetup(); // handle rx delay
      isRxModeSet = true;
      isTxModeSet = false;
    }
    currentButton = getPressedButton();
    readTxEditMode = digitalRead(txModePin);
  }
  
  ///////////////////// BUTTON SECTION /////////////////////////    
  // here comes the TX-Mode-Button logic
  if (!isTxMode)
  {
	  if (readTxEditMode == 0 && readTxEditMode != oldTxEditMode)
	  {
		if (inTxEditMode)
		{
		  inTxEditMode = false;
		  switchArrow(false);
		  digitalWrite(txModeLedPin, HIGH);
		  writeDisplayRegister(registersRx);
		  writeRelayRegister(registersRx);
		}
		else                                               // else go to the tx-edit
		{
		  inTxEditMode = true;
		  switchArrow(true);
		  digitalWrite(txModeLedPin, LOW);
		  writeDisplayRegister(registersTx);
		  writeRelayRegister(registersTx);
		}
	  }

	  // here comes the button logic
	  if (!isTxMode && currentButton > 0 && currentButton != oldButton && oldButton == 0 && (long)(millis() - pushDog) >= 200)
	  {
		if (inTxEditMode)
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
  }
  oldButton = currentButton;
  oldTxEditMode = readTxEditMode;
  webServer();

}

/*------------------------------------------------------------------------------------------------------------------------*/
/*---------------------------------------------HELPER METHODS ------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------------------------*/


/*-------------------------------------------------- LCD Display ---------------------------------------------------------*/

// the version info. Dont change anything here! CC
void displayVersion()
{
  resetDisplay();
  lcd.print("1.5.2 150711 IP");
  lcd.setCursor(0, 1);
  lcd.print(" OK2ZAW & DM5XX");
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
void removeStars(boolean mode)
{
  byte row = 0;

  if (mode)
    row = 1;

  for (int i = 5; i < 15; i = i + 3)
  {
    lcd.setCursor(i, row);
    lcd.print(" ");
  }
}

// calculate the position and set the stars needed to represent the regsiterTx/Rx Array
void setStar(boolean regArry[], boolean mode)
{
  byte row = 0;

  if (mode) // if 1 => TXMode, second row of the display
    row = 1;

  for (int x = 0; x < 4; x++)
  {
    lcd.setCursor(5 + (x * 3), row);
    if (regArry[x] == 1)
      lcd.print("*");
    else
      lcd.print(" ");
  }
}

/*-------------------------------------------------- Register handling --------------------------------------------------------------*/
// my little Register method. Chains the displayregister with the rx/tx register and writes them into the chip.
void writeRelayRegister(boolean registers[])
{
  boolean tempRegisters[8];

  for (int x = 0; x < 4; x++)
  {
    tempRegisters[x] = registers[x];
    tempRegisters[x + 4] =  registersDisplay[x];
  }

  digitalWrite(STCP_pin, LOW);
  for (int i = 7; i >= 0; i--)
  {
    digitalWrite(SHCP_pin, LOW);
    digitalWrite(DS_pin, tempRegisters[i]);
    digitalWrite(SHCP_pin, HIGH);
  }
  digitalWrite(STCP_pin, HIGH);
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
  
  for(int u = 0;u < nrOfButtons; u++)
    sum += arri[u];   
    
  return sum;
}

void setDisplayAndRelays(boolean isTx)
{
	if (isTx)
	{
		removeStars(true);
		setStar(registersTx, true);
		writeDisplayRegister(registersTx);
		writeRelayRegister(registersTx);
	}
	else
	{
		removeStars(false);
		setStar(registersRx, false);
		writeDisplayRegister(registersRx);
		writeRelayRegister(registersRx);
	}
}

/*-------------------------------------------------- Fancy Helpers --------------------------------------------------------------*/
// my little string splitting method
String getStringPartByNr(String data, char separator, int index)
{
  int stringData = 0; 
  String dataPart = "";    
  for(int i = 0; i<data.length(); i++) 
  {      
    if(data[i]==separator) 
      stringData++;
    else if(stringData==index) 
      dataPart.concat(data[i]);
    else if(stringData>index) 
    {
      return dataPart;
      break;  
    }
  }
  return dataPart;
}

/*------------------------------------------------- PTT --------------------------------------------------------------------------*/
void debouncePtt() {
	if ((long)(millis() - last_millis) >= debouncing_time) {
		isTxMode = !digitalRead(ptt_InPin);
		if (isTxMode)
			pttTriggerTX();
		else
			pttTriggerRX();
		last_millis = millis();
	}
}

void pttTriggerTX()
{
	isTxMode = true;
	if (!inTxEditMode)
		writeDisplayRegister(registersTx);		//////////////////
	writeRelayRegister(registersTx);
	pttDog = millis();
	Serial.println("ptt");
}

void pttTriggerRX()
{
	isTxMode = false;
	isRxModeSet = false;
	isTxModeSet = false;
}

// set pins for receiving
void receiving()
{
  //digitalWrite(ptt_InPin, HIGH);
  digitalWrite(ptt_OutPin, LOW);
}

/*------------------------------------------------- RX Setup --------------------------------------------------------------------*/

// set the needed relays and display messages for RX
void setRxSetup()
{
  delay(leadOut);			// leadout time
  if (currentButton > 0 && currentButton != oldButton && oldButton == 0)
  {
	  removeStars(false);
	  setStar(registersRx, false);
  }
  if (!inTxEditMode)
    writeDisplayRegister(registersRx);
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
  int enemy = analogRead(buttonPin);

  for (int i = 0; i < 4; i ++)
  {
    int currentV = analogRead(buttonPin);
    int dif = enemy - currentV;
    if ((dif >= 0 && dif < 20) || (div < 0 && dif > -20))
      sum += currentV;
    enemy = currentV;
    delay(3);
  }
  return sum / 4;
}


/*------------------------------------------------------------------------------------------------------------------------*/
/*----------------------------------------------- WEB Server Part --------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------------------------*/
/*---- Example: http://192.168.1.180 for a simple get. -------------------------------------------------------------------*/ 
/*---- Example: http://192.168.1.180/Set/1/0101 to Set 1 (TX) to 0101 (off-on-off-on), use 0 to set RX -------------------*/
/*------------------------------------------------------------------------------------------------------------------------*/
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
           
           if(cmdSet >= 0)
           {
             byte currentBank = getStringPartByNr(requestString, '/', 2).toInt(); // the 2nd part is the bank-number
			 Serial.println(currentBank);
			 String currentPinString = getStringPartByNr(requestString, '/', 3); // the 3nd part is the decimal-value to react on
			 Serial.println(currentPinString);

             String myString = currentPinString.substring(0, currentPinString.indexOf(" HTT")); // remove the _HTTP... and convert to int
			 Serial.println(myString);

             if(!isTxMode)
             {
               if(currentBank == 1)
               {
                 inTxEditMode = true;
                 switchArrow(true);
				 writeToTheRegister(registersTx, myString);
				 setDisplayAndRelays(true);
               }
               else
               {
                 inTxEditMode = false;
                 switchArrow(false);
				 writeToTheRegister(registersRx, myString);
				 setDisplayAndRelays(false);
               }
             }
             getStatus(client);
           }
           else if(cmdGet >=0)
             getStatus(client);
           else
             getPage(client);
             
           requestString="";  
  
           delay(1);
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
  client.println();
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
     printProgStr ((const char *) pgm_read_word (&messages [i]), client);
     client.println();
  }
}

void printProgStr (const char * str, EthernetClient client)
{
  char c;
  if (!str) 
    return;
  while ((c = pgm_read_byte(str++)))
    client.print (c);
} 

// Writes to both of the registers directly - Remember: If you are calling the webserverm you have to take care about urself about button-switching logic and restrictions
void writeToTheRegister(boolean regiA[], String theString)
{
  for(int d = 0; d < 4; d++)
  {
    boolean val = true;
    if(theString[d] == '0')
      val = false;
    
    regiA[d] = val;
    registersDisplay[d] = val;
  }
}

// convert an array into the string for the response method
String convertArrayToString(boolean ri[])
{
  String mytemp;
  for(int f = 0; f < 4; f++)
  {
      if(ri[f]==true)
        mytemp+="1";
      else
        mytemp+="0";
  }
  
  return mytemp;
}
