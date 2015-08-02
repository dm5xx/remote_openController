//// the welcome info. you are not allowed to change anything here! CC
//void displayWelcomeText()
//{
//  lcd.clear();
//  lcd.home();
//  lcd.backlight();
//  lcd.setCursor(0, 0);
//  lcd.print(" remoteQTH.com ");
//  lcd.setCursor(0, 1);
//  lcd.print(" openStack2Con");
//}
//
//// the default start screen template          
//void displayMain()
//{
//  resetDisplay();
//  lcd.print("->RX  T  B  I  O");
//  lcd.setCursor(0, 1);
//  lcd.print("  TX  T  B  I  O");
//}
//
//// set value of the pressed button into the relay register. Here you can define the mappings for the relays
//void setRegisterArray(byte button, boolean regArr[])
//{
//   byte checkOne = verifyButtons(regArr, 4);
//   if (regArr[button - 1] == 0)
//   {
//	if (checkOne < 3) // only but 1 or 2 is pressed
//	{
//     if(button < 3) // so 1 or 2 is pressed
//     {
//       if(button==1 && regArr[1] ==1)
//         regArr[1] = 0;
//       
//       if(button==2 && regArr[0] ==1)
//         regArr[0] = 0;
//         
//       regArr[button - 1] = 1;
//       return;
//     }
//     
//     if(button == 3) // so 3 is pressed
//     {
//       regArr[0] = 1;
//       regArr[1] = 1;
//       regArr[2] = 1;
//       return;
//     }
//
//     if(button == 4) // so 4 is pressed
//     {
//       regArr[0] = 1;
//       regArr[1] = 1;
//	   regArr[2] = 1;
//	   regArr[3] = 1;
//       return;
//     }
//	}
//	if (checkOne == 3) // 3 buttons are already pressed checkOne cannot be 4!
//	{
//		if (button == 3) // 4 must be already be pressed
//		{
//			regArr[2] = 1; // turn on 3
//			regArr[3] = 0; // turn off 4
//			return;
//		}
//
//		if (button == 4)
//		{
//			regArr[3] = 1; // turn on 4,because 1,2,3 already on
//			return;
//		}
//	}
//   }
//   else
//   {
//	   if (checkOne < 3) // so 1 or 2 is pressed
//	   {
//		   if (button < 3) // so 1 or 2 is pressed
//		   {
//			   if (button == 1 && regArr[1] == 0)
//				   regArr[1] = 1;
//
//			   if (button == 2 && regArr[0] == 0)
//				   regArr[0] = 1;
//
//			   regArr[button - 1] = 0;
//			   return;
//		   }
//	   }
//	   if (checkOne == 3) // its BIP time
//	   {
//		   if (button == 1)
//		   {
//			   regArr[3] = 0;
//			   regArr[2] = 0;
//			   regArr[1] = 1;
//			   regArr[0] = 0;
//			   return;
//		   }
//
//		   if (button == 2)
//		   {
//			   regArr[3] = 0;
//			   regArr[2] = 0;
//			   regArr[1] = 0;
//			   regArr[0] = 1;
//			   return;
//		   }
//
//		   if (button == 3)
//		   {
//			   regArr[3] = 0;
//			   regArr[2] = 0;
//			   regArr[1] = 0;
//			   regArr[0] = 1;
//			   return;
//		   }
//
//		   if (button == 4)
//		   {
//			   regArr[3] = 1;
//			   regArr[2] = 1;
//			   regArr[1] = 1;
//			   regArr[0] = 1;
//			   return;
//		   }
//	   }
//
//	   if (checkOne == 4) // its BOP time
//	   {
//		   if (button == 1)
//		   {
//			   regArr[3] = 0;
//			   regArr[2] = 0;
//			   regArr[1] = 1;
//			   regArr[0] = 0;
//			   return;
//		   }
//
//		   if (button == 2)
//		   {
//			   regArr[3] = 0;
//			   regArr[2] = 0;
//			   regArr[1] = 0;
//			   regArr[0] = 1;
//			   return;
//		   }
//
//		   if (button == 3)
//		   {
//			   regArr[3] = 0;
//			   regArr[2] = 1;
//			   regArr[1] = 1;
//			   regArr[0] = 1;
//			   return;
//		   }
//
//		   if (button == 4)
//		   {
//			   regArr[3] = 0;
//			   regArr[2] = 0;
//			   regArr[1] = 0;
//			   regArr[0] = 1;
//			   return;
//		   }
//	   }
//   }
//}
//
//// Here you can define possible exceptions buttons/leds vs. relays. Default is 1:1, but needs to be changed in stack 2
//void setRegisterLed(boolean isTx)
//{
//	if (isTx)
//	{
//		for (int i = 0; i<4; i++)
//		{
//			registersTxLed[i] = registersTx[i];
//
//			if (i==3 && registersTx[3]==1)
//				registersTxLed[2] = 0;
//		}
//	}
//	else
//	{
//		for (int i = 0; i<4; i++)
//		{
//			registersRxLed[i] = registersRx[i];
//
//			if (i == 3 && registersRx[3] == 1)
//				registersRxLed[2] = 0;
//		}
//	}
//}
//
//
//
//
