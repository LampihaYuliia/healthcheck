#ifndef FOOD_H_INCLUDED
#define FOOD_H_INCLUDED

#include <string>
#include <iostream>
#include <vector>
#include <iomanip>

class Food {
protected:
    std::string name;
    double caloriesPer100g;
    double proteinPer100g;
    double fatPer100g;
    double carbsPer100g;

public:

    Food(std::string name, double calories, double protein, double fat, double carbs);

    virtual void displayInfo() const;
    virtual Food* clone() const = 0;
    virtual Food* createWithAdjustedValues(double calories, double protein, double fat, double carbs) const = 0;

    double calculateCalories(double grams) const;
    double calculateProtein(double grams) const;
    double calculateFat(double grams) const;
    double calculateCarbs(double grams) const;

    std::string getName() const;
    virtual ~Food() {}
};

class Meat : public Food {
private:
    std::string part;
    bool isDiet;

public:
    Meat(std::string name, double calories, double protein, double fat, double carbs,
         std::string part, bool isDiet);

    void displayInfo() const override;
    Food* clone() const override;
    Food* createWithAdjustedValues(double calories, double protein, double fat, double carbs) const override;
};

class Vegetable : public Food {
private:
    bool isLeafy;
    std::string season;

public:
    Vegetable(std::string name, double calories, double protein, double fat, double carbs,
              bool isLeafy, std::string season);

    void displayInfo() const override;
    Food* clone() const override;
    Food* createWithAdjustedValues(double calories, double protein, double fat, double carbs) const override;
};

class Fruit : public Food {
private:
    double sugarContent;
    std::string origin;

public:
    Fruit(std::string name, double calories, double protein, double fat, double carbs,
          double sugarContent, std::string origin);

    void displayInfo() const override;
    Food* clone() const override;
    Food* createWithAdjustedValues(double calories, double protein, double fat, double carbs) const override;
};

class SideDish : public Food {
private:
    std::string preparationMethod;
    bool isVegetarian;

public:
    SideDish(std::string name, double calories, double protein, double fat, double carbs,
             std::string preparationMethod, bool isVegetarian);

    void displayInfo() const override;
    Food* clone() const override;
    Food* createWithAdjustedValues(double calories, double protein, double fat, double carbs) const override;
};

#endif // FOOD_H_INCLUDED
