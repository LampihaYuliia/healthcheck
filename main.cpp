#include <iostream>
#include <vector>
#include "Diary.h"

int main() {
    std::vector<Diary> days;  // Вектор для хранения объектов Diary

    while (true) {
        std::cout << "\nMenu:\n";
        std::cout << "1. Add a new diary entry\n";
        std::cout << "2. View all diary entries\n";
        std::cout << "3. Search for a diary entry by date\n";
        std::cout << "4. Exit\n";
        std::cout << "Choose an option: ";

        int choice;
        std::cin >> choice;
        std::cin.ignore();

        if (choice == 1) {
            Diary newDiary;
            newDiary.Date();

            std::cout << "Add an exercise to the diary:\n";
            newDiary.addExercise();

            std::cout << "Add food to the diary:\n";
            newDiary.addFood();

            days.push_back(newDiary);

        } else if (choice == 2) {

            if (days.empty()) {
                std::cout << "No diary entries available.\n";
            } else {
                for (size_t i = 0; i < days.size(); ++i) {
                    std::cout << "\n===== Diary Entry " << i + 1 << " =====\n";
                    days[i].displayLog();
                }
            }

        } else if (choice == 3) {
            std::cout << "Enter the date (dd-mm-yyyy): ";
            std::string searchDate;
            std::getline(std::cin, searchDate);

            bool found = false;

            for (const auto& day : days) {
                if (day.getDate() == searchDate) {
                    std::cout << "\n===== Diary Entry for " << searchDate << " =====\n";
                    day.displayLog();
                    found = true;
                    break;
                }
            }

            if (!found) {
                std::cout << "No diary entry found for date: " << searchDate << "\n";
            }

        } else if (choice == 4) {
            std::cout << "Exiting...\n";
            break;
        } else {
            std::cout << "Invalid option. Please try again.\n";
        }
    }

    return 0;
}
