#include <iostream>
using namespace std;

class FoodItem
{
private:
    string name;
    int calories;
    float grams_of_fat;
    float grams_of_carbohydrates;
    float grams_of_protein;

public:
    // Constructor with name only
    FoodItem(string nName)
        : name(nName), calories(0), grams_of_fat(0), grams_of_carbohydrates(0), grams_of_protein(0) {}

    // Constructor with name and calories
    FoodItem(string nName, int Ncalories)
        : name(nName), calories(Ncalories), grams_of_fat(0), grams_of_carbohydrates(0), grams_of_protein(0) {}

    // Constructor with all details
    FoodItem(string nName, int Ncalories, double ngramof_fat, double ngramof_carbohydrates, double ngramof_protein)
        : name(nName), calories(Ncalories), grams_of_fat(ngramof_fat), grams_of_carbohydrates(ngramof_carbohydrates), grams_of_protein(ngramof_protein) {}

    // Setters
    void setName(string nName)
    {
        name = nName;
    }
    void setCalories(int Ncalories)
    {
        calories = Ncalories;
    }
    void setFatGrams(float ngramof_fat)
    {
        grams_of_fat = ngramof_fat;
    }
    void setCarbGrams(float ngramof_carbohydrates)
    {
        grams_of_carbohydrates = ngramof_carbohydrates;
    }
    void setProteinGrams(float ngramof_protein)
    {
        grams_of_protein = ngramof_protein;
    }

    // Getters
    string getName()
    {
        return name;
    }
    int getCalories()
    {
        return calories;
    }
    float getgramsof_fat()
    {
        return grams_of_fat;
    }
    float getgramsof_carbohydrates()
    {
        return grams_of_carbohydrates;
    }
    float getgramsof_protein()
    {
        return grams_of_protein;
    }

    friend int calculateCalories(FoodItem &p);
};

int calculateCalories(FoodItem &p)
{
    int calories = (4 * p.grams_of_carbohydrates) + (4 * p.grams_of_protein);
    return calories;
}

int main()
{
    string itemName;
    float protein, carbs;
    while (true)
    {
        cout << "Enter the name of the food item (or 'exit' to quit): ";
        cin >> itemName;
        if (itemName == "exit"||itemName == "EXIT")
            break;

        cout << "Enter the protein content (in grams): ";
        cin >> protein;

        cout << "Enter the carbohydrate content (in grams): ";
        cin >> carbs;

        FoodItem food(itemName);
        food.setProteinGrams(protein);
        food.setCarbGrams(carbs);

        int calories = calculateCalories(food);

        cout << "\nFood Item: " << food.getName() << endl;
        cout << "Protein Content: " << food.getgramsof_protein() << " grams" << endl;
        cout << "Carbohydrate Content: " << food.getgramsof_carbohydrates() << " grams" << endl;
        cout << "Calories: " << calories << endl
             << endl;
    }

    return 0;
}
