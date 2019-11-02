#include <QTest>

#include "goto_line_tool.hpp"

using namespace ScIDE;

class GoToLineToolTests : public QObject {
Q_OBJECT
private slots:
    void GoToLineConstructorDoesNotCrash() {
        GoToLineTool widget;
        // TODO Add a meaningful test
    }
};

QTEST_MAIN(GoToLineToolTests)
#include "goto_line_tool_tests.moc"
