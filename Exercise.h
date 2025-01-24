#ifndef EXERCISE_H_INCLUDED
#define EXERCISE_H_INCLUDED

#include <string>
#include <iostream>

class Exercise {
private:
    std::string name;
    double caloriesPerRepetition;

public:
    Exercise(std::string name, double caloriesPerRepetition);

    std::string getName() const;
    double getCaloriesPerRepetition() const;

    void displayInfo() const;
};

#endif // EXERCISE_H_INCLUDED
