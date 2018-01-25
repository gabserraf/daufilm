/*
 * INCLUDES
 */

#include "lib.h"

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
  int* neighboors = NULL;
  int films[NB_FILMS];
  mark* currentMark = NULL;
  char line[T_MAX] = "";
  char append[T_MAX] = "";
  double pxValue = 0;
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
    
    currentMark = Users[neighboors[i]-1]->head;

    while (currentMark != NULL) {
      if (!films[currentMark->idFilm-1]) nbFilms++;
      films[currentMark->idFilm-1] = 1;
      currentMark = currentMark->sameUser;
    }

  }

  /*
   * create PGM
   */

  pgmFile = fopen("pgmView.pgm", "w");

  strcpy(line, "P2\r\n");
  fputs(line, pgmFile);

  strcpy(line, "");
  sprintf(append, "%d", nbFilms);
  strcat(line, append);
  strcat(line, " ");
  sprintf(append, "%d", k);
  strcat(line, append);
  strcat(line, " \n\r");
  fputs(line, pgmFile);

  for (int i = 0; i < k; i++) {

    strcpy(line, "");

    for (int j = 0; j < NB_FILMS; j++) {

      if (films[j]) {

        pxValue = 1.0 - 1.0*searchMark(neighboors[i], j+1) / 5;        

        sprintf(append, "%f", pxValue);
        strcat(line, append);
        strcat(line, " ");

      }

    }

    strcat(line, "\n\r");

    fputs(line, pgmFile);

  }

  /*
   * end
   */

  free(neighboors);
  fclose(pgmFile);

}

/* MAIN */

int main(int argc, char* argv[]) {

  initializeUsers();
  initializeFilms();

  for (int i = 1; i < argc; i++) readData(argv[i]);

  createPGM(7, 7);

  freeMemory();

  return 0;

}