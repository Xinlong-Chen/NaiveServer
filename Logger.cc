#include "Logger.h"

#include <iostream>

#include "Timestamp.h"

Logger& Logger::instance() {
    static Logger logger;
    return logger;
}

void Logger::setLogLevel(int level) {
    logLevel_ = level;
}

void Logger::log(std::string msg) {
    switch (logLevel_)
    {
    case INFO:
        std::cout << "[INFO]"; 
        break;
    case ERROR:
        std::cout << "[ERROR]"; 
        break;    
    case FATAL:
        std::cout << "[FATAL]"; 
        break;    
    case DEBUG:
        std::cout << "[DEBUG]"; 
        break; 
    default:
        break;
    }
    
    std::cout << Timestamp::now().toString() << " : " << msg << std::endl;
}


// int main() {
//     LOG_INFO("%d %d", 12, 3);
//     LOG_ERROR("%d %d", 12, 3);
//     LOG_FATAL("%d %d", 12, 3);
//     // LOG_DEBUG("%d %d", 12, 3);
// }