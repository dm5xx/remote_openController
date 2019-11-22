
#if SKETCHMODE == 5

void specialSetup()
{}

// the welcome info. you are not allowed to change anything here! CC
void displayWelcomeText()
{
  lcd.clear();
  lcd.home();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print(" remoteQTH.com ");
  lcd.setCursor(0, 1);
  lcd.print(" -- C N 3 A -- ");
}

// the default start screen template          
void displayMain()
{
  resetDisplay();
  lcd.print("->RX");
  lcd.setCursor(0, 1);
  lcd.print("  TX");
}

// set value of the pressed button into the relay register. Here you can define the mappings for the relays
void setRegisterArray(byte button, boolean regArr[])
{
   byte checkHowManyOn = 0;

 #ifdef DEBUG  
    Serial.print("Button ");
	Serial.println(button);
#endif

    if (button < 4) // only but 1 or 2 is pressed
    {
        if(regArr[button - 1] == 0)
    	    regArr[button - 1] = 1;
        else
        	regArr[button - 1] = 0;

	    checkHowManyOn = verifyButtons(regArr, 4);

#ifdef DEBUG
		Serial.print("Es sind ");
		Serial.println(checkHowManyOn);
		Serial.print("arr3 ist ");
		Serial.println(regArr[3]);
#endif		

		if(checkHowManyOn == 2 && regArr[3] == 1)
			regArr[3] == 0;
	}
    else
    {
        bool isOn = true;
		checkHowManyOn = verifyButtons(regArr, 4);

        if(checkHowManyOn == 3)
		{
            isOn = false;
			regArr[3] == 0;
		}

        for (int i = 0; i<3; i++)
            regArr[i] = isOn;
    }

 }

// Here you can define possible exceptions buttons/leds vs. relays. Default is 1:1, but needs to be changed in stack 2
void setRegisterLed(boolean isTx)
{   
#ifdef DEBUG
	Serial.print("Is TX ist gerade ");
	Serial.println(isTx);

	Serial.print("Is CurrentEditMode ist gerade ");
	Serial.println(isCurrentEditModeTX);
#endif

	if (isTx)
	{
		byte checkOne = verifyButtons(registersTx, 4);

#ifdef DEBUG
		Serial.println(checkOne);
#endif

		for (int i = 0; i<4; i++)
			registersTxLed[i] = registersTx[i];

		if(checkOne==3)
			registersTxLed[3] = 1;
	}
	else
	{
		byte checkOne = verifyButtons(registersRx, 4);

#ifdef DEBUG
		Serial.println(checkOne);
#endif

		for (int i = 0; i<4; i++)
			registersRxLed[i] = registersRx[i];

		if(checkOne==3)
			registersRxLed[3] = 1;
	}
}

void setDisplay(boolean regArry[], byte row)
{
    byte counter = 0;
	clearLabels(row);
	lcd.setCursor(5, row);

    for (int i = 0; i<4; i++)
	{
        if(regArry[i] == 1)
            counter += i+1;
	}

	if (counter == 0)
	{
		lcd.print("all_single");
        return;
	}

	if (row == 0)
	{
		if (counter == 1)
	    {
				lcd.print(rxDisplayArray[0]);
                return;
		}
		if (counter == 2)
	    {
				lcd.print(rxDisplayArray[1]);
                return;
		}
		if (counter == 3)
	    {
                if(regArry[0] == 0)
    				lcd.print(rxDisplayArray[2]);
                else
                	lcd.print(rxDisplayArray[4]);
                return;
		}
		if (counter == 4)
	    {
    			lcd.print(rxDisplayArray[5]);
                return;
		}
		if (counter == 5)
	    {
    			lcd.print(rxDisplayArray[6]);
                return;
		}
		if (counter > 5)
	    {
    			lcd.print(rxDisplayArray[3]);
                return;
		}
	}
	else
	{
		if (counter == 1)
	    {
				lcd.print(txDisplayArray[0]);
                return;
		}
		if (counter == 2)
	    {
				lcd.print(txDisplayArray[1]);
                return;
		}
		if (counter == 3)
	    {
                if(regArry[0] == 0)
    				lcd.print(txDisplayArray[2]);
                else
                	lcd.print(txDisplayArray[4]);
                return;
		}
		if (counter == 4)
	    {
    			lcd.print(txDisplayArray[5]);
                return;
		}
		if (counter == 5)
	    {
    			lcd.print(txDisplayArray[6]);
                return;
		}
		if (counter > 5)
	    {
    			lcd.print(txDisplayArray[3]);
                return;
		}
	}
}

#endif