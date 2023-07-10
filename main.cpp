#include <QtWidgets/QApplication>
#include <Windows.h>
#include <WtsApi32.h>
#include <QDebug>
#include <QLabel>
#include "fuzzyClockWindow.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    fuzzyClockWindow fuzzyWindow;

    fuzzyWindow.setWindowFlags(Qt::WindowStaysOnTopHint | Qt::SubWindow | Qt::Window | Qt::FramelessWindowHint);

    QDir::setCurrent(QCoreApplication::applicationDirPath());
    QFile styleFile("style.css");
    styleFile.open(QFile::ReadOnly);
    QString stylecss(styleFile.readAll());
    app.setStyleSheet(stylecss);

    fuzzyWindow.show();

    fuzzyWindow.setWindowTitle(QApplication::translate("Fuzzy clock", "Неточные часы"));

    return app.exec();
}
