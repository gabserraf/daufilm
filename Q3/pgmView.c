/*
 * INCLUDES
 */

#include "../lib.h"

/*
 * FUNCTIONS
 */

/**
 * TODO
 * @param user
 * @param k
 */
void createPGM(int user, int k) {

  /*
   * variables
   */

  FILE* pgmFile = NULL;
  char line[T_MAX] = "";
  char append[T_MAX] = "";
  
  int* neighboors = NULL;
  int films[NB_FILMS];
  mark* currentMark = NULL;

  int pxValue = 0;
  int nbFilms = 0;

  /*
   * get neighboors
   */

  neighboors = kNearestNeighboors(user, k);

  /*
   * get films
   */

  for (int i = 0; i < NB_FILMS; i++) films[i] = 0;

  for (int i = 0; i < k; i++) {
    
    currentMark = Users[neighboors[i]-1] != NULL ? Users[neighboors[i]-1]->head : NULL;

    while (currentMark != NULL) {
      
      if (!films[currentMark->idFilm-1]) nbFilms++;
      
      films[currentMark->idFilm-1] = 1;
      currentMark = currentMark->sameUser;

    }

  }

  /*
   * create PGM
   */

  pgmFile = fopen("Q3/pgmView.pgm", "w");

  /*
   * head of PGM
   */

  strcpy(line, "P2\n");
  fputs(line, pgmFile);

  strcpy(line, "");
  sprintf(append, "%d", nbFilms);
  strcat(line, append);
  strcat(line, " ");
  sprintf(append, "%d", k);
  strcat(line, append);
  strcat(line, " \n");
  fputs(line, pgmFile);

  strcpy(line, "255\n");
  fputs(line, pgmFile);

  /*
   * PGM content
   */

  for (int i = 0; i < k; i++) {

    for (int j = 0; j < NB_FILMS; j++) {

      if (films[j]) {

        strcpy(line, "");
        strcpy(append, "");

        pxValue = (int) 255.0 * (5.0 - 1.0*searchMark(neighboors[i], j+1)) / 5.0;

        sprintf(append, "%d", pxValue);
        strcat(line, append);
        strcat(line, " ");

        fputs(line, pgmFile);

      }

    }

    fputs("\n", pgmFile);

  }

  /*
   * end
   */

  free(neighboors);
  fclose(pgmFile);

}