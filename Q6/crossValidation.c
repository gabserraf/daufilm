/*
 * INCLUDES
 */

#include "../lib.h"

/*
 * FUNCTIONS
 */

/**
 * TODO
 * @param predictedValues
 * @param trueValues
 * @return
 */
double RMSE(int* predictedValues, int* trueValues, int size) {

  /*
   * variables
   */

  double R = 0.0;

  /*
   * compute RMSE
   */

  for (int i = 0; i < size; i++) {
    printf("%d %d\n", predictedValues[i], trueValues[i]);
    R += (predictedValues[i] - trueValues[i]) * (predictedValues[i] - trueValues[i]);
  }

  /*
   * end & return
   */

  return sqrt(R/size);

}

/**
 * TODO
 * @param perc
 * @return
 */
double crossValidation(double perc) {

  /*
   * variables
   */

  int size = perc*getNumberMarks();

  int films_test[size];
  int users_test[size];
  int marks_test[size];
  int predicted[size];

  mark* currentMark = NULL;
  int counter = 0;
  int i = 0;

  /*
   * compute test train
   */

  while (i < NB_FILMS && counter < size) {

    currentMark = Films[i] != NULL ? Films[i]->head : NULL;

    while (currentMark != NULL && counter < size) {

      films_test[counter] = currentMark->idFilm;
      users_test[counter] = currentMark->idUser;
      marks_test[counter] = currentMark->markValue;

      counter++;
      // printf("%d\n", counter);

      currentMark->markValue = 0;

      currentMark = currentMark->sameFilm;

    }

    i++;

  }

  /*
   * predict marks
   */

  for (int i = 0; i < size; i++) {
    predicted[i] = reco1(films_test[i], users_test[i]);

  }

  /*
   * compute RMSE & return
   */

  return RMSE(predicted, marks_test, size);

}

/* MAIN */

int main(int argc, char* argv[]) {

  initializeUsers();
  initializeFilms();

  for (int i = 1; i < argc; i++) readData(argv[i]);

  printf("%f\n", crossValidation(0.1));
  
  freeMemory();

  return 0;

}