window.addEventListener("load", setUp, false);

function setUp()
{
    var img = document.getElementById("image");
    img.addEventListener("mousedown", processMouseDown, false); // listen to mouse down on image
}
function processMouseDown(e)
{
    window.addEventListener("mousemove", processMouseMove, false); // activate mouse move
    window.addEventListener("mouseup", processMouseUp, false); // activate mouse up
}
function processMouseMove(e)
{
    var image = document.getElementById("image");
    var newPosition = "position: absolute; top: " + e.clientY + "px; left: " + e.clientX + "px;";
    image.setAttribute("style", newPosition);
}
function processMouseUp(e)
{
    window.removeEventListener("mousemove", processMouseMove, false); // disable mouse move
    window.removeEventListener("mouseup", processMouseUp, false); // disable mouse up
    setUp(); // reset
}