#include <string>
#include <regex>
#include <iostream>
#include "gather.h"

namespace injectionAttacks
{
	/**
	 * A wrapper for the gather command that removes its vulnerabilities using blacklist validation.
	 * Uses regexes and implements the principle of fail-safe defaults.
	 */
    bool gatherWithBlacklist(std::string food, std::string storage) {
        std::regex blacklist("^[^*&!@#|;\n^()`]+$");
        if(regex_match(food, blacklist) && regex_match(storage, blacklist)) {
            gather(food, storage);
            return true;
        } else {
            std::cout << "invalid input, please try again" << std::endl;
            return false;
        }
    }

	/**
	 * A wrapper for the gather command that removes its vulnerabilities using whitelist validation.
	 * Uses regexes and implements the principle of fail-safe defaults.
	 */
    bool gatherWithWhitelist(std::string food, std::string storage) {
        std::regex whitelist("^[A-Za-z0-9]+$");
        if(regex_match(food, whitelist) && regex_match(storage, whitelist)) {
            gather(food, storage);
            return true;
        } else {
            std::cout << "invalid input, please try again" << std::endl;
            return false;
        }
    }
}