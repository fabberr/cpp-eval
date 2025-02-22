#include <expressions/arithmetic_expression.hpp>

auto expressions::arithmetic_expression::operator()() const
    -> std::expected<std::int32_t, std::errc>
{
    const auto& [a, b] = operands;

    switch (operation) {
    case arithmetic_operation::noop:
        return {};
    case arithmetic_operation::adition:
        return (a + b);
    case arithmetic_operation::subtraction:
        return (a - b);
    case arithmetic_operation::multiplication:
        return (a * b);
    case arithmetic_operation::division:
        return (a / b);
    default:
        return std::unexpected(std::errc::operation_not_supported);
    }
}
