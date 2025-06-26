#include <SFML/Graphics.hpp>
#include <imgui.h>
#include <imgui-SFML.h>
#include <vector>
#include <string>
#include <functional>
#include <algorithm>

#include "Diary.h"

enum class AppState {
    MainMenu,
    AddEntry,
    ShowAll,
    SearchDate,
    Quit
};

struct ButtonInfo {
    ImVec2 pos;
    ImVec4 color;
    const char* label;
};

const ImVec2 BTN_SIZE(400, 80);
const float ROUNDING = 20.f;
const ImVec2 PADDING(5,5);
const float FONT_SCALE = 2.5f;

const ImVec4 MAIN_BTN_COLOR(0.4f, 0.75f, 0.6f, 1.0f);
const ImVec4 EXIT_BTN_COLOR(0.9f, 0.57f, 0.02f, 1.0f);
const ImVec4 CHILD_BG_COLOR(0.85f, 0.3f, 0.1f, 0.75f);
const ImVec4 BACK_BTN_COLOR(0.85f, 0.3f, 0.1f, 1.0f);
const ImVec4 BACK_BTN_HOVER(0.95f, 0.4f, 0.2f, 1.0f);
const ImVec4 BACK_BTN_ACTIVE(0.75f, 0.2f, 0.0f, 1.0f);

std::vector<ButtonInfo> mainMenuButtons = {
    { ImVec2(750, 450), MAIN_BTN_COLOR, "New Day" },
    { ImVec2(750, 550), MAIN_BTN_COLOR, "Show All Days" },
    { ImVec2(750, 650), MAIN_BTN_COLOR, "Find by Date" },
    { ImVec2(750, 750), EXIT_BTN_COLOR, "Exit" }
};

std::vector<ButtonInfo> addEntryButtons = {
    { ImVec2(750, 400), MAIN_BTN_COLOR, "Add Exercise" },
    { ImVec2(750, 500), MAIN_BTN_COLOR, "Add Food" },
};

void DrawButtons(const ButtonInfo* buttons, int count, ImVec2 size,
                 std::function<void(int)> onClick,
                 ImVec2 windowSize = ImVec2(500, 120),
                 float rounding = ROUNDING,
                 ImVec2 padding = PADDING,
                 float fontScale = FONT_SCALE)
{
    for (int i = 0; i < count; ++i) {
        ImGui::SetNextWindowPos(buttons[i].pos, ImGuiCond_Always);
        ImGui::SetNextWindowSize(windowSize, ImGuiCond_Always);

        ImGuiWindowFlags flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove |
                                 ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground;

        ImGui::Begin(("btn" + std::to_string(i)).c_str(), nullptr, flags);

        ImGui::GetStyle().FrameRounding = rounding;
        ImGui::GetStyle().FramePadding = padding;
        ImGui::SetWindowFontScale(fontScale);

        ImGui::PushStyleColor(ImGuiCol_Button, buttons[i].color);
        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1,1,1,1));

        if (ImGui::Button(buttons[i].label, size)) {
            onClick(i);
        }

        ImGui::PopStyleColor(2);
        ImGui::End();
    }
}

void DrawBackButton(AppState& state) {
    ImGui::PushStyleColor(ImGuiCol_Button, BACK_BTN_COLOR);
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, BACK_BTN_HOVER);
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, BACK_BTN_ACTIVE);

    if (ImGui::Button("Back", ImVec2(200, 60))) {
        state = AppState::MainMenu;
    }

    ImGui::PopStyleColor(3);
}

void DrawDiaryEntries(const std::vector<Diary>& entries, const char* childName, ImVec2 size) {
    if (entries.empty()) {
        ImGui::TextColored(ImVec4(1, 0.5f, 0, 1), "No entries yet.");
        return;
    }

    ImGui::BeginChild(childName, size, true);
    for (size_t i = 0; i < entries.size(); ++i) {
        ImGui::PushStyleColor(ImGuiCol_ChildBg, CHILD_BG_COLOR);
        ImGui::BeginChild(("EntryCard" + std::to_string(i)).c_str(), ImVec2(0, 300), true);
        ImGui::SetWindowFontScale(FONT_SCALE);
        ImGui::SetCursorPosX(50);
        ImGui::Text("Entry %d", (int)(i + 1));
        ImGui::Separator();
        ImGui::TextWrapped("%s", entries[i].getLogString().c_str());
        ImGui::EndChild();
        ImGui::PopStyleColor();
        ImGui::Spacing();
    }
    ImGui::EndChild();
}

void RenderMainMenu(AppState& state) {
    DrawButtons(mainMenuButtons.data(), (int)mainMenuButtons.size(), BTN_SIZE, [&](int i) {
        switch(i) {
            case 0: state = AppState::AddEntry; break;
            case 1: state = AppState::ShowAll; break;
            case 2: state = AppState::SearchDate; break;
            case 3: state = AppState::Quit; break;
        }
    });
}

