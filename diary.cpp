#include "Diary.h"

Diary::Diary() {
    initializeFoodOptions();
    initializeExerciseOptions();
}
Diary::Diary(const Diary& other) : date(other.date), exercises(other.exercises) {
    for (const auto food : other.foods) {
        foods.push_back(food->clone());
    }
}

Diary& Diary::operator=(const Diary& other) {
    if (this != &other) {
        for (auto food : foods) {
            delete food;
        }
        foods.clear();

        date = other.date;
        exercises = other.exercises;
        for (const auto food : other.foods) {
            foods.push_back(food->clone());
        }
    }
    return *this;
}

Diary::~Diary() {
    for (auto food : foods) delete food;
    for (auto food : meatOptions) delete food;
    for (auto food : vegetableOptions) delete food;
    for (auto food : fruitOptions) delete food;
    for (auto food : sideDishOptions) delete food;
}

void Diary::initializeExerciseOptions() {
    options = {
        Exercise("Push-Ups", 0.5),
        Exercise("Squats", 0.6),
        Exercise("Pull-ups", 1),
        Exercise("Jumping Jacks", 0.8)
    };
}

void Diary::initializeFoodOptions() {
    meatOptions = {
        new Meat("Chicken ", 165, 31, 3.6, 0, "Breast", true),
        new Meat("Beef ", 250, 26, 15, 0, "Fillet", true),
        new Meat("Pork ", 800, 2.4, 90, 0, "Fat", true)
    };

    vegetableOptions = {
        new Vegetable("Spinach", 23, 2.9, 0.4, 3.6, true, "Spring"),
        new Vegetable("Carrot", 41, 0.9, 0.2, 10, false, "Autumn"),
        new Vegetable("Broccoli", 55, 3.7, 0.6, 11.2, false, "Winter")
    };

    fruitOptions = {
        new Fruit("Apple", 52, 0.3, 0.2, 14, 12, "Poland"),
        new Fruit("Banana", 89, 1.1, 0.3, 23, 14, "Ecuador"),
        new Fruit("Orange", 47, 0.9, 0.1, 12, 8, "Spain")
    };

    sideDishOptions = {
        new SideDish("Rice", 130, 2.4, 0.3, 28, "Boiled", true),
        new SideDish("Mashed Potatoes", 88, 2, 4, 15, "Mashed", true),
        new SideDish("Pasta", 131, 5, 1.1, 25, "Boiled", false)
    };
}

std::string Diary::Date() {
    std::cout << "Enter the date (dd-mm-yyyy): ";
    std::string inputDate;
    std::getline(std::cin, inputDate);

    int day, month, year;
    sscanf(inputDate.c_str(), "%d-%d-%d", &day, &month, &year);

    char formattedDate[11];
    snprintf(formattedDate, sizeof(formattedDate), "%02d-%02d-%04d", day, month, year);

    date = std::string(formattedDate);
    return date;
}


void Diary::addExercise() {
    while (true) {
        std::cout << "\n=== Exercise Menu ===\n";
        for (size_t i = 0; i < options.size(); ++i) {
            std::cout << i + 1 << ". " << options[i].getName()
                      << " | Calories per repetition: " << options[i].getCaloriesPerRepetition() << " kcal\n";
        }
        std::cout << options.size() + 1 << ". Exit\n";
        std::cout << "Choose an exercise (1-" << options.size() + 1 << "): ";

        size_t choice;
        std::cin >> choice;

        if (choice == options.size() + 1) {
            std::cout << "Exiting exercise selection.\n";
            break;
        }

        if (choice < 1 || choice > options.size()) {
            std::cout << "Invalid choice. Please try again.\n";
            continue;
        }

        const Exercise& selectedExercise = options[choice - 1];

        std::cout << "Enter the number of repetitions for " << selectedExercise.getName() << ": ";
        int repetitions;
        std::cin >> repetitions;

        if (repetitions <= 0) {
            std::cout << "Invalid number of repetitions. Please try again.\n";
            continue;
        }

        double totalCaloriesBurned = repetitions * selectedExercise.getCaloriesPerRepetition();

        exercises.emplace_back(selectedExercise.getName(), totalCaloriesBurned);

        std::cout << "\n=== Exercise Added ===\n";
        std::cout << "Exercise: " << selectedExercise.getName()
                  << " | Repetitions: " << repetitions
                  << " | Total Calories Burned: " << totalCaloriesBurned << " kcal\n";
    }
}

void Diary::addFood() {
    while (true) {
        std::cout << "\nSelect a category of the food that you want to add:\n";
        std::cout << "1. Meat\n";
        std::cout << "2. Vegetables\n";
        std::cout << "3. Fruits\n";
        std::cout << "4. Side Dishes\n";
        std::cout << "5. Exit\n";
        std::cout << "Choose a category (1-5): ";

        size_t category;
        std::cin >> category;

        if (category == 5) {
            std::cout << "Exiting food selection.\n";
            break;
        }

        std::vector<Food*>* selectedCategory = nullptr;

        switch (category) {
            case 1: selectedCategory = &meatOptions; break;
            case 2: selectedCategory = &vegetableOptions; break;
            case 3: selectedCategory = &fruitOptions; break;
            case 4: selectedCategory = &sideDishOptions; break;
            default:
                std::cout << "Invalid category. Please try again.\n";
                continue;  // Повторюємо вибір
        }

        std::cout << "\nAvailable foods:\n";
        for (size_t i = 0; i < selectedCategory->size(); ++i) {
            std::cout << i + 1 << ". ";
            (*selectedCategory)[i]->displayInfo();
        }

        std::cout << "Choose a food by number: ";
        size_t choice;
        std::cin >> choice;

        if (choice < 1 || choice > selectedCategory->size()) {
            std::cout << "Invalid choice. Please try again.\n";
            continue;  // Повторюємо вибір
        }

        Food* selectedFood = (*selectedCategory)[choice - 1];
        std::cout << "Enter weight in grams: ";
        double grams;
        std::cin >> grams;

        // Обчислюємо харчові характеристики для введеної ваги
        double calories = selectedFood->calculateCalories(grams);
        double protein = selectedFood->calculateProtein(grams);
        double fat = selectedFood->calculateFat(grams);
        double carbs = selectedFood->calculateCarbs(grams);

        // Виводимо інформацію про їжу
        std::cout << "\n=== Nutritional Information ===\n";
        std::cout << "Food: " << selectedFood->getName() << "\n";
        std::cout << "Weight: " << grams << "g\n";
        std::cout << "Calories: " << calories << " kcal\n";
        std::cout << "Protein: " << protein << " g\n";
        std::cout << "Fat: " << fat << " g\n";
        std::cout << "Carbs: " << carbs << " g\n";

        // Додаємо до списку продуктів
        Food* adjustedFood = selectedFood->createWithAdjustedValues(calories, protein, fat, carbs);
        foods.push_back(adjustedFood);

        std::cout << "\nFood added successfully!\n";
    }
}


void Diary::displayLog() const {
    std::cout << "===== Diary Entry for Date: " << date << " =====\n";
    std::cout << "===== Exercise Log =====\n";
    for (const auto& exercise : exercises) {
        exercise.displayInfo();
    }

    std::cout << "===== Food Log =====\n";
    for (const auto& food : foods) {
        food->displayInfo();
    }
}

const std::vector<Exercise>& Diary::getExercises() const {
    return exercises;
}

const std::vector<Food*>& Diary::getFoods() const {
    return foods;
}

const std::string& Diary::getDate() const {
    return date;
}



