#ifndef CONFIG_H
#define CONFIG_H

#include <fstream>
#include <string>
#include <map>

using configMap = std::map<std::string, std::string>;
configMap loadConfig(const char * filename);

#endif
