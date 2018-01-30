/*
 * INCLUDES
 */

#include "../lib.h"

/*
 * FUNCTIONS
 */

/**
 * TODO
 * @param user1
 * @param user2
 */
double similarityBetweenUsers(int user1, int user2) {

  /*
   * variables
   */

  mark* currentMark1 = NULL;
  mark* currentMark2 = NULL;

  list* listUser1 = Users[user1-1];
  list* listUser2 = Users[user2-1];

  double rx = 0.0;
  double ry = 0.0;
  double rxy = 0.0;

  /*
   * find common films & save mark values
   */

  /* creates a pointer to brows chaine list 2 */
  currentMark1 = listUser1 != NULL ? listUser1->head : NULL;

  while (currentMark1 != NULL) {

    /* update rx value */
    rx += (currentMark1->markValue - 2.9) * (currentMark1->markValue - 2.9);

    /* creates a pointer to brows chaine list 2 */
    currentMark2 = listUser2 != NULL ? listUser2->head : NULL;

    while (currentMark2 != NULL) {

      /* update rx value */
      ry += (currentMark2->markValue - 2.9) * (currentMark2->markValue - 2.9);

      /* update rxy value */
      if (currentMark1->idFilm == currentMark2->idFilm) rxy += (currentMark1->markValue - 2.9) * (currentMark2->markValue - 2.9);

      currentMark2 = currentMark2->sameUser;

    }

    currentMark1 = currentMark1->sameUser;

  }

  /*
   * compute & return pearson similarity
   */

  return rxy / (rx * ry) ;

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
  int usersAlreadyDone[NB_USERS];
  double bestValues[k];

  double similarityValue = 0.0;
  int minIndex = 0;
  int nbNeighboors = 0;

  list* filmsRatedbyUser = NULL;
  list* usersWhoRatedFilm = NULL;
  mark* currentMarkUser = NULL;
  mark* currentMarkFilm = NULL;

  /*
   * initialization
   */

  for (int i = 0; i < k; i++) bestValues[i] = -2.0;

  for (int i = 0; i < NB_USERS; i++) usersAlreadyDone[i] = 0;

  /*
   * finding the k nearest neighboors
   */

  // chained list of the films rated by the user 
  filmsRatedbyUser = Users[user-1];
  currentMarkUser = filmsRatedbyUser != NULL ? filmsRatedbyUser->head : NULL;

  while (currentMarkUser != NULL) {

    // for each film rated by the user, we define the chained list of users who has rated this film 
    usersWhoRatedFilm = Films[currentMarkUser->idFilm-1];
    currentMarkFilm = usersWhoRatedFilm != NULL ? usersWhoRatedFilm->head : NULL;

    while (currentMarkFilm != NULL) {
      
      if (!usersAlreadyDone[currentMarkFilm->idUser-1] && currentMarkFilm->idUser != user) {

        // updating the number of neighboors
        nbNeighboors++;

        // mark the user as already treated */
        usersAlreadyDone[currentMarkFilm->idUser-1] = 1;

        // compute the similarity value
        similarityValue = similarityBetweenUsers(user, currentMarkFilm->idUser);
        
        // finding the index of the minimum value of the list bestvalues
        minIndex = argmin(bestValues, k);

        if (similarityValue >= bestValues[minIndex]) {

          bestValues[minIndex] = similarityValue;
          bestUsers[minIndex] = currentMarkFilm->idUser;

        }

      }

      currentMarkFilm = currentMarkFilm->sameFilm;

    }

    currentMarkUser = currentMarkUser->sameUser;

  }

  /*
   * detect error
   */
  
  if (nbNeighboors < k) {
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

  return bestUsers;

}