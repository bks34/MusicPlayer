#ifndef TOPWIDGET_H
#define TOPWIDGET_H

#include <QSplitter>
#include "leftwidget.h"
#include "rightwidget.h"

class TopWidget : public QSplitter
{
    Q_OBJECT
public:
    explicit TopWidget(QSplitter *parent = nullptr);


    LeftWidget *leftWidget;
    RightWidget *rightWidget;

    int leftWidgetIndex =0;
};

#endif // TOPWIDGET_H
