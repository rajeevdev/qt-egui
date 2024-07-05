#include <QCoreApplication>
#include <QCommandLineParser>

#include <iostream>

#include <wifi_utils.h>

void showHelp(const QString & message)
{
    std::cout << message.toLatin1().data() << std::endl << std::endl;
    std::cout << "Valid options:" << std::endl;
    std::cout << "- wifi_helper scan" << std::endl;
    std::cout << "- wifi_helper connect <AccessPoint> <PSK>" << std::endl;
}

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    if (argc < 2)
    {
        showHelp("Argument missing !!!");
        return -1;
    }

    if (QString(argv[1]) == "scan")
    {
        std::cout << "Scanning wifi accesspoints..." << std::endl;
        QStringList accessPoints;
        scanWifi(accessPoints);
        foreach (QString ap, accessPoints) {
            std::cout << "'" << ap.toLatin1().data() << "'" << std::endl;
        }
    }
    else if (QString(argv[1]) == "connect")
    {
        if (argc < 4)
        {
            showHelp("Access point and PSK required !!!");
            return -1;
        }

        QString accessPoint = QString(argv[2]).trimmed();
        QString psk = QString(argv[3]).trimmed();

        std::cout << "Connecting to AP '"
                  << accessPoint.toLatin1().data()
                  << "' with psk '"
                  << psk.toLatin1().data()
                  << "'"
                  << std::endl;

        connectWifi(accessPoint, psk);
    }
    else
    {
        showHelp("Invalid option !!!");
    }


    return 0;
}

