#include <stdio.h>
#include <stdlib.h>

/* frees old array and returns newly sorted array and start will be the starting index */
int *twowayInsort(int *arr, int n, int *start);
/* returns dynamically allocated array and n will be its size after call */
int *makeArray(FILE *in_file, int *n);
void printArr(int arr[], int start, int n);

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

  /* sort array and get starting index */
  int start;
  arr = twowayInsort(arr, n, &start);

  /* print array using the starting index */
  printArr(arr, start, n);

  free(arr);

  return 0;
}

int *twowayInsort(int *arr, int n, int *start) {
  int count = 0;
  int sortedLen = 2 * n + 1;

  int *sorted = (int *)malloc(sizeof(int) * sortedLen);
  if (sorted == NULL) {
    fprintf(stderr, "Error allocating sorted array\n");
    free(arr);
    exit(-1);
  }

  int mid = sortedLen / 2;
  int lo = mid - 1;
  int hi = mid + 1;

  sorted[mid] = arr[0];
  for (int i = 1; i < n; i++) {
    int key = arr[i];

    /* check if key should go in lo */
    if (key < sorted[lo + 1]) {
      sorted[lo] = key;
      lo--;
      count++;
    /* check if key should go in hi */
    } else if (key > sorted[hi - 1]) {
      sorted[hi] = key;
      hi++;
      count++;
    /* find where key should go then decide which side to shift from j */
    } else {
      int j = hi - 1;
      while (j > lo && key < sorted[j])
        j--;

      /* j is now in correct position for key, check which side to shift */

      /* shorter distance to lo so shift left side */
      if ((j - lo) < (hi - (j + 1))) {
        int k = lo;
        while (k < j) {
          sorted[k] = sorted[k + 1];
          k++;
          count++;
        }

        lo--;

      /* shorter distance to hi so shift right side */
      } else {
        int k = hi;
        /* increment j because key >= sorted[j] */
        j++;
        while (k > j) {
          sorted[k] = sorted[k - 1];
          k--;
          count++;
        }

        hi++;
      }

      sorted[j] = key;
      count++;
    }
  }

  /* free old array */
  free(arr);
  arr = NULL;

  /* print number of assignments and array */
  printf("# of sorting assignments = %d\n\n", count);

  /* set starting index to 1 higher than lo */
  *start = lo + 1;

  /* return dynamically allocated sorted array */
  return sorted;
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

void printArr(int arr[], int start, int n) {
  int len = start + n;
  for (int i = start; i < len; i++)
    printf("%d\n", arr[i]);
}

