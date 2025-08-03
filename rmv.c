#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  // Check for number of arguments 
  // No more than 2 for the first iteration
  if (argc != 2) {
    fprintf(stderr, "usage: %s <file>\n", argv[0]);
    return EXIT_FAILURE;
  }
 
  // file removal attempt
  if (remove(argv[1]) != 0) {
    perror(argv[1]);
    return EXIT_FAILURE;
  } 

  // success message
  printf("File %s successfully removed", argv[1]);
  
  // successful execution
  return EXIT_SUCCESS;
}
