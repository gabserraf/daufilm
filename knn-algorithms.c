/*
 * INCLUDES
 */

#include "lib.h"

/*
 * FUNCTIONS
 */

/**
 * TODO
 * @param x
 * @param y
 * @return
 * @galere changer mean par 3 si jamais
 */
double centeredDotProduct(int* x, int* y) {

  /*
   * variables
   */

  int size = sizeof(x)/sizeof(int);
  double result = 0;

  /*
   * compute the dot product
   */

  for (int i = 0; i < size; i++) result += 1.0 * (x[i] - 3) * (y[i] - 3);

  /*
   * end & return
   */

  return result;

}

/*.0*
 * TODO
 * @param x
 * @return
 */
double centeredNorm(int* x) {
  return sqrt(1.0 * centeredDotProduct(x, x));
}

/**
 * TODO
 * @galere remplacer 3 par mean
 */
double pearsonSimilarity(int* x, int* y) {
  return 1.0 * centeredDotProduct(x, y) / (centeredNorm(x) * centeredNorm(y));
}

/**
 * TODO
 * @param user1
 * @param user2
 */
double pearsonSimilarityBetweenUsers(int user1, int user2) {

  /*
   * variables
   */

  mark* currentMark1 = NULL;
  mark* currentMark2 = NULL;
  list* listUser1 = Users[user1-1];
  list* listUser2 = Users[user2-1];
  int n = numberOfFilmsInCommon(user1, user2);
  int counter = 0;
  int rxi[n];
  int ryi[n];

  /*
   * find common films & save mark values
   */

  currentMark1 = listUser1->head;

  while (currentMark1 != NULL) {

    currentMark2 = listUser2->head;

    while (currentMark2 != NULL) {

      if (currentMark1->idFilm == currentMark2->idFilm) {

        rxi[counter] = currentMark1->markValue;
        ryi[counter] = currentMark2->markValue;
        counter++;

      }

      currentMark2 = currentMark2->sameUser;

    }

    currentMark1 = currentMark1->sameUser;

  }

  /*
   * compute & return pearson similarity
   */

  return pearsonSimilarity(rxi, ryi);

}

/**
 * TODO
 * @param user1
 * @param user2
 * @return
 */
int numberOfFilmsInCommon(int user1, int user2) {

  /*
   * variables
   */

  mark* currentMark = NULL;
  list* listUser1 = Users[user1-1];
  list* listUser2 = Users[user2-1];
  int result = 0;

  if (listUser1 == NULL || listUser2 == NULL) return 0;

  /*
   * find the number of films in common
   */

  currentMark = listUser1->head;

  while (currentMark != NULL) {
    
    if (inList(listUser2, currentMark->idFilm)) result++;
    currentMark = currentMark->sameUser;

  }

  /*
   * return
   */

  return result;

}

/**
 * TODO
 * @param user
 * @param k
 * @param nearestNeighboors
 */
int* kNearestNeighboors(int user, int k) {

  /*
   * variables
   */

  int* bestUsers = malloc(sizeof(int) * k);
  double bestValues[k];
  double pearsonSimilarityValue = 0.0;
  int minIndex = 0;
  int counter = 0; 

  /*
   * initialization
   */

  for (int i = 0; i < k; i++) bestValues[i] = -2.0;

  /*
   * get all users and all pearson values
   */

  for (int u = 1; u <= NB_USERS; u++) {

    if (numberOfFilmsInCommon(user, u) != 0 && user != u) {

      counter++;

      pearsonSimilarityValue = pearsonSimilarityBetweenUsers(user, u);
      
      minIndex = argmin(bestValues, k);

      if (pearsonSimilarityValue >= bestValues[minIndex]) {

        bestValues[minIndex] = pearsonSimilarityValue;
        bestUsers[minIndex] = u;

      }

    }

  }

  /*
   * detect error
   */

  if (counter < k) {
    throwError("Number of neighboors higher than it can be");
  }

  /*
   * sort neighboors (using bubble sort)
   */

  double tmpValue = 0.0;
  int tmpUser = 0;
  int size = k;
  int sorted = 0;

  while (!sorted) {

    sorted = 1;

    for (int i = 0; i < size-1; i++) {

      if (bestValues[i] < bestValues[i+1]) {
        
        tmpValue = bestValues[i];
        bestValues[i] = bestValues[i+1];
        bestValues[i+1] = tmpValue;

        tmpUser = bestUsers[i];
        bestUsers[i] = bestUsers[i+1];
        bestUsers[i+1] = tmpUser;

        sorted = 0;

      }

    }

    size--;

  }

  /*
   * end & return
   */

  return bestUsers;

}

/* MAIN */

/*
int main(int argc, char* argv[]) {

  initializeUsers();
  initializeFilms();

  for (int i = 1; i < argc; i++) readData(argv[i]);

  int* nearestNeighboors = kNearestNeighboors(7, 7);

  for (int i = 0; i < 7; i++) {
    printf("%d\n", nearestNeighboors[i]);
  }

  free(nearestNeighboors);
  freeMemory();

  return 0;

}
*/