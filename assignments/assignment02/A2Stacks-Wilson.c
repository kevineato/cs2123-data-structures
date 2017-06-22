#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INIT_ARR_SIZE 10
#define MAX_LEN 255

typedef struct stack {
  int currsize;
  int maxsize;
  char **strings;
} stack;

stack *create();
void push(stack *stk, const char *str);
char *pop(stack *stk);
void freestack(stack *stk);
int empty(stack *stk);
int full(stack *stk);

int main(int argc, char *argv[]) {
  /* Check for correct number of command-line arguments */
  if (argc != 2) {
    fprintf(stderr, "Usage: %s FILENAME\n", argv[0]);
    exit(-1);
  }

  /* Print header */
  printf("Assignment 2 Problem 1 by Kevin Wilson.\n");
  printf("---------------------------------------\n\n");

  /* Open filename provided, check for error */
  FILE *infile = fopen(argv[1], "r");
  if (infile == NULL) {
    fprintf(stderr, "Error opening %s\n", argv[1]);
    exit(-1);
  }

  /* Create stack and temp char buffer used for reading strings from file */
  stack *stk = create();
  char temp[MAX_LEN];
  while (fscanf(infile, "%254s", temp) != EOF) {
    /* If string from file is pop, pop stack then print size and string */
    if (strncmp(temp, "pop", 3) == 0) {
      char *popped = pop(stk);
      /* Make sure popped is not NULL */
      if (popped != NULL) {
        printf("# elements after popping: %d\t", stk->currsize);
        printf("string popped: %s\n", popped);
        free(popped);
      } else {
        printf("Cannot pop an empty stack!\n");
      }
    /* Any other string from file will be pushed onto stack */
    } else {
      push(stk, temp);
    }
  }

  /* Close file and free everything allocated */
  fclose(infile);
  freestack(stk);

  return 0;
}

stack *create() {
  stack *newstack = (stack *)malloc(sizeof(stack));
  /* Initialize array of strings with all pointers to NULL */
  newstack->strings = (char **)malloc(sizeof(char *) * INIT_ARR_SIZE);
  for (int i = 0; i < INIT_ARR_SIZE; i++)
    newstack->strings[i] = NULL;

  /* Initialize current size to 0 and max capacity to INIT_ARR_SIZE */
  newstack->currsize = 0;
  newstack->maxsize = INIT_ARR_SIZE;

  return newstack;
}

void push(stack *stk, const char *str) {
  /* Increment current size and check to make sure there is space, if not realloc */
  stk->currsize++;
  if (full(stk)) {
    stk->maxsize *= 2;
    stk->strings = (char **)realloc(stk->strings, sizeof(char *) * stk->maxsize);
    printf("Stack capacity has grown from %d elements to %d elements\n", stk->maxsize / 2, stk->maxsize);
  }

  /* Allocate memory equal to string length + 1 for null-byte */
  int len = strlen(str);
  stk->strings[stk->currsize - 1] = (char *)calloc(len + 1, sizeof(char));
  /* Copy string into string array */
  strncpy(stk->strings[stk->currsize - 1], str, len);
}

char *pop(stack *stk) {
  /* Check if stack is empty */
  if (empty(stk))
    return NULL;

  /* Decrement current size */
  stk->currsize--;
  /* Allocate new string equal to top element length + 1 */
  int len = strlen(stk->strings[stk->currsize]);
  char *popped = (char *)calloc(len + 1, sizeof(char));

  /* Copy top element string into newly allocated string */
  strncpy(popped, stk->strings[stk->currsize], len);

  /* Free the previously allocated top element */
  free(stk->strings[stk->currsize]);

  return popped;
}

void freestack(stack *stk) {
  /* Free any strings that have not been freed from pop */
  for (int i = 0; i < stk->currsize; i++)
    free(stk->strings[i]);

  /* Free the strings array and then the stack itself */
  free(stk->strings);
  free(stk);
}

int empty(stack *stk) {
  /* Empty when current size is 0 */
  return (stk->currsize == 0);
}

int full(stack *stk) {
  /* Full when current size is greater than or equal to max capacity */
  return (stk->currsize >= stk->maxsize);
}

