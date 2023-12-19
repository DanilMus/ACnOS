#include "lib.h"
#include <iostream>

extern "C" {
    EXPORT_SYMBOL int showMessage() {
        std::cout << "Hello from the library!" << std::endl;
        return 42; // Значение кода завершения
    }
}
