#ifndef __WIFI_UTILS_H__
#define __WIFI_UTILS_H__

#include <QString>

#if defined WIFI_UTILS_LIB
    #define WIFI_UTILS_EXPORT Q_DECL_EXPORT
#else
    #define WIFI_UTILS_EXPORT Q_DECL_IMPORT
#endif


extern "C" WIFI_UTILS_EXPORT bool scanWifi(QStringList& accessPoints, int delay = 5);
extern "C" WIFI_UTILS_EXPORT bool connectWifi(const QString& accessPoint, const QString& psk);

#endif // __WIFI_UTILS_H__
