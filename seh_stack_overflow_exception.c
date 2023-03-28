#include <Windows.h>
#include <stdio.h>

int main() {
  __try {
    // Allocate a very large buffer on the stack to cause a stack overflow
    char buffer[1024 * 1024 * 1024]; // 1 GB
  }
  __except(GetExceptionCode() == EXCEPTION_STACK_OVERFLOW ? EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH) {
    printf("Stack overflow exception caught\n");
  }
  return 0;
}