#include "catch.hpp"

#include "color_widget.hpp"

#include "catch_qt_string_makers.hpp"

using namespace ScIDE;

// TODO Consider adding tags for tests
TEST_CASE("ColorWidget initial state") {
    ColorWidget widget;
    QColor expected_color(0, 0, 0, 255);
    CHECK(widget.color() == expected_color);
}

TEST_CASE("ColorWidget changing color updates and emits correctly") {
    // Arrange
    ColorWidget widget;
    QColor red("red");

    // Act
    widget.setColor(red);

    // Assert
    CHECK(widget.color() == red);
    // TODO Check that signals are emitted correctly, and only once
}
