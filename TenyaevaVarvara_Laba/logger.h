#include <fstream>

static std::ofstream logger;

void log(std::string message) {
    logger.open("log.txt", std::ios_base::app);
    logger << message << std::endl;
    logger.close();
}