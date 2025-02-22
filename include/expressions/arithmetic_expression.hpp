#pragma once

#include <cstdint>
#include <expected>
#include <system_error>

namespace expressions {

/**
 * @brief Enumerates the supported arithmetic operations.
 * 
 * Each enumeration value can be explicitly converted (typically through the
 * `std::to_underlying` utility) to a `char` value representing the arithmetic
 * operator typically associated with the operation.
*/
enum class arithmetic_operation : char {
    noop            = ' ', /** Represents an empty operation. */
    adition         = '+',  /** Represents an adition operation. */
    subtraction     = '-',  /** Represents a subtraction operation. */
    multiplication  = '*',  /** Represents a multiplication operation. */
    division        = '/',  /** Represents a division operation. */
};

/**
 * @brief Represents an arithmetic expression.
 * 
 * This is a callable object that when invoked, will attempt to evaluate the 
 * expression it represents and return its result.
*/
typedef struct arithmetic_expression {

    /******************** Public Members ********************/

    arithmetic_operation operation = arithmetic_operation::noop;

    struct { std::int32_t a = {}, b = {}; } operands = {};

    /******************** Operator Overloads ********************/

    /**
     * @brief Function call operator overload.
     * 
     * Attempts to evaluate the arithmetic expression represented by this
     * instance and returns its result wrapped in a `std::expected` object.
     * 
     * @returns `std::expected<std::int32_t, std::errc>`
    */
    auto operator()() const -> std::expected<std::int32_t, std::errc>;

} arithmetic_expression_t;

} // namespace expressions
