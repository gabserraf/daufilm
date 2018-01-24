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

void throwError(char msg[T_MAX]);
mark* initializeMark(int markValue, int idFilm, int idUser);
list* initializeList();
mark* findSimilarity(mark* m1, mark* m2);
list* addList(list* l, mark* m);
void displayFilms();
void displayUsers();

/* extractData.c */

void readData(char filename[T_MAX]);
void initializeUsers();
void initializeFilms();

/*
 * END
 */

#endif