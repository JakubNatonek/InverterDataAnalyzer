#include "DataAnalysis.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <ctime>
#include <iomanip>
#include <cmath>

// Function to trim whitespace and quotes from a string
std::string trim(const std::string& str) {
    auto start = str.begin();
    while (start != str.end() && std::isspace(*start)) {
        start++;
    }

    auto end = str.end();
    do {
        end--;
    } while (std::distance(start, end) > 0 && std::isspace(*end));

    if (*start == '\"' && *end == '\"') {
        start++;
        end--;
    }

    return std::string(start, end + 1);
}

void DataAnalysis::loadDataFromCSV(const std::string& filename) {
    std::ifstream file(filename);
    std::cout << filename << "\n";
    if (!file.is_open()) {
        std::cerr << "Nie udalo sie otworzyc pliku CSV: " << filename << "\n";
        return;
    }

    std::string line;
    std::getline(file, line);

    int correctRecords = 0;
    int incorrectRecords = 0;

    // Otwórz plik logowy do zapisywania niepoprawnych rekordów
    std::ofstream logData("log_data_" + getCurrentDateTime() + ".txt");
    std::ofstream logError("log_error_" + getCurrentDateTime() + ".txt");

    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') continue; // Pomijamy puste i komentarze

        std::istringstream stream(line);

        std::string timestamp, auto_consumption_str, power_export_str, power_import_str, power_consumption_str, power_production_str;
        double auto_consumption = 0, power_export = 0, power_import = 0, power_consumption = 0, power_production = 0;
        try
        {
            std::getline(stream, timestamp, ',');
            std::getline(stream, auto_consumption_str, ',');
            std::getline(stream, power_export_str, ',');
            std::getline(stream, power_import_str, ',');
            std::getline(stream, power_consumption_str, ',');
            std::getline(stream, power_production_str);
        }
        catch (const std::invalid_argument& e) {
                std::cerr << "To short: " << e.what() << "\n";
                logError << line << std::endl;
                incorrectRecords++;
                continue;
        }
        catch (...) {
            std::cerr << "Cos sie zjebalo: " << "\n";
            logError << line << std::endl;
            incorrectRecords++;
            continue;
        }

        if (timestamp == "")
        {
            std::cout << "empty" << std::endl;
            logError << line << std::endl;
            incorrectRecords++;
            continue;
        }

        if (auto_consumption_str == "")
        {
            std::cout << "empty" << std::endl;
            logError << line << std::endl;
            incorrectRecords++;
            continue;
        }

        if (power_export_str == "")
        {
            std::cout << "empty" << std::endl;
            logError << line << std::endl;
            incorrectRecords++;
            continue;
        }

        if (power_import_str == "")
        {
            std::cout << "empty" << std::endl;
            logError << line << std::endl;
            incorrectRecords++;
            continue;
        }

        if (power_consumption_str == "")
        {
            std::cout << "empty" << std::endl;
            logError << line << std::endl;
            incorrectRecords++;
            continue;
        }
        
        if (power_production_str == "")
        {
            std::cout << "empty" << std::endl;
            logError << line << std::endl;
            incorrectRecords++;
            continue;
        }

        // Konwersja stringów na liczby
        try {

            // Trim strings before conversion
            auto_consumption_str = trim(auto_consumption_str);
            power_export_str = trim(power_export_str);
            power_import_str = trim(power_import_str);
            power_consumption_str = trim(power_consumption_str);
            power_production_str = trim(power_production_str);
    
            auto_consumption = std::stod(auto_consumption_str);
            power_export = std::stod(power_export_str);
            power_import = std::stod(power_import_str);
            power_consumption = std::stod(power_consumption_str);
            power_production = std::stod(power_production_str);
        }
        catch (const std::invalid_argument& e) {
            std::cerr << "Invalid argument: " << e.what() << "\n";
            logError << "Invalid argument: " << e.what() << " in line: " << line << std::endl;
            incorrectRecords++;
            continue;
        }
        catch (const std::out_of_range& e) {
            std::cerr << "Out of range: " << e.what() << "\n";
            logError << "Out of range: " << e.what() << " in line: " << line << std::endl;
            incorrectRecords++;
            continue;
        }
        catch (...) {
            std::cerr << "Unknown error occurred\n";
            logError << "Unknown error in line: " << line << std::endl;
            incorrectRecords++;
            continue;
        }
        
        // Utwórz rekord
        Record* record = new Record(timestamp, auto_consumption, power_export, power_import, power_consumption, power_production);
        // record->show();

        if (record->isValid()) {
            // Jeżeli rekord jest poprawny, dodajemy go do drzewa
            addRecordToTree(record);
            logData << line << std::endl;  // Zapisujemy poprawny rekord do logu
            correctRecords++;
        }
        else {
            // Jeżeli rekord jest niepoprawny, zapisujemy go do logu błędów
            logError << line << std::endl;
            incorrectRecords++;
        }

        // Parsowanie daty
        std::tm tm = record->timestamp;
        int year = tm.tm_year + 1900;
        int month = tm.tm_mon + 1;
        int day = tm.tm_mday;
        int hour = tm.tm_hour;

        // Ćwiartki
        int quarter = (hour < 6) ? 0 : (hour < 12) ? 1 : (hour < 18) ? 2 : 3;

        // Dodaj rekord do odpowiedniego węzła w drzewie
        if (data[year][month][day].find(quarter) == data[year][month][day].end()) {
            data[year][month][day][quarter] = new TreeNode(year, month, day, quarter);
        }
        data[year][month][day][quarter]->addRecord(record);
    }

    file.close();
    logData.close();
    logError.close();
}

