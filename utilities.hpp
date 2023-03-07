#include <cstdlib>

#ifndef UTILITIES_HPP
#define UTILITIES_HPP

inline double randomDouble() {
    return static_cast<double>(rand()) / RAND_MAX;
}

inline double randomDouble(double min, double max) {
    return min + (max - min) * randomDouble();
}

inline int randomInt(int min, int max) {
    return min + static_cast<int>(randomDouble() * (max - min + 1));
}

inline double clip(double number, double min, double max) {
    if (number < min) {
        return min;
    } else if (number > max) {
        return max;
    } else {
        return number;
    }
}

inline std::string getTimeInMinutes(time_t start, time_t end) {
    double timeInSeconds = difftime(end, start);
    double timeInMinutes = timeInSeconds / 60;

    int minutes = static_cast<int>(timeInMinutes);
    int seconds = static_cast<int>(timeInSeconds - minutes * 60);

    std::string timeString = std::to_string(minutes) + 'm' + std::to_string(seconds) + 's';
    return timeString;
}
#endif  // !UTILITIES_HPP