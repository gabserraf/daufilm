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
float centeredDotProduct(int* x, int* y) {

  /*
   * variables
   */

  int size = sizeof(x)/sizeof(int);
  float result = 0;
  float mean_x = mean(x);
  float mean_y = mean(y);

  /*
   * compute the dot product
   */

  for (int i = 0; i < size; i++) result += (x[i] - mean_x) * (y[i] - mean_y);

  /*
   * end & return
   */

  return result;

}

/**
 * TODO
 * @param x
 * @return
 */
float centeredNorm(int* x) {
  return sqrt(centeredDotProduct(x, x));
}

/**
 * TODO
 * @param x
 * @return
 */
float mean(int* x) {

  /*
   * variables
   */

  int size = sizeof(x)/sizeof(int);
  float result = 0;

  /*
   * compute mean
   */

  for (int i = 0; i < size; i++) result += x[i];
  result /= size;

  /*
   * end & result
   */

  return result;

}

/**
 * TODO
 * @galere remplacer 3 par mean
 */
float pearsonSimilarity(int* x, int* y) {
  return centeredDotProduct(x, y) / (centeredNorm(x) * centeredNorm(y));
}

/**
 * TODO
 * @param user1
 * @param user2
 */
float pearsonSimilarityBetweenUsers(int user1, int user2) {

  /*
   * variables
   */

  mark* currentMark1 = NULL;
  mark* currentMark2 = NULL;
  list* listUser1 = Users[user1-1];
  list* listUser2 = Users[user2-1];
  int* rxi = NULL;
  int* ryi = NULL;

  /*
   * find common films & save mark values
   */

  currentMark1 = listUser1->head;

  while (currentMark != NULL) {

    currentMark2 = listUser2->head;

    while (currentMark2 != NULL) {

      if (currentMark1->idFilm == currentMark2->idFilm) {

        *rxi = currentMark1->markValue;
        *ryi = currentMark1->markValue;

        rxi++;
        ryi++;

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
int hasAtLeastOneFilmInCommon(int user1, int user2) {

  /*
   * variables
   */

  mark* currentMark = NULL;
  list* listUser1 = Users[user1-1];
  list* listUser2 = Users[user2-1];

  /*
   * find at least a film in common
   */

  currentMark = listUser1->head;

  while (currentMark != NULL) {
    
    if (inList(listUser2, currentMark->idFilm)) return 1;
    currentMark = currentMark->sameUser;

  }

  /*
   * return 0 if there is no film in common
   */

  return 0;

}

/**
 * TODO
 * @param user
 * @param k
 * @param nearestNeighboors
 */
void kNearestNeighboors(int user, int k, int* nearestNeighboors) {

  /*
   * variables
   */

  float bestValues[k];
  int bestUsers[k];
  float pearsonSimilarityValue = 0;

  /*
   * initialze best values
   */

  for (int i = 0; i < k; i++) bestValues[i] = -1;

  /*
   * finding k nearest neighboors
   */

  for (int u = 1; u <= NB_USERS; u++) {

    if (hasAtLeastOneFilmInCommon(user, u) && user != u) {

      pearsonSimilarityValue = pearsonSimilarityBetweenUsers(user, u);

      for (int i = 0; i < k; i++) {

        if (pearsonSimilarityValue > bestValues[i]) {

          for (int j = k-1; j = i+1; j--) {
            bestValues[j] = bestValues[j-1];
            bestUsers[j] = bestUsers[j-1];
          }

          bestValues[i] = pearsonSimilarityValue;
          bestUsers[i] = u;

        }

      }

    }

  }

  /*
   * end
   */

  nearestNeighboors = bestUsers;

}

/* MAIN */

int main(int argc, char* argv[]) {
  return 0;
}