//======================================================================================================================

// Metody sumujące
double DataAnalysis::sumAutokonsumpcja(int startYear, int startMonth, int startDay, int startQuarter,
                                      int endYear, int endMonth, int endDay, int endQuarter) {
    double total = 0;

    // Iteracja po latach, miesiącach, dniach i ćwiartkach
    for (int year = startYear; year <= endYear; ++year) {
        for (int month = startMonth; month <= endMonth; ++month) {
            for (int day = startDay; day <= endDay; ++day) {
                for (int quarter = startQuarter; quarter <= endQuarter; ++quarter) {
                    if (data[year][month][day].find(quarter) != data[year][month][day].end()) {
                        auto records = data[year][month][day][quarter]->getRecords();
                        for (auto& record : records) {
                            total += record->auto_consumption;
                        }
                    }
                }
            }
        }
    }
    std::cout << "Suma autokonsumpcji: " << total << " W" << std::endl;
    return total; 
}

// Metody sumujące dla innych parametrów (eksport, import, pobór, produkcja) można zaimplementować podobnie:
double DataAnalysis::sumEksport(int startYear, int startMonth, int startDay, int startQuarter,
                               int endYear, int endMonth, int endDay, int endQuarter) {
    double total = 0;

    // Iteracja po latach, miesiącach, dniach i ćwiartkach
    for (int year = startYear; year <= endYear; ++year) {
        for (int month = startMonth; month <= endMonth; ++month) {
            for (int day = startDay; day <= endDay; ++day) {
                for (int quarter = startQuarter; quarter <= endQuarter; ++quarter) {
                    if (data[year][month][day].find(quarter) != data[year][month][day].end()) {
                        auto records = data[year][month][day][quarter]->getRecords();
                        for (auto& record : records) {
                            total += record->power_export;
                        }
                    }
                }
            }
        }
    }
    std::cout << "Suma export: " << total << " W" << std::endl;
    
    return total; 
}

double DataAnalysis::sumImport(int startYear, int startMonth, int startDay, int startQuarter,
                              int endYear, int endMonth, int endDay, int endQuarter) {
    double total = 0;

    // Iteracja po latach, miesiącach, dniach i ćwiartkach
    for (int year = startYear; year <= endYear; ++year) {
        for (int month = startMonth; month <= endMonth; ++month) {
            for (int day = startDay; day <= endDay; ++day) {
                for (int quarter = startQuarter; quarter <= endQuarter; ++quarter) {
                    if (data[year][month][day].find(quarter) != data[year][month][day].end()) {
                        auto records = data[year][month][day][quarter]->getRecords();
                        for (auto& record : records) {
                            total += record->power_import;
                        }
                    }
                }
            }
        }
    }
    std::cout << "Suma import: " << total << " W" << std::endl;
    
    return total; 
}

