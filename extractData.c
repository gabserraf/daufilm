/*
 * INCLUDES
 */

#include "lib.h"

void initializeFilms() {

  for (int i = 0; i < NB_FILMS; i++) {
    Films[i] = NULL;
  }

}

void initializeUsers() {

  for (int i = 0; i < NB_USERS; i++) {
    Users[i] = NULL;
  }

}

void readData(char filename[T_MAX]) {

  /*
   * variables
   */

  FILE* file = NULL;
  char* line = NULL;
  size_t len = 0;
  ssize_t read = 0;
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

  if (file == NULL) throwError("File doesn't exist");

  while ((read = getline(&line, &len, file)) != -1) {
    
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

void freeMemory() {

  for (int i = 0; i < NB_FILMS; i++) {
    
    if (Films[i] != NULL) {

      mark* currentMark = Films[i]->head;
      mark* nextMark = NULL;

      if (currentMark != NULL) {
        nextMark = currentMark->sameFilm;
        free(currentMark);
        currentMark = NULL;
      }

      while (nextMark != NULL) {
        free(currentMark);
        currentMark = nextMark;
        nextMark = nextMark->sameFilm;
      }

      free(Films[i]);
      Films[i] = NULL;

    }

  }

  for (int i = 0; i < NB_USERS; i++) {
    
    if (Users[i] != NULL) {

      free(Users[i]);
      Users[i] = NULL;

    }

  }

}


/* MAIN */

int main(int argc, char* argv[]) {
  
  initializeFilms();
  initializeUsers();
  readData("testFile.txt");
  displayFilms();
  displayUsers();

  return 0;

}