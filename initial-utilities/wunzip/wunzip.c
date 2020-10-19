#include <stdio.h>
#include <stdlib.h>
int main(int argc, char* argv[]) {
  if (argc == 1) {
    printf("wunzip: file1 [file2 ...]\n");
    exit(1);
  }
  FILE *fp = NULL;
  for (int i = 1; i < argc; i++) {
    if ((fp = fopen(argv[i], "r")) == NULL) {
      printf("wunzip: cannot open file\n");
      exit(1);
    }
    int count;
    char ch;
    while (fread(&count, 4, 1, fp) == 1) {
      if (fread(&ch, 1, 1, fp) == 1) {
        for (int j = 0; j < count; j++) {
          printf("%c", ch);
        }
      } else {
        printf("wunzip: file format mismatch\n");
        exit(1);
      }
    }
  }
  return 0;
}
