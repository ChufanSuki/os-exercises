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
  size_t name_size = 100;
  char *name = (char*)malloc(name_size);
  if (strings != NULL)
  {
    int num = size - 3;
    printf ("Obtained %d stack frames.\n", size);
    for (i = 0; i < size; i++) {
      printf("stack %d: ", size - i);
      char* begin_name;
      char* begin_offset;
      char* end_offset;
      char* function_address_begin;
      char* function_address_end;
      for (char* p = strings[i]; *p; ++p) {
        if (*p == '(')
          begin_name = p;
        else if (*p == ')')
          end_offset = p;
        else if (*p == '+')
          begin_offset = p;
        else if (*p == '[')
          function_address_begin = p;
        else if (*p == ']')
          function_address_end = p;
      }
      if (begin_name && begin_offset && end_offset && function_address_begin && function_address_end) {
        int status = -4;
        *begin_name++ = '\0';
        *begin_offset++ = '\0';
        *end_offset++ = '\0';
        char *ret = abi::__cxa_demangle(begin_name, name, &name_size, &status);
        if (status == 0) {
          name = ret;
          printf("%s:%s+%s\n", strings[i], name, begin_offset);
        } else{
          printf("%s:%s()+%s\n", strings[i], begin_name, begin_offset);
        }
      } else 
        printf("%s\n", strings[i]);
      int* upper_ebp = (int *) *ebp;
      printf("(0x%0x) ", *ebp);
      for (int i = 0; i < 5; i++) {
        printf("0x%0x ", *(ebp+i));
      }
      printf("\n");
      ebp = upper_ebp;
      if (*ebp == 0) {
        printf("$ebp reach 0\n");
        break;
      }
    }
  }
  free(name);
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
