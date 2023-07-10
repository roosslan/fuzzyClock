#include <stdio.h>
#include <QtGui>
#include <QtWidgets>
//#include <QtWidgets/QApplication>
#include <Windows.h>
#include <WtsApi32.h>
#include <QDebug>
#include <QLabel>
#include "fuzzyClockWindow.h"
#include "fuzzyClock.h"

fuzzyClockWindow::fuzzyClockWindow() : m("HKEY_CURRENT_USER\\SOFTWARE\\0x9.io\\FuzzyClock", QSettings::NativeFormat), fuzzyClock(this->winId() )
{

    ::SetTimer((HWND)this->winId(), ID_TIMER, 1000, (TIMERPROC) NULL);
    WTSRegisterSessionNotification((HWND)this->winId(), NOTIFY_FOR_THIS_SESSION);
    fuzzyClock.SetLabel(new QLabel(this));
    fuzzyClock.SetWindow(this);

    // read registry
    int wTop = m.value("Top", 300).toInt();
    int wLeft = m.value("Left", 300).toInt();
    this->setGeometry(wLeft, wTop, 200, 20);

    // for CSS
    setObjectName("fuzzyClockWindow");

    // Context menu
    createActions();
}

void fuzzyClockWindow::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu(this);
    menu.addAction(aboutAct);
    menu.addAction(aboutQtAct);
    menu.addAction(exitAct);
    menu.exec(event->globalPos());
}

void fuzzyClockWindow::mousePressEvent(QMouseEvent *event){
    mpos = event->pos();
}

// Drag window without title
void fuzzyClockWindow::mouseMoveEvent(QMouseEvent *event){
    if (event->buttons() & Qt::LeftButton) {
        QPoint diff = event->pos() - mpos;
        QPoint newpos = this->pos() + diff;

        this->move(newpos);
    }
}

bool fuzzyClockWindow::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
    if (eventType != "windows_generic_MSG") return false;
    MSG *msg = static_cast<MSG*>(message);

    switch (msg->message) {
      case WM_WTSSESSION_CHANGE:
        qDebug() << "Session changed: " << msg->wParam;
        if (msg->wParam == 7) {

        }
      case WM_TIMER:
        fuzzyClock.DisplayTime();
    }
    return false;
}

fuzzyClockWindow::~fuzzyClockWindow()
{
    KillTimer((HWND)this->winId(), ID_TIMER);
    WTSUnRegisterSessionNotification((HWND)this->winId());
}

void fuzzyClockWindow::createActions()
{
    aboutAct = new QAction(tr("&About"), this);
    aboutAct->setStatusTip(tr("Show the application's About box"));
    connect(aboutAct, &QAction::triggered, this, &fuzzyClockWindow::about);

    aboutQtAct = new QAction(tr("About &Qt"), this);
    aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));
    connect(aboutQtAct, &QAction::triggered, qApp, &QApplication::aboutQt);

    exitAct = new QAction(tr("E&xit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setStatusTip(tr("Exit the application"));
    connect(exitAct, &QAction::triggered, this, &fuzzyClockWindow::exit);
}

void fuzzyClockWindow::about()
{
    QMessageBox::about(this, tr("О \"Неточных\" часах..."),
            tr("\"Неточные\" часы v3.1,        <br/> (ремейк версии 2.1  "
               "от 12.01.2004)<br/>www.0x9.io"));
}

void fuzzyClockWindow::exit()
{
    m.setValue("currentPath", QDir::currentPath());
    QPoint XY = this->pos();
    m.setValue("Top", QString::number(XY.y()));
    m.setValue("Left", QString::number(XY.x()));
    QApplication::quit();
}
