#include <stdio.h>
#include <stdlib.h>
#include <getopt.h> // for getopt_long()

int main(int argc, char *argv[]) {
  int exit_status = EXIT_SUCCESS;
  int verbose = 0; // Verbose logic indicator 
  
  struct option long_opts[] = {
    {"verbose", no_argument, 0, 'v'},
    {0, 0, 0, 0}
  };

  int opt;
  while ((opt = getopt_long(argc, argv, "v", long_opts, NULL)) != -1) {
    switch (opt) {
      case 'v':
        verbose = 1;
        break;
      case '?':
        if (optopt)
          fprintf(stderr, "Unknown option -%c\n", optopt);
        else
          fprintf(stderr, "Unknown option -%s\n", argv[optind-1]);
        exit(EXIT_FAILURE);
    }
  }
  

  if (optind >= argc) {
    fprintf(stderr, "Error: No files specified.\n");
    fprintf(stderr, "usage: %s [-v|--verbose] <file1> [<file2> ...]\n", argv[0]);
    return EXIT_FAILURE;
  }
 
  for (int i = optind; i < argc; i++) {
    const char *file_name = argv[i];
    if (remove(file_name) != 0) {
      perror(file_name);
      exit_status = EXIT_FAILURE;
    } else if (verbose) {
      printf("Remove '%s' successfully.\n", file_name);
    }
  }
 
  return exit_status;
}
