#ifndef FUZZYCLOCK_H
#define FUZZYCLOCK_H

#include <QtGui>
#include <QtWidgets/QApplication>
#include <Windows.h>
#include <WtsApi32.h>
#include <QDebug>
#include <QLabel>
#include <QString>

struct fuzzyClock : public QWidget
{
private:
    Q_OBJECT // macro to declare own signals and slots

    QWidget *m_window;
    QLabel *m_label = nullptr;
    int hourToUse;
    int referMinPos;
    QString timeToShow;
    int fHeight; // font height
    int fWidth; // font width
    QSettings m_sSettingsFile;

public:
    fuzzyClock(WId pWindow);

    /*  ~fuzzyClock(); */

    void SetLabel(QLabel *timeLabel); // pass QLabel from parent fuzzyWindow to fuzzyClock class
    void SetWindow(QWidget *pWindow); // pass fuzzyWindow to fuzzyClock class

    void DisplayTime();
    int getHourNow(int h12);
    int getMinuteNow();

    // Declare arrays to be allocated on the stack
    // Depending on the minute - position of displayed text in the next arrays:
    int minuteRefer[60] {};
    /* int posRefer[60] {  0, 0, 0, // nominative 0 1 2
                        1, 1, 1, 1, 1, // genitive 3 4 5 6 7
                        2, 2, 2, 2, 2, // 8 9 10 11 12
                        3, 3, 3, 3, 3, // 13 14 15 16 17
                        4, 4, 4, 4, 4, // 18 19 20 21 22
                        5, 5, 5, 5, 5, // 23 24 25 26 27
                        6, 6, 6, 6, 6, // 28 29 30 31 32
                        7, 7, 7, 7, 7, // nominative 33 34 35 36 37
                        8, 8, 8, 8, 8, // 38 39 40 41 42
                        9, 9, 9, 9, 9, // 43 44 45 46 47
                        10, 10, 10, 10, 10, // 48 49 50 51 52
                        11, 11, 11, 11, 11, //
                        12, 12 }; // 58 59
    */    

    QString fuzzyMinutes[13]{};
    /* QString fuzzyMinutes[13]{ "Ровно %0", "Пять минут %1", "Десять минут %1", "Четверть %1", "Двадцать минут %1", "Двадцать пять минут %1",
                                       "Половина %1", "Без двадцати пяти %0", "Без двадцати %0", "Без четверти %0",
                                       "Без десяти %0", "Без пяти %0", "Почти %0" };
    */

    QString nominativeHour[12]{};
    /* QString nominativeHour[12]{ "час", "два", "три", "четыре", "пять", "шесть",
                                     "семь", "восемь", "девять", "десять", "одиннадцать", "двенадцать" };
    */

    QString genitiveHour[12]{};
    /* QString genitiveHour[12]{ "первого", "второго", "третьего", "четвертого", "пятого", "шестого",
                                    "седьмого", "восьмого", "девятого", "десятого", "одиннадцатого", "двенадцатого" };
    */
protected:
    void readArrays();

};

#endif // FUZZYCLOCK_H
