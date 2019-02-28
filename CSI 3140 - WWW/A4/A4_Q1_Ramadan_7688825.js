/* Question 1 */

window.addEventListener("load", loadGame, false);

function loadGame()
{
    var cell1 = document.getElementById("cell1");
    var cell2 = document.getElementById("cell2");
    var cell3 = document.getElementById("cell3");
    var cell4 = document.getElementById("cell4");
    var cell5 = document.getElementById("cell5");
    var cell6 = document.getElementById("cell6");
    var cell7 = document.getElementById("cell7");
    var cell8 = document.getElementById("cell8");
    var cell9 = document.getElementById("cell9");
    var cell10 = document.getElementById("cell10");
    var cell11 = document.getElementById("cell11");
    var cell12 = document.getElementById("cell12");
    var cell13 = document.getElementById("cell13");
    var cell14 = document.getElementById("cell14");
    var cell15 = document.getElementById("cell15");
    var cell16 = document.getElementById("cell16");
    // add click event listeners on all 16 table cells
    cell1.addEventListener("click", processCell, false);
    cell2.addEventListener("click", processCell, false);
    cell3.addEventListener("click", processCell, false);
    cell4.addEventListener("click", processCell, false);
    cell5.addEventListener("click", processCell, false);
    cell6.addEventListener("click", processCell, false);
    cell7.addEventListener("click", processCell, false);
    cell8.addEventListener("click", processCell, false);
    cell9.addEventListener("click", processCell, false);
    cell10.addEventListener("click", processCell, false);
    cell11.addEventListener("click", processCell, false);
    cell12.addEventListener("click", processCell, false);
    cell13.addEventListener("click", processCell, false);
    cell14.addEventListener("click", processCell, false);
    cell15.addEventListener("click", processCell, false);
    cell16.addEventListener("click", processCell, false);

    // generate random positioning of numbers in cells
    var listOfNumbers = new Array(16);
    for (var i = 0; i < listOfNumbers.length; i++)
    {
        listOfNumbers[i] = i; // define array containing valid numbers, note value
        // 0 represents an empty cell the others represent their numeric value in the cell
    }
    shuffleArray(listOfNumbers); // shuffle the list (generate random values for positions)

    for (var a = 0; a < 16; a++) // starts all 16 cells by adding the random value
    {
        startCell(a + 1,listOfNumbers[a]);
    }
}

