#include "catch.hpp"

#include <QTest>
#include <QSignalSpy>
#include "safe_qcompare.h"

#include <memory>

#include "goto_line_tool.hpp"

using namespace ScIDE;

// DO NOT USE ANY Qt Test checkers, like QVERIFY, QCOMPARE - as any test failures are currently not detected

class GoToLineToolFixture {
private:
    GoToLineTool mGoToLineWidget;
    QSpinBox* mSpinner = nullptr;
    QToolButton* mGoButton = nullptr;
    std::unique_ptr<QSignalSpy> mActivatedSpy;

protected:
    GoToLineToolFixture() {
        mGoToLineWidget.raise();
        mGoToLineWidget.show();

        // This is needed to make sure that text in the spinner is selected, so that
        // as we type in characters, the initial text ("0" or "1") is erased
        mGoToLineWidget.setFocus();

        mSpinner = mGoToLineWidget.spinBox();
        mGoButton = mGoToLineWidget.goButton();

        mActivatedSpy = std::unique_ptr<QSignalSpy>(new QSignalSpy(&mGoToLineWidget, &GoToLineTool::activated));
        REQUIRE(mActivatedSpy->isValid());
    }

    void setMaximumLineCount(int maxLines) { mGoToLineWidget.setMaximum(27); }

    void typeCharacterIntoSpinner(QChar character) { QTest::keyClicks(mSpinner, character); }

    void clickGoButton() { mGoButton->click(); }

    void checkActivatedSignalCount(int expectedCount) { REQUIRE(mActivatedSpy->count() == expectedCount); }

    void checkActivatedSignalValue(int expectedSignalValue) {
        INFO("Check GoToLineTool::activated() signal has been emitted with correct value.");
        const QVariant& signalArgument = (*mActivatedSpy).at(0).at(0);
        CHECK(signalArgument.type() == QVariant::Int);
        CHECK(signalArgument.toInt() == expectedSignalValue);

        // The Qt way of checking gets silently swallowed, so should fail to compile,
        // when safe_qcompare.h is included
        //QCOMPARE(signalArgument.toInt(), expectedSignalValue);
    }
};

TEST_CASE_METHOD(GoToLineToolFixture, "GoToLineTool emits signal when Go button clicked") {
    // Arbitrary upper limit in number of lines.
    // When used in the application, this would be obtained from the open document
    setMaximumLineCount(27);

    // Type a number, one digit at a time
    typeCharacterIntoSpinner('1');
    typeCharacterIntoSpinner('7');
    checkActivatedSignalCount(0);

    clickGoButton();
    checkActivatedSignalCount(1);
    checkActivatedSignalValue(17);
}
