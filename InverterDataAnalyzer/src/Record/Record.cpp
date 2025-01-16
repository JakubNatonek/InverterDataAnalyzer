#include "Record.h"
#include <sstream>
#include <iomanip>
#include <stdexcept>
#include <iostream>

/**
 * @brief Konstruktor domyślny klasy Record.
 */
Record::Record()
{
    
}

/**
 * @brief Konstruktor klasy Record inicjalizujący wszystkie pola.
 * 
 * @param timestamp Znacznik czasu w formacie "dd.mm.yyyy hh:mm".
 * @param auto_consumption Autokonsumpcja w watach.
 * @param power_export Eksport mocy w watach.
 * @param power_import Import mocy w watach.
 * @param power_consumption Pobór mocy w watach.
 * @param power_production Produkcja mocy w watach.
 * 
 * @throw std::invalid_argument Jeśli format znacznika czasu jest nieprawidłowy.
 */
Record::Record(const std::string& timestamp, double auto_consumption, double power_export, double power_import, double power_consumption, double power_production) {
    std::istringstream ss(timestamp);
    ss >> std::get_time(&this->timestamp, "%d.%m.%Y %H:%M");
    if (ss.fail()) {
        throw std::invalid_argument("Invalid timestamp format");
    }
    this->auto_consumption = auto_consumption;
    this->power_export = power_export;
    this->power_import = power_import;
    this->power_consumption = power_consumption;
    this->power_production = power_production;
    show();
}

/**
 * @brief Wyświetla dane rekordu na standardowym wyjściu.
 */
void Record::show() {
    std::cout << "Timestamp: " << std::put_time(&timestamp, "%d.%m.%Y %H:%M") << "\n"
              << "Auto Consumption: " << auto_consumption << " W\n"
              << "Power Export: " << power_export << " W\n"
              << "Power Import: " << power_import << " W\n"
              << "Power Consumption: " << power_consumption << " W\n"
              << "Power Production: " << power_production << " W\n";
}

/**
 * @brief Sprawdza, czy rekord jest prawidłowy.
 * 
 * @return true Jeśli wszystkie wartości są większe lub równe zero.
 * @return false Jeśli którakolwiek z wartości jest mniejsza od zera.
 */
bool Record::isValid() const {
    return auto_consumption >= 0 && power_export >= 0 && power_import >= 0 && power_consumption >= 0 && power_production >= 0;
}

/**
 * @brief Zwraca dane rekordu jako sformatowany ciąg znaków.
 * 
 * @return std::string Sformatowany ciąg znaków zawierający dane rekordu.
 */
std::string Record::toString() const {
    std::ostringstream oss;
    oss << "Autokonsumpcja: " << auto_consumption << " W, Eksport: " << power_export << " W, "
        << "Import: " << power_import << " W, Pobór: " << power_consumption << " W, Produkcja: " << power_production << " W";
    return oss.str();
}