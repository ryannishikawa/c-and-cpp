#include <stdio.h>
#include <string.h>

enum ClassLevel {Freshman, Sophomore, Junior, Senior, Unknown};

//function to help print enum ClassLevel
const char* class_level(enum ClassLevel level) {
    switch (level) {
        case Freshman:
            return "Freshman";
        case Sophomore:
            return "Sophomore";
        case Junior:
            return "Junior";
        case Senior:
            return "Senior";
        default:
            return "Unknown";
    }
}

//function to help read enum ClassLevel from file
enum ClassLevel getClassLevel(const char *str) {
    if (strcmp(str, "Freshman") == 0) {
        return Freshman;
    } else if (strcmp(str, "Sophomore") == 0) {
        return Sophomore;
    } else if (strcmp(str, "Junior") == 0) {
        return Junior;
    } else if (strcmp(str, "Senior") == 0) {
        return Senior;
    } else {
        return Unknown;
    }
}