#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>

class Settings
{
public:
    Settings();
    void loadFile();
    void storeFile();

    int volume;
    bool autoNext;
};

#endif // SETTINGS_H
