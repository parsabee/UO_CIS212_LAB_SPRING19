#include <stdio.h>

int main() {
  char* str1 = "hello1"; //str1 is a pointer to the memory address at which the 'h' exists
  char str2[] = "hello2"; //str2 is an array of characters
  
  printf("%s\n%s", str1, str2); /*when passed to the printf function, str2 decays into a pointer to the first character of the original character array, so str1 and str2 are printed out in a similar fashion*/
  
  return 0;
}