void RenderShowAll(AppState& state, const std::vector<Diary>& days, sf::RenderWindow& window, sf::Sprite& bg) {
    window.clear();
    window.draw(bg);

    ImGui::SetNextWindowPos(ImVec2(450, 250), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(1000, 700), ImGuiCond_Always);
    ImGuiWindowFlags flags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar;

    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0,0,0,0));
    ImGui::Begin("All Entries", nullptr, flags);
    ImGui::PopStyleColor();

    ImGui::SetWindowFontScale(FONT_SCALE);
    DrawDiaryEntries(days, "Child", ImVec2(0, 575));
    DrawBackButton(state);
    ImGui::End();
}

void RenderSearch(AppState& state, const std::vector<Diary>& days, sf::RenderWindow& window, sf::Sprite& bg) {
    static int day = 1, month = 1, year = 2025;
    static std::vector<std::string> results;

    window.clear();
    window.draw(bg);

    ImGui::SetNextWindowPos(ImVec2(450, 250), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(1000, 700), ImGuiCond_Always);

    ImGuiWindowFlags flags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar;

    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0,0,0,0));
    ImGui::Begin("Search by Date", nullptr, flags);
    ImGui::PopStyleColor();

    ImGui::SetWindowFontScale(FONT_SCALE);
    ImGui::Text("Enter date:");
    ImGui::InputInt("Day", &day);
    day = std::clamp(day, 1, 31);
    ImGui::InputInt("Month", &month);
    month = std::clamp(month, 1, 12);
    ImGui::InputInt("Year", &year);
    year = std::max(0, year);

    char dateStr[11];
    snprintf(dateStr, sizeof(dateStr), "%02d-%02d-%04d", day, month, year);

    if (ImGui::Button("Find", ImVec2(200, 60))) {
        results.clear();
        for (const auto& d : days) {
            if (d.getDate() == dateStr) {
                results.push_back(d.getLogString());
            }
        }
        if (results.empty()) {
            results.push_back("No entries found.");
        }
    }

    ImGui::Spacing();
    ImGui::Separator();

    ImGui::BeginChild("SearchResults", ImVec2(0, 325), true);
    for (size_t i = 0; i < results.size(); ++i) {
        ImGui::PushStyleColor(ImGuiCol_ChildBg, CHILD_BG_COLOR);
        ImGui::BeginChild(("ResultCard" + std::to_string(i)).c_str(), ImVec2(0, 300), true);
        ImGui::SetWindowFontScale(FONT_SCALE);
        ImGui::SetCursorPosX(50);
        ImGui::Text("Result %d", (int)(i + 1));
        ImGui::Separator();
        ImGui::TextWrapped("%s", results[i].c_str());
        ImGui::EndChild();
        ImGui::PopStyleColor();
        ImGui::Spacing();
    }
    ImGui::EndChild();

    DrawBackButton(state);
    ImGui::End();
}