double DataAnalysis::sumPobor(int startYear, int startMonth, int startDay, int startQuarter, int endYear, int endMonth, int endDay, int endQuarter) {
    double total = 0;

    // Iteracja po latach, miesiącach, dniach i ćwiartkach
    for (int year = startYear; year <= endYear; ++year) {
        for (int month = startMonth; month <= endMonth; ++month) {
            for (int day = startDay; day <= endDay; ++day) {
                for (int quarter = startQuarter; quarter <= endQuarter; ++quarter) {
                    if (data[year][month][day].find(quarter) != data[year][month][day].end()) {
                        auto records = data[year][month][day][quarter]->getRecords();
                        for (auto& record : records) {
                            total += record->power_consumption;
                        }
                    }
                }
            }
        }
    }
    std::cout << "Suma pobor: " << total << " W" << std::endl;
    
    return total; 
}

double DataAnalysis::sumProdukcja(int startYear, int startMonth, int startDay, int startQuarter, int endYear, int endMonth, int endDay, int endQuarter) {
    double total = 0;

    // Iteracja po latach, miesiącach, dniach i ćwiartkach
    for (int year = startYear; year <= endYear; ++year) {
        for (int month = startMonth; month <= endMonth; ++month) {
            for (int day = startDay; day <= endDay; ++day) {
                for (int quarter = startQuarter; quarter <= endQuarter; ++quarter) {
                    if (data[year][month][day].find(quarter) != data[year][month][day].end()) {
                        auto records = data[year][month][day][quarter]->getRecords();
                        for (auto& record : records) {
                            total += record->power_production;
                        }
                    }
                }
            }
        }
    }
    std::cout << "Suma produkcja: " << total << " W" << std::endl;
    
    return total; 
}

// Średnia
double DataAnalysis::avgAutokonsumpcja(int startYear, int startMonth, int startDay, int startQuarter,
                                      int endYear, int endMonth, int endDay, int endQuarter) {
    double total = 0;
    int count = 0;

    for (int year = startYear; year <= endYear; ++year) {
        for (int month = startMonth; month <= endMonth; ++month) {
            for (int day = startDay; day <= endDay; ++day) {
                for (int quarter = startQuarter; quarter <= endQuarter; ++quarter) {
                    if (data[year][month][day].find(quarter) != data[year][month][day].end()) {
                        auto records = data[year][month][day][quarter]->getRecords();
                        for (auto& record : records) {
                            total += record->auto_consumption;
                            count++;
                        }
                    }
                }
            }
        }
    }

    double avrege = 0;
    if (count > 0) {
        avrege = total / count;
        std::cout << "Srednia autokonsumpcji: " << total / count << " W" << std::endl;
    } else {
        std::cout << "Brak danych w podanym przedziale!" << std::endl;
    }
    return avrege; 
}

double DataAnalysis::avgEksport(int startYear, int startMonth, int startDay, int startQuarter, int endYear, int endMonth, int endDay, int endQuarter) {
    double total = 0;
    int count = 0;

    for (int year = startYear; year <= endYear; ++year) {
        for (int month = startMonth; month <= endMonth; ++month) {
            for (int day = startDay; day <= endDay; ++day) {
                for (int quarter = startQuarter; quarter <= endQuarter; ++quarter) {
                    if (data[year][month][day].find(quarter) != data[year][month][day].end()) {
                        auto records = data[year][month][day][quarter]->getRecords();
                        for (auto& record : records) {
                            total += record->power_export;
                            count++;
                        }
                    }
                }
            }
        }
    }

    double avrege = 0;
    if (count > 0) {
        avrege = total / count;
        std::cout << "Srednia export: " << total / count << " W" << std::endl;
    } else {
        std::cout << "Brak danych w podanym przedziale!" << std::endl;
    }
    return avrege; 
}

