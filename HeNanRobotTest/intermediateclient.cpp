#include "intermediateclient.h"
#include "ui_intermediateclient.h"
#include "henancommand.h"
#include "CommonPacketObj.h"

IntermediateClient::IntermediateClient(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IntermediateClient)
{
    ui->setupUi(this);

    WebSocketInit();

    QList<QComboBox *> list_ComboBox = findChildren<QComboBox *>();
    foreach(QComboBox *p, list_ComboBox)
       p->setStyleSheet("QComboBox {background-color: #6a8f95;border: 0px solid gray; color: #bbbbbb;font: normal normal 12px \"Microsoft YaHei\";}"
                        "QComboBox:hover{background-color: #386972;}"
                        "QComboBox QAbstractItemView {outline: 0px solid gray;border: 1px solid #fdfdfd;color: green;background-color: #c4d2d5;selection-background-color: lightgreen;}"
                        "QComboBox QAbstractItemView::item{height:33px;color: #000000;}"
                        "QComboBox QAbstractItemView::item:selected { color: #bbbbbb;background-color: #386972;}"
                        "QComboBox QAbstractItemView::item:hover {color: #bbbbbb;background-color: #386972;}"
                        "QComboBox::drop-down {subcontrol-origin: padding; subcontrol-position: top right;height:33px;width:29px;border-left-width: 0px;}"
                        "QComboBox::drop-down:hover {background: #386972;}"
                        "QComboBox::down-arrow {height:33px;width:29px;image: url(:/resource/xiala.png);}"
                        "QComboBox::down-arrow:hover {image: url(:/resource/xiala.png);}"
                        "QComboBox::down-arrow:pressed {image: url(:/resource/xiala.png);}");
}

IntermediateClient::~IntermediateClient()
{
    delete ui;
}

//初始化WebSocket
void IntermediateClient::WebSocketInit()
{
    if(m_timer == nullptr)
    {
        m_timer = new QTimer();
    }
}

void IntermediateClient::on_pushButton_Connect_clicked()
{
    m_Url = "ws://"+ui->lineEdit_Url->text()+":9090";
    qDebug() << __LINE__ << __FUNCTION__ << "连接服务器，地址："+m_Url;
    if(m_WebSocket == nullptr)
    {
        m_WebSocket = new QWebSocket();
        connect(m_WebSocket, &QWebSocket::disconnected, this, &IntermediateClient::SlotDisConnected, Qt::AutoConnection);
        connect(m_WebSocket, &QWebSocket::binaryMessageReceived, this, &IntermediateClient::SlotBinaryMessageReceived, Qt::AutoConnection);
        connect(m_WebSocket, &QWebSocket::connected, this, &IntermediateClient::SlotConnected, Qt::AutoConnection);
        connect(m_timer, &QTimer::timeout,this, &IntermediateClient::SlotSendHeartBeat, Qt::AutoConnection);
        m_WebSocket->open(QUrl(m_Url));
        //m_timer->start(10000);
    }
    else if(m_IsConnect == false)
    {
        qDebug() << __LINE__ << __FUNCTION__ << "Reconnect...";
        m_WebSocket->abort();
        m_WebSocket->open(QUrl(m_Url));
    }
}

//断开连接
void IntermediateClient::SlotDisConnected()
{
    qDebug() << __LINE__ << __FUNCTION__ << "DisConnected!";
    ui->label_status->setText("断开连接");
    m_IsConnect = false;
}

void IntermediateClient::SlotConnected()
{
    ui->label_status->setText("连接成功");
    m_IsConnect = true;
}

//发送心跳包
void IntermediateClient::SlotSendHeartBeat()
{
    if(m_IsConnect)
    {
        qDebug() << __LINE__ << __FUNCTION__ << "发送心跳";
        QString qStr = HeNanCommand::GetInstance().PackHeartBeat();
        SlotSendData(qStr);
    }
}

//接收数据
void IntermediateClient::SlotBinaryMessageReceived(const QByteArray &msg)
{
    if(msg.length()!=0 && m_RecvFlag)
    {
        //使textEdit控件追加显示接收到的数据
        QString hexstr;
        hexstr.append(msg.toHex(' ').toUpper());
        ui->textEdit->append("[接收] " + hexstr);
    }
}

