#include <stdio.h>
#include <stdlib.h>
#include <getopt.h> // for getopt_long()
#include <ctype.h> // for tolower()
#include <stdbool.h>
#include <string.h> // strcspn(), strchr()

void to_lower(char *str) {
  for (int i = 0; str[i]; i++) {
    str[i] = tolower(str[i]);
  }
}

bool prompt_ans(const char *file_name) {
  // Assign a buffer for user input
  char buf[8];

  // while loop; re-prompting till valid
  while (1) {
    printf("trashman: remove file '%s'? [y/N] ", file_name); 
    fflush(stdout);

    if (fgets(buf, sizeof(buf), stdin) == NULL) {
      printf("\n");
      return false;
    }

    // Handle potential buffer overflow
    if (strchr(buf, '\n') == NULL) {
      int c;
      while ((c = getchar()) != '\n' && c != EOF);
    }

    buf[strcspn(buf, "\n")] = '\0';
    to_lower(buf);

    if (buf[0] == 'y') return true;
    if (buf[0] == 'n') return false;
    printf("Invalid input. Please enter 'y' or 'n'.\n");
 }
}

void show_help(const char* prog_name) {
  printf("Usage: %s [OPTIONS] <file1> [<file2> ...]\n"
         "Remove files with optional confirmation and verbose output.\n\n"
         "Options:\n"
         "  -h, --help         Show this help message and exit\n"
         "  -v, --verbose      Show detailed operation output\n"
         "  -i, --interactive  Prompt before each deletion\n\n"
         "Examples:\n"
         "  %s file.txt            # Silent deletion\n"
         "  %s -vi *.log          # Interactive verbose mode\n",
           prog_name, prog_name, prog_name);
  exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[]) {
  int exit_status = EXIT_SUCCESS;
  int verbose = 0; // Verbose logic indicator 
  int interactive = 0;
  
  struct option long_opts[] = {
    {"verbose", no_argument, 0, 'v'},
    {"interactive", no_argument, 0, 'i'},
    {"help", no_argument, 0, 'h'},
    {0, 0, 0, 0}
  };

  int opt;
  while ((opt = getopt_long(argc, argv, "hvi", long_opts, NULL)) != -1) {
    switch (opt) {
      case 'v':
        verbose = 1;
        break;
      case 'i': 
        interactive = 1;
        break;
      case 'h':
        show_help(argv[0]);
        break;
      case '?':
        if (optopt)
          fprintf(stderr, "Unknown option -%c\n", optopt);
        else
          fprintf(stderr, "Unknown option -%s\n", argv[optind-1]);
        fprintf(stderr, "Try '%s --help' for more information.\n", argv[0]);
        exit(EXIT_FAILURE);
    }
  }
  

  if (optind >= argc) {
    fprintf(stderr, "Error: No files specified.\n");
    fprintf(stderr, "Try: '%s --help' for usage information.\n", argv[0]);
    return EXIT_FAILURE;
  }
 
  for (int i = optind; i < argc; i++) {
    const char *file_name = argv[i];

    if (file_name[0] == '\0') {
      fprintf(stderr, "Error: Empty filename provided.\n");
      exit_status = EXIT_FAILURE;
      continue;
    }

    if (interactive && !prompt_ans(file_name)) {
      continue; // skip current iteration
    }

    if (remove(file_name) != 0) {
      perror(file_name);
      exit_status = EXIT_FAILURE;
    } else if (verbose) {
      printf("Removed '%s'.\n", file_name);
    }
  }
 
  return exit_status;
}
