#include "src/Record/Record.h"
#include "src/TreeNode/TreeNode.h"
#include "src/DataAnalysis/DataAnalysis.h"
#include <iostream>

void displayMenu() {
    std::cout << "\nWybierz opcję:\n";
    std::cout << "1. Wczytaj plik CSV\n";
    std::cout << "2. Zapisz dane do pliku binarnego\n";
    std::cout << "3. Odczytaj dane z pliku binarnego\n";
    std::cout << "4. Wyświetl sumy autokonsumpcji, eksportu, importu, poboru, produkcji\n";
    std::cout << "5. Wyświetl średnie wartości autokonsumpcji, eksportu, importu, poboru, produkcji\n";
    std::cout << "6. Porównaj wartości dla dwóch przedziałów czasowych\n";
    std::cout << "7. Wyszukaj dane według warunków\n";
    std::cout << "8. Zakończ program\n";
}


void handleMenuSelection(int choice, DataAnalysis& analysis) {
    switch (choice) {
        case 1:
            {
                std::string fileName;
                std::cout << "Podaj nazwę pliku CSV do wczytania: ";
                std::cin >> fileName;
                analysis.loadDataFromCSV(fileName);
                break;
            }
        case 2:
            {
                std::string fileName;
                std::cout << "Podaj nazwę pliku binarnego do zapisania: ";
                std::cin >> fileName;
                analysis.saveToBinaryFile(fileName);
                break;
            }
        case 3:
            {
                std::string fileName;
                std::cout << "Podaj nazwę pliku binarnego do odczytu: ";
                std::cin >> fileName;
                analysis.loadFromBinaryFile(fileName);
                break;
            }
        case 4:
            {
                int helper = 0;
                std::cout << "1.autokonsumpcji" << std::endl;
                std::cout << "2.eksportu" << std::endl;
                std::cout << "3.importu" << std::endl;
                std::cout << "4.poboru" << std::endl;
                std::cout << "5.produkcji" << std::endl;
                std::cin >> helper;

                int startYear1, startMonth1, startDay1, startQuarter1;
                int endYear1, endMonth1, endDay1, endQuarter1;

                std::cout << "Enter start date for period 1 (year month day quarter): ";
                std::cin >> startYear1 >> startMonth1 >> startDay1 >> startQuarter1;
                std::cout << "Enter end date for period 1 (year month day quarter): ";
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
                std::cout << "1.autokonsumpcji" << std::endl;
                std::cout << "2.eksportu" << std::endl;
                std::cout << "3.importu" << std::endl;
                std::cout << "4.poboru" << std::endl;
                std::cout << "5.produkcji" << std::endl;
                std::cin >> helper;

                int startYear1, startMonth1, startDay1, startQuarter1;
                int endYear1, endMonth1, endDay1, endQuarter1;

                std::cout << "Enter start date for period 1 (year month day quarter): ";
                std::cin >> startYear1 >> startMonth1 >> startDay1 >> startQuarter1;
                std::cout << "Enter end date for period 1 (year month day quarter): ";
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
                std::cout << "1.autokonsumpcji" << std::endl;
                std::cout << "2.eksportu" << std::endl;
                std::cout << "3.importu" << std::endl;
                std::cout << "4.poboru" << std::endl;
                std::cout << "5.produkcji" << std::endl;
                std::cin >> helper;

                int startYear1, startMonth1, startDay1, startQuarter1;
                int endYear1, endMonth1, endDay1, endQuarter1;
                int startYear2, startMonth2, startDay2, startQuarter2;
                int endYear2, endMonth2, endDay2, endQuarter2;
                std::cout << "Enter start date for period 1 (year month day quarter): ";
                std::cin >> startYear1 >> startMonth1 >> startDay1 >> startQuarter1;
                std::cout << "Enter end date for period 1 (year month day quarter): ";
                std::cin >> endYear1 >> endMonth1 >> endDay1 >> endQuarter1;
                std::cout << "Enter start date for period 2 (year month day quarter): ";
                std::cin >> startYear2 >> startMonth2 >> startDay2 >> startQuarter2;
                std::cout << "Enter end date for period 2 (year month day quarter): ";
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
                std::cout << "1.autokonsumpcji" << std::endl;
                std::cout << "2.eksportu" << std::endl;
                std::cout << "3.importu" << std::endl;
                std::cout << "4.poboru" << std::endl;
                std::cout << "5.produkcji" << std::endl;
                std::cin >> helper;

                double target, tolerance;

                std::cout << "Podaj wartości dla funkcji searchImport:" << std::endl;
                std::cout << "Target: ";
                std::cin >> target;
                std::cout << "Tolerance: ";
                std::cin >> tolerance;

                int startYear1, startMonth1, startDay1, startQuarter1;
                int endYear1, endMonth1, endDay1, endQuarter1;

                std::cout << "Enter start date for period 1 (year month day quarter): ";
                std::cin >> startYear1 >> startMonth1 >> startDay1 >> startQuarter1;
                std::cout << "Enter end date for period 1 (year month day quarter): ";
                std::cin >> endYear1 >> endMonth1 >> endDay1 >> endQuarter1;
                analysis.searchImport( target,  tolerance,  startYear1,  startMonth1,  startDay1, startQuarter1,
                                  endYear1,  endMonth1,  endDay1,  endQuarter1, helper);
                break;
            }
        case 8:
            std::cout << "Zakończenie programu...\n";
            break;
        default:
            std::cout << "Nieprawidłowy wybór, spróbuj ponownie.\n";
            break;
    }
}

int main(int argc, char* argv[])
{
    DataAnalysis analysis;

    int choice;
    bool running = true;

    while (running) {
        displayMenu();
        std::cout << "Wybierz opcję (1-8): ";
        
        // Sprawdzamy, czy użytkownik wprowadził poprawny numer
        if (!(std::cin >> choice)) {
            std::cin.clear();  // Wyczyść błąd strumienia
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Ignoruj błędne dane
            std::cout << "Proszę podać liczbę od 1 do 8.\n";
            continue;
        }
        
        if (choice == 8) {
            running = false;
        }

        handleMenuSelection(choice, analysis);
    }
    
    return 0;
}

//Time,Autokonsumpcja (W),Eksport (W),Import (W),Pobór (W),Produkcja (W)
//01.10.2020 0:00,"0","0","406.8323","406.8323","0"