void RenderAddEntry(AppState& state, Diary& diary, std::vector<Diary>& days, sf::RenderWindow& window, sf::Sprite& bg) {
    static int day = 1, month = 1, year = 2025;
    static bool dateSet = false;
    static bool showExercise = false;
    static bool showFood = false;

    window.clear();
    window.draw(bg);

    ImGui::SetNextWindowPos(ImVec2(700, 300), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(700, 1000), ImGuiCond_Always);

    ImGuiWindowFlags flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground;
    ImGui::Begin("Add Entry", nullptr, flags);
    ImGui::SetWindowFontScale(FONT_SCALE);

    if (!dateSet) {
        ImGui::Text("Enter date:");
        ImGui::InputInt("Day", &day);
        day = std::clamp(day, 1, 31);
        ImGui::InputInt("Month", &month);
        month = std::clamp(month, 1, 12);
        ImGui::InputInt("Year", &year);
        year = std::max(0, year);

        char dateBuf[11];
        snprintf(dateBuf, sizeof(dateBuf), "%02d-%02d-%04d", day, month, year);

        if (ImGui::Button("Set Date", ImVec2(200, 50))) {
            diary.setDate(dateBuf);
            dateSet = true;
        }
    } else {
        ImGui::Text("Date: %02d-%02d-%04d", day, month, year);
        ImGui::Spacing();

        if (!showExercise && !showFood) {
            DrawButtons(addEntryButtons.data(), (int)addEntryButtons.size(), BTN_SIZE, [&](int i) {
                if (i == 0) showExercise = true;
                if (i == 1) showFood = true;
            });
            ImGui::SetCursorScreenPos(ImVec2(860, 650));
        }

        if (showExercise) {
            const auto& exOptions = diary.getExerciseOptions();
            static int exIndex = 0;
            static int exReps = 1;

            std::vector<const char*> names;
            for (const auto& ex : exOptions) names.push_back(ex.getName().c_str());

            ImGui::Text("Choose exercise:");
            ImGui::Combo("Exercise", &exIndex, names.data(), (int)names.size());

            ImGui::InputInt("Repeats", &exReps);
            if (exReps < 1) exReps = 1;

            if (ImGui::Button("Add", ImVec2(150, 50))) {
                diary.addExercise(exOptions[exIndex], exReps);
                exReps = 1;
            }
            if (ImGui::Button("Close", ImVec2(300, 60))) {
                showExercise = false;
                exIndex = 0;
                exReps = 1;
            }

            ImGui::PushStyleColor(ImGuiCol_Text, EXIT_BTN_COLOR);
            ImGui::Text("Exercises added:");
            for (const auto& e : diary.getExercises()) {
                ImGui::BulletText("%s  %.1f kcal", e.getName().c_str(), e.getCaloriesPerRepetition());
            }
            ImGui::PopStyleColor();
            ImGui::SetCursorScreenPos(ImVec2(860, 850));
        }

        if (showFood) {
            static int selectedCategory = 0;
            static int selectedFood = -1;
            static double grams = 100.0;

            ImGui::Text("Choose category:");
            const char* cats[] = { "Select...", "Meat", "Vegetable", "Fruit", "Side Dish" };
            ImGui::Combo("Category", &selectedCategory, cats, IM_ARRAYSIZE(cats));

            if (selectedCategory > 0) {
                std::vector<Food*> foods = diary.getFoodOptionsByCategory(selectedCategory);
                if (foods.empty()) {
                    ImGui::Text("No food in this category.");
                } else {
                    std::vector<std::string> foodNamesStr;
                    std::vector<const char*> foodNames;
                    for (auto f : foods) foodNamesStr.push_back(f->getName());
                    for (auto& s : foodNamesStr) foodNames.push_back(s.c_str());

                    if (ImGui::Combo("Food", &selectedFood, foodNames.data(), (int)foodNames.size())) {
                        grams = 100.0;
                    }

                    if (selectedFood >= 0 && selectedFood < (int)foods.size()) {
                        ImGui::InputDouble("Weight (g)", &grams, 10.0, 100.0, "%.1f");
                        if (grams < 0) grams = 0;

                        if (ImGui::Button("Add Food", ImVec2(150, 50))) {
                            Food* newFood = diary.createAdjustedFood(foods[selectedFood], grams);
                            if (newFood) {
                                diary.addFood(newFood);
                                selectedFood = -1;
                                grams = 100.0;
                            }
                        }
                    }
                }
            }

            if (ImGui::Button("Close Food", ImVec2(200, 60))) {
                showFood = false;
                selectedCategory = 0;
                selectedFood = -1;
                grams = 100.0;
            }

            ImGui::PushStyleColor(ImGuiCol_Text, EXIT_BTN_COLOR);
            ImGui::SetWindowFontScale(2.1f);
            ImGui::Text("Food added:");

            ImGui::PushTextWrapPos(0.0f);
            for (const auto& f : diary.getFoods()) {
                std::string info = "--" + f->getInfoString();
                ImGui::TextWrapped("%s", info.c_str());
            }
            ImGui::PopTextWrapPos();
            ImGui::PopStyleColor();
        }

        ImGui::SetWindowFontScale(FONT_SCALE);
        if (ImGui::Button("Save", ImVec2(200, 60))) {
            days.push_back(diary);
            diary = Diary();
            day = 1; month = 1; year = 2025;
            dateSet = false;
            showExercise = false;
            showFood = false;
            state = AppState::MainMenu;
        }
    }

    ImGui::End();
}

int main() {
    std::vector<Diary> days;
    Diary newDiary;

    sf::RenderWindow window(sf::VideoMode(1280, 720), "Health Diary");
    window.setFramerateLimit(60);
    ImGui::SFML::Init(window);

    AppState currentState = AppState::MainMenu;

    sf::Texture tex1, tex2, tex3;
    tex1.loadFromFile("background.png");
    tex2.loadFromFile("background1.png");
    tex3.loadFromFile("background2.png");

    sf::Sprite bg1(tex1);
    bg1.setScale(float(window.getSize().x) / tex1.getSize().x,
                 float(window.getSize().y) / tex1.getSize().y);
    sf::Sprite bg2(tex2);
    bg2.setScale(float(window.getSize().x) / tex2.getSize().x,
                 float(window.getSize().y) / tex2.getSize().y);
    sf::Sprite bg3(tex3);
    bg3.setScale(float(window.getSize().x) / tex3.getSize().x,
                 float(window.getSize().y) / tex3.getSize().y);

    sf::Clock deltaClock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);
            if (event.type == sf::Event::Closed)
                window.close();
        }

        ImGui::SFML::Update(window, deltaClock.restart());

        switch (currentState) {
            case AppState::MainMenu:
                window.clear();
                window.draw(bg1);
                RenderMainMenu(currentState);
                break;

            case AppState::AddEntry:
                RenderAddEntry(currentState, newDiary, days, window, bg2);
                break;

            case AppState::ShowAll:
                RenderShowAll(currentState, days, window, bg3);
                break;

            case AppState::SearchDate:
                RenderSearch(currentState, days, window, bg3);
                break;

            case AppState::Quit:
                window.close();
                break;
        }

        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
    return 0;
}
