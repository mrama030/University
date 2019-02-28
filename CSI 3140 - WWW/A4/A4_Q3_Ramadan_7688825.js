// Mohamed Ramadan - Question 3

window.addEventListener("load", setUp, false);

function setUp()
{
    window.addEventListener("click", processClick, false);
}

/* Processes the mouse click event e*/
function processClick(e)
{
    if (e.ctrlKey == true && e.shiftKey == true) // user pressed shift and control keys
    {
        window.alert("Since you pressed the shift key while clicking the mouse, the event name is : " + e.type);
        window.alert("Since you pressed the control key while clicking the mouse, the element name " +
            "that triggered the event is : " + e.target.getAttribute("name"));
    }
    else if (e.ctrlKey == true && e.shiftKey == false) // user pressed control key
    {
        window.alert("Since you pressed the control key while clicking the mouse, the event name is : " + e.type);
    }
    else if (e.ctrlKey == false && e.shiftKey == true) // user pressed shift key
    {
        window.alert("Since you pressed the shift key while clicking the mouse, the element name " +
            "that triggered the event is : " + e.target.getAttribute("name"));
    }
    else // user did not press either key
    {
        /* Do Nothing */ ;
    }
}