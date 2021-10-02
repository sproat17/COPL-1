#include <stdio.h>

void scan();

int main(void)
{
  scan();
  return 0;
}

void scan(){

  char name[20];
  printf("Enter file name: ");
  scanf("%s", &name);
  printf("Attempting to open the file: %s \n", name);

  FILE *fp;
  fp  = fopen (name, "r");

  if (fp == NULL){
    printf("Failed to open the file\n");
  }

  char everyChar[100];
  char ch;
  for(int i = 0; (ch = fgetc(fp)) != EOF; i++) {
    if(ch != '\n'){
      everyChar[i] = ch;
    } else {
      everyChar[i] = ' ';
    }
    i++;
  }

  for(int i = 0; everyChar[i] != '\0'; i++) {
    printf("%c", everyChar[i]);
    i++;
  }

   printf("\n");
}
