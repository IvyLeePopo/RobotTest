#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QShowEvent>
#include <QHideEvent>
#include "intermediateclient.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public:
    void showEvent(QShowEvent *event);
    void hideEvent(QHideEvent *event);

public slots:
    void slot_showHomeWidget();

private slots:
    void on_pushButton_WebSocketTool_clicked();

private:
    Ui::MainWindow *ui;
    IntermediateClient *intermediateClient;
};
#endif // MAINWINDOW_H
