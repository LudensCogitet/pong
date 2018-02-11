#include "./config.h"

configMap loadConfig(const char * filename) {
    configMap config;
    std::ifstream   configFile(filename);
    std::string     line;
    std::string     key;
    std::string     value;

    while(std::getline(configFile, line)) {
        if(line.length() == 0 || line[0] == '#') continue;

       std::size_t start  = line.find_first_not_of(" =", 0);
       std::size_t end    = line.find_first_of(" =", start);

       key = line.substr(start, end - start);

       start    = line.find_first_not_of(" =", end);
       end      = line.find_first_of(" =", start);

       value = line.substr(start, end - start);

       config[key] = value;
    }
    configFile.close();

    return config;
}
