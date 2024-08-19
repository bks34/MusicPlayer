#include "mainwidget.h"


MainWidget::MainWidget(QWidget *parent) : QWidget(parent)
{
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setWindowFlag(Qt::FramelessWindowHint);
    this->setWindowIcon(QIcon(":/icon/icon.png"));

    playerWidget =new PlayerWidget;
    topWidget = new TopWidget;

    QVBoxLayout* mainLayout= new QVBoxLayout(this);
    mainLayout->addWidget(topWidget);
    mainLayout->setStretchFactor(topWidget,7);
    mainLayout->addWidget(playerWidget);
    mainLayout->setStretchFactor(playerWidget,1);
    mainLayout->setMargin(0);

    connect(topWidget->rightWidget,SIGNAL(changeMusic(int)),playerWidget,SLOT(slotPlay(int)));
    connect(playerWidget,SIGNAL(changeMusic(int)),topWidget->rightWidget,SLOT(slotChangemusicInfoWidget(int)));
    connect(topWidget->rightWidget->settingWidget,SIGNAL(changeVolume()),playerWidget,SLOT(slotChangeVolume()));
}
