#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <sys/stat.h>

char ** scan(char *everyChar);
int j = 0;
char *tokens[16];
int size;

int main(void)
{
  char name[20];
  printf("Scanner ");
  scanf("%s", name);

  FILE *fp;
  fp  = fopen (name, "r");

  while (fp == NULL){
    printf("File %s does not exist\n", name);
    printf("Scanner ");
    scanf("%s", name);
    fp  = fopen (name, "r");
  }

  struct stat st;
  stat(name, &st);
  size = st.st_size;

  char *everyChar = malloc(size);

  char ch;
  for(int i = 0; (ch = fgetc(fp)) != EOF; i++) {
      everyChar[i] = ch;
  }

  char ** token = scan(everyChar);
  for(int i = 0; i < j; i++){
    printf("%s ", token[i]);
  }

  printf("\n");
  return 0;
}

void error(){
  printf("error\n");
  exit(0);
}

char ** scan(char *everyChar){

  char *current = malloc(sizeof(64));
  for(int i = 0; i < size; i++){
    int k = 0;
    switch(everyChar[i]){
      case ' ':
        break;
      case '\n':
        break;
      case '/':
        if(everyChar[i+1] == '/'){
          while(everyChar[i+1] != '\n'){
            i++;
          }
          break;
        } else if(everyChar[i+1] != '*'){
          tokens[j] = "division";
          j++;
          break;
        }
        i++;
        while((everyChar[i] != '*') | (everyChar[i] != '/')){
          if(everyChar[i] == '/'){
            break;
          }
          i++;
        }
      break;
      case '(':
        tokens[j] = "lparen";
        j++;
        break;
      case ')':
        tokens[j] = "rparen";
        j++;
        break;
      case '+':
        tokens[j] = "plus";
        j++;
        break;
      case '-':
        tokens[j] = "minus";
        j++;
        break;
      case ':':
        if(everyChar[i+1] == '='){
          tokens[j] = "assign";
          j++;
          break;
        } else {
          error();
        }
        break;
      case '*':
        tokens[j] = "times";
        j++;
        break;
      case '.':
        if(isdigit(everyChar[i+1])){
          i++;
          tokens[j] = "number";
          j++;
        } else {
          i++;
          error();
        }
        while(isdigit(everyChar[i+1])){
            i++;
        }
        break;
      default:
        if(isdigit(everyChar[i])){
          tokens[j] = "number";
          j++;
          while((isdigit(everyChar[i+1])) | (everyChar[i+1] == '.')){
            i++;
            if(everyChar[i] == '.'){
              i++;
              while(isdigit(everyChar[i])){
                  i++;
              }
              break;
            }
          }

          break;
        } else if(isalpha(everyChar[i])){
            while((isalpha(everyChar[i])) | (isdigit(everyChar[i]))){
              current[k] = everyChar[i];
              i++;
              k++;
            }
            if(!strcmp(current, "read")){
              tokens[j] = "read";
              j++;
            }
            if(!strcmp(current, "write")){
              tokens[j] = "write";
              j++;
            }
            if((strcmp(current, "write")) && (strcmp(current, "read"))){
              tokens[j] = "id";
              j++;
            }
            memset(current, 0, strlen(current));
            break;
        }
        error();
      }
    }
  return tokens;
}
