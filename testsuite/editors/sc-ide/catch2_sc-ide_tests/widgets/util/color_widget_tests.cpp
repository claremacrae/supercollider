#include "catch.hpp"

#include "color_widget.hpp"

#include "catch_qt_string_makers.hpp"

using namespace ScIDE;

TEST_CASE("ColorWidget initial state") {
    ColorWidget widget;
    QColor expected_color(0, 0, 0, 255);
    CHECK(widget.color() == expected_color);
}

TEST_CASE("ColorWidget initial state - approval testing") {
    ColorWidget widget;
    auto color = Catch::StringMaker<QColor>::convert(widget.color());
    CHECK(color == "(0, 0, 0), alpha = 1");
}

TEST_CASE("ColorWidget changing color updates correctly") {
    // Arrange
    ColorWidget widget;
    QColor red("red");

    // Act
    widget.setColor(red);

    // Assert
    CHECK(widget.color() == red);
}
