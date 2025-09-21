//
// Created by jiahang on 25-9-21.
//

#include "DragWidget.h"
#include<QMouseEvent>
#include<QPainter>
#include<QDateTime>
#include<QPen>
#include<QBrush>
DragWidget::DragWidget(QWidget *parent) : QWidget(parent) {
    setMouseTracking(true);
    ani = new QPropertyAnimation(this, "pos");
    ani->setEasingCurve(QEasingCurve::OutElastic);


}
DragWidget::~DragWidget() {
    delete ani;
}

void DragWidget::moveEvent(QMoveEvent *event) {
    if (!isBoomed && pos().y() < 0 && isAnirun) {
        emit boom();
        qDebug() << "DragWidget::boom";
        isBoomed = true;
    }
}
void DragWidget::mousePressEvent(QMouseEvent *event) {
    if(event->button() == Qt::LeftButton){
        isDragging = true;
        offset = event->position().toPoint();
        ani->setEndValue(pos());
        qDebug()<<ani->endValue();
        isBoomed = false;
        startTime = QDateTime::currentMSecsSinceEpoch()/1000.0;

    }
}
void DragWidget::mouseReleaseEvent(QMouseEvent *event) {
    endTime = QDateTime::currentMSecsSinceEpoch()/1000.0;
    if (event->button() == Qt::LeftButton) {
        isDragging = false;
    }
    double sec = endTime-startTime;
    ani->setDuration(qFloor(1000/(1+sec/3.5)));

    isAnirun = true;
    ani->setStartValue(pos());

    ani->start();
    QMediaPlayer *player = new QMediaPlayer(this);
    QAudioOutput *audioOut = new QAudioOutput(this);
    player->setAudioOutput(audioOut);
    audioOut->setVolume(0.5);
    player->setSource(QUrl("qrc:/res/audio/ji.mp3"));
    player->play();
    connect(ani,&QPropertyAnimation::finished,this,[=](){
        isAnirun = false;
    });
}
void DragWidget::mouseMoveEvent(QMouseEvent *event) {
    if (isDragging && event->buttons() & Qt::LeftButton) {
        QPoint global_pos = event->globalPosition().toPoint();
        QPoint parent_pos = static_cast<QWidget*>(parent())->mapFromGlobal(global_pos);
        QPoint new_pos = parent_pos - offset;
        move(new_pos);
        if (!parent()) return;
        QRect p = static_cast<QWidget*>(parent())->rect();
        int x = qMax(0,qMin(this->x(),p.width()-width()));
        int y = qMax(0,qMin(this->y(),p.height()-height()));
        move(x,y);
    }
}
void DragWidget::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);
    int colorv = 0;
    if (isDragging) {
        colorv = qFloor((QDateTime::currentMSecsSinceEpoch()/1000.0-startTime)*70);
        if (colorv > 200) colorv=200;
    }

    QColor color(255, 255 - colorv, 255 - colorv);
    QPixmap pixmap(":/res/img/ikun.png");
    QPixmap scaledPixmap = pixmap.scaled(size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);

    // 计算绘制位置
    int x = (width() - scaledPixmap.width()) / 2;
    int y = (height() - scaledPixmap.height()) / 2;

    // 先绘制原图
    painter.drawPixmap(x, y, scaledPixmap);

    // 只在有颜色的区域添加滤镜效果
    if (colorv > 0) {
        // 保存当前绘图状态
        painter.save();

        // 使用原图作为裁剪区域，这样滤镜只会在图片的非透明部分生效
        painter.setClipRegion(QRegion(scaledPixmap.mask()));

        // 设置混合模式和滤镜
        painter.setCompositionMode(QPainter::CompositionMode_Screen);

        // 在图片区域内绘制颜色滤镜
        painter.fillRect(x, y, scaledPixmap.width(), scaledPixmap.height(),
                        QColor(255, 0, 0, colorv));

        // 恢复绘图状态
        painter.restore();
    }

    painter.end();
}