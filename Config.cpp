/**
 * @file Config.hpp
 * @brief Provides configuration constants for the application.
 *
 * This header file contains constant definitions used throughout the application.
 * These constants include program name, file information, release details, author information, and copyright.
 */

#include "Config.hpp"

// Name of the program
const std::string Config::PROGNAME = "Lord Quixard";

// The file name where this constant is defined
const std::string Config::FILE_NAME = __FILE__;

// Release information of the program, including version and last update date
const std::string Config::RELEASE = "Revision 1.0 | Last update 13 December 2023";

// Author of the program
const std::string Config::AUTHOR = "Aubertin Emmanuel";

// Copyright information for the program, including the year and the author's name
const std::string Config::COPYRIGHT = "(c) 2023 " + Config::AUTHOR + " more at github.com/emmanuel-aubertin";
