// Setup all tooltips (main menu and forms).
$(function(){
    $('[data-toggle="tooltip"]').tooltip()
});
// page load
window.addEventListener("load", loadPage, false);
function loadPage()
{
    var searchButton = document.getElementById("searchButton");
    searchButton.addEventListener("click",buttonClicked, false);
    searchButton.disabled = true;
    var temp = document.getElementById("searchText");
    temp.addEventListener("keyup", validate);
}

// in search field, when key is pressed
function validate()
{
    event.preventDefault();

    var temp = document.getElementById("searchText").value;

    if (event.keyCode === 13) // Enter
    {
        if (temp == "" && temp == null)
        {
            return;
        }
        else {
            var valid = validateText(temp);
            if (valid)
            {
                document.location.href = "ResultPage.html";
            }
        }
    }
    else
    {
        var b = validateText(temp);
    }
}

function validateText(toCheck)
{
    event.preventDefault();

    if (toCheck == "" && toCheck == null)
        return false;

    var dob = /^(((0[1-9]|[12]\d|3[01])\/(0[13578]|1[02])\/((19|[2-9]\d)\d{2}))|((0[1-9]|[12]\d|3[01])\/(0[13578]|1[02])\/((18|[2-9]\d)\d{2}))|((0[1-9]|[12]\d|30)\/(0[13456789]|1[012])\/((19|[2-9]\d)\d{2}))|((0[1-9]|[12]\d|30)\/(0[13456789]|1[012])\/((18|[2-9]\d)\d{2}))|((0[1-9]|1\d|2[0-8])\/02\/((19|[2-9]\d)\d{2}))|(29\/02\/((1[6-9]|[2-9]\d)(0[48]|[2468][048]|[13579][26])|((16|[2468][048]|[3579][26])00))))$/;
    var name = /^([A-Za-z][a-z]+)$/;

    var searchButton = document.getElementById("searchButton");

    if (dob.test(toCheck) || name.test(toCheck))
    {
        searchButton.disabled = false;
        return true;
    }
    else
    {
        searchButton.disabled = true;
        return false;
    }
}

function buttonClicked()
{
    document.location.href = "ResultPage.html";
}