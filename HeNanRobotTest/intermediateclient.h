#ifndef INTERMEDIATECLIENT_H
#define INTERMEDIATECLIENT_H

#include <QWidget>
#include <QDebug>
#include <QListView>
#include <QWebSocket>
#include <QTimer>
#include <QThread>

namespace Ui {
class IntermediateClient;
}

class IntermediateClient : public QWidget
{
    Q_OBJECT

public:
    explicit IntermediateClient(QWidget *parent = nullptr);
    ~IntermediateClient();

protected:
    void WebSocketInit();

signals:
    void signal_showHomeWidget();

protected slots:
    void SlotSendData(QString data="");//发送数据
    void SlotBinaryMessageReceived(const QByteArray &msg);//接收数据
    void SlotDisConnected();
    void SlotConnected();
    void SlotSendHeartBeat();

private slots:
    void on_pushButton_Connect_clicked();
    void on_pushButton_Back_clicked();
    void on_pushButton_Clean_clicked();
    void on_pushButton_Stop_clicked();
    void on_pushButton_Send_clicked();
    //应答机器人
    void on_pushButton_UserInfo_clicked();
    void on_pushButton_GoWork_clicked();
    void on_pushButton_WorkOff_clicked();
    void on_pushButton_DownloadPara_clicked();
    void on_pushButton_LandInitLoad_clicked();
    void on_pushButton_HoliDay_clicked();
    void on_pushButton_QueueQuery_clicked();
    void on_pushButton_QueueAdd_clicked();
    void on_pushButton_QueueDel_clicked();
    //中间件请求
    void on_pushButton_HeartBeat_clicked();
    void on_comboBox_PrepareCard_activated(const QString &arg1);
    void on_comboBox_ReadCard_activated(const QString &arg1);
    void on_comboBox_WriteCard_activated(const QString &arg1);
    void on_pushButton_TextBroadCast_clicked();
    void on_comboBox_TradeInfo_activated(const QString &arg1);
    void on_pushButton_TradeResult_clicked();
    void on_pushButton_Start_clicked();
    void on_pushButton_End_clicked();
    void on_comboBox_GetBackCode_En_activated(const QString &arg1);
    void on_comboBox_GetBackCode_Ex_activated(const QString &arg1);
    void on_pushButton_CheckMsgCtrl_clicked();
    void on_pushButton_SelectMsgCtrl_clicked();

private:
    Ui::IntermediateClient *ui;
    bool m_RecvFlag = true;
    bool m_IsConnect = false;
    QWebSocket *m_WebSocket = nullptr;
    QTimer *m_timer = nullptr;
    QString m_Url;
};

#endif // INTERMEDIATECLIENT_H
