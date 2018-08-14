#pragma once

#include <cstdint>

/**
 * Вычислить факториал.
 * @param n - значение для которго вычисляется факториал. Допустимый диапазон: 0..20.
 * @return Факториал от n.
 */
constexpr uint64_t factorial(unsigned int n) {
    return n <= 1 ? 1 : n * factorial(n - 1);
}