double DataAnalysis::avgImport(int startYear, int startMonth, int startDay, int startQuarter, int endYear, int endMonth, int endDay, int endQuarter) {
    double total = 0;
    int count = 0;

    for (int year = startYear; year <= endYear; ++year) {
        for (int month = startMonth; month <= endMonth; ++month) {
            for (int day = startDay; day <= endDay; ++day) {
                for (int quarter = startQuarter; quarter <= endQuarter; ++quarter) {
                    if (data[year][month][day].find(quarter) != data[year][month][day].end()) {
                        auto records = data[year][month][day][quarter]->getRecords();
                        for (auto& record : records) {
                            total += record->power_import;
                            count++;
                        }
                    }
                }
            }
        }
    }

    double avrege = 0;
    if (count > 0) {
        avrege = total / count;
        std::cout << "Srednia import: " << total / count << " W" << std::endl;
    } else {
        std::cout << "Brak danych w podanym przedziale!" << std::endl;
    }
    return avrege; 
}

double DataAnalysis::avgPobor(int startYear, int startMonth, int startDay, int startQuarter, int endYear, int endMonth, int endDay, int endQuarter) {
    double total = 0;
    int count = 0;

    for (int year = startYear; year <= endYear; ++year) {
        for (int month = startMonth; month <= endMonth; ++month) {
            for (int day = startDay; day <= endDay; ++day) {
                for (int quarter = startQuarter; quarter <= endQuarter; ++quarter) {
                    if (data[year][month][day].find(quarter) != data[year][month][day].end()) {
                        auto records = data[year][month][day][quarter]->getRecords();
                        for (auto& record : records) {
                            total += record->power_consumption;
                            count++;
                        }
                    }
                }
            }
        }
    }

    double avrege = 0;
    if (count > 0) {
        avrege = total / count;
        std::cout << "Srednia pobor: " << total / count << " W" << std::endl;
    } else {
        std::cout << "Brak danych w podanym przedziale!" << std::endl;
    }
    return avrege; 
}

double DataAnalysis::avgProdukcja(int startYear, int startMonth, int startDay, int startQuarter, int endYear, int endMonth, int endDay, int endQuarter) {
    double total = 0;
    int count = 0;

    for (int year = startYear; year <= endYear; ++year) {
        for (int month = startMonth; month <= endMonth; ++month) {
            for (int day = startDay; day <= endDay; ++day) {
                for (int quarter = startQuarter; quarter <= endQuarter; ++quarter) {
                    if (data[year][month][day].find(quarter) != data[year][month][day].end()) {
                        auto records = data[year][month][day][quarter]->getRecords();
                        for (auto& record : records) {
                            total += record->power_production;
                            count++;
                        }
                    }
                }
            }
        }
    }

    double avrege = 0;
    if (count > 0) {
        avrege = total / count;
        std::cout << "Srednia produkcja: " << total / count << " W" << std::endl;
    } else {
        std::cout << "Brak danych w podanym przedziale!" << std::endl;
    }
    return avrege; 
}

// Porównanie dwóch przedziałów
void DataAnalysis::compareAutokonsumpcja(int startYear1, int startMonth1, int startDay1, int startQuarter1,
                                          int endYear1, int endMonth1, int endDay1, int endQuarter1,
                                          int startYear2, int startMonth2, int startDay2, int startQuarter2,
                                          int endYear2, int endMonth2, int endDay2, int endQuarter2) {
    double sum1 = 0, sum2 = 0;

    // Suma dla pierwszego przedziału
    sum1 = sumAutokonsumpcja(startYear1, startMonth1, startDay1, startQuarter1, endYear1, endMonth1, endDay1, endQuarter1);

    // Suma dla drugiego przedziału
    sum2 = sumAutokonsumpcja(startYear2, startMonth2, startDay2, startQuarter2, endYear2, endMonth2, endDay2, endQuarter2);

    // Porównanie sumy
    if (sum1 > sum2) {
        std::cout << "Przedział 1 ma większą autokonsumpcję: " << sum1 << std::endl;
    } else if (sum1 < sum2) {
        std::cout << "Przedział 2 ma większą autokonsumpcję: " << sum2 << std::endl;
    } else {
        std::cout << "Oba przedziały mają taką samą autokonsumpcję: " << sum1 << ", " << sum2 << std::endl;
    }
}

