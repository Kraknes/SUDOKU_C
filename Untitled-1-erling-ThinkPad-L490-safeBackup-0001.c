#include <stdio.h> // Inneholder printf,  scanf, og diverse
#include <stdbool.h> // kan gjøre lage variabler med (bool isTrue = true;), for print er det 1 eller 0 (%i)
#include <stdlib.h> // inneholder malloc


int main()
{
    int x, y;
    x = 3;
    y = 5;
    printf("X er %i og y er %i", x, y);
    printf("Helo wolrd!");

    int numbers = 12345;

// A variable to store the reversed number
    int revNumbers = 0;

    // Reverse and reorder the numbers
    while (numbers) {
  // Get the last number of 'numbers' and add it to 'revNumber' 
    revNumbers = revNumbers * 10 + numbers % 10;
  // Remove the last number of 'numbers'
    numbers /= 10;
}
}