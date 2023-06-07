#pragma once

#include <QImageReader>

inline QSize getPreferredImageSize(const QString &fileName, int w) {
    QImageReader ir(fileName);
    return ir.size() * (w * 1. / ir.size().width());
}
