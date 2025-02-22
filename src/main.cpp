#include <cstdio>
#include <expected>
#include <print>
#include <system_error>
#include <utility>

#include <expressions/arithmetic_expression.hpp>

auto main(
    [[maybe_unused]] int argc,
    [[maybe_unused]] const char** argv
)
    -> int
{
    using namespace expressions;

    // Declares a expression
    const auto mul = arithmetic_expression_t {
        .operation = arithmetic_operation::multiplication,
        .operands = {
            .a = 10,
            .b = 3,
        },
    };

    // Evaluate the expression
    const auto result = mul();

    if (not result.has_value()) {
        const auto error_code = std::make_error_code(result.error());
        std::println(stderr, "{}", error_code.message());
        return error_code.value();
    }

    const auto& [a, b] = mul.operands;
    std::println(
        "{} {} {} = {}",
        a,
        std::to_underlying(mul.operation),
        b,
        result.value()
    );
}
