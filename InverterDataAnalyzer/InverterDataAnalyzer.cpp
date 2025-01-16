#include "src/Record/Record.h"
#include "src/TreeNode/TreeNode.h"
#include "src/DataAnalysis/DataAnalysis.h"
#include <iostream>

/**
 * @brief Wyświetla menu główne programu.
 */
void displayMenu() {
    std::cout << "\nWybierz opcje:\n";
    std::cout << "1. Wczytaj plik CSV\n";
    std::cout << "2. Zapisz dane do pliku binarnego\n";
    std::cout << "3. Odczytaj dane z pliku binarnego\n";
    std::cout << "4. Wyswietl sumy autokonsumpcji, eksportu, importu, poboru, produkcji\n";
    std::cout << "5. Wyswietl srednie wartosci autokonsumpcji, eksportu, importu, poboru, produkcji\n";
    std::cout << "6. Porownaj wartosci dla dwoch przedzialow czasowych\n";
    std::cout << "7. Wyszukaj dane wedlug warunkow\n";
    std::cout << "8. Zakoncz program\n";
}

/**
 * @brief Obsługuje wybór opcji z menu.
 *
 * @param choice Wybrana opcja z menu.
 * @param analysis Obiekt klasy DataAnalysis do analizy danych.
 */
void handleMenuSelection(int choice, DataAnalysis& analysis) {
    switch (choice) {
    case 1:
    {
        std::string fileName;
        std::cout << "Podaj nazwe pliku CSV do wczytania: ";
        std::cin >> fileName;
        analysis.loadDataFromCSV(fileName);
        break;
    }
    case 2:
    {
        std::string fileName;
        std::cout << "Podaj nazwe pliku binarnego do zapisania: ";
        std::cin >> fileName;
        analysis.saveToBinaryFile(fileName);
        break;
    }
    case 3:
    {
        std::string fileName;
        std::cout << "Podaj nazwe pliku binarnego do odczytu: ";
        std::cin >> fileName;
        analysis.loadFromBinaryFile(fileName);
        break;
    }
    case 4:
    {
        int helper = 0;
        std::cout << "1. autokonsumpcji" << std::endl;
        std::cout << "2. eksportu" << std::endl;
        std::cout << "3. importu" << std::endl;
        std::cout << "4. poboru" << std::endl;
        std::cout << "5. produkcji" << std::endl;
        std::cin >> helper;

        int startYear1, startMonth1, startDay1, startQuarter1;
        int endYear1, endMonth1, endDay1, endQuarter1;

        std::cout << "Podaj date poczatkowa dla okresu 1 (rok miesiac dzien kwartal): ";
        std::cin >> startYear1 >> startMonth1 >> startDay1 >> startQuarter1;
        std::cout << "Podaj date koncowa dla okresu 1 (rok miesiac dzien kwartal): ";
        std::cin >> endYear1 >> endMonth1 >> endDay1 >> endQuarter1;

        switch (helper) {
        case 1:
            analysis.sumAutokonsumpcja(startYear1, startMonth1, startDay1, startQuarter1,
                endYear1, endMonth1, endDay1, endQuarter1);
            break;
        case 2:
            analysis.sumEksport(startYear1, startMonth1, startDay1, startQuarter1,
                endYear1, endMonth1, endDay1, endQuarter1);
            break;
        case 3:
            analysis.sumImport(startYear1, startMonth1, startDay1, startQuarter1,
                endYear1, endMonth1, endDay1, endQuarter1);
            break;
        case 4:
            analysis.sumPobor(startYear1, startMonth1, startDay1, startQuarter1,
                endYear1, endMonth1, endDay1, endQuarter1);
            break;
        case 5:
            analysis.sumProdukcja(startYear1, startMonth1, startDay1, startQuarter1,
                endYear1, endMonth1, endDay1, endQuarter1);
            break;
        default:
            break;
        }
        break;
    }
    case 5:
    {
        int helper = 0;
        std::cout << "1. autokonsumpcji" << std::endl;
        std::cout << "2. eksportu" << std::endl;
        std::cout << "3. importu" << std::endl;
        std::cout << "4. poboru" << std::endl;
        std::cout << "5. produkcji" << std::endl;
        std::cin >> helper;

        int startYear1, startMonth1, startDay1, startQuarter1;
        int endYear1, endMonth1, endDay1, endQuarter1;

        std::cout << "Podaj date poczatkowa dla okresu 1 (rok miesiac dzien kwartal): ";
        std::cin >> startYear1 >> startMonth1 >> startDay1 >> startQuarter1;
        std::cout << "Podaj date koncowa dla okresu 1 (rok miesiac dzien kwartal): ";
        std::cin >> endYear1 >> endMonth1 >> endDay1 >> endQuarter1;

        switch (helper) {
        case 1:
            analysis.avgAutokonsumpcja(startYear1, startMonth1, startDay1, startQuarter1,
                endYear1, endMonth1, endDay1, endQuarter1);
            break;
        case 2:
            analysis.avgEksport(startYear1, startMonth1, startDay1, startQuarter1,
                endYear1, endMonth1, endDay1, endQuarter1);
            break;
        case 3:
            analysis.avgImport(startYear1, startMonth1, startDay1, startQuarter1,
                endYear1, endMonth1, endDay1, endQuarter1);
            break;
        case 4:
            analysis.avgPobor(startYear1, startMonth1, startDay1, startQuarter1,
                endYear1, endMonth1, endDay1, endQuarter1);
            break;
        case 5:
            analysis.avgProdukcja(startYear1, startMonth1, startDay1, startQuarter1,
                endYear1, endMonth1, endDay1, endQuarter1);
            break;
        default:
            break;
        }
        break;
    }
    case 6:
    {
        int helper = 0;
        std::cout << "1. autokonsumpcji" << std::endl;
        std::cout << "2. eksportu" << std::endl;
        std::cout << "3. importu" << std::endl;
        std::cout << "4. poboru" << std::endl;
        std::cout << "5. produkcji" << std::endl;
        std::cin >> helper;

        int startYear1, startMonth1, startDay1, startQuarter1;
        int endYear1, endMonth1, endDay1, endQuarter1;
        int startYear2, startMonth2, startDay2, startQuarter2;
        int endYear2, endMonth2, endDay2, endQuarter2;
        std::cout << "Podaj date poczatkowa dla okresu 1 (rok miesiac dzien kwartal): ";
        std::cin >> startYear1 >> startMonth1 >> startDay1 >> startQuarter1;
        std::cout << "Podaj date koncowa dla okresu 1 (rok miesiac dzien kwartal): ";
        std::cin >> endYear1 >> endMonth1 >> endDay1 >> endQuarter1;
        std::cout << "Podaj date poczatkowa dla okresu 2 (rok miesiac dzien kwartal): ";
        std::cin >> startYear2 >> startMonth2 >> startDay2 >> startQuarter2;
        std::cout << "Podaj date koncowa dla okresu 2 (rok miesiac dzien kwartal): ";
        std::cin >> endYear2 >> endMonth2 >> endDay2 >> endQuarter2;

        switch (helper) {
        case 1:
            analysis.compareAutokonsumpcja(startYear1, startMonth1, startDay1, startQuarter1, endYear1, endMonth1, endDay1,
                endQuarter1, startYear2, startMonth2, startDay2, startQuarter2, endYear2, endMonth2, endDay2, endQuarter2);
            break;
        case 2:
            analysis.compareEksport(startYear1, startMonth1, startDay1, startQuarter1, endYear1, endMonth1, endDay1,
                endQuarter1, startYear2, startMonth2, startDay2, startQuarter2, endYear2, endMonth2, endDay2, endQuarter2);
            break;
        case 3:
            analysis.compareImport(startYear1, startMonth1, startDay1, startQuarter1, endYear1, endMonth1, endDay1,
                endQuarter1, startYear2, startMonth2, startDay2, startQuarter2, endYear2, endMonth2, endDay2, endQuarter2);
            break;
        case 4:
            analysis.comparePobor(startYear1, startMonth1, startDay1, startQuarter1, endYear1, endMonth1, endDay1,
                endQuarter1, startYear2, startMonth2, startDay2, startQuarter2, endYear2, endMonth2, endDay2, endQuarter2);
            break;
        case 5:
            analysis.compareProdukcja(startYear1, startMonth1, startDay1, startQuarter1, endYear1, endMonth1, endDay1,
                endQuarter1, startYear2, startMonth2, startDay2, startQuarter2, endYear2, endMonth2, endDay2, endQuarter2);
            break;
        default:
            break;
        }
        break;
    }
    case 7:
    {
        int helper = 0;
        std::cout << "1. autokonsumpcji" << std::endl;
        std::cout << "2. eksportu" << std::endl;
        std::cout << "3. importu" << std::endl;
        std::cout << "4. poboru" << std::endl;
        std::cout << "5. produkcji" << std::endl;
        std::cout << "Podaj wartosci dla funkcji searchImport:" << std::endl;
        std::cin >> helper;

        double target, tolerance;


        std::cout << "Target: ";
        std::cin >> target;
        std::cout << "Tolerance: ";
        std::cin >> tolerance;

        int startYear1, startMonth1, startDay1, startQuarter1;
        int endYear1, endMonth1, endDay1, endQuarter1;

        std::cout << "Podaj date poczatkowa dla okresu 1 (rok miesiac dzien kwartal): ";
        std::cin >> startYear1 >> startMonth1 >> startDay1 >> startQuarter1;
        std::cout << "Podaj date koncowa dla okresu 1 (rok miesiac dzien kwartal): ";
        std::cin >> endYear1 >> endMonth1 >> endDay1 >> endQuarter1;
        analysis.searchImport(target, tolerance, startYear1, startMonth1, startDay1, startQuarter1,
            endYear1, endMonth1, endDay1, endQuarter1, helper);
        break;
    }
    case 8:
        std::cout << "Zakonczenie programu...\n";
        break;
    default:
        std::cout << "Nieprawidlowy wybor, sprobuj ponownie.\n";
        break;
    }
}

/**
 * @brief Główna funkcja programu.
 *
 * @param argc Liczba argumentów wiersza poleceń.
 * @param argv Tablica argumentów wiersza poleceń.
 * @return int Kod zakończenia programu.
 */
int main(int argc, char* argv[])
{
    DataAnalysis analysis;

    int choice = 0;
    bool running = true;

    while (running) {
        displayMenu();
        std::cout << "Wybierz opcje (1-8): ";
        std::cin >> choice;

        if (choice == 8) {
            running = false;
        }

        handleMenuSelection(choice, analysis);
    }

    return 0;
}

//Time,Autokonsumpcja (W),Eksport (W),Import (W),Pobor (W),Produkcja (W)
//01.10.2020 0:00,"0","0","406.8323","406.8323