void DataAnalysis::compareEksport(int startYear1, int startMonth1, int startDay1, int startQuarter1,
                            int endYear1, int endMonth1, int endDay1, int endQuarter1,
                            int startYear2, int startMonth2, int startDay2, int startQuarter2,
                            int endYear2, int endMonth2, int endDay2, int endQuarter2)
{
    double sum1 = 0, sum2 = 0;

    // Suma dla pierwszego przedziału
    sum1 = sumEksport(startYear1, startMonth1, startDay1, startQuarter1, endYear1, endMonth1, endDay1, endQuarter1);

    // Suma dla drugiego przedziału
    sum2 = sumEksport(startYear2, startMonth2, startDay2, startQuarter2, endYear2, endMonth2, endDay2, endQuarter2);

    // Porównanie sumy
    if (sum1 > sum2) {
        std::cout << "Przedział 1 ma wieksza eksport: " << sum1 << std::endl;
    } else if (sum1 < sum2) {
        std::cout << "Przedział 2 ma wieksza eksport: " << sum2 << std::endl;
    } else {
        std::cout << "Oba przedzialy mają taka sama eksport: " << sum1 << ", " << sum2 << std::endl;
    }
}

void DataAnalysis::compareImport(int startYear1, int startMonth1, int startDay1, int startQuarter1,
                        int endYear1, int endMonth1, int endDay1, int endQuarter1,
                        int startYear2, int startMonth2, int startDay2, int startQuarter2,
                        int endYear2, int endMonth2, int endDay2, int endQuarter2)
{
    double sum1 = 0, sum2 = 0;

    // Suma dla pierwszego przedziału
    sum1 = sumImport(startYear1, startMonth1, startDay1, startQuarter1, endYear1, endMonth1, endDay1, endQuarter1);

    // Suma dla drugiego przedziału
    sum2 = sumImport(startYear2, startMonth2, startDay2, startQuarter2, endYear2, endMonth2, endDay2, endQuarter2);

    // Porównanie sumy
    if (sum1 > sum2) {
        std::cout << "Przedział 1 ma wieksza import: " << sum1 << std::endl;
    } else if (sum1 < sum2) {
        std::cout << "Przedział 2 ma wieksza import: " << sum2 << std::endl;
    } else {
        std::cout << "Oba przedzialy mają taka sama import: " << sum1 << ", " << sum2 << std::endl;
    }
}

void DataAnalysis::comparePobor(int startYear1, int startMonth1, int startDay1, int startQuarter1,
                        int endYear1, int endMonth1, int endDay1, int endQuarter1,
                        int startYear2, int startMonth2, int startDay2, int startQuarter2,
                        int endYear2, int endMonth2, int endDay2, int endQuarter2)
{
    double sum1 = 0, sum2 = 0;

    // Suma dla pierwszego przedziału
    sum1 = sumPobor(startYear1, startMonth1, startDay1, startQuarter1, endYear1, endMonth1, endDay1, endQuarter1);

    // Suma dla drugiego przedziału
    sum2 = sumPobor(startYear2, startMonth2, startDay2, startQuarter2, endYear2, endMonth2, endDay2, endQuarter2);

    // Porównanie sumy
    if (sum1 > sum2) {
        std::cout << "Przedział 1 ma wieksza pobor: " << sum1 << std::endl;
    } else if (sum1 < sum2) {
        std::cout << "Przedział 2 ma wieksza pobor: " << sum2 << std::endl;
    } else {
        std::cout << "Oba przedzialy mają taka sama pobor: " << sum1 << ", " << sum2 << std::endl;
    }
}

void DataAnalysis::compareProdukcja(int startYear1, int startMonth1, int startDay1, int startQuarter1,
                            int endYear1, int endMonth1, int endDay1, int endQuarter1,
                            int startYear2, int startMonth2, int startDay2, int startQuarter2,
                            int endYear2, int endMonth2, int endDay2, int endQuarter2)
{
    double sum1 = 0, sum2 = 0;

    // Suma dla pierwszego przedziału
    sum1 = sumProdukcja(startYear1, startMonth1, startDay1, startQuarter1, endYear1, endMonth1, endDay1, endQuarter1);

    // Suma dla drugiego przedziału
    sum2 = sumProdukcja(startYear2, startMonth2, startDay2, startQuarter2, endYear2, endMonth2, endDay2, endQuarter2);

    // Porównanie sumy
    if (sum1 > sum2) {
        std::cout << "Przedział 1 ma wieksza produkcja: " << sum1 << std::endl;
    } else if (sum1 < sum2) {
        std::cout << "Przedział 2 ma wieksza produkcja: " << sum2 << std::endl;
    } else {
        std::cout << "Oba przedzialy mają taka sama produkcja: " << sum1 << ", " << sum2 << std::endl;
    }
}

