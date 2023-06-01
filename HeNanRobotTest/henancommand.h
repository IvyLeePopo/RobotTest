#ifndef HENANCOMMAND_H
#define HENANCOMMAND_H

#include <QObject>
#include <QJsonObject>
#include <QDateTime>

class HeNanCommand
{
public:
    HeNanCommand();
    static HeNanCommand &GetInstance();
    //0x70
    QString GoWorkCardCmdToHex();
    QString WorkOffCmdToHex();
    QString DownloadParamCmdToHex();
    QString LandInitLoadCmdToHex();
    QString HoliDayCmdToHex();
    QString QueueQueryCmdToHex();
    QString QueueAddCmdToHex();
    QString QueueDelCmdToHex();
    //0x80
    QString PackHeartBeat();
    QString PrepareCardCmdToHex(QString VehType);
    QString CardRecycleCmdToHex(QString strNum);
    QString WriteCardCmdToHex(QString strNum);
    QString SpecialStartCmdToHex();
    QString SpecialEndCmdToHex();
    QString TextBroadCastCmdToHex(QString text);
    QString TradeInfoCmdToHex(QString strNum);
    QString TradeResultCmdToHex();
    QString GetBackCodeCmdToHex(QString strNum);
    QString CheckMsgCtrlCmdToHex();
    QString SelectMsgCtrlCmdToHex();

    //websocketserver
    QJsonObject PackagingExternJson(QString StrApiKey, QJsonObject Obj);
    QString PackagingCheckPlateInfo();
    QString PackagingCheckWeightInfoConfirm();
    QString PackagingCheckQueueInfoConfirm();
    QString PackagingAuthorizeConfirm();
    QString PackagingUnpaidConfirm();
    QString PackagingAccountPasswdAuthorizeResp();
    QString PackagingLargeLicense();
    QString PackagingCheckMsgCtrl();
    QString PackagingSelectMsgCtrlResp();
    QString PackagingEntryUpCmdJSON();

public:
    QString GetSerialNo();
    QString GetSpecialEventNo();
    QString m_serialNo;
    QString m_specialEventNo;
    //QString m_LaneHex = "6201080365";   //测试
    QString m_LaneHex = "4101177903";
    QString m_userId = "020403054";
    QString vehPlate = "粤A8301Z_1";
    QString msgId = "";
    QString time = "2022-12-02T14:33:12";
    int enExitType = 0;
    QString bizType = "JSON";
    QString sign = "NONE";
    int zdType = 1;
    QJsonObject bizContentObj;
};

#endif // HENANCOMMAND_H
