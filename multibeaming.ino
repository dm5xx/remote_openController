//// the welcome info. you are not allowed to change anything here! CC
//void displayWelcomeText()
//{
//  lcd.clear();
//  lcd.home();
//  lcd.backlight();
//  lcd.setCursor(0, 0);
//  lcd.print(" remoteQTH.com ");
//  lcd.setCursor(0, 1);
//  lcd.print(" openMultiCon");
//}
//
//// the default start screen template
//void displayMain()
//{
//  resetDisplay();
//  lcd.print("->RX  1  2  3  A");
//  lcd.setCursor(0, 1);
//  lcd.print("  TX  1  2  3  A");
//}
//
//// set value of the pressed button into the relay register. Here you can define the mappings for the relays
//void setRegisterArray(byte button, boolean regArr[])
//{
//  if (!inTxEditMode)                    // im rx mode
//  {
//    if (button < 4)                     // only button could be active, except button 4 
//    {
//      toggleRegisterArray(regArr, 0);
//
//      if (regArr[button - 1] == 1)
//        regArr[button - 1] = 0;
//      else
//        regArr[button - 1] = 1;
//    }
//    else                                // button 4: all combinations possible
//    {
//      if (regArr[button - 1] == 0)
//        toggleRegisterArray(regArr, 1);
//    }
//  }
//  else // im tx mode
//  {
//    if (button != 4 && regArr[button - 1] == 1 && verifyButtons(regArr, 4) > 1)
//    {
//      if(regArr[3] == 1 && verifyButtons(regArr, 3) == 3)
//        regArr[3] = 0;
//
//      regArr[button - 1] = 0;
//    }
//    else
//    {
//      if(button == 4 && regArr[3] == 0 && verifyButtons(regArr, 3) < 3)
//      {
//        regArr[0] = 1;
//        regArr[1] = 1;
//        regArr[2] = 1;
//      }
//      regArr[button - 1] = 1;
//
//      if(verifyButtons(regArr, 3) == 3)
//        regArr[3] = 1;
//    }    
//  }
//}
//
//
//// Here you can define possible exceptions buttons/leds vs. relays. Default is 1:1
//void setRegisterLed(boolean isTx)
//{
//	if (isTx)
//	{
//		for (int i = 0; i<4; i++)
//		{
//			registersTxLed[i] = registersTx[i];
//		}
//	}
//	else
//	{
//		for (int i = 0; i<4; i++)
//		{
//			registersRxLed[i] = registersRx[i];
//		}
//	}
//}
//
