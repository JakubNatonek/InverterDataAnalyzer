/**
 * @file TreeNode.cpp
 * @brief Implementacja klasy TreeNode.
 */
#include <iostream>
#include "TreeNode.h"



/**
 * @brief Konstruktor klasy TreeNode.
 * 
 * @param year Rok.
 * @param month Miesiąc.
 * @param day Dzień.
 * @param quarter Kwartał.
 */
TreeNode::TreeNode(int year, int month, int day, int quarter) {
    this->year = year;
    this->month = month;
    this->day = day;
    this->quarter = quarter;
    show();
}


/**
 * @brief Dodaje rekord do węzła drzewa.
 * 
 * @param record Wskaźnik na obiekt typu Record.
 */
void TreeNode::addRecord(Record* record) {
    this->records.push_back(record);
}

/**
 * @brief Zwraca wektor rekordów przechowywanych w węźle drzewa.
 * 
 * @return std::vector<Record*> Wektor wskaźników na obiekty typu Record.
 */
std::vector<Record*> TreeNode::getRecords() {
    return this->records;
}
