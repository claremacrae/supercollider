#pragma once

#include "catch.hpp"

#include <QColor>
#include <QStringBuilder>

// https://github.com/catchorg/Catch2/blob/master/docs/tostring.md#top
namespace Catch {
template <> struct StringMaker<QColor> {
    static std::string convert(QColor const& color) {
        const QString result = "(" % QString::number(color.redF()) % ", " % QString::number(color.greenF()) % ", "
            % QString::number(color.blueF()) % "), alpha = " % QString::number(color.alphaF(), 'g', 20);
        return result.toStdString();
    }
};
}
