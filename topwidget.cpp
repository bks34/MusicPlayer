#include "topwidget.h"


TopWidget::TopWidget(QSplitter *parent) : QSplitter(parent)
{
    leftWidget =new LeftWidget(this);
    rightWidget = new RightWidget(this);

    this->setStretchFactor(1,1);

    connect(leftWidget,SIGNAL(changeItem(int)),rightWidget,SLOT(slotchangeWidget(int)));
}


