#include <stdio.h>
#include <stdlib.h>

char * scan(void);

int main(void)
{
  char * myString = scan();

  for(int i = 0; myString[i] != '\0'; i++) {
    printf("%c", myString[i]);
  }

  printf("\n");
  return 0;
}

char * scan(void){

  char name[20];
  printf("Enter file name: ");
  scanf("%s", &name);
  printf("Attempting to open the file: %s \n", name);

  FILE *fp;
  fp  = fopen (name, "r");

  if (fp == NULL){
    printf("Failed to open the file\n");
  }

  char *everyChar = malloc(sizeof(100));
  char ch;
  for(int i = 0; (ch = fgetc(fp)) != EOF; i++) {
    if(ch != '\n'){
      everyChar[i] = ch;
    } else {
      everyChar[i] = ' ';
    }
  }

  return everyChar;
}
