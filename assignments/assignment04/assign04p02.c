#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_NUMS 100
#define NUM_RUNS 50

typedef struct node {
  int data;
  struct node *left;
  struct node *right;
} node;

void freeTree(node *root);
int getMax(node *root);
int getMin(node *root);
int getRand();
node *insert(node *root, int val);
int max(int num1, int num2);
int min(int num1, int num2);
node *newNode(int val);

int main(void) {
  /* array to keep track of count of runs per difference */
  int diffScores[MAX_NUMS] = {0};
  node *root = NULL;
  srand(time(NULL));

  for (int i = 0; i < NUM_RUNS; i++) {
    /* insert 100 random numbers */
    for (int j = 0; j < MAX_NUMS; j++)
      root = insert(root, getRand());

    /* get smallest and greatest levels */
    int minLevel = getMin(root);
    int maxLevel = getMax(root);
    int diff = maxLevel - minLevel;

    /* print the largest, smallest, and difference of current run */
    printf("\nRun #%d:\n", i + 1);
    printf("Largest Level:  %d\n", maxLevel);
    printf("Smallest Level: %d\n", minLevel);
    printf("Difference:     %d\n", diff);

    /* increment array that keeps track of number of runs per difference */
    diffScores[diff]++;

    /* free tree resources and set root to NULL for next iteration */
    freeTree(root);
    root = NULL;
  }

  /* find max difference recorded to avoid printing unnecessary info */
  /* range of possible differences is 0 to n - 3, so maxDiff starts n - 3 */
  int maxDiff = MAX_NUMS - 3;
  while (diffScores[maxDiff] == 0)
    maxDiff--;

  /* print summaray of runs per difference */
  printf("\nLevel Difference\t# Runs\n");
  printf("------------------------------\n");
  for (int i = 0; i <= maxDiff; i++)
    printf("%d               \t%d\n", i, diffScores[i]);

  return 0;
}

void freeTree(node *root) {
  if (root == NULL)
    return;

  freeTree(root->left);
  freeTree(root->right);
  free(root);
}

int getMax(node *root) {
  /* root is NULL minus 1 to signal error or cancel previously added level */
  if (root == NULL)
    return -1;

  /* if left or right subtree is NULL skip it and traverse other subtree */
  if (root->left == NULL)
    return 1 + getMax(root->right);
  if (root->right == NULL)
    return 1 + getMax(root->left);

  /* return max of left and right subtree levels */
  return 1 + max(getMax(root->left), getMax(root->right));
}

int getMin(node *root) {
  /* root is NULL minus 1 to signal error or cancel previously added level */
  if (root == NULL)
    return -1;

  /* if left or right subtree is NULL skip it and traverse other subtree */
  if (root->left == NULL)
    return 1 + getMin(root->right);
  if (root->right == NULL)
    return 1 + getMin(root->left);

  /* return min of left and right subtree levels */
  return 1 + min(getMin(root->left), getMin(root->right));
}

int getRand() {
  return rand() % 1000 + 1;
}

node *insert(node *root, int val) {
  /*  is empty insert at root */
  if (root == NULL)
    return newNode(val);

  /* recursively call insert to find correct position to insert */
  if (val < root->data)
    root->left = insert(root->left, val);
  else
    root->right = insert(root->right, val);

  /* return original root */
  return root;
}

int max(int num1, int num2) {
  return (num1 > num2) ? num1 : num2;
}

int min(int num1, int num2) {
  return (num1 < num2) ? num1 : num2;
}

node *newNode(int val) {
  node *nextNode = (node *)malloc(sizeof(node));
  nextNode->left = NULL;
  nextNode->right = NULL;
  nextNode->data = val;

  return nextNode;
}

