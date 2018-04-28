function setRegisterArray(button, regArr)
{
    var checkOne = verifyButtons(regArr, 4);
    if (regArr[button - 1] == 0) {
        if (checkOne < 3) // only but 1 or 2 is pressed
        {
            if (button < 3) // so 1 or 2 is pressed
            {
                if (button == 1 && regArr[1] == 1)
                    regArr[1] = 0;

                if (button == 2 && regArr[0] == 1)
                    regArr[0] = 0;

                regArr[button - 1] = 1;
                return regArr;
            }

            if (button == 3) // so 3 is pressed
            {
                regArr[0] = 1;
                regArr[1] = 1;
                regArr[2] = 1;
                return regArr;
            }

            if (button == 4) // so 4 is pressed
            {
                regArr[0] = 1;
                regArr[1] = 1;
                regArr[2] = 1;
                regArr[3] = 1;
                return regArr;
            }
        }
        if (checkOne == 3) // 3 buttons are already pressed checkOne cannot be 4!
        {
            if (button == 3) // 4 must be already be pressed
            {
                regArr[2] = 1; // turn on 3
                regArr[3] = 0; // turn off 4
                return regArr;
            }

            if (button == 4) {
                regArr[3] = 1; // turn on 4,because 1,2,3 already on
                return regArr;
            }
        }
    }
    else {
        if (checkOne < 3) // so 1 or 2 is pressed
        {
            if (button < 3) // so 1 or 2 is pressed
            {
                if (button == 1 && regArr[1] == 0)
                    regArr[1] = 1;

                if (button == 2 && regArr[0] == 0)
                    regArr[0] = 1;

                regArr[button - 1] = 0;
                return regArr;
            }
        }
        if (checkOne == 3) // its BIP time
        {
            if (button == 1) {
                regArr[3] = 0;
                regArr[2] = 0;
                regArr[1] = 1;
                regArr[0] = 0;
                return regArr;
            }

            if (button == 2) {
                regArr[3] = 0;
                regArr[2] = 0;
                regArr[1] = 0;
                regArr[0] = 1;
                return regArr;
            }

            if (button == 3) {
                regArr[3] = 0;
                regArr[2] = 0;
                regArr[1] = 0;
                regArr[0] = 1;
                return regArr;
            }

            if (button == 4) {
                regArr[3] = 1;
                regArr[2] = 1;
                regArr[1] = 1;
                regArr[0] = 1;
                return regArr;
            }
        }

        if (checkOne == 4) // its BOP time
        {
            if (button == 1) {
                regArr[3] = 0;
                regArr[2] = 0;
                regArr[1] = 1;
                regArr[0] = 0;
                return regArr;
            }

            if (button == 2) {
                regArr[3] = 0;
                regArr[2] = 0;
                regArr[1] = 0;
                regArr[0] = 1;
                return regArr;
            }

            if (button == 3) {
                regArr[3] = 0;
                regArr[2] = 1;
                regArr[1] = 1;
                regArr[0] = 1;
                return regArr;
            }

            if (button == 4) {
                regArr[3] = 0;
                regArr[2] = 0;
                regArr[1] = 0;
                regArr[0] = 1;
                return regArr;
            }
        }
    }
}

function createLcdString(arrei, isTx)
{
    var tempString = "";
    var checkOne = verifyButtons(arrei, 4);


    if (!isTx)
    {
        if (!isTxEditMode)
            tempString += "-> ";
        else
            tempString += "&nbsp;&nbsp;&nbsp;";
        tempString += "RX&nbsp;";
    }
    else
    {
        if (isTxEditMode)
            tempString += "-> ";
        else
            tempString += "&nbsp;&nbsp;&nbsp;";
        tempString += "TX&nbsp;";
    }

    if (arrei[0] == 1)
        tempString += "*";
    else
        tempString += "&nbsp;";
    tempString += "T&nbsp;";

    if (arrei[1] == 1)
        tempString += "*";
    else
        tempString += "&nbsp;";
    tempString += "B&nbsp;";

    if (arrei[2] == 1 && arrei[3] != 1)
        tempString += "*";
    else
        tempString += "&nbsp;";
    tempString += "I&nbsp;";

    if (arrei[3] == 1)
        tempString += "*";
    else
        tempString += "&nbsp;";
    tempString += "O&nbsp;";

    if (!isTx)
        $('#myRxString').html(tempString);
    else
        $('#myTxString').html(tempString);
}

function setButtons(arr) { // override setbuttons

    var checkOne = verifyButtons(arr, 4);

    for (var i = 0; i < 4; i++) {

        if (i == 2 && checkOne == 4)
            setButton(2, 0);
        else
            setButton(i, arr[i]);
    }
}
