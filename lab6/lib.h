#ifndef LIB_EXAMPLE_H
#define LIB_EXAMPLE_H

#ifdef _WIN32
    #define EXPORT_SYMBOL __declspec(dllexport)
#else
    #define EXPORT_SYMBOL
#endif

extern "C" {
    EXPORT_SYMBOL int showMessage();
}

#endif // LIB_EXAMPLE_H
