#include <iostream>
#include <windows.h>
#include "lib.h"

typedef int (*ShowMessageFunction)();

int main() {
    // Неявное связывание
    int resultImplicit = showMessage();
    std::cout << "Returned implicitly: " << resultImplicit << std::endl;

    // Явное связывание
    HMODULE lib = LoadLibraryA("lib.dll");
    if (!lib) {
        std::cerr << "Cannot open library." << std::endl;
        return 1;
    }

    // Получение указателя на функцию
    ShowMessageFunction showMessageExplicit = reinterpret_cast<ShowMessageFunction>(GetProcAddress(lib, "showMessage"));
    if (!showMessageExplicit) {
        std::cerr << "Cannot load symbol showMessage." << std::endl;
        FreeLibrary(lib);
        return 1;
    }

    // Вызов функции
    int resultExplicit = showMessageExplicit();
    std::cout << "Returned explicitly: " << resultExplicit << std::endl;

    FreeLibrary(lib);

    return 0;
}
