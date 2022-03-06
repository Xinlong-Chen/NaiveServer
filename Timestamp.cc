#include "Timestamp.h"

#include <time.h>

Timestamp Timestamp::now() {
    return Timestamp(time(NULL));
}

std::string Timestamp::toString() const {
    char buf[128] = {0};
    tm* time = localtime(&microSecondsSinceEpoch_);
    snprintf(buf, 128, "%04d-%02d-%02d %02d:%02d:%02d", 
        time->tm_year + 1900,
        time->tm_mon + 1,
        time->tm_mday,
        time->tm_hour,
        time->tm_min,
        time->tm_sec);
    return buf;
}

// #include <iostream>

// int main() {
//     std::cout << Timestamp::now().toString() << std::endl;
// }