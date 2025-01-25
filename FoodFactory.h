#ifndef FOODFACTORY_H
#define FOODFACTORY_H

#include "Food.h"
#include <string>
#include <vector>

class FoodFactory {
public:
    virtual ~FoodFactory() = default;

    virtual Food* createFood(const std::string& name, double calories, double protein, double fat, double carbs,
                             const std::vector<std::string>& additionalParams) = 0;
};

class MeatFactory : public FoodFactory {
public:
    Food* createFood(const std::string& name, double calories, double protein, double fat, double carbs,
                     const std::vector<std::string>& additionalParams) override;
};

class VegetableFactory : public FoodFactory {
public:
    Food* createFood(const std::string& name, double calories, double protein, double fat, double carbs,
                     const std::vector<std::string>& additionalParams) override;
};

class FruitFactory : public FoodFactory {
public:
    Food* createFood(const std::string& name, double calories, double protein, double fat, double carbs,
                     const std::vector<std::string>& additionalParams) override;
};

class SideDishFactory : public FoodFactory {
public:
    Food* createFood(const std::string& name, double calories, double protein, double fat, double carbs,
                     const std::vector<std::string>& additionalParams) override;
};

#endif // FOODFACTORY_H