function processCell(e) // processes the click of the cell
{
    var validClick = false; // true only if empty cell is adjacent to clicked cell
    var emptyCellId = null; // may or may not be found later on
    var clickedCellId = e.target.getAttribute("id");

    // the following checks the tiles surrounding each cell for an empty value, varies depending on the cell
    if (e.target.getAttribute("id") == "cell1") // verify surroundings of cell 1
    {
        if (document.getElementById("cell5").innerHTML == "")
        {
            validClick = true;
            emptyCellId = "cell5";
        }
        else if (document.getElementById("cell2").innerHTML == "")
        {
            validClick = true;
            emptyCellId = "cell2";
        }
    }
    else if (e.target.getAttribute("id") == "cell2") // verify surroundings of cell 2
    {
        if (document.getElementById("cell1").innerHTML == "")
        {
            validClick = true;
            emptyCellId = "cell1";
        }
        else if (document.getElementById("cell3").innerHTML == "")
        {
            validClick = true;
            emptyCellId = "cell3";
        }
        else if (document.getElementById("cell6").innerHTML == "")
        {
            validClick = true;
            emptyCellId = "cell6";
        }
    }
    else if (e.target.getAttribute("id") == "cell3") // verify surroundings of cell 3
    {
        if (document.getElementById("cell2").innerHTML == "")
        {
            validClick = true;
            emptyCellId = "cell2";
        }
        else if (document.getElementById("cell4").innerHTML == "")
        {
            validClick = true;
            emptyCellId = "cell4";
        }
        else if (document.getElementById("cell7").innerHTML == "")
        {
            validClick = true;
            emptyCellId = "cell7";
        }
    }
    else if (e.target.getAttribute("id") == "cell4") // verify surroundings of cell 4
    {
        if (document.getElementById("cell3").innerHTML == "")
        {
            validClick = true;
            emptyCellId = "cell3";
        }
        else if (document.getElementById("cell8").innerHTML == "")
        {
            validClick = true;
            emptyCellId = "cell8";
        }
    }
    else if (e.target.getAttribute("id") == "cell5") // verify surroundings of cell 5
    {
        if (document.getElementById("cell1").innerHTML == "")
        {
            validClick = true;
            emptyCellId = "cell1";
        }
        else if (document.getElementById("cell6").innerHTML == "")
        {
            validClick = true;
            emptyCellId = "cell6";
        }
        else if (document.getElementById("cell9").innerHTML == "")
        {
            validClick = true;
            emptyCellId = "cell9";
        }
    }
    else if (e.target.getAttribute("id") == "cell6") // verify surroundings of cell 6
    {
        if (document.getElementById("cell2").innerHTML == "")
        {
            validClick = true;
            emptyCellId = "cell2";
        }
        else if (document.getElementById("cell5").innerHTML == "")
        {
            validClick = true;
            emptyCellId = "cell5";
        }
        else if (document.getElementById("cell10").innerHTML == "")
        {
            validClick = true;
            emptyCellId = "cell10";
        }
        else if (document.getElementById("cell7").innerHTML == "")
        {
            validClick = true;
            emptyCellId = "cell7";
        }
    }
    else if (e.target.getAttribute("id") == "cell7") // verify surroundings of cell 7
    {
        if (document.getElementById("cell3").innerHTML == "")
        {
            validClick = true;
            emptyCellId = "cell3";
        }
        else if (document.getElementById("cell6").innerHTML == "")
        {
            validClick = true;
            emptyCellId = "cell6";
        }
        else if (document.getElementById("cell8").innerHTML == "")
        {
            validClick = true;
            emptyCellId = "cell8";
        }
        else if (document.getElementById("cell11").innerHTML == "")
        {
            validClick = true;
            emptyCellId = "cell11";
        }
    }
    else if (e.target.getAttribute("id") == "cell8") // verify surroundings of cell 8
    {
        if (document.getElementById("cell4").innerHTML == "")
        {
            validClick = true;
            emptyCellId = "cell4";
        }
        else if (document.getElementById("cell7").innerHTML == "")
        {
            validClick = true;
            emptyCellId = "cell7";
        }
        else if (document.getElementById("cell12").innerHTML == "")
        {
            validClick = true;
            emptyCellId = "cell12";
        }
    }
    else if (e.target.getAttribute("id") == "cell9") // verify surroundings of cell 9
    {
        if (document.getElementById("cell5").innerHTML == "")
        {
            validClick = true;
            emptyCellId = "cell5";
        }
        else if (document.getElementById("cell10").innerHTML == "")
        {
            validClick = true;
            emptyCellId = "cell10";
        }
        else if (document.getElementById("cell13").innerHTML == "")
        {
            validClick = true;
            emptyCellId = "cell13";
        }
    }
    else if (e.target.getAttribute("id") == "cell10") // verify surroundings of cell 10
    {
        if (document.getElementById("cell6").innerHTML == "")
        {
            validClick = true;
            emptyCellId = "cell6";
        }
        else if (document.getElementById("cell9").innerHTML == "")
        {
            validClick = true;
            emptyCellId = "cell9";
        }
        else if (document.getElementById("cell11").innerHTML == "")
        {
            validClick = true;
            emptyCellId = "cell11";
        }
        else if (document.getElementById("cell14").innerHTML == "")
        {
            validClick = true;
            emptyCellId = "cell14";
        }
    }
    else if (e.target.getAttribute("id") == "cell11") // verify surroundings of cell 11
    {
        if (document.getElementById("cell7").innerHTML == "")
        {
            validClick = true;
            emptyCellId = "cell7";
        }
        else if (document.getElementById("cell10").innerHTML == "")
        {
            validClick = true;
            emptyCellId = "cell10";
        }
        else if (document.getElementById("cell12").innerHTML == "")
        {
            validClick = true;
            emptyCellId = "cell12";
        }
        else if (document.getElementById("cell15").innerHTML == "")
        {
            validClick = true;
            emptyCellId = "cell15";
        }
    }
    else if (e.target.getAttribute("id") == "cell12") // verify surroundings of cell 12
    {
        if (document.getElementById("cell8").innerHTML == "")
        {
            validClick = true;
            emptyCellId = "cell8";
        }
        else if (document.getElementById("cell11").innerHTML == "")
        {
            validClick = true;
            emptyCellId = "cell11";
        }
        else if (document.getElementById("cell16").innerHTML == "")
        {
            validClick = true;
            emptyCellId = "cell16";
        }
    }
    else if (e.target.getAttribute("id") == "cell13") // verify surroundings of cell 13
    {
        if (document.getElementById("cell9").innerHTML == "")
        {
            validClick = true;
            emptyCellId = "cell9";
        }
        else if (document.getElementById("cell14").innerHTML == "")
        {
            validClick = true;
            emptyCellId = "cell14";
        }
    }
    else if (e.target.getAttribute("id") == "cell14") // verify surroundings of cell 14
    {
        if (document.getElementById("cell10").innerHTML == "")
        {
            validClick = true;
            emptyCellId = "cell10";
        }
        else if (document.getElementById("cell13").innerHTML == "")
        {
            validClick = true;
            emptyCellId = "cell13";
        }
        else if (document.getElementById("cell15").innerHTML == "")
        {
            validClick = true;
            emptyCellId = "cell15";
        }
    }
    else if (e.target.getAttribute("id") == "cell15") // verify surroundings of cell 15
    {
        if (document.getElementById("cell11").innerHTML == "")
        {
            validClick = true;
            emptyCellId = "cell11";
        }
        else if (document.getElementById("cell14").innerHTML == "")
        {
            validClick = true;
            emptyCellId = "cell14";
        }
        else if (document.getElementById("cell16").innerHTML == "")
        {
            validClick = true;
            emptyCellId = "cell16";
        }
    }
    else if (e.target.getAttribute("id") == "cell16") // verify surroundings of cell 16
    {
        if (document.getElementById("cell12").innerHTML == "")
        {
            validClick = true;
            emptyCellId = "cell12";
        }
        else if (document.getElementById("cell15").innerHTML == "")
        {
            validClick = true;
            emptyCellId = "cell15";
        }
    }

    if (validClick == true) // perform the switch between the clicked tile and the empty tile
    {
        var clickedCell = document.getElementById(clickedCellId); // node which the value must be switched with the empty cell
        var tempValue = clickedCell.innerHTML;
        clickedCell.innerHTML = ""; // becomes empty
        var emptyCell = document.getElementById(emptyCellId);
        emptyCell.innerHTML = tempValue;
    }
    else
    {
        window.alert("Illegal Move ! The tile you clicked is not adjacent to the empty spot.");
    }
}

function shuffleArray (array)
{
    var a, b, temp; // a and b are indices, temp will hold an array element's value for swapping

    for (var i = 0; i < array.length; i++) // loop through entire array
    {
        a = i; // index of element to shuffle
        b = Math.floor(Math.random() * array.length); // switch with random element in array at index b

        temp = array[b];
        array[b] = array[a];
        array[a] = temp;
    }
}

function startCell (cellID, value) // adds the randomly generated value to the cell
{
    var cell = document.getElementById("cell" + cellID);

    if (value == 0)
    {
        cell.innerHTML = "";// this will be the empty cell
    }
    else
    {
        cell.innerHTML = value;
    }
}