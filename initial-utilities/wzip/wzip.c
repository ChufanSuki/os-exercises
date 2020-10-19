#include <stdio.h>
#include <stdlib.h>
int main(int argc, char* argv[]) {
  if (argc == 1) {
    printf("wzip: file1 [file2 ...]\n");
    exit(1);
  }
  int count = 1;
  int curr = '\0';
  int last = '\0';
  for (int i = 1; i < argc; i++) {
    FILE* fp = NULL;
    if ((fp = fopen(argv[i], "r")) == NULL) {
      printf("wzip: cannot open file\n");
      exit(1);
    }
    if (last == '\0') {
      last = getc(fp);
    }
    while ((curr = getc(fp)) != EOF) {
      if (curr == last) {
        count++;
      } else {
        fwrite(&count, 4, 1, stdout);
        fwrite(&last, 1, 1, stdout);
        count = 1;
        last = curr;
      }
    }
    if (argc - 1== i) {
      fwrite(&count, 4, 1, stdout);
      fwrite(&last, 1, 1, stdout);
      count = 1;
    }

    fclose(fp);
  }
  return 0;
}
