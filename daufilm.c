/*
 * INCLUDES
 */

#include "lib.h"

/*
 * CLUI (Command Line User Interface)
 */

/**
 * TODO
 */
void showHelp() {

  printf("||-------------------------------------------||\n");
  printf("||                                           ||\n");
  printf("|| DAUFILM - The netflix recommandation CLUI ||\n");
  printf("||                                           ||\n");
  printf("||-------------------------------------------||\n");
  printf("\n");
  printf("USAGE :\n");
  printf("- extractData <fileName1.txt> [<fileName2.txt>] ... [<fileNameN.txt>]\n");
  printf("\t => allows to extract data from files and combine them in variables\n");
  printf("\t => creates a data.txt file where data are combined\n");
  printf("- knn <user> <k>\n");
  printf("\t => allows to find the k nearest neighboors of the given user\n");
  printf("- pgm <user> <k>\n");
  printf("\t => allows to create a .pgm file which shows the similarity matrix between the given user and its k nearest neighboors\n");
  exit(0);

}

/**
 * TODO
 * @params argc
 * @params argv
 */
void extractData(int argc, char* argv[]) {

  /*
   * variables
   */

  int show = 0;

  /*
   * initilization
   */

  initializeUsers();
  initializeFilms();

  /*
   * reading data
   */

  for (int i = 2; i < argc; i++) {
    if (strcmp(argv[i], "--showh") == 0) show = 1;
    else readData(argv[i]);
  }

  /*
   * showing data
   */

  if (show) {
    
    printf("=== DATA ===\n");

    displayFilms();

    printf("=== END ===\n");

  }

  /*
   * output file
   */

  createDataFile();

}

/**
 * TODO
 * @params argc
 * @params argv
 */
void knn(int argc, char* argv[]) {

  /*
   * variables
   */

  int* neighboors = NULL;
  int user = 0;
  int k = 0;
  int show = 0;

  /*
   * initialization
   */

  initializeUsers();
  initializeFilms();

  /*
   * reading data
   */

  readData("data.txt");

  /*
   * lake of arguments --> error 
   */

  if (argc < 4) showHelp();

  /*
   * getting user
   */

  if (isNumber(argv[2])) user = atoi(argv[2]);
  else throwError("User must be an integer");
  if (user > NB_USERS) throwError("User must lower than max");

  /*
   * getting k
   */

  if (isNumber(argv[3])) k = atoi(argv[3]);
  else throwError("k must be an integer");

  /*
   * getting show
   */

  if (argc >= 5 && strcmp(argv[4], "--show") == 0) show = 1;

  /*
   * knn algorithm
   */

  neighboors = kNearestNeighboors(user, k);

  /*
   * showing nearest neighboors
   */

  if (show) {

    printf("=== NEAREST NEIGHBOORS ===\n");

    for (int i = 0; i < k; i++) printf("Neighboor n°%d : %d\n", (i+1), neighboors[i]);

    printf("=== END ===\n");

  }

  /*
   * end
   */

  free(neighboors);

}

/**
 * TODO
 * @params argc
 * @params argv
 */
void pgm(int argc, char* argv[]) {

  /*
   * variables
   */

  int user = 0;
  int k = 0;

  /*
   * initialization
   */

  initializeUsers();
  initializeFilms();

  /*
   * reading data
   */

  readData("data.txt");

  /*
   * lake of arguments --> error 
   */

  if (argc < 4) showHelp();

  /*
   * getting user
   */

  if (isNumber(argv[2])) user = atoi(argv[2]);
  else throwError("User must be an integer");
  if (user > NB_USERS) throwError("User must lower than max");

  /*
   * getting k
   */

  if (isNumber(argv[3])) k = atoi(argv[3]);
  else throwError("k must be an integer");

  /*
   * creating pgmFile
   */

  createPGM(user, k);

}

/* MAIN */

int main(int argc, char* argv[]) {

  /*
   * variables
   */

  char command[T_MAX] = "";
  clock_t startTime, endTime;

  /*
   * starting timer
   */

  startTime = clock();

  /*
   * compute main func
   */

  if (argc < 2) {
    
    showHelp();

  } else {

    strcpy(command, argv[1]);

    /* extractData command */
    
    if (strcmp(command, "extractData") == 0) extractData(argc, argv);

    /* knn command */

    else if (strcmp(command, "knn") == 0) knn(argc, argv);

    /* pgm command */

    else if (strcmp(command, "pgm") == 0) pgm(argc, argv);

    /* recommandation command */

    // else if (strcmp(command, "recommandation") == 0) pgm(argc, argv);

    /* help command */

    else showHelp();

  }

  /*
   * free all mem alloc
   */

  freeMemory();

  /*
   * ending timer
   */

  endTime = clock();

  /*
   * end
   */

  printf("Done in %f s\n", (double) (endTime - startTime)/CLOCKS_PER_SEC);

  return 0;

}