//发送数据
void IntermediateClient::SlotSendData(QString data)
{
    QString strdata;
    if(data != "")
        strdata = data;
    else
        strdata = ui->lineEdit_Send->text();
    strdata = strdata.simplified(); //将多个空格转换为单个空格(包涵\n)
    QString showSendData;
    QString s[strdata.size()];
    int hexnum[strdata.size()];
    QByteArray bytes;
    QStringList strlist = strdata.split(" ");

    for(int i=0;i<strlist.size();i++)
    {
        //s[i] = "0x"+strlist.at(i);
        s[i] = strlist.at(i);
        showSendData += s[i]+" ";
        bool ok;
        hexnum[i] = s[i].toInt(&ok,16); // 表示以16进制方式读取字符串
        bytes[i] = hexnum[i];
        //qDebug()<<s[i]<<" "<<hexnum[i];
    }
    ui->textEdit->append("[发送] " + showSendData);
    qint64 len = m_WebSocket->sendBinaryMessage(bytes);
    qDebug() << __LINE__ << __FUNCTION__ << "发送长度：" << len;
}

void IntermediateClient::on_pushButton_Back_clicked()
{
    qDebug() << __LINE__ << __FUNCTION__ << "返回";
    //this->parentWidget()->show();
    emit signal_showHomeWidget();
    this->hide();
}

void IntermediateClient::on_pushButton_Clean_clicked()
{
    qDebug() << __LINE__ << __FUNCTION__ << "清空接收";
    ui->textEdit->clear();
}

//停止接收
void IntermediateClient::on_pushButton_Stop_clicked()
{
    m_RecvFlag = !m_RecvFlag;
    if(m_RecvFlag)
        ui->pushButton_Stop->setText("暂停接收");
    else
        ui->pushButton_Stop->setText("继续接收");
}

void IntermediateClient::on_pushButton_Send_clicked()
{
    qDebug() << __LINE__ << __FUNCTION__ << "发送";
    SlotSendData();
}

//////////////////////////////////////////////////////////////////////////////////////////
//身份数据解密应答
void IntermediateClient::on_pushButton_UserInfo_clicked()
{

}

void IntermediateClient::on_pushButton_GoWork_clicked()
{
    qDebug() << __LINE__ << __FUNCTION__ << "上班应答";
    QString qStr = HeNanCommand::GetInstance().GoWorkCardCmdToHex();
    ui->lineEdit_Send->setText(qStr);
    SlotSendData();
}

void IntermediateClient::on_pushButton_WorkOff_clicked()
{
    qDebug() << __LINE__ << __FUNCTION__ << "下班应答";
    QString qStr = HeNanCommand::GetInstance().WorkOffCmdToHex();
    ui->lineEdit_Send->setText(qStr);
    SlotSendData();
}

void IntermediateClient::on_pushButton_DownloadPara_clicked()
{
    qDebug() << __LINE__ << __FUNCTION__ << "参数下载应答";
    QString qStr = HeNanCommand::GetInstance().DownloadParamCmdToHex();
    ui->lineEdit_Send->setText(qStr);
    SlotSendData();
}

void IntermediateClient::on_pushButton_LandInitLoad_clicked()
{
    qDebug() << __LINE__ << __FUNCTION__ << "车道初始化应答";
    QString qStr = HeNanCommand::GetInstance().LandInitLoadCmdToHex();
    ui->lineEdit_Send->setText(qStr);
    SlotSendData();
}

void IntermediateClient::on_pushButton_HoliDay_clicked()
{
    qDebug() << __LINE__ << __FUNCTION__ << "节假日控制接口应答";
    QString qStr = HeNanCommand::GetInstance().HoliDayCmdToHex();
    ui->lineEdit_Send->setText(qStr);
    SlotSendData();
}

void IntermediateClient::on_pushButton_QueueQuery_clicked()
{
    qDebug() << __LINE__ << __FUNCTION__ << "队列列表查询回复";
    QString qStr = HeNanCommand::GetInstance().QueueQueryCmdToHex();
    ui->lineEdit_Send->setText(qStr);
    SlotSendData();
}

void IntermediateClient::on_pushButton_QueueAdd_clicked()
{
    qDebug() << __LINE__ << __FUNCTION__ << "队列列表查询回复";
    QString qStr = HeNanCommand::GetInstance().QueueAddCmdToHex();
    ui->lineEdit_Send->setText(qStr);
    SlotSendData();
}

void IntermediateClient::on_pushButton_QueueDel_clicked()
{
    qDebug() << __LINE__ << __FUNCTION__ << "队列删除请求回复";
    QString qStr = HeNanCommand::GetInstance().QueueDelCmdToHex();
    ui->lineEdit_Send->setText(qStr);
    SlotSendData();
}

//////////////////////////////////////////////////////////////////////////////////////////
//心跳包
void IntermediateClient::on_pushButton_HeartBeat_clicked()
{
    qDebug() << __LINE__ << __FUNCTION__ << "发送心跳";
    SlotSendHeartBeat();
}

