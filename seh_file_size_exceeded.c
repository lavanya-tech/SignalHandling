#include <windows.h>
#include <stdio.h>
#include <excpt.h>

void file_size_exception_handler(unsigned int exception_code, EXCEPTION_POINTERS* exception_pointers) {
    printf("Process exceeded its file size limit!\n");
}

int main() {
    __try{
        // Open a file and write data until the file size limit is exceeded
        FILE* file = fopen("test.txt", "w");
        if (file == NULL) {
            printf("Failed to open file\n");
            return 1;
        }
        int count = 0;
        while (1) {
            fprintf(file, "This is a test line %d\n", count);
            count++;
        }
        fclose(file);
    }
    __except (file_size_exception_handler(GetExceptionCode(), GetExceptionInformation())) {
        // Handle the file size exception here
    }
    return 0;
}
