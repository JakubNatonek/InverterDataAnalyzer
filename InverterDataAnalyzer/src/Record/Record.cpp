#include "Record.h"
#include <sstream>
#include <iomanip>
#include <stdexcept>

Record::Record(const std::string& timestamp, double auto_consumption, double power_export, double power_import, double power_consumption, double power_production) {
    std::istringstream ss(timestamp);
    ss >> std::get_time(&this->timestamp, "%d-%m-%Y %H:%M");
    if (ss.fail()) {
        throw std::invalid_argument("Invalid timestamp format");
    }
    this->auto_consumption = auto_consumption;
    this->power_export = power_export;
    this->power_import = power_import;
    this->power_consumption = power_consumption;
    this->power_production = power_production;
}
