#include "catch.hpp"

#include <QSignalSpy>
#include "safe_qcompare.h"

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

    // Qt5 "pointer-to-member-function" connection for compile-time checking
    QSignalSpy colorChangedSpy(&widget, &ColorWidget::colorChanged);
    // Always check that the spy is valid:
    REQUIRE(colorChangedSpy.isValid());

    // Act
    // Simplifying assumption: We don't want to deal with the pop-up color dialog
    // and clicking on it to select a color. So instead simulate its effect
    // by calling the slot that it calls.
    widget.setColor(red);

    // Assert
    CHECK(widget.color() == red);
    REQUIRE(colorChangedSpy.count() == 1);
    const QColor colorEmittedBySignal = qvariant_cast<QColor>(colorChangedSpy.at(0).at(0));
    REQUIRE(colorEmittedBySignal == red);

    // The Qt way of checking gets silently swallowed, so should fail to compile,
    // when safe_qcompare.h is included
    // QCOMPARE(colorEmittedBySignal, red);
}
