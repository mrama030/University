/*
Student Name: Mohamed Ali Ramadan
Student Number: 7688825

A prime integer is an integer greater than 1 that is evenly divisible only by itself and 1.
The Sieve of Eratosthenes is an algorithm for finding prime numbers. It operates as follows:

a) Create an array with all elements initialized to 1 (true). Array elements with prime indices will remain as 1.
All other array elements will eventually be set to zero.

b) Set the first two elements to zero because 0 and 1 are not primes. Starting with array index 2,
every time an array element is found whose value is 1, loop through the remainder of the array and
set to zero every element whose index is a multiple of the index for the element with value 1.
For example, for array index 2, all elements beyond 2 in the array that are multiples of 2 will be
set to zero (i.e., indices 4, 6, 8, 10, etc.); for array index 3, all elements beyond 3 in the array
that are multiples of 3 will be set to zero (i.e., indices 6, 9, 12, 15, etc.); and so on.

When this process is complete, the array elements that are still set to 1 indicate that their
indices are prime numbers. These indices can be printed. Write a script (in a .js file separate
from the HTML5 document) that uses an array of 1000 elements to determine the number of the prime
numbers between 1 and 999 and output these prime numbers. Ignore element 0 of the array. Your CSS rules
(if any) should also be placed in a separate .css file from the HTML5 document. [10 marks]
*/

var counter = 0;
var primeArray = new Array (1000); //indexes 0 to 999

primeArray[0] = 0;
primeArray[1] = 0;

for (counter=2; counter <= 999; counter++) // initialize remaining array values to 1
{
    primeArray[counter] = 1;
}

for (counter=2; counter <= 999; counter++)
{
    if (primeArray[counter] == 1) // if value is 1
    {
        // loop through remainder of the array, all elements afterwards that are multiples of counter are set to 0
        for (var a = 2*counter ;  a <= 999; a = a + counter)
        {
            primeArray[a] = 0;
        }
    }
}

document.writeln("<p>0 = non-prime number ; 1 = prime number");

document.writeln("<table border='3'><thead><tr><th>Prime Number</th><th>Value in Array (0 or 1)</th></tr></thead><tbody>");

for (counter = 1; counter <= 999; counter++)
{
    if (primeArray[counter] == 1)
    {
        document.writeln("<tr><td>" + counter + "</td><td>" + primeArray[counter] + "</td></tr>");
    }
}
document.writeln("</tbody></table>");