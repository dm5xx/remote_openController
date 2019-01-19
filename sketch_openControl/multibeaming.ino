
#if SKETCHMODE == 0

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
  lcd.print(" openMultiCon");
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
	byte checkHowManyOn = verifyButtons(regArr, 4);

	boolean isSameKeyPressed = false;

	if (regArr[button - 1] == 1)
		isSameKeyPressed = true;

	if (checkHowManyOn == 1 && button < 4)
	{
		if (isSameKeyPressed == false)
		{
			regArr[0] = 0;
			regArr[1] = 0;
			regArr[2] = 0;
			regArr[button - 1] = 1;
			return;
		}
		else
		{
			if (button == 1)
			{
				regArr[0] = 1;
				regArr[1] = 1;
				regArr[2] = 0;
				return;
			}
			if (button == 2)
			{
				regArr[0] = 0;
				regArr[1] = 1;
				regArr[2] = 1;
				return;
			}
			if (button == 3)
			{
				regArr[0] = 1;
				regArr[1] = 0;
				regArr[2] = 1;
				return;
			}
		}
	}
	if (checkHowManyOn == 2 && button < 4)
	{
		regArr[0] = 0;
		regArr[1] = 0;
		regArr[2] = 0;
		regArr[button - 1] = 1;
		return;
	}

	if (checkHowManyOn == 1 && button == 4)
	{
		toggleRegisterArray(regArr, 1);
		return;
	}

	if (checkHowManyOn == 4 && button < 4 || checkHowManyOn == 3 && button < 4)
	{
		toggleRegisterArray(regArr, 0);
		regArr[button - 1] = 1;
		return;
	}

	if (checkHowManyOn == 4 && button == 4)
	{
		regArr[0] = 1;
		regArr[1] = 1;
		regArr[2] = 0;
		return;
	}

	if (checkHowManyOn == 3 && button == 4 && regArr[0] == 1)
	{
		regArr[0] = 0;
		regArr[1] = 1;
		regArr[2] = 1;
		return;
	}

	if (checkHowManyOn == 3 && button == 4 && regArr[2] == 1)
	{
		regArr[0] = 1;
		regArr[1] = 1;
		regArr[2] = 1;
		return;
	}

	if (checkHowManyOn == 2 && button == 4)
	{
		regArr[0] = 1;
		regArr[1] = 1;
		regArr[2] = 1;
		regArr[3] = 1;
		return;
	}
}


// Here you can define possible exceptions buttons/leds vs. relays. Default is 1:1
void setRegisterLed(boolean isTx)
{
	if (isTx)
	{
		byte checkOne = verifyButtons(registersTx, 4);
		Serial.println(checkOne);
		for (int i = 0; i<4; i++)
		{
			registersTxLed[i] = registersTx[i];
		}

		if (checkOne == 3)
			registersTxLed[3] = 0;
	}
	else
	{
		for (int i = 0; i<4; i++)
		{
			registersRxLed[i] = registersRx[i];
		}
	}
}


void setDisplay(boolean regArry[], byte row)
{
	clearLabels(row);
	lcd.setCursor(5, row);

	int sum = 0;
	sum = verifyButtons(regArry, 4);
	//Serial.print("summe ");
	//Serial.print(sum);

	if (sum == 1 || sum > 3)
	{
		for (byte i = 3; i >= 0; i--)
		{
			if (regArry[i] == 1)
			{
				lcd.print(txDisplayArray[i]);
				return;
			}
		}
	}
	else
	{
		if (regArry[0] == 1 && regArry[1] == 1)
		{
			lcd.print(txDisplayArray[4]);
			return;
		}
		if (regArry[0] == 1 && regArry[2] == 1)
		{
			lcd.print(txDisplayArray[5]);
			return;
		}
		if (regArry[1] == 1 && regArry[2] == 1)
		{
			lcd.print(txDisplayArray[6]);
			return;
		}
	}
}
#endif

