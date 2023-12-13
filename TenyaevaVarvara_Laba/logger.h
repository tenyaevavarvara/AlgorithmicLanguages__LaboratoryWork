#pragma once
#include <fstream>

static std::ofstream logger;

template <typename T>
void logValue(T message) {
    logger.open("log.txt", std::ios_base::app);
    logger << message << std::endl;
    logger.close();
}