//备卡请求
void IntermediateClient::on_comboBox_PrepareCard_activated(const QString &arg1)
{
    QString num = arg1.right(1);
    QString VehType;
    if(arg1.contains("客"))
    {
        VehType = num;
    }
    else if(arg1.contains("货"))
    {
        VehType = "1"+num;
    }
    else if(arg1.contains("专"))
    {
        VehType = "2"+num;
    }
    qDebug() << __LINE__ << __FUNCTION__ << "备卡请求" << VehType;
    QString qStr = HeNanCommand::GetInstance().PrepareCardCmdToHex(VehType);
    ui->lineEdit_Send->setText(qStr);
    SlotSendData();
}

//读卡状态
void IntermediateClient::on_comboBox_ReadCard_activated(const QString &arg1)
{
    qDebug() << __LINE__ << __FUNCTION__ << "读卡状态请求";
    QString qStr = HeNanCommand::GetInstance().CardRecycleCmdToHex(arg1.left(2));
    ui->lineEdit_Send->setText(qStr);
    SlotSendData();
}

//写卡完成
void IntermediateClient::on_comboBox_WriteCard_activated(const QString &arg1)
{
    qDebug() << __LINE__ << __FUNCTION__ << "写卡完成";
    QString qStr = HeNanCommand::GetInstance().WriteCardCmdToHex(arg1.left(2));
    ui->lineEdit_Send->setText(qStr);
    SlotSendData();
}

//文字播音
void IntermediateClient::on_pushButton_TextBroadCast_clicked()
{
    qDebug() << __LINE__ << __FUNCTION__ << "文字播音";
    QString qStr = HeNanCommand::GetInstance().TextBroadCastCmdToHex(ui->lineEdit_Send->text());
    SlotSendData(qStr);
}

//车辆（交易）信息
void IntermediateClient::on_comboBox_TradeInfo_activated(const QString &arg1)
{
    qDebug() << __LINE__ << __FUNCTION__ << "车辆（交易）信息";
    QString qStr = HeNanCommand::GetInstance().TradeInfoCmdToHex(arg1.left(2));
    ui->lineEdit_Send->setText(qStr);
    SlotSendData();
}

//显示交易结果
void IntermediateClient::on_pushButton_TradeResult_clicked()
{
    qDebug() << __LINE__ << __FUNCTION__ << "显示交易结果";
    QString qStr = HeNanCommand::GetInstance().TradeResultCmdToHex();
    ui->lineEdit_Send->setText(qStr);
    SlotSendData();
}

//特情开始
void IntermediateClient::on_pushButton_Start_clicked()
{
    qDebug() << __LINE__ << __FUNCTION__ << "特情开始请求";
    QString qStr = HeNanCommand::GetInstance().SpecialStartCmdToHex();
    ui->lineEdit_Send->setText(qStr);
    SlotSendData();
}

//特情结束
void IntermediateClient::on_pushButton_End_clicked()
{
    qDebug() << __LINE__ << __FUNCTION__ << "特情结束请求";
    QString qStr = HeNanCommand::GetInstance().SpecialEndCmdToHex();
    ui->lineEdit_Send->setText(qStr);
    SlotSendData();
}

//获取回控数据请求
void IntermediateClient::on_comboBox_GetBackCode_En_activated(const QString &arg1)
{
    qDebug() << __LINE__ << __FUNCTION__ << "获取回控数据请求";
    QString qStr = HeNanCommand::GetInstance().GetBackCodeCmdToHex(arg1.left(2));
    ui->lineEdit_Send->setText(qStr);
    SlotSendData();
}

void IntermediateClient::on_comboBox_GetBackCode_Ex_activated(const QString &arg1)
{
    qDebug() << __LINE__ << __FUNCTION__ << "获取回控数据请求";
    QString qStr = HeNanCommand::GetInstance().GetBackCodeCmdToHex(arg1.left(2));
    ui->lineEdit_Send->setText(qStr);
    SlotSendData();
}

//确认信息回控请求
void IntermediateClient::on_pushButton_CheckMsgCtrl_clicked()
{
    qDebug() << __LINE__ << __FUNCTION__ << "确认信息回控请求";
    QString qStr = HeNanCommand::GetInstance().CheckMsgCtrlCmdToHex();
    ui->lineEdit_Send->setText(qStr);
    SlotSendData();
}

//选项信息回控请求
void IntermediateClient::on_pushButton_SelectMsgCtrl_clicked()
{
    qDebug() << __LINE__ << __FUNCTION__ << "选项信息回控请求";
    QString qStr = HeNanCommand::GetInstance().SelectMsgCtrlCmdToHex();
    ui->lineEdit_Send->setText(qStr);
    SlotSendData();
}
