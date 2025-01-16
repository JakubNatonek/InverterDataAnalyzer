#pragma once
#pragma once
#include <string>
#include <ctime>

class Record {
    private:
        std::tm timestamp;  // Data i godzina pomiaru
        double auto_consumption;
        double power_export;
        double power_import;
        double power_consumption;
        double power_production;
    public:
        Record(const std::string& timestamp, double auto_consumption, double power_export, double power_import, double power_consumption, double power_production);
        
};