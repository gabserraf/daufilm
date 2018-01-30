/*
 * INCLUDES
 */

#include "../lib.h"

/*
 * FUNCTIONS
 */

/**
 * TODO
 * @param x
 * @param y
 * @return
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

  currentMark1 = listUser1 != NULL ? listUser1->head : NULL;

  while (currentMark1 != NULL) {

    currentMark2 = listUser2 != NULL ? listUser2->head : NULL;

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

  /*
   * find the number of films in common
   */

  currentMark = listUser1 != NULL ? listUser1->head : NULL;

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
 * @return
 * @galere sizeof
 */
int* findNeighboors(int user) {

  /*
   * variables
   */

  int* neighboors = malloc(sizeof(int) * NB_USERS); // (max number of neighboors (NB_USERS-1) + array size (1))
  list* filmsRatedbyUser = NULL;
  list* usersWhoRatedFilm = NULL;
  mark* currentMarkUser = NULL;
  mark* currentMarkFilm = NULL;

  /*
   * find neighboors
   */

  neighboors[0] = 0;
  filmsRatedbyUser = Users[user-1];

  currentMarkUser = filmsRatedbyUser != NULL ? filmsRatedbyUser->head : NULL;

  while (currentMarkUser != NULL) {

    usersWhoRatedFilm = Films[currentMarkUser->idFilm-1];
    currentMarkFilm = usersWhoRatedFilm != NULL ? usersWhoRatedFilm->head : NULL;

    while (currentMarkFilm != NULL) {
      
      if (!inArray(neighboors, currentMarkFilm->idUser, neighboors[0]) && currentMarkFilm->idUser != user) {
        neighboors[0]++;
        neighboors[neighboors[0]] = currentMarkFilm->idUser;
      }

      currentMarkFilm = currentMarkFilm->sameFilm;

    }

    currentMarkUser = currentMarkUser->sameUser;

  }

  /*
   * end & return
   */

  return neighboors;

}

/**
 * TODO
 * @param user
 * @param k
 * @param nearestNeighboors
 * @galere sizeof
 */
int* kNearestNeighboors(int user, int k) {

  /*
   * variables
   */

  int* bestUsers = malloc(sizeof(int) * k);
  double bestValues[k];
  double pearsonSimilarityValue = 0.0;
  int minIndex = 0;
  int* neighboors = NULL;

  /*
   * initialization
   */

  for (int i = 0; i < k; i++) bestValues[i] = -2.0;

  /*
   * get all neighboors
   */

  neighboors = findNeighboors(user);

  /*
   * get all neighboors and all pearson values
   */

  for (int i = 1; i < neighboors[0]; i++) {

    pearsonSimilarityValue = pearsonSimilarityBetweenUsers(user, neighboors[i]);
    
    minIndex = argmin(bestValues, k);

    if (pearsonSimilarityValue >= bestValues[minIndex]) {

      bestValues[minIndex] = pearsonSimilarityValue;
      bestUsers[minIndex] = neighboors[i];

    }

  }

  /*
   * detect error
   */
  
  if (neighboors[0] < k) {
    free(neighboors);
    free(bestUsers);
    throwError("Number of neighboors higher than it can be");
  }

  /*
   * sort neighboors
   */

  bubbleSort(bestValues, bestUsers, k);

  /*
   * end & return
   */

  free(neighboors);
  return bestUsers;

}