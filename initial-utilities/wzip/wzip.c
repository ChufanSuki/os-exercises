#include <stdio.h>
#include <stdlib.h>
int main(int argc, char* argv[]) {
  if (argc == 1) {
    printf("wzip: file1 [file2 ...]\n");
    exit(1);
  }
  ssize_t nread;
  for (int i = 1; i < argc; i++) {
    FILE* fp = NULL;
    if ((fp = fopen(argv[i], "r")) == NULL) {
      printf("wzip: cannot open file\n");
      exit(1);
    }
    fclose(fp);
  }
  return 0;
}
