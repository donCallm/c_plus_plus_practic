#pragma once

#include <cstddef>
#include <typeinfo>

constexpr const size_t DEFAULT_VAL = 1;
constexpr const size_t PROTEIN_VAL = 4;
constexpr const size_t FAT_VAL = 9;
constexpr const size_t CARB_VAL = 4;
constexpr const size_t LIGHT_VAL = 8;

using Oxygen = size_t;

struct DefaultEnergySource {
    DefaultEnergySource(size_t val = DEFAULT_VAL)
        : _nutritional_value(val)
    {}

    size_t value() { return _nutritional_value; }
    virtual const std::type_info& get_type() { return typeid(DefaultEnergySource); }

private:
    const size_t _nutritional_value;
};

struct Nutrient
            : DefaultEnergySource
{
    Nutrient(size_t val = DEFAULT_VAL)
        : DefaultEnergySource(val)
    {}

    virtual const std::type_info& get_type() override { return typeid(Nutrient); }
};

struct Protein
            : Nutrient
{
    Protein()
        : Nutrient(PROTEIN_VAL)
    {}

    const std::type_info& get_type() override { return typeid(Protein); }
};

struct Fat
            : Nutrient
{
    Fat()
        : Nutrient(FAT_VAL)
    {}

    const std::type_info& get_type() override { return typeid(Fat); }
};

struct Carb
            : Nutrient
{
    Carb()
        : Nutrient(CARB_VAL)
    {}

    const std::type_info& get_type() override { return typeid(Carb); }
};

struct LightEnergy
            : DefaultEnergySource
{
    LightEnergy()
        : DefaultEnergySource(LIGHT_VAL)
    {}

    const std::type_info& get_type() override { return typeid(LightEnergy); }
};
