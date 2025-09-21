//
// Created by jiahang on 25-9-21.
//

#include "MainWindow.h"

#include <QDateTime>
#include <qguiapplication.h>
#include<QLabel>
#include<QTimer>
MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {
    setWindowTitle("Drag it!");
    setFixedSize(1000,700);
    dragWidget = new DragWidget(this);
    dragWidget->setGeometry(450,100,150,150);
    ani = new QPropertyAnimation(this, "pos");
    ani->setEasingCurve(QEasingCurve::OutElastic);
    label = new QLabel(this);

    connect(dragWidget,&DragWidget::boom,this,&MainWindow::boom);
#ifdef __linux__
    if (QGuiApplication::platformName() == "wayland") {
        label->setText("你正在使用Wayland平台，\n部分功能将会受到限制。");
    }

#endif
}
MainWindow::~MainWindow() {
}

void MainWindow::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.setPen(QPen(QColor("#f5d664"),10,Qt::SolidLine));
    painter.drawLine(dragWidget->x()+64,dragWidget->y()+75,width()/2+20,height()/2);

    painter.end();
    if (dragWidget->x() < 120 && dragWidget->y() < 50) {
        label->hide();
    }else {
        label->show();
    }
    update();
}
void MainWindow::boom() {
    qDebug() << "MainWindow::boom";
    ani->setKeyValueAt(0,pos());
    double v = QDateTime::currentMSecsSinceEpoch()/1000.0 - dragWidget->startTime;
    ani->setKeyValueAt(0.5,QPoint(x(),qFloor(y()-100*((v>=2?0.7:1.2)+v*1.7))));
    ani->setKeyValueAt(1,pos());
    ani->setDuration(floor(700 + v*100));
    ani->start();
    QMediaPlayer *player = new QMediaPlayer(this);
    QAudioOutput *audioOut = new QAudioOutput(this);
    player->setAudioOutput(audioOut);
    audioOut->setVolume(1);
    player->setSource(QUrl("qrc:/res/audio/wtf.mp3"));
    QLabel* wtfLabel = new QLabel(this);
    wtfLabel->setText("你干嘛");
    wtfLabel->setAlignment(Qt::AlignCenter);
    wtfLabel->setGeometry(width()/2-width()/4,height()/4*3,width()/2,100);
    wtfLabel->setFont(QFont("微软雅黑", 50));
    wtfLabel->hide();
    connect(player,&QMediaPlayer::playbackStateChanged,this,[=] {
        if (player->playbackState() == QMediaPlayer::StoppedState) {
            wtfLabel->hide();
        }
    });
    player->play();
    wtfLabel->show();

}
