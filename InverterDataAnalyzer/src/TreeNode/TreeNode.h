#pragma once
#include "../Record/Record.h"
#include <vector>


class TreeNode {
    public:
        int year;
        int month;
        int day;
        int quarter; // 0 - 3 dla czterech ćwiartek
        std::vector<Record*> records;  // Wskaźniki na obiekty Record

        TreeNode(int year, int month, int day, int quarter);
        void addRecord(Record* record);
        std::vector<Record*> getRecords();
};
