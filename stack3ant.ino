// the welcome info. you are not allowed to change anything here! CC
void displayWelcomeText()
{
  lcd.clear();
  lcd.home();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print(" remoteQTH.com ");
  lcd.setCursor(0, 1);
  lcd.print(" openStack3Con  ");
}

// the default start screen template            
void displayMain()
{
  resetDisplay();
  lcd.print("->RX  T  M  B  S");
  lcd.setCursor(0, 1);
  lcd.print("  TX  T  M  B  S");
}


// set value of the pressed button into the relay register. Here you can define the mappings for the relays
void setRegisterArray(byte button, boolean regArr[])
{
   byte checkOne = verifyButtons(regArr, 4);

   if(checkOne == 1 && button < 4)
   {
      regArr[0] = 0;
      regArr[1] = 0;
      regArr[2] = 0;
      regArr[button - 1] = 1;
      return;
   }
   if(checkOne == 1 && button == 4)
   {
      toggleRegisterArray(regArr, 1);
      return;
   }
   
   if(checkOne == 4 && button < 4 || checkOne == 3 && button < 4)
   {
      toggleRegisterArray(regArr, 0);
      regArr[button - 1] = 1;
      return;
   }

   if(checkOne == 4 && button == 4)
   {
      regArr[0] = 1;
      regArr[1] = 1;
      regArr[2] = 0;
      return;     
   }

   if(checkOne == 3 && button == 4  && regArr[0] == 1)
   {
      regArr[0] = 0;
      regArr[1] = 1;
      regArr[2] = 1;
      return;     
   }   

   if(checkOne == 3 && button == 4 && regArr[2] == 1)
   {
      regArr[0] = 1;
      regArr[1] = 1;
      regArr[2] = 1;
      return;     
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


