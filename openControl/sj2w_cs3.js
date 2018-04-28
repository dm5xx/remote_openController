function setRegisterArray(button, regArr)
{
  var checkOne = verifyButtons(regArr, 4);
  console.log(checkOne);

  if (checkOne == 2 && button < 4) {
      regArr[0] = 0;
      regArr[1] = 0;
      regArr[2] = 0;
      regArr[3] = 1;
      regArr[button - 1] = 1;
      return regArr;
  }
  if (checkOne == 2 && button == 4) {
      toggleRegisterArray(regArr, 0);
      return regArr;
  }

  if (checkOne == 0 && button == 4) {
      regArr[0] = 0;
      regArr[1] = 0;
      regArr[2] = 1;
      regArr[3] = 0;
      return regArr;
  }

  if (checkOne == 1 && button == 4 && regArr[2] == 1) {
      regArr[0] = 1;
      regArr[1] = 0;
      regArr[2] = 0;
      regArr[3] = 0;
      return regArr;
  }

  if (checkOne == 1 && button == 4 && regArr[0] == 1) {
      regArr[0] = 0;
      regArr[1] = 1;
      regArr[2] = 0;
      regArr[3] = 0;
      return regArr;
  }

  if (checkOne == 1 && button == 4 && regArr[1] == 1) {
      regArr[0] = 0;
      regArr[1] = 0;
      regArr[2] = 0;
      regArr[3] = 0;
      return regArr;
  }

  if (checkOne < 2 && button < 4) {
      toggleRegisterArray(regArr, 0);
      regArr[3] = 1;
      regArr[button - 1] = 1;
      return regArr;
  }
}

var arrl = ['T', 'M', 'B', 'S'];

function createLcdString(arrei, isTx)
{
   var checkOne = verifyButtons(arrei, 4);

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

   for (var a = 0; a < 4; a++)
   {
       if (checkOne == 2)
       {
           if (arrei[a] == 1 && a != 3)
               tempString += "*";
           else
               tempString += "&nbsp;";
       }
       else if (checkOne == 0)
           tempString += "*";
       else
       {
           var val1 = arrei[a];

           if (val1 == 1)
               tempString += "&nbsp;";
           else
               tempString += "*";
       }
       tempString += arrl[a] + "&nbsp;";
   }

   if (!isTx)
      $('#myRxString').html(tempString);
   else
      $('#myTxString').html(tempString);
}

function setButtons(arr) {

    var checkOne = verifyButtons(arr, 4);

    for (var i = 0; i < 4; i++) {

        if (checkOne == 2)
        {
            if (i == 3)
                setButton(i, 0);
            else
                setButton(i, arr[i]);
        }
        else if (checkOne==0)
            setButton(i, 1);
        else
        {
            var val1 = arr[i];

            if(val1 == 1)
                setButton(i, 0);
            else
                setButton(i, 1);
        }
    }
}
