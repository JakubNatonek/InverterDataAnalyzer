#include "TreeNode.h"

TreeNode::TreeNode(int year, int month, int day, int quarter) {
    this->year = year;
    this->month = month;
    this->day = day;
    this->quarter = quarter;
}
    

void TreeNode::addRecord(Record* record) {
    this->records.push_back(record);
}

std::vector<Record*> TreeNode::getRecords() {
    return this->records;
}
