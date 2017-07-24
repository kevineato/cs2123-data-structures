#include <stdio.h>
#include <stdlib.h>

void insort(int arr[], int n);
/* returns dynamically allocated array and n will be its size after call */
int *makeArray(FILE *in_file, int *n);
void printArr(int arr[], int n);

int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s FILENAME\n", argv[0]);
    exit(-1);
  }

  FILE *in_file = fopen(argv[1], "r");
  if (in_file == NULL) {
    fprintf(stderr, "Error opening %s\n", argv[1]);
    exit(-1);
  }

  int n = 0;
  /* make array with file contents */
  int *arr = makeArray(in_file, &n);

  /* done with file so close it */
  fclose(in_file);

  /* sort array and get number of assignments */
  insort(arr, n);

  printArr(arr, n);

  free(arr);

  return 0;
}

void insort(int arr[], int n) {
  int count = 0;

  for (int i = 1; i < n; i++) {
    int key = arr[i];
    int j = i - 1;

    while (j >= 0 && key < arr[j]) {
      arr[j + 1] = arr[j];
      /* increment count for each shift */
      count++;
      j--;
    }

    arr[j + 1] = key;
    /* increment count for final assignment */
    count++;
  }

  /* print number of assignments */
  printf("# of sorting assignments = %d\n\n", count);
}

int *makeArray(FILE *in_file, int *n) {
  int *arr = NULL;
  int currsize = 1;
  *n = 0;
  arr = malloc(sizeof(int));
  if (arr == NULL) {
    fprintf(stderr, "Error allocating array\n");
    fclose(in_file);
    exit(-1);
  }

  int temp;
  while (fscanf(in_file, "%d", &temp) != EOF) {
    /* dynamically increase array size as needed */
    if (currsize <= *n) {
      currsize *= 2;
      arr = realloc(arr, sizeof(int) * currsize);
      if (arr == NULL) {
        fprintf(stderr, "Error reallocating array\n");
        free(arr);
        fclose(in_file);
        exit(-1);
      }
    }

    /* assign number read from file to array and increment index */
    arr[*n] = temp;
    (*n)++;
  }

  /* return array and n will now be the size of the array */
  return arr;
}

void printArr(int arr[], int n) {
  for (int i = 0; i < n; i++)
    printf("%d\n", arr[i]);
}

