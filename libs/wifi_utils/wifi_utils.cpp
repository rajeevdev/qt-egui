#include <QStringList>
#include <QThread>
#include <QFile>
#include <QProcess>

#include <iostream>

#include "wifi_utils.h"

QString getAccessPoint(const QString & line)
{
    QStringList tokens = line.split("\t");
    if (tokens.size() == 5)
        return tokens[4];

    return QString();
}

void getAccessPointAndNetworkId(const QString & line, QString & accessPoint, int & networkId)
{
    networkId = -1;
    QStringList tokens = line.split("\t");
    if (tokens.size() == 4)
    {
        networkId = tokens[0].trimmed().toInt();
        accessPoint = tokens[1];
    }
}

bool scanWifi(QStringList& accessPoints, int delay)
{
    system("/usr/sbin/wpa_cli scan > /dev/null");
    QThread::sleep(delay);
    system("/usr/sbin/wpa_cli scan_results > /tmp/scan_results");

    QFile file("/tmp/scan_results");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;
    while (!file.atEnd()) {
        QByteArray line = file.readLine();
        QString token = getAccessPoint(line.trimmed());
        if (!token.isEmpty())
            accessPoints << token;
    }

    return true;
}

bool connectWifi(const QString& accessPoint, const QString& psk)
{
    int networkId = -1;
    char command[200];

    system("wpa_cli list_network > /tmp/list_network");
    QFile file("/tmp/list_network");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;
    while (!file.atEnd())
    {
        QByteArray line = file.readLine();
        QString ap;
        int id = -1;
        getAccessPointAndNetworkId(line.trimmed(), ap, id);
        if (!ap.isEmpty())
        {
            if (accessPoint == ap)
            {
                networkId = id;
                break;
            }
        }
    }
    file.close();

    std::cout << "Existing Network ID: " << networkId << std::endl;

    if (networkId < 0)
    {
        std::cout << "Access point not available" << std::endl;

        system("wpa_cli add_network > /tmp/network_id");
        QFile file("/tmp/network_id");
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return false;
        while (!file.atEnd())
        {
            QByteArray line = file.readLine();
            if (line.contains("Selected interface"))
                continue;

            networkId = line.trimmed().toInt();
        }
        file.close();

        if (networkId < 0)
            return false;

        std::cout << "Network ID: " << networkId << std::endl;

        sprintf(command, "wpa_cli set_network %d ssid '\"%s\"'", networkId, accessPoint.toLatin1().data());
        std::cout << "Command " << command << std::endl;
        system(command);
        sprintf(command, "wpa_cli set_network %d psk '\"%s\"'", networkId, psk.toLatin1().data());
        std::cout << "Command " << command << std::endl;
        system(command);
    }

    sprintf(command, "wpa_cli enable %d > /dev/null", networkId);
    std::cout << "Command " << command << std::endl;
    system(command);
    sprintf(command, "wpa_cli select_network %d > /dev/null", networkId);
    std::cout << "Command " << command << std::endl;
    system(command);
    sprintf(command, "wpa_cli save_config");
    std::cout << "Command " << command << std::endl;
    system(command);
    sprintf(command, "/etc/init.d/S40network restart");
    std::cout << "Command " << command << std::endl;
    system(command);

    return true;

}
