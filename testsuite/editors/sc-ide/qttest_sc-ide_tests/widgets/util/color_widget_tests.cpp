#include <QTest>

#include "color_widget.hpp"

using namespace ScIDE;

class ColorWidgetTests : public QObject {
    Q_OBJECT
private slots:
    void ColorWidgetInitialState() {
        ColorWidget widget;
        QColor expected_color(0, 0, 0, 255);
        QCOMPARE(widget.color(), expected_color);
    }

    void ColorWidgetChangingColourUpdatesAndEmitsCorrectly() {
        // Arrange
        ColorWidget widget;
        QColor red("red");

        // Act
        widget.setColor(red);

        // Assert
        QCOMPARE(widget.color(), red);
        // TODO Check that signals are emitted correctly, and only once
    }
};

QTEST_MAIN(ColorWidgetTests)
#include "color_widget_tests.moc"
