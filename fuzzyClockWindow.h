#ifndef FUZZYCLOCKWINDOW_H
#define FUZZYCLOCKWINDOW_H

#include <QtGui>
#include <QtWidgets/QApplication>
#include <Windows.h>
#include <WtsApi32.h>
#include <QDebug>
#include <QLabel>
#include "fuzzyClock.h"
#define ID_TIMER 100

class fuzzyClockWindow : public QWidget
{
public:
    fuzzyClockWindow();
    ~fuzzyClockWindow();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
protected:
    bool nativeEvent(const QByteArray &eventType, void *message, long *result);
    void contextMenuEvent(QContextMenuEvent *event) override;
private slots:
    void about();
    void exit();
private:
    QPoint mpos;
    fuzzyClock fuzzyClock;
    void createActions();
    QAction *aboutAct;
    QAction *aboutQtAct;
    QAction *exitAct;
    QSettings m;
};

#endif // FUZZYCLOCKWINDOW_H
