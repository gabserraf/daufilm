#ifndef LIB_H
#define LIB_H

/*
 * INCLUDES
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/*
 * DEFINES
 */

#define T_MAX 512
#define NB_FILMS 10 /*17770*/
#define NB_USERS 100 /*2649429*/

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

/* auxiliaries.c */

mark* initializeMark(int markValue, int idFilm, int idUser);
list* initializeList();
mark* findSimilarity(mark* m1, mark* m2);
list* addList(list* l, mark* m);
int inList(list* haystack, int needle);
int len(list* l);
int searchMark(int user, int film);
void displayFilms();
void displayUsers();
void displayMark(mark* m);
void throwError(char msg[T_MAX]);
int argmin(double l[], int size);
void freeMemory();

/* extractData.c */

void readData(char filename[T_MAX]);
void initializeUsers();
void initializeFilms();

/* knn-algorithms.c */

double centeredDotProduct(int* x, int* y);
double centeredNorm(int* x);
double pearsonSimilarity(int* x, int* y);
double pearsonSimilarityBetweenUsers(int user1, int user2);
int numberOfFilmsInCommon(int user1, int user2);
int* kNearestNeighboors(int user, int k);

/* pgmView.c */

void createPGM(int user, int k);

/*
 * END
 */

#endif