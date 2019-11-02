#include <QTest>
#include <QSignalSpy>

#include "goto_line_tool.hpp"

using namespace ScIDE;

class GoToLineToolTests : public QObject {
Q_OBJECT
private slots:
    void testSignalEmittedWhenGoButtonClicked() {
        GoToLineTool widget;
        widget.raise();
        widget.show();
        widget.setMaximum(27);

        auto spinner = widget.findChild<QSpinBox*>();
        QVERIFY2(spinner, "This test is no longer valid: the class being test has been changed");

        auto goButton = widget.findChild<QToolButton*>();
        QVERIFY2(goButton, "This test is no longer valid: the class being test has been changed");

        widget.setFocus();
        QApplication::processEvents(QEventLoop::AllEvents);
        QVERIFY(spinner->hasFocus());

        QSignalSpy activatedSpy(&widget, SIGNAL(activated(int)));
        QVERIFY(activatedSpy.isValid());

        // Type a number
        QTest::keyClicks(spinner, "1");
        QTest::keyClicks(spinner, "7");
        QApplication::processEvents(QEventLoop::AllEvents);

        // Check that no signals have yet been emitted:
        QCOMPARE(activatedSpy.count(), 0);

        // Clicking the Go button:
        goButton->click();
        QApplication::processEvents(QEventLoop::AllEvents);
        QVERIFY(spinner->hasFocus());

        activatedSpy.wait(1000);
        QVERIFY(spinner->hasFocus());

        // Check the activated() signal was emitted only once:
        QCOMPARE(activatedSpy.count(), 1);

        // And check that the signal emitted the correct value
        QList<QVariant> arguments = activatedSpy.takeFirst();
        QVariant argument = arguments.at(0);
        QVERIFY(argument.type() == QVariant::Int);
        QVERIFY(argument.toInt() == 17);
    }

};

QTEST_MAIN(GoToLineToolTests)
#include "goto_line_tool_tests.moc"
