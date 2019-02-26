/*
 Student Name: Mohamed Ali Ramadan
 Student Number: 7688825

Question 6
Write a script that encodes English-language phrases in pig Latin. Pig Latin is a form of coded language often used for amusement.
Many variations exist in the methods used to form pig Latin phrases. For simplicity, use the following algorithm:
To form a pig Latin phrase from an English-language phrase, tokenize the phrase into an array of words using String
method split. To translate each English word into a pig Latin word, place the first letter of the English word at the
end of the word and add “ay”. Thus, the word “jump” becomes “umpjay”, the word “the” becomes “hetay”, and the word “computer”
becomes “omputercay”. Blanks between words remain as blanks. Assume the following: The English phrase consists of words
separated by blanks, there are no punctuation marks, and all words have two or more letters. Your script should include
function printLatinWord, which displays each pig Latin word. Each token (i.e., word in the sentence) is passed to function
printLatinWord to print the corresponding pig Latin word. Enable the user to input the sentence through an HTML5 form. Keep
a running display of all the converted sentences in an HTML5 textarea. Separate your script from the HTML5 document. [15 marks]
 */

window.addEventListener("load", loadForm, false);

function loadForm()
{
    var form = document.getElementById("form1");
    form.addEventListener("submit", translate, false);
}

function translate() //translates phrase and calls translateWord and printLatinWord
{
    event.preventDefault();
    var form = document.getElementById("form1");
    var input = form.elements[0].value; //text input value
    var wordsArray = input.split(" "); // tokenize input
    var translatedWordsArray = new Array(wordsArray.length); //new array for translations

    // section under the text area
    var converted = document.getElementById("converted");
    converted.innerHTML = "Most Recent Conversion : ";

    for (var a = 0; a <= wordsArray.length - 1; a++)
    {
        translatedWordsArray[a] = translateWord(wordsArray[a]);
        // prints every converted word to the text area and to the section beneath it
        printLatinWord(translatedWordsArray[a]);
    }

    var output = document.getElementById("textArea");
    output.value += "\n"; //new line to separate the text area conversions
}

function translateWord(englishWord) //translates a single word to pig latin
{
    var firstCharacter = englishWord.charAt(0);
    var remainder = englishWord.slice(1);//index one to last index
    var result = remainder + firstCharacter + "ay";
    return (result);
}

function printLatinWord(latinWord)
{
    var output = document.getElementById("textArea");
    output.value += latinWord + " ";
    var converted = document.getElementById("converted");
    converted.innerHTML += latinWord + " ";
}