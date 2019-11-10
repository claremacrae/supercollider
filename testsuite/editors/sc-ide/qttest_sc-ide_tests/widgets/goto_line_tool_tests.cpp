#include <QTest>
#include <QSignalSpy>

#include "auto_test.hpp"

#include <memory>

#include "goto_line_tool.hpp"

using namespace ScIDE;

// TODO I am expecting that this code will be discarded - but if it is not, I'll compare it with
//      that in testsuite/editors/sc-ide/catch2_sc-ide_tests/widgets/goto_line_tool_tests.cpp
//      and apply the refactorings there to this, to make the actual test function much
//      more expressive.

class GoToLineToolTests : public QObject {
    Q_OBJECT
private:
    std::unique_ptr<GoToLineTool> mGoToLineWidget;
    QSpinBox* mSpinner = nullptr;
    QToolButton* mGoButton = nullptr;
private slots:
    void init() {
        mGoToLineWidget = std::unique_ptr<GoToLineTool>(new GoToLineTool);
        mGoToLineWidget->raise();
        mGoToLineWidget->show();
        // TODO Maybe use QTest::qWaitForWindowExposed()
        // https://doc.qt.io/qt-5/qtest.html#qWaitForWindowExposed
        // TODO Do we need to create a QWindow first, as parent for this?
        // TODO Do we need to make sure widget has a non-null parent?

        // This is needed to may sure that text in the spinner is selected, so that
        // as we type in characters, the initial text ("1") is erased
        mGoToLineWidget->setFocus();

        mSpinner = mGoToLineWidget->findChild<QSpinBox*>();
        QVERIFY2(mSpinner, "This test is no longer valid: the class being test has been changed");

        mGoButton = mGoToLineWidget->findChild<QToolButton*>();
        QVERIFY2(mGoButton, "This test is no longer valid: the class being test has been changed");
    }

    void cleanup() {
        mGoToLineWidget.release();
        mSpinner = nullptr;
        mGoButton = nullptr;
    }

    void testSignalEmittedWhenGoButtonClicked() {
        mGoToLineWidget->setMaximum(27);

        QSignalSpy activatedSpy(mGoToLineWidget.get(), SIGNAL(activated(int)));
        QVERIFY(activatedSpy.isValid());

        // Type a number, one digit at a time
        QTest::keyClicks(mSpinner, "1");
        QTest::keyClicks(mSpinner, "7");

        // Check that no signals have yet been emitted:
        QCOMPARE(activatedSpy.count(), 0);

        // Clicking the Go button:
        mGoButton->click();

        // Check the activated() signal was emitted only once:
        QCOMPARE(activatedSpy.count(), 1);

        // And check that the signal emitted the correct value
        QList<QVariant> arguments = activatedSpy.takeFirst();
        QVariant argument = arguments.at(0);
        QVERIFY(argument.type() == QVariant::Int);
        QCOMPARE(argument.toInt(), 17);
    }
};

DECLARE_TEST(GoToLineToolTests)
#include "goto_line_tool_tests.moc"
