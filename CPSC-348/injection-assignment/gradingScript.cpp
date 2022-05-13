#include "exploit.h"
#include "gatherWithValidation.h"
#include <iostream>

using std::cout;
using std::endl;

namespace injectionAttacks
{
    bool testStudentCode()
    {
        causeErrorWithGatherCommand();
        causeErrorWithCheckCommand();
        viewContentsOfDataDirectory();
        viewContentsOfUserFile();
        insertNewUser("st_Pascal", "abc123xyz789");
        exfiltrateUserFileToLocation("..");

        gatherWithWhitelist("flour", "pantry");
        gatherWithBlacklist("flour", "pantry");

        gatherWithWhitelist("malicious*&^command", "another_malicious!@#command");
        gatherWithBlacklist("malicious*&^command", "another_malicious!@#command");

        return true;
    }
}

int main(int argc, char *argv[])
{
    return injectionAttacks::testStudentCode();
}
