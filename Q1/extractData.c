/*
 * INCLUDES
 */

#include "../lib.h"

/*
 * FUNCTIONS
 */

/**
 * TODO
 */
void initializeFilms() {

  for (int i = 0; i < NB_FILMS; i++) {
    Films[i] = NULL;
  }

}

/**
 * TODO
 */
void initializeUsers() {

  for (int i = 0; i < NB_USERS; i++) {
    Users[i] = NULL;
  }

}

/**
 * TODO
 * @param filename
 */
void readData(char filename[T_MAX]) {

  /*
   * variables
   */

  FILE* file = NULL;
  char line[T_MAX] = "";
  char* token = NULL;

  int idFilm = 0;
  int idUser = 0;
  int markValue = 0;

  mark* createdMark = NULL;
  list* filmList = NULL;

  /*
   * TODO
   */
  
  file = fopen(filename, "r");

  if (file == NULL) {
    printf("[Daufilm] Error: File doesn't exist\n");
    exit(0);
  }

  while (fgets(line, T_MAX, file) != NULL) {

    if (strstr(line, ":")) {

      if (idFilm != 0) Films[idFilm-1] = filmList;
      token = strtok(line, " :\r\n\t");
      idFilm = atoi(token);
      filmList = initializeList();
  
    } else if (strstr(line, ",")) {

      token = strtok(line, " ,\r\n\t");
      idUser = atoi(token);
      token = strtok(NULL, " ,\r\n\t");
      markValue = atoi(token);

      createdMark = initializeMark(markValue, idFilm, idUser);
      filmList = addList(filmList, createdMark);

      if (Users[idUser-1] == NULL) {
        Users[idUser-1] = initializeList();
        Users[idUser-1]->head = createdMark;
      } else {
        Users[idUser-1] = addList(Users[idUser-1], createdMark);
      }

    }

    Films[idFilm-1] = filmList;
    
  }

  /*
   * end & return
   */

  fclose(file);

}

/**
 * TODO
 */
void createDataFile() {

  /*
   * variables
   */

  FILE* file = NULL;
  char line[T_MAX] = "";
  char append[T_MAX] = "";
  mark* currentMark = NULL;

  /*
   * open file
   */

  file = fopen("data.txt", "w");

  /*
   * output
   */

  for (int i = 0; i < NB_FILMS; i++) {

    strcpy(line, "");

    sprintf(append, "%d", (i+1));
    strcat(line, append);
    strcat(line, ":\n");
    fputs(line, file);

    currentMark = Films[i] != NULL ? Films[i]->head : NULL;

    while (currentMark != NULL) {

      strcpy(line, "");

      sprintf(append, "%d", currentMark->idUser);
      strcat(line, append);
      strcat(line, ",");

      sprintf(append, "%d", currentMark->markValue);
      strcat(line, append);
      strcat(line, ",\n");

      currentMark = currentMark->sameFilm;

      fputs(line, file);

    }

  }

  /*
   * end
   */

  fclose(file);

}