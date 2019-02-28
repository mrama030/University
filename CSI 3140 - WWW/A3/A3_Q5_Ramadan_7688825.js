/*
 Student Name: Mohamed Ali Ramadan
 Student Number: 7688825

Question 5

Please note that the winner is displayed at the TOP not the bottom of the page.
 */
var tortoisePosition = -1;
var harePosition = -1;
var interval = null;
var random = -1;
var ticks = 0;
window.addEventListener("load", load, false);

function load()
{
    var start = document.getElementById("startButton");
    start.addEventListener("click", startGame, false);
}
function startGame()
{
    document.getElementById("startButton").setAttribute("disabled", "disabled");
    tortoisePosition = 1;
    harePosition = 1;
    interval = window.setInterval("tick()", 1000);
    var results = document.getElementById("results");
    results.innerHTML = "<br>ON YOUR MARK, GET SET<br>BANG!!!<br>AND THEY’RE OFF!!!<br>";
}
function tick()
{
    ticks++;
    random = Math.floor(1 + Math.random()*10);

    moveTortoise(random);
    moveHare(random);
    printPositions();
    verifyWin();
}
function moveTortoise(random)
{
    if (random >= 1 && random <= 5) //50% = Fast Plod
    {
        tortoisePosition += 3; //3 to the right
    }
    else if (random == 6 || random == 7) //20% = Slip
    {
        tortoisePosition -= 6; //6 to the left

        if (tortoisePosition < 1)
        {
            // Race is only between square 1 and 70
            tortoisePosition = 1;
        }
    }
    else if (random >= 8 && random <= 10) //30% = Slow Plod
    {
        tortoisePosition++; //1 to the right
    }
}
function moveHare(random)
{
    if (random == 1 || random == 2) //20% = Sleep
    {
        ;//No movement
    }
    else if (random == 3 || random == 4) //20% = Big Hop
    {
        harePosition += 9; //9 to the right
    }
    else if (random == 5) //10% = Big Slip
    {
        harePosition -= 12; //12 to the left

        if (harePosition < 1)
        {
            // Race is only between square 1 and 70
            harePosition = 1;
        }
    }
    else if (random >= 6 && random <= 8) //30% = Small Hop
    {
        harePosition++; //1 to the right
    }
    else if (random == 9 || random == 10) //20% = Small slip
    {
        harePosition -= 2; //2 to the left

        if (harePosition < 1)
        {
            // Race is only between square 1 and 70
            harePosition = 1;
        }
    }
}
function verifyWin()
{
    var results = document.getElementById("results");

    if (harePosition >= 70 && tortoisePosition >= 70) // Its a TIE !!!
    {
        results.innerHTML += "<h1>IT’S A TIE</h1><h1>Time to complete race: " + ticks + " seconds.</h1>";
        window.clearInterval(interval);
    }
    else if (harePosition >= 70) // not a tie, HARE WINS
    {
        results.innerHTML += "<h1>HARE WINS. YUCK!</h1><h1>Time to complete race: " + ticks + " seconds.</h1>";
        window.clearInterval(interval);
    }
    else if (tortoisePosition >= 70) //not a tie, Tortoise WINS
    {
        results.innerHTML += "<h1>TORTOISE WINS!!! YAY!!!</h1><h1>Time to complete race: " + ticks + " seconds.</h1>";
        window.clearInterval(interval);
    }
    // else, no one has won yet
}
function printPositions() //it states to print a line, which is too general, I will use a table as it is more appropriate...
{
    var race = document.getElementById("racePositions");

    var table = "";

    table += "<br><table border='5'><thead><tr><th colspan='70'>Race progress at time: " + ticks + " seconds.</th></tr></thead><tbody><tr>";

    for (var i = 1; i <= 70; i++) // Print a row for the positions
    {
        table += "<td>" + i + "</td>";
    }
    table += "</tr><tr>";

    for (var a = 1; a <= 70; a++)
    {
        if (a == tortoisePosition && tortoisePosition == harePosition) //both at same position
        {
            table += "<td>OUCH!!!</td>";
        }
        else if (a == tortoisePosition)
        {
            table += "<td>T</td>";
        }
        else if (a == harePosition)
        {
            table += "<td>H</td>";
        }
        else
        {
            table += "<td></td>"; // Blank cell
        }
    }
    table += "</tr></tbody></table><br>";

    race.innerHTML += table;

    /* Please note the winner will be displayed at the top not the bottom. */
}
















