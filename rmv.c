#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  // if +1 files failed, set status to 1 to indicate failure.
  int exit_status = EXIT_SUCCESS;

  // 1. Check at least 2 arguments are present
  if (argc < 2) {
    fprintf(stderr, "usage: %s <file1> [<file2>, ...]\n", argv[0]);
    return EXIT_FAILURE;
  }
 
  // 2. Loop through argc, remove files, and handle errors 
  for (int i = 1; i < argc; i++) {
    const char *file_name = argv[i];
    if (remove(file_name) != 0) {
      perror(file_name);
      exit_status = 1;
    } else {
      printf("File '%s' successfully removed.\n", file_name);
    }
  }
 
  // 3. Return success status
  return exit_status;
}
