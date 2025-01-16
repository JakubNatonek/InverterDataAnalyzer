#include "Record.h"
#include <sstream>
#include <iomanip>
#include <stdexcept>
#include <iostream>

Record::Record()
{
    
}

Record::Record(const std::string& timestamp, double auto_consumption, double power_export, double power_import, double power_consumption, double power_production) {
    std::istringstream ss(timestamp);
    ss >> std::get_time(&this->timestamp, "%d.%m.%Y %H:%M");
    if (ss.fail()) {
        std::cout << "Cos sie zjebalo " << std::endl;
        throw std::invalid_argument("Invalid timestamp format");
    }
    this->auto_consumption = auto_consumption;
    this->power_export = power_export;
    this->power_import = power_import;
    this->power_consumption = power_consumption;
    this->power_production = power_production;
}

void Record::show() {
    std::cout << "Timestamp: " << std::put_time(&timestamp, "%d.%m.%Y %H:%M") << "\n"
              << "Auto Consumption: " << auto_consumption << " W\n"
              << "Power Export: " << power_export << " W\n"
              << "Power Import: " << power_import << " W\n"
              << "Power Consumption: " << power_consumption << " W\n"
              << "Power Production: " << power_production << " W\n";
}

//======================================================================================================================

bool Record::isValid() const {
    // Przykładowa walidacja: sprawdzamy, czy wszystkie wartości są większe od zera
    return auto_consumption >= 0 && power_export >= 0 && power_import >= 0 && power_consumption >= 0 && power_production >= 0;
}

std::string Record::toString() const {
    std::ostringstream oss;
    oss << "Autokonsumpcja: " << auto_consumption << " W, Eksport: " << power_export << " W, "
        << "Import: " << power_import << " W, Pobór: " << power_consumption << " W, Produkcja: " << power_production << " W";
    return oss.str();
}