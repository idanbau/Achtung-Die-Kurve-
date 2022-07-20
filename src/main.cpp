#include "GameController.h"
#include <fstream>
const auto LOG_FILE = "log.txt";


int main() try {
    srand((unsigned int)time(NULL));
    auto gameControl = GameController{};
    gameControl.run();
}

catch (std::exception& e)
{
    auto file = std::ofstream(LOG_FILE);
    file << e.what() << '\n';
    return EXIT_FAILURE;
}
catch (...)
{
    auto file = std::ofstream(LOG_FILE);
     file << "Unknown Exception" << '\n';
    return EXIT_FAILURE;
}