// Wyszukiwanie danych
void DataAnalysis::searchImport(double target, double tolerance, int startYear, int startMonth, int startDay, int startQuarter,
                                 int endYear, int endMonth, int endDay, int endQuarter, int type) {
    std::cout << "Wyszukiwanie importu z tolerancją +/- " << tolerance << std::endl;

    for (int year = startYear; year <= endYear; ++year) {
        for (int month = startMonth; month <= endMonth; ++month) {
            for (int day = startDay; day <= endDay; ++day) {
                for (int quarter = startQuarter; quarter <= endQuarter; ++quarter) {
                    if (data[year][month][day].find(quarter) != data[year][month][day].end()) {
                        auto records = data[year][month][day][quarter]->getRecords();
                        for (auto& record : records) {
                            switch (type) {
                                case 1: // Autokonsumpcja
                                    if (std::fabs(record->auto_consumption - target) <= tolerance) {
                                        std::cout << "====================================================================" << std::endl;
                                        std::cout << "Znaleziono rekord: " << record->auto_consumption << " W" << std::endl;
                                        std::cout << std::endl;
                                        record->show();
                                        std::cout << std::endl;
                                        std::cout << "====================================================================" << std::endl;
                                    }
                                    break;
                                case 2: // Eksport
                                    if (std::fabs(record->power_export - target) <= tolerance) {
                                        std::cout << "====================================================================" << std::endl;
                                        std::cout << "Znaleziono rekord: " << record->power_export << " W" << std::endl;
                                        std::cout << std::endl;
                                        record->show();
                                        std::cout << std::endl;
                                        std::cout << "====================================================================" << std::endl;
                                    }
                                    break;
                                case 3: // Import
                                    if (std::fabs(record->power_import - target) <= tolerance) {
                                        std::cout << "====================================================================" << std::endl;
                                        std::cout << "Znaleziono rekord: " << record->power_import << " W" << std::endl;
                                        std::cout << std::endl;
                                        record->show();
                                        std::cout << std::endl;
                                        std::cout << "====================================================================" << std::endl;
                                    }
                                    break;
                                case 4: // Pobór
                                    if (std::fabs(record->power_consumption - target) <= tolerance) {
                                        std::cout << "====================================================================" << std::endl;
                                        std::cout << "Znaleziono rekord: " << record->power_consumption << " W" << std::endl;
                                        std::cout << std::endl;
                                        record->show();
                                        std::cout << std::endl;
                                        std::cout << "====================================================================" << std::endl;
                                    }
                                    break;
                                case 5: // Produkcja
                                    if (std::fabs(record->power_production - target) <= tolerance) {
                                        std::cout << "====================================================================" << std::endl;
                                        std::cout << "Znaleziono rekord: " << record->power_production << " W" << std::endl;
                                        std::cout << std::endl;
                                        record->show();
                                        std::cout << std::endl;
                                        std::cout << "====================================================================" << std::endl;
                                    }
                                    break;
                                default:
                                    std::cout << "Zly wybor" << std::endl;
                                    break;
                            }
                            if (std::fabs(record->power_import - target) <= tolerance) {
                                std::cout << "Znaleziono rekord: " << record->power_import << " W" << std::endl;
                            }
                        }
                    }
                }
            }
        }
    }
}

