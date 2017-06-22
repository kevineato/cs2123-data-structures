#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct student {
  int id;
  char name[255];
  int age;
  float gpa;
};

typedef struct student student;

student *student_new(int id, char *name);
// Returns 1 if age and gpa were set else 0
int student_set_age(student *studentptr, int age);
int student_set_gpa(student *studentptr, float gpa);
float student_avg_age(student **students, int num_students);
float student_avg_gpa(student **students, int num_students);

int main(int argc, char *argv[]) {
  printf("CS 2123 Assignment 1 written by Kevin Wilson\n");
  printf("--------------------------------------------\n");

  // Check for correct command-line arguments
  if (argc != 2) {
    fprintf(stderr, "Usage: %s FILENAME\n", argv[0]);
    exit(-1);
  }

  FILE *infile = fopen(argv[1], "r");
  if (infile == NULL) {
    fprintf(stderr, "Unable to open %s\n", argv[0]);
    exit(-1);
  }

  student **students = (student **)malloc(sizeof(student *));
  int file_row = 1;
  int num_students = 0;
  int temp_id, temp_age;
  char temp_name[255];
  float temp_gpa;
  while (fscanf(infile, "%d %254[^\n0-9] %d %f", &temp_id, temp_name, &temp_age, &temp_gpa) != EOF) {
    file_row += 4;
    if (strlen(temp_name) < 1) {
      fprintf(stderr, "Cannot create student record from file row %d: name is invalid\n", file_row - 3);
      continue;
    } else if (temp_id <= 0) {
      fprintf(stderr, "Cannot create student record from file row %d: id is invalid\n", file_row - 4);
      continue;
    }

    student *next_student = student_new(temp_id, temp_name);

    if (!student_set_age(next_student, temp_age)) {
      fprintf(stderr, "Cannot create student record from file row %d: age is invalid\n", file_row - 2);
      free(next_student);
      continue;
    }

    if (!student_set_gpa(next_student, temp_gpa)) {
      fprintf(stderr, "Cannot create student record from file row %d: gpa is invalid\n", file_row - 1);
      free(next_student);
      continue;
    }

    num_students++;
    students = (student **)realloc(students, sizeof(student *) * num_students);
    *(students + num_students - 1) = next_student;
  }
  fclose(infile);

  float avg_age = student_avg_age(students, num_students);
  float avg_gpa = student_avg_gpa(students, num_students);

  printf("\n# of students: %d\n", num_students);
  printf("Average age: %lf\n", avg_age);
  printf("Average gpa: %lf\n", avg_gpa);

  // Free everything
  for(int i = 0; i < num_students; i++)
    free(*(students + i));
  free(students);

  return 0;
}

student *student_new(int id, char *name) {
  student *new_student = (student *)malloc(sizeof(student));

  if (strlen(name) >= 1)
    strncpy(new_student->name, name, 254);

  if (id > 0)
    new_student->id = id;

  return new_student;
}

int student_set_age(student *studentptr, int age) {
  if (age > 0) {
    studentptr->age = age;
    return 1;
  }

  return 0;
}

int student_set_gpa(student *studentptr, float gpa) {
  if (gpa >= 0.0 && gpa <= 4.0) {
    studentptr->gpa = gpa;
    return 1;
  }

  return 0;
}

float student_avg_age(student **students, int num_students) {
  float sum = 0.0;
  for (int i = 0; i < num_students; i++)
    sum += (*(students + i))->age;

  return sum / num_students;
}

float student_avg_gpa(student **students, int num_students) {
  float sum = 0.0;
  for (int i = 0; i < num_students; i++)
    sum += (*(students + i))->gpa;

  return sum / num_students;
}

