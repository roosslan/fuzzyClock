#include <vector>
#include <QString>
#include <QWidget>
#include <QSettings>
#include <QTextCodec>

struct fuzzyHelper : public QWidget
{    
    template<typename T>
    std::vector<T> iniValueToVector(QString groupName, QString keyName)
    {
        std::vector<T> vectRet;

        QSettings settings("fuzzy.conf", QSettings::IniFormat);
       // QTextCodec *textCodec = QTextCodec::codecForName("UTF-8");
        settings.setIniCodec(QTextCodec::codecForName("UTF-8"));

        QStringList qslMinutes = {};

        settings.beginGroup(groupName);
        const QStringList player_number = settings.childGroups();
        const QStringList childKeys = settings.childKeys();

        QStringList values;
        foreach (const QString &childKey, childKeys)
        {

            values << settings.value(childKey).toString();
            if(keyName == childKey)
            {
                QString line = settings.value(childKey).toString();
                qslMinutes = line.split('\\');
                for (int i=0; i <= qslMinutes.size() - 1; i++)
                    vectRet.push_back(qslMinutes.at(i));                    // except <int>. For int we have specialization
            };
        }
        settings.endGroup();

        return vectRet;
    }

/* =================================================================================== */

    template<>
    std::vector<int> iniValueToVector<int>(QString groupName, QString keyName)
    {
        std::vector<int> vectRet;

        QSettings settings("fuzzy.conf", QSettings::IniFormat);

        QStringList qslMinutes = {};

        settings.beginGroup(groupName);
        const QStringList player_number = settings.childGroups();
        const QStringList childKeys = settings.childKeys();

        QStringList values;
        foreach (const QString &childKey, childKeys)
        {

            values << settings.value(childKey).toString();
            if(keyName == childKey)
            {
                QString line = settings.value(childKey).toString();
                qslMinutes = line.split(' ');
                for (int i=0; i <= qslMinutes.size() - 1; i++)
                    vectRet.push_back(qslMinutes.at(i).toInt());            // specialization INT
            };
        }
        settings.endGroup();

        return vectRet;
    }

};
