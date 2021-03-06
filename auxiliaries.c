/*
 * INCLUDES
 */

#include "lib.h"

/*
 * INITIALIZATION
 */

/**
 * TODO
 * @param markValue
 * @param idFilm
 * @param idUser
 * @return 
 */
mark* initializeMark(int markValue, int idFilm, int idUser) {
  
  mark* new_mark = malloc(sizeof(mark));

  if (new_mark == NULL) throwError("Malloc error");

  new_mark->markValue = markValue;
  new_mark->idFilm = idFilm;
  new_mark->idUser = idUser;
  new_mark->sameFilm = NULL;
  new_mark->sameUser = NULL;

  return new_mark;

}

/**
 * TODO
 * @return
 */
list* initializeList() {

  list* new_list = malloc(sizeof(list));
  
  if (new_list == NULL) throwError("Malloc error");

  new_list->head = NULL;

  return new_list;

}

/*
 * CHAINE LIST FUNCTIONS
 */

/**
 * TODO
 * @param m1
 * @param m2
 * @return
 */
mark* findSimilarity(mark* m1, mark* m2) {

  if (m2 == NULL || m1->idFilm == m2->idFilm || m1->idUser == m2->idUser) {
    return m2;
  }

  mark* m3 = findSimilarity(m1, m2->sameFilm);
  if (m3 != NULL) return m3;

  mark* m4 = findSimilarity(m1, m2->sameUser);
  if (m4 != NULL) return m4;

  return NULL;

}

/**
 * TODO
 * @param l
 * @param m
 * @return
 */
list* addList(list* l, mark* m) {

  mark* head = l != NULL ? l->head : NULL;

  if (head == NULL) {

    l->head = m;

  } else {

    mark* m1 = findSimilarity(m, head);

    if (m1 == NULL) return l;

    if (m1->idFilm == m->idFilm) {
      while (m1->sameFilm != NULL) m1 = m1->sameFilm;
      m1->sameFilm = m;
    } else {
      while (m1->sameUser != NULL) m1 = m1->sameUser;
      m1->sameUser = m;
    }

  }

  return l;

}

/**
 * TODO
 * @param haystack
 * @param needle
 * @return
 */
int inList(list* haystack, int needle) {

  /*
   * variables
   */

  mark* currentMark = NULL;

  /*
   * find needle in a haystack
   */

  currentMark = haystack != NULL ? haystack->head : NULL;

  while (currentMark != NULL) {
    if (currentMark->idFilm == needle) return 1;
    currentMark = currentMark->sameUser;
  }

  /*
   * return 0 if not found
   */

  return 0;

}

/**
 * computes and return the size of a chained list
 * @param l, the list
 * @return the size of a chained list
 */
int lenForUser(list* l) {

  /*
   * variables
   */

  mark* currentMark = NULL;
  int size = 0;

  /*
   * compute size
   */

  currentMark = l != NULL ? l->head : NULL;

  while (currentMark != NULL) {
    size++;
    currentMark = currentMark->sameUser;
  }

  /*
   * end & return
   */

  return size;

}

/**
 * computes and return the size of a chained list
 * @param l, the list
 * @return the size of a chained list
 */
int lenForFilm(list* l) {

  /*
   * variables
   */

  mark* currentMark = NULL;
  int size = 0;

  /*
   * compute size
   */

  currentMark = l != NULL ? l->head : NULL;

  while (currentMark != NULL) {
    size++;
    currentMark = currentMark->sameFilm;
  }

  /*
   * end & return
   */

  return size;

}

/**
 * TODO
 * @param user
 * @param film
 * @return
 */
int searchMark(int user, int film) {

  mark* currentMark = Users[user-1] != NULL ? Users[user-1]->head : NULL;

  while (currentMark != NULL) {
    
    if (currentMark->idFilm == film) return currentMark->markValue;
    currentMark = currentMark->sameUser;
    
  }

  return 0;

}

/*
 * ARRAY FUNCTIONS
 */

/**
 * TODO
 * @param haystack
 * @param needle
 * @return
 */
int inArray(int* haystack, int needle, int size) {

  if (haystack == NULL) return 0;

  for (int i = 0; i < size; i++) {
    if (haystack[i] == needle) return 1;
  }

  return 0;

}

