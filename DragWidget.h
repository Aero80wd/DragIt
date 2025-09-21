//
// Created by jiahang on 25-9-21.
//

#ifndef DRAGWIDGET_H
#define DRAGWIDGET_H
#include <QPropertyAnimation>
#include<QWidget>
#include<QMediaPlayer>
#include<QAudioOutput>
class DragWidget : public QWidget{
    Q_OBJECT
public:
    explicit DragWidget(QWidget *parent = nullptr);
    ~DragWidget() override;
private:
    void moveEvent(QMoveEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
private:
    bool isDragging = false;
    QPoint offset;
    QPropertyAnimation *ani;
    bool isBoomed = false;
    bool isAnirun = false;
    //QMediaPlayer *player;
    //QAudioOutput *audioOut;
public:
    double startTime = 0;
    double endTime = 0;

signals:
    void boom();
};



#endif //DRAGWIDGET_H
