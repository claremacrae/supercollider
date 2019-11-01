#include <iostream>
#include <QApplication>
#include "widgets/util/color_widget.hpp"

using namespace ScIDE;

int main(int argc, char* argv[]) {
    std::cout << "Hello\n";
    QApplication app(argc, argv);
    ColorWidget widget;
    widget.show();
    widget.raise();
    return app.exec();
}
