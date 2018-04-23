#pragma once

#include <string>
#include <sstream>
#include <type_traits>
#include <cmath>
#include <cstdint>
#include <iomanip>

enum class Unit {
    None = 0,
    Kilo = 3,
    Mega = 6,
    Giga = 9,
    Tera = 12,
    Peta = 15,
    Exa = 18
};

Unit& operator++(Unit &unit) {
    using Type = typename std::underlying_type<Unit>::type;
    if (unit == Unit::Exa) {
        unit = Unit::None;
    } else {
        unit = static_cast<Unit>(static_cast<Type>(unit) + 3);
    }
    return unit;
}

Unit operator++(Unit &unit, int) {
    Unit result = unit;
    ++unit;
    return result;
}

std::ostream& operator<< (std::ostream& stream, const Unit& unit) {
    switch (unit) {
        case Unit::None: break;
        case Unit::Kilo: stream << "Kilo"; break;
        case Unit::Mega: stream << "Mega"; break;
        case Unit::Giga: stream << "Giga"; break;
        case Unit::Tera: stream << "Tera"; break;
        case Unit::Peta: stream << "Peta"; break;
        case Unit::Exa: stream << "Exa"; break;
    }

    return stream;
}

template <typename Number>
std::string suffixWithUnit(Number number) {
    static_assert(std::is_integral<Number>::value || std::is_floating_point<Number>::value, "Not a number");

    std::stringstream result;
    uint64_t num = static_cast<uint64_t>(number);

    if constexpr (std::is_signed<Number>::value || std::is_floating_point<Number>::value) {
        if (number < 0) {
            num = static_cast<uint64_t>(std::abs(number));
            result << "-";
        }
    }

    Unit unit = Unit::None;
    for (uint64_t div = num / 1000; div > 0 && unit != Unit::Exa; div = div / 1000) {
        unit++;
    }

    if (unit == Unit::None) {
        result << num;
    }
    else {
        uint64_t divider = std::pow(10, static_cast<uint64_t>(unit));
        uint64_t div = num / divider;
        uint64_t rem = num % divider;
        result << div;
        if (rem > 0) {
            result << "." << std::setfill('0') << std::setw(static_cast<int>(unit)) << rem;
        }
        result << " " << unit;
    }

    return result.str();
}
