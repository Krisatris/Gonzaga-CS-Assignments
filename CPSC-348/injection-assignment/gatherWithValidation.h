#include <string>

namespace injectionAttacks
{
	/**
	 * A wrapper for the gather command that removes its vulnerabilities using blacklist validation.
	 * Uses regexes and implements the principle of fail-safe defaults.
	 */
    bool gatherWithBlacklist(std::string food, std::string storage);

	/**
	 * A wrapper for the gather command that removes its vulnerabilities using whitelist validation.
	 * Uses regexes and implements the principle of fail-safe defaults.
	 */
    bool gatherWithWhitelist(std::string food, std::string storage);
}
