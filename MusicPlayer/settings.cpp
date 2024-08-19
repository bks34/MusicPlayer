#include "settings.h"
#include <fstream>

using std::fstream;

Settings::Settings()
{
    volume=50;
    autoNext=false;
}

void Settings::loadFile()
{
    fstream f;
    f.open("settings",std::ios::in | std::ios::binary);
    f>>volume;
    f.get();
    f>>autoNext;
}

void Settings::storeFile()
{
    fstream f;
    f.open("settings",std::ios::out | std::ios::binary);
    f<<volume;
    f<<'\n';
    f<<autoNext;
}
