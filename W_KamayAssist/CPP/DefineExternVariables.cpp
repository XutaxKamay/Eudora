#include "Includes.hxx"
#include "Lib.hxx"

// Let's put all strings into a vector (buffer)
stdString N_Console::sAllStrings;

// If console is openned
bool N_Console::bOpenned = false;
bool N_Console::bClearedLogs = false;
bool N_Console::bClearOnceLogFile = false;
bool N_FileSystem::bOnceWrite = false;