void DataAnalysis::printSummary() {
    int correctRecords = 0;
    int incorrectRecords = 0;
    int totalDays = 0;
    int totalQuarters = 0;

    // Iteracja po latach, miesiącach, dniach i ćwiartkach
    for (auto& yearPair : data) {
        for (auto& monthPair : yearPair.second) {
            for (auto& dayPair : monthPair.second) {
                for (auto& quarterPair : dayPair.second) {
                    TreeNode* node = quarterPair.second;
                    if (node != nullptr) {
                        auto records = node->getRecords();
                        for (auto& record : records) {
                            // Sprawdzamy, czy rekord jest poprawny (np. przez funkcję isValid)
                            if (record->isValid()) {
                                correctRecords++;
                            } else {
                                incorrectRecords++;
                                // Zapisz niepoprawny rekord do pliku log_error_data_godzina.txt
                                std::ofstream errorLog("log_error_" + getCurrentDateTime() + ".txt", std::ios::app);
                                errorLog << "Niepoprawny rekord: " << record->toString() << std::endl;
                                errorLog.close();
                            }
                        }

                        // Zliczanie dni i ćwiartek z danymi
                        totalDays++;
                        totalQuarters += node->getRecords().size();
                    }
                }
            }
        }
    }

    // Wypisywanie podsumowania
    std::cout << "Podsumowanie danych:" << std::endl;
    std::cout << "Liczba poprawnych rekordów: " << correctRecords << std::endl;
    std::cout << "Liczba niepoprawnych rekordów: " << incorrectRecords << std::endl;
    std::cout << "Liczba dni z danymi: " << totalDays << std::endl;
    std::cout << "Liczba ćwiartek z danymi: " << totalQuarters << std::endl;

    // Zapisanie poprawnych rekordów do log_data_godzina.txt
    std::ofstream dataLog("log_data_" + getCurrentDateTime() + ".txt", std::ios::app);
    dataLog << "Poprawne rekordy: " << correctRecords << std::endl;
    dataLog << "Niepoprawne rekordy: " << incorrectRecords << std::endl;
    dataLog.close();
}

std::string DataAnalysis::getCurrentDateTime() {
    std::time_t now = std::time(0);
    std::tm localTime;
    localtime_s(&localTime, &now);
    std::ostringstream oss;
    oss << std::put_time(&localTime, "%Y-%m-%d_%H-%M-%S");
    return oss.str();
}
//======================================================================================================================

// Funkcja zapisująca dane do pliku binarnego
void DataAnalysis::saveToBinaryFile(std::string& fileName) {
    std::ofstream outFile(fileName, std::ios::binary);
    
    if (!outFile) {
        std::cerr << "Błąd otwarcia pliku do zapisu.\n";
        return;
    }

    // Zapisujemy dane do pliku binarnego
    for (const auto& yearPair : data) {
        for (const auto& monthPair : yearPair.second) {
            for (const auto& dayPair : monthPair.second) {
                for (const auto& quarterPair : dayPair.second) {
                    TreeNode* node = quarterPair.second;
                    if (node != nullptr) {
                        auto records = node->getRecords();
                        for (auto& record : records) {
                            // Zapisujemy każdy rekord do pliku
                            outFile.write(reinterpret_cast<const char*>(&record), sizeof(Record));
                        }
                    }
                }
            }
        }
    }

    outFile.close();
    std::cout << "Dane zostały zapisane do pliku: " << fileName << std::endl;
}

// Funkcja ładująca dane z pliku binarnego
void DataAnalysis::loadFromBinaryFile(std::string& fileName) {
    std::ifstream inFile(fileName, std::ios::binary);
    
    if (!inFile) {
        std::cerr << "Błąd otwarcia pliku do odczytu.\n";
        return;
    }

    // Ładujemy dane z pliku binarnego
    Record record;
    while (inFile.read(reinterpret_cast<char*>(&record), sizeof(Record))) {
        // Przechowujemy dane w odpowiednich strukturach
        // W zależności od struktury danych, musimy umieścić rekordy w odpowiednich węzłach drzewa
        // Na przykład: dodajemy rekord do odpowiedniego węzła w drzewie:
        addRecordToTree(&record);
    }

    inFile.close();
    std::cout << "Dane zostały wczytane z pliku: " << fileName << std::endl;
}

void DataAnalysis::addRecordToTree(Record* record) {
    // Parsowanie daty
    std::tm tm = record->timestamp;
    int year = tm.tm_year + 1900;
    int month = tm.tm_mon + 1;
    int day = tm.tm_mday;
    int hour = tm.tm_hour;

    // Ćwiartki
    int quarter = (hour < 6) ? 0 : (hour < 12) ? 1 : (hour < 18) ? 2 : 3;

    // Dodaj rekord do odpowiedniego węzła w drzewie
    if (data[year][month][day].find(quarter) == data[year][month][day].end()) {
        data[year][month][day][quarter] = new TreeNode(year, month, day, quarter);
    }
    data[year][month][day][quarter]->addRecord(record);
}