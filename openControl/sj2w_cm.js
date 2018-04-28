function setRegisterArray(button, regArr) {
    var checkOne = verifyButtons(regArr, 4);
    console.log(checkOne);

    if (!isTxEditMode)                    // im rx mode
    {
        if ((checkOne == 2 || checkOne == 0) && button < 4) {
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
    }
    else {
        if (button == 4) {
            toggleRegisterArray(regArr, 0);
            return regArr;
        }

        if (checkOne == 0) // select all was called before, so if you click but1...3, switch them + k4 on
        {
            regArr[button - 1] = 1;
            regArr[3] = 1;
            return regArr;
        }

        if (checkOne == 1) {
            if (regArr[button - 1] == 1) {
                toggleRegisterArray(regArr, 0);
                return regArr;
            }

            regArr[3] = 1;

            if (regArr[2] == 1) {
                regArr[2] = 0;
                if (button == 1)
                    regArr[1] = 1;
                if (button == 2)
                    regArr[0] = 1;
                return regArr;
            }

            if (regArr[0] == 1) {
                regArr[0] = 0;
                if (button == 2)
                    regArr[2] = 1;
                if (button == 3)
                    regArr[1] = 1;
                return regArr;
            }

            if (regArr[1] == 1) {
                regArr[1] = 0;
                if (button == 1)
                    regArr[2] = 1;
                if (button == 3)
                    regArr[0] = 1;
                return regArr;
            }

        }

        if (checkOne == 2 && regArr[3] == 0) // if 2 are on, but not k4 => 2 directions selected
        {
            if (regArr[button - 1] == 0) {
                toggleRegisterArray(regArr, 0);
            }
            else {
                regArr[button - 1] = 0;
                regArr[3] = 1;
            }
            return regArr;
        }

        if (checkOne == 2 && regArr[3] == 1) // only one direction is selected, so k4 has to be on
        {
            if (regArr[button - 1] == 0) {
                regArr[3] = 0;
                if ((regArr[0] == 1 && button == 2) || (regArr[1] == 1 && button == 1)) {
                    regArr[0] = 0;
                    regArr[1] = 0;
                    regArr[2] = 1;
                    return regArr;
                }

                if (regArr[0] == 1 && button == 3 || regArr[2] == 1 && button == 1) {
                    regArr[0] = 0;
                    regArr[1] = 1;
                    regArr[2] = 0;
                    return regArr;
                }

                if ((regArr[1] == 1 && button == 3) || (regArr[2] == 1 && button == 2)) {
                    regArr[0] = 1;
                    regArr[1] = 0;
                    regArr[2] = 0;
                    return regArr;
                }
            }
            return regArr;
        }
    }
    return regArr;
}

var arrl = ['1', '2', '3', 'All'];

function createLcdString(arrei, isTx) {
    var checkOne = verifyButtons(arrei, 4);

    var tempString = "";

    if (!isTx) {
        if (!isTxEditMode)
            tempString += "-> ";
        else
            tempString += "&nbsp;&nbsp;&nbsp;";
        tempString += "RX&nbsp;";
    }
    else {
        if (isTxEditMode)
            tempString += "-> ";
        else
            tempString += "&nbsp;&nbsp;&nbsp;";
        tempString += "TX&nbsp;";
    }

    for (var a = 0; a < 4; a++) {
        if (checkOne == 2) {
            if (arrei[a] == 1 && a != 3)
                tempString += "*";
            else
                tempString += "&nbsp;";
        }
        else if (checkOne == 0)
            tempString += "*";
        else {
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

        if (checkOne == 2) {
            if (i == 3)
                setButton(i, 0);
            else
                setButton(i, arr[i]);
        }
        else if (checkOne == 0)
            setButton(i, 1);
        else {
            var val1 = arr[i];

            if (val1 == 1)
                setButton(i, 0);
            else
                setButton(i, 1);
        }
    }
}
