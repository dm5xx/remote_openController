#if SKETCHMODE == 3 // multibeaming

void specialSetup()
{
	registersRx[3] = 1;
	registersTx[3] = 1;
}


// the welcome info. you are not allowed to change anything here! CC
void displayWelcomeText()
{
	lcd.clear();
	lcd.home();
	lcd.backlight();
	lcd.setCursor(0, 0);
	lcd.print(" remoteQTH.com ");
	lcd.setCursor(0, 1);
	lcd.print(" SJ2W MultiB");
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
	byte checkOne = verifyButtons(regArr, 4);

	if(!inTxEditMode)                    // im rx mode
	{
		if ((checkOne == 2 || checkOne == 0) && button < 4)
		{
			regArr[0] = 0;
			regArr[1] = 0;
			regArr[2] = 0;
			regArr[3] = 1;
			regArr[button - 1] = 1;
			return;
		}

		if (checkOne == 2 && button == 4)
		{
			toggleRegisterArray(regArr, 0);
			return;
		}
	}
	else
	{
		if (button == 4)
		{
			toggleRegisterArray(regArr, 0);
			return;
		}

		if (checkOne == 0) // select all was called before, so if you click but1...3, switch them + k4 on
		{
			regArr[button - 1] = 1;
			regArr[3] = 1;
			return;
		}

		if (checkOne == 1)
		{
			if (regArr[button - 1] == 1)
			{
				toggleRegisterArray(regArr, 0);
				return;
			}

			regArr[3] = 1;

			if (regArr[2] == 1)
			{
				regArr[2] = 0;
				if (button == 1)
					regArr[1] = 1;
				if (button == 2)
					regArr[0] = 1;
				return;
			}

			if (regArr[0] == 1)
			{
				regArr[0] = 0;
				if (button == 2)
					regArr[2] = 1;
				if (button == 3)
					regArr[1] = 1;
				return;
			}

			if (regArr[1] == 1)
			{
				regArr[1] = 0;
				if (button == 1)
					regArr[2] = 1;
				if (button == 3)
					regArr[0] = 1;
				return;
			}

		}

		if (checkOne == 2 && regArr[3] == 0) // if 2 are on, but not k4 => 2 directions selected
		{
			if (regArr[button - 1] == 0)
			{
				toggleRegisterArray(regArr, 0);
			}
			else
			{
				regArr[button - 1] = 0;
				regArr[3] = 1;
			}
			return;
		}

		if (checkOne == 2 && regArr[3] == 1) // only one direction is selected, so k4 has to be on
		{
			if (regArr[button - 1] == 0)
			{
				regArr[3] = 0;
				if ((regArr[0] == 1 && button == 2) || (regArr[1] == 1 && button == 1))
				{
					regArr[0] = 0;
					regArr[1] = 0;
					regArr[2] = 1;
					return;
				}

				if (regArr[0] == 1 && button == 3 || regArr[2] == 1 && button == 1)
				{
					regArr[0] = 0;
					regArr[1] = 1;
					regArr[2] = 0;
					return;
				}

				if ((regArr[1] == 1 && button == 3) || (regArr[2] == 1 && button ==2))
				{
					regArr[0] = 1;
					regArr[1] = 0;
					regArr[2] = 0;
					return;
				}
			}
			return;
		}
	}

}

// Here you can define possible exceptions buttons/leds vs. relays. Default is 1:1
void setRegisterLed(boolean isTx)
{
	if (isTx)
	{
		byte checkOne = verifyButtons(registersTx, 4);

		for (int i = 0; i<4; i++)
		{
			if (checkOne == 0)
				registersTxLed[i] = 1;
			else if (checkOne == 2)
			{
				registersTxLed[i] = registersTx[i];

				if (i == 3)
					registersTxLed[3] = 0;
			}
			else
			{
				byte v = registersTx[i];
				if (v == 0)
				{
					if (checkOne == 1 && i == 3)
						registersTxLed[3] = 0;
					else
						registersTxLed[i] = 1;
				}
				else
					registersTxLed[i] = 0;
			}
		}
	}
	else
	{
		byte checkOne = verifyButtons(registersRx, 4);

		for (int i = 0; i<4; i++)
		{
			if (checkOne == 0)
				registersRxLed[i] = 1;
			else if (checkOne == 2)
			{
				registersRxLed[i] = registersRx[i];

				if (i == 3)
					registersRxLed[3] = 0;
			}
			else
			{
				byte v = registersRx[i];
				if (v == 0)
					registersRxLed[i] = 1;
				else
					registersRxLed[i] = 0;
			}
		}
	}
}


void setDisplay(boolean regArry[], byte row)
{
	clearLabels(row);
	lcd.setCursor(5, row);
	int sum = 0;
	sum = verifyButtons(regArry, 4);
	Serial.println(sum);
	if (row == 0)
	{
		if (sum == 1)
		{
			for (byte i = 2; i >= 0; i--)
			{
				if (regArry[i] == 1)
				{
					lcd.print(rxDisplayArray[i]);
					return;
				}
			}
		}

		if (sum == 4)
		{
			lcd.print(rxDisplayArray[3]);
			return;
		}
	}
	else
	{
		if (sum == 1)
		{
			for (byte i = 2; i >= 0; i--)
			{
				if (regArry[i] == 1)
				{
					lcd.print(txDisplayArray[i]);
					return;
				}
			}
		}

		if (sum == 4)
		{
			lcd.print(txDisplayArray[3]);
			return;
		}
		else
		{
			if (regArry[0] == 1 && regArry[1] == 1)
			{
				lcd.print(txDisplayArray[4]);
				return;
			}
			else if (regArry[1] == 1 && regArry[2] == 1)
			{
				lcd.print(txDisplayArray[5]);
				return;
			}
			else
			{
				lcd.print(txDisplayArray[6]);
				return;
			}
		}
	}
}
#endif

