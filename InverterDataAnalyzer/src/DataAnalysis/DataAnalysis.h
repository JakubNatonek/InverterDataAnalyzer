#pragma once
#include <map>
#include <string>
#include "../TreeNode/TreeNode.h"

class DataAnalysis {
    public:
        std::map<int, std::map<int, std::map<int, std::map<int, TreeNode*>>>> data;
    
        // Wczytywanie danych
        void loadDataFromCSV(const std::string& filename);
    
        // Operacje na danych
        double sumAutokonsumpcja(int startYear, int startMonth, int startDay, int startQuarter, int endYear, int endMonth, int endDay, int endQuarter);
        double sumEksport(int startYear, int startMonth, int startDay, int startQuarter, int endYear, int endMonth, int endDay, int endQuarter);
        double sumImport(int startYear, int startMonth, int startDay, int startQuarter, int endYear, int endMonth, int endDay, int endQuarter);
        double sumPobor(int startYear, int startMonth, int startDay, int startQuarter, int endYear, int endMonth, int endDay, int endQuarter);
        double sumProdukcja(int startYear, int startMonth, int startDay, int startQuarter, int endYear, int endMonth, int endDay, int endQuarter);

        // Średnie
        double avgAutokonsumpcja(int startYear, int startMonth, int startDay, int startQuarter, int endYear, int endMonth, int endDay, int endQuarter);
        double avgEksport(int startYear, int startMonth, int startDay, int startQuarter, int endYear, int endMonth, int endDay, int endQuarter);
        double avgImport(int startYear, int startMonth, int startDay, int startQuarter, int endYear, int endMonth, int endDay, int endQuarter);
        double avgPobor(int startYear, int startMonth, int startDay, int startQuarter, int endYear, int endMonth, int endDay, int endQuarter);
        double avgProdukcja(int startYear, int startMonth, int startDay, int startQuarter, int endYear, int endMonth, int endDay, int endQuarter);

        // Porównanie dwóch przedziałów
        void compareAutokonsumpcja(int startYear1, int startMonth1, int startDay1, int startQuarter1,
                                   int endYear1, int endMonth1, int endDay1, int endQuarter1,
                                   int startYear2, int startMonth2, int startDay2, int startQuarter2,
                                   int endYear2, int endMonth2, int endDay2, int endQuarter2);

        void compareEksport(int startYear1, int startMonth1, int startDay1, int startQuarter1,
                            int endYear1, int endMonth1, int endDay1, int endQuarter1,
                            int startYear2, int startMonth2, int startDay2, int startQuarter2,
                            int endYear2, int endMonth2, int endDay2, int endQuarter2);

        void compareImport(int startYear1, int startMonth1, int startDay1, int startQuarter1,
                        int endYear1, int endMonth1, int endDay1, int endQuarter1,
                        int startYear2, int startMonth2, int startDay2, int startQuarter2,
                        int endYear2, int endMonth2, int endDay2, int endQuarter2);

        void comparePobor(int startYear1, int startMonth1, int startDay1, int startQuarter1,
                        int endYear1, int endMonth1, int endDay1, int endQuarter1,
                        int startYear2, int startMonth2, int startDay2, int startQuarter2,
                        int endYear2, int endMonth2, int endDay2, int endQuarter2);

        void compareProdukcja(int startYear1, int startMonth1, int startDay1, int startQuarter1,
                            int endYear1, int endMonth1, int endDay1, int endQuarter1,
                            int startYear2, int startMonth2, int startDay2, int startQuarter2,
                            int endYear2, int endMonth2, int endDay2, int endQuarter2);

        // Wyszukiwanie danych
        void searchImport(double target, double tolerance, int startYear, int startMonth, int startDay, int startQuarter,
                             int endYear, int endMonth, int endDay, int endQuarter, int type);
    
        // Wypisywanie podsumowania
        void printSummary();
        std::string getCurrentDateTime();

        //zapis binary
        void saveToBinaryFile(std::string& fileName);
        void loadFromBinaryFile(std::string& fileName);
        void addRecordToTree(Record* record);
};