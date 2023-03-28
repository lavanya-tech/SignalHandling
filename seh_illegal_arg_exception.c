#include <float.h>
#include <excpt.h>
#include <stdio.h>
#include <fenv.h>

void floating_point_exception_handler(unsigned int exception_code, EXCEPTION_POINTERS* exception_pointers) {
    printf("Floating point exception occurred!\n");
}

int main() {
    unsigned int fp_control_word = 0;
    _controlfp_s(&fp_control_word, _EM_INVALID, _MCW_EM);

    __try {
        float a = 1.0;
        float b = 0.0;
        float c = a / b;
    }
    __except (floating_point_exception_handler(GetExceptionCode(), GetExceptionInformation())) {
        // Handle the floating-point exception here
    }

    return 0;
}