#if SKETCHMODE == 4

void specialSetup()
{
	registersRx[3] = 1;
	registersTx[3] = 1;
}

// the welcome info. you are not allowed to change anything here! CC
void displayWelcomeText()
{
	lcd.clear();
	lcd.home();
	lcd.backlight();
	lcd.setCursor(0, 0);
	lcd.print(" remoteQTH.com ");
	lcd.setCursor(0, 1);
	lcd.print(" SJ2W Stack");
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
	byte checkOne = verifyButtons(regArr, 4);

	if (checkOne == 2 && button < 4)
	{
		regArr[0] = 0;
		regArr[1] = 0;
		regArr[2] = 0;
		regArr[3] = 1;
		regArr[button - 1] = 1;
		return;
	}
	if (checkOne == 2 && button == 4)
	{
		toggleRegisterArray(regArr, 0);
		return;
	}

	if (checkOne == 0 && button == 4)
	{
		regArr[0] = 0;
		regArr[1] = 0;
		regArr[2] = 1;
		regArr[3] = 0;
		return;
	}

	if (checkOne == 1 && button == 4 && regArr[2] == 1)
	{
		regArr[0] = 1;
		regArr[1] = 0;
		regArr[2] = 0;
		regArr[3] = 0;
		return;
	}

	if (checkOne == 1 && button == 4 && regArr[0] == 1)
	{
		regArr[0] = 0;
		regArr[1] = 1;
		regArr[2] = 0;
		regArr[3] = 0;
		return;
	}

	if (checkOne == 1 && button == 4 && regArr[1] == 1)
	{
		regArr[0] = 0;
		regArr[1] = 0;
		regArr[2] = 0;
		regArr[3] = 0;
		return;
	}

	if (checkOne < 2 && button < 4)
	{
		toggleRegisterArray(regArr, 0);
		regArr[3] = 1;
		regArr[button - 1] = 1;
		return;
	}
}



// Here you can define possible exceptions buttons/leds vs. relays. Default is 1:1
void setRegisterLed(boolean isTx)
{
	if (isTx)
	{
		byte checkOne = verifyButtons(registersTx, 4);

		for (int i = 0; i<4; i++)
		{
			if (checkOne == 0)
				registersTxLed[i] = 1;
			else if (checkOne == 2)
			{
				registersTxLed[i] = registersTx[i];

				if (i == 3)
					registersTxLed[3] = 0;
			}
			else
			{
				byte v = registersTx[i];
				if (v == 0)
					registersTxLed[i] = 1;
				else
					registersTxLed[i] = 0;
			}
		}
	}
	else
	{
		byte checkOne = verifyButtons(registersRx, 4);

		for (int i = 0; i<4; i++)
		{
			if (checkOne == 0)
				registersRxLed[i] = 1;
			else if (checkOne == 2)
			{
				registersRxLed[i] = registersRx[i];

				if(i==3)
					registersRxLed[3] = 0;
			}
			else
			{
				byte v = registersRx[i];
				if (v == 0)
					registersRxLed[i] = 1;
				else
					registersRxLed[i] = 0;
			}
		}
	}
}

void setDisplay(boolean regArry[], byte row)
{
	clearLabels(row);
	lcd.setCursor(5, row);
	int sum = 0;
	sum = verifyButtons(regArry, 4);
	Serial.println(sum);
	if (row == 0)
	{
		if (sum == 1)
		{
			for (byte i = 2; i >= 0; i--)
			{
				if (regArry[i] == 1)
				{
					lcd.print(rxDisplayArray[i]);
					return;
				}
			}
		}

		if (sum == 4)
		{
			lcd.print(rxDisplayArray[3]);
			return;
		}
		else
		{
			if (regArry[0] == 1 && regArry[1] == 1)
			{
				lcd.print(rxDisplayArray[4]);
				return;
			}
			else if (regArry[1] == 1 && regArry[2] == 1)
			{
					lcd.print(rxDisplayArray[5]);
					return;
			}
			else
			{
				lcd.print(rxDisplayArray[6]);
				return;
			}
		}
	}
	else
	{
		if (sum == 1)
		{
			for (byte i = 2; i >= 0; i--)
			{
				if (regArry[i] == 1)
				{
					lcd.print(txDisplayArray[i]);
					return;
				}
			}
		}

		if (sum == 4)
		{
			lcd.print(txDisplayArray[3]);
			return;
		}
		else
		{
			if (regArry[0] == 1 && regArry[1] == 1)
			{
				lcd.print(txDisplayArray[4]);
				return;
			}
			else if (regArry[1] == 1 && regArry[2] == 1)
			{
				lcd.print(txDisplayArray[5]);
				return;
			}
			else
			{
				lcd.print(txDisplayArray[6]);
				return;
			}
		}
	}
}
#endif