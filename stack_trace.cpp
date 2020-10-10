#include <execinfo.h>
#include <stdio.h>
#include <stdlib.h>
#include <cxxabi.h>

/* Obtain a backtrace and print it to stdout. */
void
print_trace (void)
{
  printf("stack trace begin:\n");
  void *array[100];
  char **strings;
  int size, i;

  size = backtrace (array, 100);
  strings = backtrace_symbols (array, size);
  register int* current_ebp __asm__("%ebp");
  int* ebp = current_ebp;
  if (strings != NULL)
  {
    int num = size - 3;
    printf ("Obtained %d stack frames.\n", size);
    for (i = 0; i < size; i++) {
      printf("stack %d: ", size - i);
      printf("%s\n", strings[i]);
      int* upper_ebp = (int *) *ebp;
      printf("(0x%0x) ", *ebp);
      for (int i = 0; i < 5; i++) {
        printf("0x%0x ", *(ebp+i));
      }
      printf("\n");
      ebp = upper_ebp;
    }
  }

  free (strings);
  printf("--------done---------\n");
}

void foo(void);

/* A dummy function to make the backtrace more interesting. */
void
dummy_function (void)
{
  printf("Enter dummy_function\n");
  foo();
  print_trace ();
  printf("Exit dummy_function\n");
}

void
foo (void)
{
  printf("Enter foo\n");
  print_trace ();
  printf("Exit foo\n");
}

int
main (void)
{
  register int *main_ebp __asm__("%ebp");
  printf("$ebp: %d\n", *main_ebp);
  dummy_function ();
  return 0;
}
