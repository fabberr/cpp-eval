#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <utility>
#include <expected>
#include <system_error>
#include <print>

/**
 * @brief Supported binary expression operators.
*/
enum class binary_operator_t : char {
    none = '\0',
    multiply = '*',
};

/**
 * @brief Represents a binary expression's operands.
*/
struct operands_t {
    std::int32_t x = {};
    std::int32_t y = {};
};

/**
 * @brief Represents a binary expression.
 * 
 * Callable object that when invoked, will attempt to evaluate the expression.
 * 
 * Demo: https://godbolt.org/z/x9GKcYsqK
*/
struct binary_expression_t {
    binary_operator_t operator_type = binary_operator_t::none;
    operands_t operands = {};

    auto operator()() const
        -> std::expected<std::int32_t, std::errc>
    {
        const auto& [x, y] = operands;

        switch (operator_type) {
        case binary_operator_t::multiply:
            return (x * y);
        case binary_operator_t::none:
        default:
            return std::unexpected(std::errc::operation_not_supported);
        }
    }
};

/*
 * Required flags: -std=c++26
*/
int main() {
    const auto mul = binary_expression_t {
        .operator_type = binary_operator_t::multiply,
        .operands = {
            .x = 10,
            .y = 3,
        },
    };

    const auto& [x, y] = mul.operands;
    const auto result = mul();

    if (not result.has_value()) {
        const auto message = std::make_error_code(result.error()).message();
        std::println(stderr, "{}", message);
        return EXIT_FAILURE;
    }

    std::println(
        "{} {} {} = {}",
        x,
        std::to_underlying(mul.operator_type),
        y,
        result.value()
    );
}
