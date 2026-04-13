#include "factory/factory.hpp"

#include <iostream>
#include <string>
#include <cstdlib>

RecommenderConfig parseArgs(int argc, char* argv[]) {
    RecommenderConfig config;
    config.seed       = 67;
    config.numUsers   = 100;
    config.numItems   = 50;
    config.numRatings = 1000;
    config.topK       = 5;
    config.useCuckoo  = false;
    config.rngName    = "acorn";
    config.hashName   = "fnv1a";

    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];
        if(i+1 < argc) { // caso seja passado um argumento vazio
            try {
                if (arg == "--seed") config.seed = std::stoi(argv[++i]);
                else if (arg == "--users") config.numUsers = std::stoi(argv[++i]);
                else if (arg == "--items") config.numItems = std::stoi(argv[++i]);
                else if (arg == "--ratings") config.numRatings = std::stoi(argv[++i]);
                else if (arg == "--topk") config.topK = std::stoi(argv[++i]);
                else if (arg == "--rng") config.rngName = argv[++i];
                else if (arg == "--hash") config.hashName = argv[++i];
                else if (arg == "--cuckoo") config.useCuckoo = true;
            } catch(const std::exception& err) {
                std::cout << "error parsing args " << err.what() << '\n';
            }
        }
    }

    return config;
}

int main(int argc, char* argv[]) {
    RecommenderConfig config = parseArgs(argc, argv);
    Recommender* recommender = ObjectFactory::create(config);
    recommender->run();
    delete recommender;

    return 0;
}