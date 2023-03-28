#include <Windows.h>
#include <stdio.h>

int main() {
  int *ptr = NULL;
  __try {
    // Dereference a null pointer to cause a null pointer exception
    *ptr = 42;
  }
  __except(GetExceptionCode() == EXCEPTION_ACCESS_VIOLATION ? EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH) {
    printf("Null pointer exception caught\n");
  }
  return 0;
}