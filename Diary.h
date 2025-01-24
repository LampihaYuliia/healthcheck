#ifndef DIARY_H_INCLUDED
#define DIARY_H_INCLUDED

#include "Food.h"
#include "Exercise.h"
#include <vector>
#include <iostream>

class Diary {
private:
    std::vector<Exercise> exercises;
    std::vector<Food*> foods;
    std::string date;

    std::vector<Food*> meatOptions;
    std::vector<Food*> vegetableOptions;
    std::vector<Food*> fruitOptions;
    std::vector<Food*> sideDishOptions;
    std::vector<Exercise> options;

    void initializeFoodOptions();
    void initializeExerciseOptions();

public:
    Diary();
    Diary(const Diary& other);
    Diary& operator=(const Diary& other);
    ~Diary();

    std::string Date();

    void addExercise();
    void addFood();

    void displayLog() const;
    void Log() const;

    const std::vector<Exercise>& getExercises() const;
    const std::vector<Food*>& getFoods() const;
    const std::string& getDate() const;
};

#endif // DIARY_H_INCLUDED
