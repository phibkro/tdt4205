#include <stdio.h>
#include <stdbool.h>
#include <string.h>

static char FIZZ[] = "fizz";
static char BUZZ[] = "buzz";
static char EMPTY_STRING[] = "";

/* Int TO Ascii */
/* https://stackoverflow.com/questions/9655202/how-to-convert-integer-to-string-in-c */
char *itoa(int i, char b[])
{
  char const digit[] = "0123456789";
  char *p = b;
  if (i < 0)
  {
    *p++ = '-';
    i *= -1;
  }
  int shifter = i;
  do
  { // Move to where representation ends
    ++p;
    shifter = shifter / 10;
  } while (shifter);
  *p = '\0';
  do
  { // Move back, inserting digits as u go
    *--p = digit[i % 10];
    i = i / 10;
  } while (i);
  return b;
}

/* 
  calculates FizzBuzz and writes the result in buffer

  takes in a number, memory buffer and the buffer size
  if number is divisable by 3, write "fizz" in buffer
  if number is divisable by 5, write "buzz" in buffer
  if number is divisable by 3 AND 5, writes "fizzbuzz" in buffer
  if number NOT divisable by 3 or 5, writes the number in buffer

  returns true/1 (error) if:
    - buffer is NULL
    - buffer_size is less than MAX_LENGTH of "fizzbuzz"
  
  returns false/0 if no errors

*/
bool fizzbuzz(int input, char *buffer, int buffer_size)
{
  int MAX_LENGTH = strlen(FIZZ) + strlen(BUZZ);
  if (buffer == NULL)
    return true;
  if (buffer_size < MAX_LENGTH)
    return true;
  if (strcmp(buffer, EMPTY_STRING))
  {
    strcpy(buffer, EMPTY_STRING);
  }

  bool altered = false;

  if (input % 3 == 0)
  {
    altered = true;
    strcat(buffer, FIZZ);
  }
  if (input % 5 == 0)
  {
    altered = true;
    strcat(buffer, BUZZ);
  }
  if (!altered)
  {
    itoa(input, buffer);
  }

  return false;
}

int main(int argc, char const *argv[])
{
  int MAX_LENGTH = strlen(FIZZ) + strlen(BUZZ);
  char buffer[MAX_LENGTH];

  for (int i = 1; i < 100; i++)
  {
    if (fizzbuzz(i, buffer, MAX_LENGTH) == 0)
    {
      puts(buffer);
    } else {
      printf("error\n");
    }
  }

  // fizzbuzz(INPUT);
  return 0;
}
