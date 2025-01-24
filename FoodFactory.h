#ifndef FOODFACTORY_H_INCLUDED
#define FOODFACTORY_H_INCLUDED

#include "Food.h"
#include <string>
#include <stdexcept>

class FoodFactory {
public:
    static Food* createFood(const std::string& type, const std::string& name, double calories,
                            double protein, double fat, double carbs, const std::string& extra1 = "",
                            bool extra2 = false);
};

#endif // FOODFACTORY_H_INCLUDED

