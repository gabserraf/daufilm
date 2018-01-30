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
  printf("- reco1 <user> <film>\n");
  printf("\t => predicts the mark that the given user would give to the given film \n");
  printf("- reco2 <user>\n");
  printf("\t => predicts the top 10 of the films the given user would rather see \n");
  printf("- reco3 <X>\n");
  printf("\t => take the file inputX.txt and predits all missing marks in the outputX.txt file \n");
  exit(0);

}

/**
 * TODO
 * @param argc
 * @param argv
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
 * @param argc
 * @param argv
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
  else throwError("user must be an integer");
  if (user > NB_USERS) throwError("user must lower than max");

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
 * @param argc
 * @param argv
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
  else throwError("user must be an integer");
  if (user > NB_USERS) throwError("user must lower than max");

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

/**
 * TODO
 * @param argc
 * @param argv
 */
void reco1(int argc, char* argv[]) {

  /*
   * variables
   */

  int user = 0;
  int film = 0;
  int show = 0;
  int rate = 0;

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
  else throwError("user must be an integer");
  if (user > NB_USERS) throwError("user must lower than max");

  /*
   * getting film
   */

  if (isNumber(argv[3])) film = atoi(argv[3]);
  else throwError("film must be an integer");
  if (film > NB_FILMS) throwError("film must lower than max");

  /*
   * getting show
   */

  if (argc >= 5 && strcmp(argv[4], "--show") == 0) show = 1;

  /*
   * computing recommandation 1 (prediction)
   */

  rate = predict(user, film);

  /*
   * showing result
   */

  if (show) {

    printf("=== RECOMMANDATION 1 ===\n");

    printf("The user %d may rate the film %d as : %d\n", user, film, rate);

    printf("=== END ===\n");

  }

}

/**
 * TODO
 * @param argc
 * @param argv
 */
void reco2(int argc, char* argv[]) {

  /*
   * variables
   */

  int user = 0;

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

  if (argc < 3) showHelp();

  /*
   * getting user
   */
   
  if (isNumber(argv[2])) user = atoi(argv[2]);
  else throwError("user must be an integer");
  if (user > NB_USERS) throwError("user must lower than max");

  /*
   * computing recommandation 2 (top 10)
   */

  printf("=== RECOMMANDATION 2 ===\n");

  top10(user);

  printf("=== END ===\n");

}

/**
 * TODO
 * @param argc
 * @param argv
 */
void reco3(int argc, char* argv[]) {

  /*
   * variables
   */

  int X = 0;

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

  if (argc < 3) showHelp();

  /*
   * getting user
   */
   
  if (isNumber(argv[2])) X = atoi(argv[2]);
  else throwError("X must be an integer");

  /*
   * computing recommandation 3 (file prediction)
   */

  filePrediction(X);

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

    // extractData command 
    if (strcmp(command, "extractData") == 0) extractData(argc, argv);

    // knn command 
    else if (strcmp(command, "knn") == 0) knn(argc, argv);

    // pgm command 
    else if (strcmp(command, "pgm") == 0) pgm(argc, argv);

    // recommandation 1 command (prediction) 
    else if (strcmp(command, "reco1") == 0) reco1(argc, argv);

    // recommandation 2 command (top 10)
    else if (strcmp(command, "reco2") == 0) reco2(argc, argv);

    // recommandation 3 command (file prediction)
    else if (strcmp(command, "reco3") == 0) reco3(argc, argv);

    // cross-validation command
    // else if (strcmp(command, "cv") == 0) cv(argc, argv);

    // help command 
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

  printf("Done in %.3f s\n", (double) (endTime - startTime)/CLOCKS_PER_SEC);

  return 0;

}