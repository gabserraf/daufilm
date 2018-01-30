/*
 * INCLUDES
 */

#include "lib.h"

/*
 * FUNCTIONS
 */

/**
 * TODO
 * @param film
 * @param user
 * @param k
 * @return
 */
int estimatedMark(int film, int user, int k) {

  /*
   * variables
   */

  int* neighboors = NULL;
  int neighboorMark = 0;
  double similarity = 0.0;
  double weightedMarks = 0.0;
  double totalSimilarity = 0.0;

  /*
   * get neighboors
   */

  neighboors = kNearestNeighboors(user, k);

  /*
   * compute estimate mark
   */

  for (int i = 0; i < k; i++) {

    neighboorMark = searchMark(neighboors[i], film);

    if (neighboorMark) {

      similarity = pearsonSimilarityBetweenUsers(user, neighboors[i]);
      weightedMarks += similarity * neighboorMark;
      totalSimilarity += similarity > 0 ? similarity : -1.0 * similarity;
      printf("%f %f\n ",similarity, totalSimilarity);

    }    

  }

  /*
   * end
   */

  free(neighboors);
  return round(weightedMarks/totalSimilarity);  

}

/**
 * TODO
 * @param X
 * @return
 */
int* mostPopularFilms(int X) {

  /*
   * variables
   */

  int* bestFilms = malloc(sizeof(int) * X);
  double bestValues[X];
  int minIndex = 0;
  double lenValue = 0;

  /*
   * initialization
   */

  for (int i = 0; i < X; i++) bestValues[i] = 0.0;

  /*
   * finding most popular films
   */

  for (int i = 0; i < NB_FILMS; i++) {

    lenValue = 1.0 * lenForFilm(Films[i]);
    
    minIndex = argmin(bestValues, X);

    if (lenValue >= bestValues[minIndex]) {

      bestValues[minIndex] = lenValue;
      bestFilms[minIndex] = i+1;

    }

  }

  /*
   * end
   */

  return bestFilms;

}

/**
 * TODO
 * @param film
 * @param user
 * @return
 */
int reco1(int film, int user) {

  /*
   * variables
   */

  int* neighboors = NULL;
  // int neighboor = 0;
  int nbNeighboors = 0;

  /*
   * compute number of neighboors
   */

  neighboors = findNeighboors(user);
  
  nbNeighboors = neighboors[0];


  /*
  
  while (neighboor != 0 && nbNeighboors < NB_USERS-1) {
    nbNeighboors++;
    neighboor = neighboors[0];
  }
  */
  /*
   * end & return
   */

  free(neighboors);
  return estimatedMark(film, user, round(sqrt(nbNeighboors)));

}

/**
 * TODO
 * @param user
 */
void reco2(int user) {

  /*
   * variables
   */

  double bestMarks[10];
  int bestFilms[10];
  double predictedMark = 0.0;
  int minIndex = 0;

  /*
   * initialization
   */

  for (int i = 0; i < 10; i++) bestMarks[i] = 0.0;

  /*
   * get all films and all estimated marks
   */

  for (int i = 0; i < NB_FILMS; i++) {

    if (searchMark(user, i+1) == 0) {
      
      predictedMark = reco1((i+1), user);
      
      minIndex = argmin(bestMarks, 10);

      if (predictedMark >= bestMarks[minIndex]) {

        bestMarks[minIndex] = predictedMark;
        bestFilms[minIndex] = i+1;

      }

    }

  }

  /*
   * sort neighboors
   */

  bubbleSort(bestMarks, bestFilms, 10);

  /*
   * end & display
   */

  printf("RECOMMANDATION :\n");
  for (int i = 0; i < 10; i++) printf("Film n°%d : %d;\tMark=%d\n", (i+1), bestFilms[i], (int) bestMarks[i]);

}

/**
 * TODO
 * @param X
 */
void reco3(int X) {
  
  /*
   * variables
   */

  FILE* inputFile = NULL;
  FILE* outputFile = NULL;
  char inputName[T_MAX] = "";
  char outputName[T_MAX] = "";
  char inputLine[T_MAX] = "";
  char outputLine[T_MAX] = "";
  char numberX[T_MAX] = "";

  int idFilm = 0;
  int idUser = 0;
  char predictedMark[T_MAX] = "";
  char* token = NULL;

  /*
   * names
   */
  
  sprintf(numberX, "%d", X);

  strcat(inputName, "input");
  strcat(inputName, numberX);
  strcat(inputName, ".txt");

  strcat(outputName, "output");
  strcat(outputName, numberX);
  strcat(outputName, ".txt");

  /*
   * open files
   */

  inputFile = fopen(inputName, "r");
  outputFile = fopen(outputName, "w");

  /*
   * read & edit films
   */

  if (inputFile == NULL) throwError("File does not exist");

  while (fgets(inputLine, T_MAX, inputFile) != NULL) {

    if (strstr(inputLine, ":")) {

      token = strtok(inputLine, " :\r\t\n");
      idFilm = atoi(token);
      strcpy(outputLine, inputLine);

    } else {

      token = strtok(inputLine, " \r\t\n");
      idUser = atoi(token);

      strcpy(outputLine, "");

      strcat(outputLine, token);
      strcat(outputLine, ",");

      sprintf(predictedMark, "%d", reco1(idFilm, idUser));
      strcat(outputLine, predictedMark);

      strcat(outputLine, "\n");

    }

    fputs(outputLine, outputFile);

  }

  /*
   * end
   */

  fclose(inputFile);
  fclose(outputFile);

}

/* MAIN */
/*
int main(int argc, char* argv[]) {

  initializeUsers();
  initializeFilms();

  for (int i = 1; i < argc; i++) readData(argv[i]);

  int* films = mostPopularFilms(20);

  for (int i = 0; i < 20; i++) printf("Film n°%d : %d\n", i+1, films[i]);
  
  free(films);

  freeMemory();

  return 0;

}
*/