#include "Food.h"

Food::Food(std::string name, double calories, double protein, double fat, double carbs)
    : name(name), caloriesPer100g(calories), proteinPer100g(protein), fatPer100g(fat), carbsPer100g(carbs) {}

void Food::displayInfo() const {
    std::cout << std::setw(20) << name
              << " | Calories: " << caloriesPer100g
              << " kcal | Protein: " << proteinPer100g
              << "g | Fat: " << fatPer100g
              << "g | Carbs: " << carbsPer100g << "g" << std::endl;
}

double Food::calculateCalories(double grams) const {
    return (caloriesPer100g / 100) * grams;
}

double Food::calculateProtein(double grams) const {
    return (proteinPer100g / 100) * grams;
}

double Food::calculateFat(double grams) const {
    return (fatPer100g / 100) * grams;
}

double Food::calculateCarbs(double grams) const {
    return (carbsPer100g / 100) * grams;
}

std::string Food::getName() const {
    return name;
}

// Ðåàë³çàö³ÿ Meat
Meat::Meat(std::string name, double calories, double protein, double fat, double carbs,
           std::string part, bool isDiet)
    : Food(name, calories, protein, fat, carbs), part(part), isDiet(isDiet) {}

void Meat::displayInfo() const {
    Food::displayInfo();
    std::cout << "What part: " << part << ", Is it diet food: " << (isDiet ? "Yes" : "No") << std::endl;
}

Food* Meat::clone() const {
    return new Meat(*this);
}

Food* Meat::createWithAdjustedValues(double calories, double protein, double fat, double carbs) const {
    return new Meat(name, calories, protein, fat, carbs, part, isDiet);
}

// Ðåàë³çàö³ÿ Vegetable
Vegetable::Vegetable(std::string name, double calories, double protein, double fat, double carbs,
                     bool isLeafy, std::string season)
    : Food(name, calories, protein, fat, carbs), isLeafy(isLeafy), season(season) {}

void Vegetable::displayInfo() const {
    Food::displayInfo();
    std::cout << "Leafy: " << (isLeafy ? "Yes" : "No") << ", Season: " << season << std::endl;
}

Food* Vegetable::clone() const {
    return new Vegetable(*this);
}

Food* Vegetable::createWithAdjustedValues(double calories, double protein, double fat, double carbs) const {
    return new Vegetable(name, calories, protein, fat, carbs, isLeafy, season);
}

Fruit::Fruit(std::string name, double calories, double protein, double fat, double carbs,
             double sugarContent, std::string origin)
    : Food(name, calories, protein, fat, carbs), sugarContent(sugarContent), origin(origin) {}

void Fruit::displayInfo() const {
    Food::displayInfo();
    std::cout << "Sugar Content: " << sugarContent << "g, Origin: " << origin << std::endl;
}

Food* Fruit::clone() const {
    return new Fruit(*this);
}

Food* Fruit::createWithAdjustedValues(double calories, double protein, double fat, double carbs) const {
    return new Fruit(name, calories, protein, fat, carbs, sugarContent, origin);
}

SideDish::SideDish(std::string name, double calories, double protein, double fat, double carbs,
                   std::string preparationMethod, bool isVegetarian)
    : Food(name, calories, protein, fat, carbs), preparationMethod(preparationMethod), isVegetarian(isVegetarian) {}

void SideDish::displayInfo() const {
    Food::displayInfo();
    std::cout << "Preparation Method: " << preparationMethod
              << ", Vegetarian: " << (isVegetarian ? "Yes" : "No") << std::endl;
}

Food* SideDish::clone() const {
    return new SideDish(*this);
}

Food* SideDish::createWithAdjustedValues(double calories, double protein, double fat, double carbs) const {
    return new SideDish(name, calories, protein, fat, carbs, preparationMethod, isVegetarian);
}
