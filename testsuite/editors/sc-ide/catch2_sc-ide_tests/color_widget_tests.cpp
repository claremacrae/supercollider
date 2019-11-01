#include "catch.hpp"

// TODO Could move this test to a sub-directory widgets/util, as number of tests grows
#include "widgets/util/color_widget.hpp"

#include <QStringBuilder>
#include <QStringLiteral>
#include <iostream>

using namespace ScIDE;

// https://github.com/catchorg/Catch2/blob/master/docs/tostring.md#top
namespace Catch {
    template<>
    struct StringMaker<QColor> {
        static std::string convert( QColor const& color ) {
            const QString result =
                    "(" %
                    QString::number(color.redF()) % ", " %
                    QString::number(color.greenF()) % ", " %
                    QString::number(color.blueF()) %
                    "), alpha = " %
                    QString::number(color.alphaF(), 'g', 20);
            return result.toStdString();
        }
    };
}

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
