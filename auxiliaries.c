/*
 * INCLUDES
 */

#include "lib.h"

/*
 * FUNCTIONS
 */

/**
 * TODO
 * @param msg
 */
void throwError(char msg[T_MAX]) {
  printf("[Daufilm] Error: %s", msg);
  exit(0);
}

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

  mark* head = l->head;

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

void displayMark(mark* m) {

  printf("Value=%d;\tidFilm=%d;\tidUser=%d\n", m->markValue, m->idFilm, m->idUser);

}