//
// Created by jiahang on 25-9-21.
//

#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include<QWidget>
#include<QCheckBox>
#include<QSize>
#include<QPoint>
#include<QRect>
#include<QPropertyAnimation>
#include<QEasingCurve>
#include <QLabel>
#include<QPainter>

#include "DragWidget.h"


class MainWindow : public QWidget {
Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;
private:
    void paintEvent(QPaintEvent*) override;
private slots:
    void boom();
private:
    DragWidget *dragWidget;
    QPropertyAnimation *ani;
    QLabel *label;
};



#endif //MAINWINDOW_H
