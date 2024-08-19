#include "leftwidget.h"
#include <QVBoxLayout>

LeftWidget::LeftWidget(QWidget *parent) : QWidget(parent)
{
    appTitleLabel= new QLabel(tr("音乐播放器"));
    QFont font = appTitleLabel->font(); //调整字体
    font.setPointSize(25);
    appTitleLabel->setFont(font);
    appTitleLabel->setStyleSheet("color: rgb(230,230,230)");

    optionListWidget =new QListWidget;
    optionListWidget->insertItem(0,tr("播放列表"));
    optionListWidget->insertItem(1,tr("歌曲详情"));
    optionListWidget->insertItem(2,tr("设置"));
    font =optionListWidget->font();
    font.setPointSize(18);
    optionListWidget->setFont(font);
    optionListWidget->setStyleSheet("background-color: rgb(220,210,200);"
                                    "color: rgb(20,80,100);");
    connect(optionListWidget,SIGNAL(itemPressed(QListWidgetItem*)),this,SLOT(slotItemChange(QListWidgetItem*)));


    QVBoxLayout *layout=new QVBoxLayout(this);
    layout->addWidget(appTitleLabel);
    layout->setStretchFactor(appTitleLabel,1);
    layout->addWidget(optionListWidget);
    layout->setStretchFactor(optionListWidget,5);
}

void LeftWidget::slotItemChange(QListWidgetItem* item)
{
    int index=optionListWidget->row(item);
    changeItem(index);
}
