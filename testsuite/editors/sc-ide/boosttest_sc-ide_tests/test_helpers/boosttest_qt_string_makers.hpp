#pragma once

#include <QColor>

std::ostream& boost_test_print_type(std::ostream& ostr, QColor const& color) {
    // clang-format off
    ostr << "(" <<
        color.redF() << ", " <<
        color.greenF() << ", " <<
        color.blueF() <<
        "), alpha = " <<
        color.alphaF();
    // clang-format on
    return ostr;
}
