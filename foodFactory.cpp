#include "Food.h"
#include "FoodFactory.h"


Food* MeatFactory::createFood(const std::string& name, double calories, double protein, double fat, double carbs,
                              const std::vector<std::string>& additionalParams) {
    std::string part = additionalParams.size() > 0 ? additionalParams[0] : "Unknown";
    bool isDiet = additionalParams.size() > 1 ? (additionalParams[1] == "true") : true;

    return new Meat(name, calories, protein, fat, carbs, part, isDiet);
}

Food* VegetableFactory::createFood(const std::string& name, double calories, double protein, double fat, double carbs,
                                   const std::vector<std::string>& additionalParams) {
    bool isLeafy = additionalParams.size() > 0 ? (additionalParams[0] == "true") : true;
    std::string season = additionalParams.size() > 1 ? additionalParams[1] : "Spring";

    return new Vegetable(name, calories, protein, fat, carbs, isLeafy, season);
}

Food* FruitFactory::createFood(const std::string& name, double calories, double protein, double fat, double carbs,
                               const std::vector<std::string>& additionalParams) {
    double sugarContent = additionalParams.size() > 0 ? std::stod(additionalParams[0]) : 10.0;
    std::string origin = additionalParams.size() > 1 ? additionalParams[1] : "Imported";

    return new Fruit(name, calories, protein, fat, carbs, sugarContent, origin);
}

Food* SideDishFactory::createFood(const std::string& name, double calories, double protein, double fat, double carbs,
                                  const std::vector<std::string>& additionalParams) {
    std::string preparationMethod = additionalParams.size() > 0 ? additionalParams[0] : "Boiled";
    bool isVegetarian = additionalParams.size() > 1 ? (additionalParams[1] == "true") : true;

    return new SideDish(name, calories, protein, fat, carbs, preparationMethod, isVegetarian);
}
