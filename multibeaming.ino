// the welcome info. you are not allowed to change anything here! CC
void displayWelcomeText()
{
  lcd.clear();
  lcd.home();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print(" remoteQTH.com ");
  lcd.setCursor(0, 1);
  lcd.print(" openMultiCon");
}

// the default start screen template
void displayMain()
{
  resetDisplay();
  lcd.print("->RX  1  2  3  A");
  lcd.setCursor(0, 1);
  lcd.print("  TX  1  2  3  A");
}

// set value of the pressed button into the relay register. Here you can define the mappings for the relays
void setRegisterArray(byte button, boolean regArr[])
{
  if (!inTxEditMode)                    // im rx mode
  {
    if (button < 4)                     // only button could be active, except button 4 
    {
      toggleRegisterArray(regArr, 0);

      if (regArr[button - 1] == 1)
        regArr[button - 1] = 0;
      else
        regArr[button - 1] = 1;
    }
    else                                // button 4: all combinations possible
    {
      if (regArr[button - 1] == 0)
        toggleRegisterArray(regArr, 1);
    }
  }
  else // im tx mode
  {
    byte checkOne = verifyButtons(regArr, 4);
	if (checkOne == 1) // only on is on
	{
		if (regArr[button - 1] == 0) // was the button off before? For sure, because its only one on...
		{
			if (button < 4) // if its 2, turn it on..
				regArr[button-1] = 1;
			else
			{
				regArr[0] = 1;
				regArr[1] = 1;
				regArr[2] = 1;
			}
			regArr[3] = 1; // if more than one is on, switch on 4, because of phasing...
		}
	}
	if (checkOne == 3) // if 3 are on (hint: 2 can never be on, because phasing is missing..
	{
		if (regArr[button - 1] == 0) // turn last missing one on...
			regArr[button - 1] = 1;
		else // so now a button is switched off...
		{
			if (button==4) // if its 4, go back to default 1 on
			{
				regArr[0] = 1;
				regArr[1] = 0;
				regArr[2] = 0;
			}
			else // turn the button off
				regArr[button-1] = 0;
			regArr[3] = 0; // phasing has to be off
		}
	}
	if (checkOne == 4) // if all are on...
	{
		if (button < 4) // if button < 4 is pressed, just turn it off
			regArr[button-1] = 0;
		else // if button 4 is pressed, go to default 1 on
		{
			regArr[0] = 1;
			regArr[1] = 0;
			regArr[2] = 0;
			regArr[3] = 0;
		}
	}
  }
}

// Here you can define possible exceptions buttons/leds vs. relays. Default is 1:1
void setRegisterLed(boolean isTx)
{
	if (isTx)
	{
		for (int i = 0; i<4; i++)
		{
			registersTxLed[i] = registersTx[i];
		}
	}
	else
	{
		for (int i = 0; i<4; i++)
		{
			registersRxLed[i] = registersRx[i];
		}
	}
}

