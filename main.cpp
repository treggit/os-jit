//
// Created by Anton Shelepov on 2019-05-05.
//

#include "function_storage.h"
#include <iostream>

uint8_t func[]{
        0xdb, 0x6c, 0x24, 0x08,
        0xba, 0x00, 0x00, 0x00, 0x00,
        0xdb, 0x6c, 0x24, 0x18,
        0xdb, 0x6c, 0x24, 0x38,
        0xd8, 0xe9,
        0xdb, 0x6c, 0x24, 0x28,
        0xd8, 0xe3,
        0xd9, 0xc1,
        0xd9, 0xe0,
        0xde, 0xcc,
        0xdc, 0xca,
        0xd9, 0xca,
        0xde, 0xeb,
        0xdb, 0x6c, 0x24, 0x48,
        0xde, 0xc9,
        0xdb, 0x6c, 0x24, 0x58,
        0xde, 0xca,
        0xde, 0xc1,
        0xde, 0xc1,
        0xd9, 0xee,
        0xdf, 0xe9,
        0xdd, 0xd8,
        0x0f, 0x9b, 0xc0,
        0x0f, 0x45, 0xc2,
        0xc3
};

using func_ptr = bool(*)(long double, long double, long double, long double, long double, long double);

int main(int argc, char* argv[]) {
    if (argc > 1 && strcmp(argv[1], "-help") == 0) {
        std::cout << "Program checks, whether three given points lay on the same line." << std::endl;
    }
    long double x1, y1, x2, y2, x3, y3;
    std::cout << "Enter the points" << std::endl;
    std::cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
    function_storage<func_ptr> storage(func, sizeof(func));

    if (storage.loaded()) {
        std::cout << (storage.call(x1, y1, x2, y2, x3, y3) ? "Yes" : "No") << std::endl;
    }
}