/**
 * TODO
 * @param l
 * @return
 */
int argmin(double l[], int size) {

  int index = 0;

  for (int i = 0; i < size; i++) {
    if (l[i] <= l[index]) index = i;
  }

  return index;

}

/**
 * TODO
 */
void bubbleSort(double* values, int* objects, int size) {
  
  /*
   * variables
   */

  double tmpValue = 0.0;
  int tmpObject = 0;
  int sorted = 0;

  /*
   * sorting algorithm
   */

  while (!sorted) {

    sorted = 1;

    for (int i = 0; i < size-1; i++) {

      if (values[i] < values[i+1]) {
        
        tmpValue = values[i];
        values[i] = values[i+1];
        values[i+1] = tmpValue;

        tmpObject = objects[i];
        objects[i] = objects[i+1];
        objects[i+1] = tmpObject;

        sorted = 0;

      }

    }

    size--;

  }

}

/*
 * DISPLAY FUNCTIONS
 */

/**
 * TODO
 */
void displayFilms() {
  
  printf("Films list : \n");

  for (int i = 0; i < NB_FILMS; i++) {
    
    printf("idFilm = %d\n", i+1);

    if (Films[i] != NULL) {

      mark* m = Films[i]->head;
      
      while (m != NULL) {
        printf("Note=%d;\tidUser=%d\n", m->markValue, m->idUser);
        m = m->sameFilm;
      }

    }

  }
  
}

/**
 * TODO
 */
void displayUsers() {
  
  printf("Users list : \n");

  for (int i = 0; i < NB_USERS; i++) {
    
    printf("idUser = %d\n", i+1);

    if (Users[i] != NULL) {
      
      mark* m = Users[i]->head;
      
      while (m != NULL) {
        printf("Note=%d;\tidFilm=%d\n", m->markValue, m->idFilm);
        m = m->sameUser;
      }

    }

  }

}

/**
 * TODO
 * @param m
 */
void displayMark(mark* m) {

  if (m != NULL) printf("Value=%d;\tidFilm=%d;\tidUser=%d\n", m->markValue, m->idFilm, m->idUser);

}

/*
 * OTHER
 */

/**
 * TODO
 * @param msg
 */
void throwError(char msg[T_MAX]) {
  
  printf("[Daufilm] Error: %s\n", msg);
  freeMemory();
  exit(0);

}

/**
 * TODO
 * @param chr
 * @return
 */
int isNumber(char* chr) {

  for (int i = 0; i < strlen(chr); i++) {
    if (!isdigit(chr[i])) return 0;
  }

  return 1;

}

/**
 * TODO
 * @return
 */
int getNumberMarks() {

  /*
   * variables
   */

  mark* currentMark = NULL;
  int nbMarks = 0;

  /*
   * compute nb marks
   */

  for (int i = 0; i < NB_FILMS; i++) {

    currentMark = Films[i] != NULL ? Films[i]->head : NULL;

    while (currentMark != NULL) {
      nbMarks++;
      currentMark = currentMark->sameFilm;
    }

  }

  /* 
   * end & return
   */

  return nbMarks;

}

/**
 * free all memory allocations
 * @galere compter les frees/allocs (printf, &line)
 */
void freeMemory() {

  /*
   * variables
   */

  mark* currentMark = NULL;
  mark* nextMark = NULL;

  /*
   * free the marks
   */

  for (int i = 0; i < NB_FILMS; i++) {
    
    if (Films[i] != NULL) {

      currentMark = Films[i]->head;

      while (currentMark != NULL) {

        nextMark = currentMark->sameFilm;
        free(currentMark);
        currentMark = nextMark;

      }
      
    }

  }

  /*
   * free the Films lists
   */

  for (int i = 0; i < NB_FILMS; i++) {
    
    if (Films[i] != NULL) {

      free(Films[i]);
      Films[i] = NULL;
      
    }

  }

  /*
   * free the Users lists
   */
  
  for (int i = 0; i < NB_USERS; i++) {
    
    if (Users[i] != NULL) {

      free(Users[i]);
      Users[i] = NULL;

    }

  }

}