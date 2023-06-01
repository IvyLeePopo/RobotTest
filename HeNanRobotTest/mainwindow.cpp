#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "henancommand.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    intermediateClient = new IntermediateClient;

    connect(intermediateClient, SIGNAL(signal_showHomeWidget()), this, SLOT(slot_showHomeWidget()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showEvent(QShowEvent *event)
{
    Q_UNUSED(event);
    //ui->pushButton_WebSocketTool->show();
}

void MainWindow::hideEvent(QHideEvent *event)
{
    Q_UNUSED(event);
    //ui->pushButton_WebSocketTool->hide();
}

void MainWindow::slot_showHomeWidget()
{
    this->show();
}

//WebSocket调试
void MainWindow::on_pushButton_WebSocketTool_clicked()
{
    intermediateClient->show();
    this->hide();
}

