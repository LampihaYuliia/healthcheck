#include "Exercise.h"

Exercise::Exercise(std::string name, double caloriesPerRepetition)
    : name(name), caloriesPerRepetition(caloriesPerRepetition) {}

std::string Exercise::getName() const {
    return name;
}

double Exercise::getCaloriesPerRepetition() const {
    return caloriesPerRepetition;
}

void Exercise::displayInfo() const {
    std::cout << "Exercise: " << name
              << ", Calories per repetition: " << caloriesPerRepetition << " kcal" << std::endl;
}
