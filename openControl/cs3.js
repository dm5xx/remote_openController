function setRegisterArray(button, regArr)
{
  var checkHowManyOn = verifyButtons(regArr, 4);
  console.log(checkHowManyOn);

  var isSameKeyPressed = false;

  if(regArr[button-1] == 1)
      isSameKeyPressed = true;

  if (checkHowManyOn == 1 && button < 4)
  {
      if (isSameKeyPressed == false)
      {
          regArr[0] = 0;
          regArr[1] = 0;
          regArr[2] = 0;
          regArr[button - 1] = 1;
          return regArr;
      }
      else
      {
          if (button == 1)
          {
              regArr[0] = 1;
              regArr[1] = 1;
              regArr[2] = 0;
              return regArr;
          }
          if (button == 2)
          {
              regArr[0] = 0;
              regArr[1] = 1;
              regArr[2] = 1;
              return regArr;
          }
          if (button == 3)
          {
              regArr[0] = 1;
              regArr[1] = 0;
              regArr[2] = 1;
              return regArr;
          }
      }
  }
  if (checkHowManyOn == 2 && button < 4)
  {
      regArr[0] = 0;
      regArr[1] = 0;
      regArr[2] = 0;
      regArr[button - 1] = 1;
      return regArr;
  }

   if(checkHowManyOn == 1 && button == 4)
   {
      toggleRegisterArray(regArr, 1);
      return regArr;
   }
   
   if(checkHowManyOn == 4 && button < 4 || checkHowManyOn == 3 && button < 4)
   {
      toggleRegisterArray(regArr, 0); 
      regArr[button - 1] = 1;
      return regArr;
   }

   if(checkHowManyOn == 4 && button == 4)
   {
      regArr[0] = 1;
      regArr[1] = 1;
      regArr[2] = 0;
      return regArr;     
   }

   if(checkHowManyOn == 3 && button == 4  && regArr[0] == 1)
   {
      regArr[0] = 0;
      regArr[1] = 1;
      regArr[2] = 1;
      return regArr;     
   }   

   if(checkHowManyOn == 3 && button == 4 && regArr[2] == 1)
   {
      regArr[0] = 1;
      regArr[1] = 1;
      regArr[2] = 1;
      return regArr;     
   }

   if (checkHowManyOn == 2 && button == 4)
   {
       regArr[0] = 1;
       regArr[1] = 1;
       regArr[2] = 1;
       regArr[3] = 1;
       return regArr;
   }
}

function createLcdString(arrei, isTx)
{
   var tempString = "";

   if(!isTx)
   {
      if(!isTxEditMode)
         tempString += "-> ";
      else
         tempString += "&nbsp;&nbsp;&nbsp;";
      tempString += "RX&nbsp;";     
   }
   else
   {
      if(isTxEditMode)
         tempString += "-> "; 
      else
         tempString += "&nbsp;&nbsp;&nbsp;";
      tempString += "TX&nbsp;";
   }

   if (arrei[0]==1)
      tempString += "*";
   else
      tempString += "&nbsp;";
   tempString += "T&nbsp;";

   if (arrei[1]==1)
      tempString += "*";
   else
      tempString += "&nbsp;";
   tempString += "M&nbsp;";

   if (arrei[2]==1)
      tempString += "*";
   else
      tempString += "&nbsp;";
   tempString += "B&nbsp;";

   if (arrei[3]==1)
      tempString += "*";
   else
      tempString += "&nbsp;";
   tempString += "S&nbsp;";

   if(!isTx)
      $('#myRxString').html(tempString);
   else
      $('#myTxString').html(tempString);
}