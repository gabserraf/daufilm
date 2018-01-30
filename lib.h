#ifndef LIB_H
#define LIB_H

/*
 * INCLUDES
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <time.h>

/*
 * DEFINES
 */

#define T_MAX 128
#define NB_FILMS 100 // 17770
#define NB_USERS 1000 // 2649429

/*
 * TYPE DEF
 */

typedef struct mark {
  int markValue;
  int idFilm;
  int idUser;
  struct mark* sameFilm;
  struct mark* sameUser;
} mark ;

typedef struct list {
  mark* head;
} list ;

/*
 * VARIABLES
 */

list* Films[NB_FILMS];
list* Users[NB_USERS];

/*
 * FUNCTIONS
 */

// auxiliaries.c 

mark* initializeMark(int markValue, int idFilm, int idUser);
list* initializeList();
mark* findSimilarity(mark* m1, mark* m2);
list* addList(list* l, mark* m);
int lenForUser(list* l);
int lenForFilm(list* l);
int searchMark(int user, int film);
int inList(list* haystack, int needle);
int inArray(int* haystack, int needle, int size);
void bubbleSort(double* values, int* objects, int size);
int argmin(double l[], int size);
void displayFilms();
void displayUsers();
void displayMark(mark* m);
void throwError(char msg[T_MAX]);
int isNumber(char* chr);
int getNumberMarks();
void freeMemory();

// extractData.c 

void initializeUsers();
void initializeFilms();
void readData(char filename[T_MAX]);
void createDataFile();

// knn-algorithms.c 

double similarityBetweenUsers(int user1, int user2);
int* kNearestNeighboors(int user, int k);

// pgmView.c 

void createPGM(int user, int k);

// recommandation.c 

int estimatedMark(int film, int user, int k);
int predict(int user, int film);
void top10(int user);
void filePrediction(int X);

// crossValidation.c

double RMSE(int* predictedValues, int* trueValues, int size);
double crossValidation(double perc);

/*
 * END
 */

#endif