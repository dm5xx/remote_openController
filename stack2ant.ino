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
//// set value of the pressed button into the relay register     
//void setRegisterArray(byte button, boolean regArr[])
//{
//   byte checkOne = verifyButtons(regArr, 4);
//
//   if (regArr[button - 1] == 0)
//   {
//     if(checkOne < 3 && button < 3)
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
//     if(checkOne < 3 && button == 3)
//     {
//       regArr[0] = 1;
//       regArr[1] = 1;
//       regArr[2] = 1;
//       return;
//     }
//
//     if(checkOne < 3 && button == 4)
//     {
//       regArr[0] = 1;
//       regArr[1] = 1;
//       regArr[3] = 1;
//       return;
//     }
//   
//     if(button == 3)
//     {
//       regArr[2] = 1;
//       regArr[3] = 0;
//       return;
//     }
//
//     if(button == 4)
//     {
//       regArr[0] = 1;
//       regArr[1] = 1;
//       regArr[2] = 0;
//       regArr[3] = 1;
//       return;
//     }     
//   }
//   else
//   {
//     if(button == 3)
//     {
//       regArr[3] = 0;
//       regArr[2] = 0;
//       regArr[1] = 0;
//       return;
//     }
//
//     if(button == 4)
//     {
//       regArr[3] = 0;
//       return;
//     }
//       
//     if(checkOne == 3)
//     {
//       if(button == 2)
//       {
//         regArr[3] = 0;
//         regArr[2] = 0;
//         regArr[1] = 0;
//         return;
//       }
//       if(button == 1)
//       {
//         regArr[3] = 0;
//         regArr[2] = 0;
//         regArr[0] = 0;
//         return;
//       }
//     }
//     
//     if(checkOne == 4)
//     {
//       if(button > 2)
//       {
//         regArr[3] = 0;
//         regArr[2] = 0;
//         regArr[1] = 0;       
//         return;
//       }  
//
//       if(button == 2)
//       {
//         regArr[3] = 0;
//         regArr[2] = 0;
//         regArr[1] = 0;       
//         return;
//       }  
//
//       if(button == 1)
//       {
//         regArr[3] = 0;
//         regArr[2] = 0;
//         regArr[0] = 0;       
//         return;
//       }  
//     }
//   }
//}

