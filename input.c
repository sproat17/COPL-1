#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

char * scan(char ch);
void search(void);
int fpeek(void);
int j = 0;
char * tokens[16];
char name[20];
FILE * fp;

int main(void) {
  printf("Scanner ");
  scanf("%s", name);

  fp = fopen(name, "r");

  while (fp == NULL) {
    printf("File %s does not exist\n", name);
    printf("Scanner ");
    scanf("%s", name);
    fp = fopen(name, "r");
  }

  search();

  for (int i = 0; i < j; i++) {
    printf("%s ", tokens[i]);
  }

  printf("\n");
  return 0;
}
void search(void) {
  char ch;
  for (;
    (ch = fgetc(fp)) != EOF;) {
    tokens[j] = scan(ch);
  }
}

int fpeek(void) {
  int c = getc(fp);
  ungetc(c, fp);
  return c;
}

void next(void) {
  fseek(fp, 1, SEEK_CUR);
}

void error(void) {
  printf("error\n");
  exit(1);
}

char * scan(char ch) {

  switch (ch) {
  case ' ':
    break;
  case '\n':
    break;
  case '/':
    if (fpeek() == '/') {
      while (fpeek() != '\n') {
        next();
      }
      break;
    } else if (fpeek() != '*') {
      j++;
      return "division";
      break;
    }
    while ((fpeek() != '*') | (fpeek() != '/') | (fpeek() != EOF)) {
      next();
      if ((fpeek() == '/') | (fpeek() == EOF)) {
        next();
        break;
      }
    }
    break;
  case '(':
    j++;
    return "lparen";
    break;
  case ')':
    j++;
    return "rparen";
    break;
  case '+':
    j++;
    return "plus";
    break;
  case '-':
    j++;
    return "minus";
    break;

  case ':':
    if (fpeek() == '=') {
      j++;
      return "assign";
      break;
    } else {
      error();
    }
    break;
  case '*':
    j++;
    return "times";
    break;

  case '.':
    if (isdigit(fpeek())) {
      next();
      j++;
      return "number";
    } else {
      error();
    }
    while (isdigit(fpeek())) {
      next();
    }
    break;
  default:
    if (isdigit(ch)) {
      while ((isdigit(fpeek())) | (fpeek() == '.')) {
        next();
        if (fpeek() == '.') {
          next();
          while (isdigit(fpeek())) {
            next();
          }
          j++;
          return "number";
        }
      }
      j++;
      return "number";

    } else if (isalpha(ch)) {

      char * longest = malloc(sizeof(64));
      int k = 0;
      longest[k] = ch;
      k++;
      while (isalpha(fpeek()) | (isdigit(fpeek()))) {
        longest[k] = fpeek();
        next();
        k++;
      }
      if (!strcmp(longest, "read")) {
        j++;
        return "read";
      }
      if (!strcmp(longest, "write")) {
        j++;
        return "write";
      }
      if ((strcmp(longest, "write")) && (strcmp(longest, "read"))) {
        j++;
        return "id";
      }
      memset(longest, 0, strlen(longest));
      break;
    }

    error();
  }
  return "error\n";
  exit(1);
}
