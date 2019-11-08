#include "catch.hpp"

#include <QSignalSpy>

#include "color_widget.hpp"

#include "catch_qt_string_makers.hpp"

using namespace ScIDE;

TEST_CASE("ColorWidget initial state") {
    ColorWidget widget;
    QColor expected_color(0, 0, 0, 255);
    CHECK(widget.color() == expected_color);
}

TEST_CASE("ColorWidget changing color updates and emits correctly") {
    // Arrange
    ColorWidget widget;
    QColor red("red");
    QSignalSpy colorChangedSpy(&widget, &ColorWidget::colorChanged);
    REQUIRE(colorChangedSpy.isValid());

    // Act
    widget.setColor(red);

    // Assert
    CHECK(widget.color() == red);
    REQUIRE(colorChangedSpy.count() == 1);
}
