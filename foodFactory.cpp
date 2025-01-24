#include "FoodFactory.h"
#include "Food.h"

Food* FoodFactory::createFood(const std::string& type, const std::string& name, double calories,
                              double protein, double fat, double carbs, const std::string& extra1,
                              bool extra2) {
    if (type == "Meat") {
        return new Meat(name, calories, protein, fat, carbs, extra1, extra2);
    } else if (type == "Vegetable") {
        return new Vegetable(name, calories, protein, fat, carbs, extra2, extra1);
    } else if (type == "Fruit") {
        return new Fruit(name, calories, protein, fat, carbs, std::stod(extra1), extra2 ? "Local" : "Imported");
    } else if (type == "SideDish") {
        return new SideDish(name, calories, protein, fat, carbs, extra1, extra2);
    } else {
        throw std::invalid_argument("Unknown food type: " + type);
    }
}
