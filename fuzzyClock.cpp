#include <time.h>
#include <QSettings>
#include <QMessageBox>
#include "fuzzyClock.h"
#include "fuzzyClockWindow.h"

int fuzzyClock::getHourNow(int h12)
{
    time_t t = time(0);   // get time now
    tm* now = localtime(&t);
    if (12 == h12) // запрошен 12-часовой формат времени
        // если время в диапазоне от 12 до 23, чтобы
        // из массива считывались значения от 0 до 11
        if (now->tm_hour >= 12)
            return now->tm_hour - 12;
    return now->tm_hour;
}

int fuzzyClock::getMinuteNow()
{
    time_t t = time(0);   // get time now
    tm* now = localtime(&t);
    return now->tm_min;
}

void fuzzyClock::SetLabel(QLabel *timeLabel){
    m_label = timeLabel;
    m_label->setObjectName("timeLabel"); // for CSS
}

void fuzzyClock::DisplayTime(){
    readArrays();

    int actMinute = getMinuteNow();
    hourToUse = getHourNow(12);

    referMinPos = minuteRefer[getMinuteNow()]; // referMinPos = posRefer[getMinuteNow()];
    timeToShow = fuzzyMinutes[referMinPos];

    if (actMinute >= 0 && actMinute <= 2 && hourToUse != 0) // "Ровно ХХ"
        hourToUse--;
    if (actMinute >= 0 && actMinute <= 2 && 0 == hourToUse)
        hourToUse = 11; // Для винительного падежа

//    if (12 == getHourNow(24) && 0 == getMinuteNow())
//        timeToShow = "Полдень";
//    if (0 == getHourNow(24) && 0 == getMinuteNow())
//        timeToShow = "Полночь";

    if (timeToShow.contains("%0")){
        timeToShow.replace("%0", "%1");
        timeToShow = QString(fuzzyMinutes[referMinPos]).arg(nominativeHour[hourToUse]);
    }
    if (timeToShow.contains("%1")){
        //timeToShow.replace("%0", "%1");
        timeToShow = QString(fuzzyMinutes[referMinPos]).arg(genitiveHour[hourToUse]);
    }

    m_label->setText(timeToShow);
    fWidth = m_label->fontMetrics().boundingRect(m_label->text()).width();
    fHeight = m_label->fontMetrics().boundingRect(m_label->text()).height();
    m_label->setGeometry(5, 5, fWidth, fHeight);
    m_label->setFixedWidth(fWidth);
    m_window->setFixedSize(fWidth + 10, fHeight + 10);
}

void fuzzyClock::SetWindow(QWidget *pWindow){
    m_window = pWindow;
}

fuzzyClock::fuzzyClock(WId pWindow) {}

fuzzyClock::~fuzzyClock() {}

void fuzzyClock::readArrays(){
    QFile fuzzy_arrays("fuzzy.conf");
    if(!fuzzy_arrays.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "error", fuzzy_arrays.errorString());
    }

    QTextStream in(&fuzzy_arrays);
    QRegExp rx("(\\,)"); //RegEx for ' ' or ',' or '.' or ':' or '\t'
    while(!in.atEnd()) {
        QString line = in.readLine();
        QStringList arrMinutes = line.split(rx);
        int arrMinutesSize = arrMinutes.size() - 1; // Because array starts from zero we've minus 1
        for (int i=0; i <= arrMinutesSize; i++){
            minuteRefer[i] = arrMinutes.at(i).toInt();
        }
    }

    fuzzy_arrays.close();
}
