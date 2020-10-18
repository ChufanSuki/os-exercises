#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
  if (argc == 1) {
    printf("wgrep: searchterm [file ...]\n");
    exit(1);
  }
  char* pattern = argv[1];
  char* line = NULL;
  size_t len = 0;
  int nread;
  if (argc == 2) {
    while ((nread = getline(&line, &len, stdin)) != -1) {
      if (strstr(line, pattern) != NULL) {
        printf("%s", line);
      }
    }
  } else {
    int i = 2;
    for (; i < argc; i++) {
      FILE* fp = fopen(argv[i], "r");
      if (fp == NULL) {
        printf("wgrep: cannot open file\n");
        exit(1);
      }
      while ((nread = getline(&line, &len, fp)) != -1) {
        if (strstr(line, pattern) != NULL) {
          printf("%s", line);
        }
      }
      fclose(fp);
    }
  }
  free(line);
  return 0;
}
