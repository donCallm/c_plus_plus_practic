#pragma once

#include <cstddef>

constexpr const size_t DEFAULT_VAL = 1;
constexpr const size_t PROTEIN_VAL = 4;
constexpr const size_t FAT_VAL = 9;
constexpr const size_t CARB_VAL = 4;
constexpr const size_t LIGHT_VAL = 890; // in 1 hours

struct DefaultNutrient {
    DefaultNutrient(size_t val = DEFAULT_VAL)
        : _nutritional_value(val)
    {}

    size_t value() { return _nutritional_value; }

private:
    const size_t _nutritional_value;
};

struct Nutrient
            : DefaultNutrient
{
    Nutrient(size_t val = DEFAULT_VAL)
        : DefaultNutrient(val)
    {}
};

struct Protein
            : Nutrient
{
    Protein()
        : Nutrient(PROTEIN_VAL)
    {}
};

struct FAT
            : Nutrient
{
    FAT()
        : Nutrient(FAT_VAL)
    {}
};

struct Carb
            : Nutrient
{
    Carb()
        : Nutrient(CARB_VAL)
    {}
};

struct LightEnergi
            : DefaultNutrient
{
    LightEnergi()
        : DefaultNutrient(LIGHT_VAL)
    {}
};
