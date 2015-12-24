#include <iostream>
#include <execinfo.h>
#include <stdio.h>
#include <stdlib.h>
#include <backtrace.h>

using namespace std;

/* Obtain a backtrace and print it to stdout. */

void error_cb(void *data, const char *msg,
                int errnum) {
  cout << "##### error_cb #####" << endl;
  if (errnum != 0) {
    cout << "ERROR_NUM: " << errnum << endl;
    cout << "ERROR_MSG: " << msg << endl;
    if (data) {
        cout << "data is not null" << endl;
    }
  }
}

int full_callback (void *data, uintptr_t pc,
              const char *filename, int lineno,
                        const char *function) {
  cout << "##### full_cb #####" << endl;
  if (filename) {
    cout << "filename: " << filename << endl;
    if (lineno) {
      cout << "lineno: " << lineno << endl;
    }
  }
  if (function) {
      cout << "function: " << function << endl;
  }
  return 0;
}

void
print_trace (void)
{
  //void *array[10];
  //size_t size;
  //char **strings;
  //size_t i;

  //size = backtrace (array, 10);
  //strings = backtrace_symbols (array, size);

  //printf ("Obtained %zd stack frames.\n", size);

  //for (i = 0; i < size; i++)
     //printf ("%s\n", strings[i]);

  //free (strings);
  char data[10000];
  auto state = backtrace_create_state(nullptr, 0, &error_cb, data);
  backtrace_full(state, 0, &full_callback, &error_cb, data);
}

/* A dummy function to make the backtrace more interesting. */
void
dummy_function (void)
{
  print_trace ();
}

int
main (void)
{
  dummy_function ();
  return 0;
}
