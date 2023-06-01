#include "henancommand.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>
#include <QDateTime>
#include "CommonPacketObj.h"

HeNanCommand::HeNanCommand()
{

}

HeNanCommand &HeNanCommand::GetInstance()
{
    static HeNanCommand instace;
    return instace;
}

//上班应答
QString HeNanCommand::GoWorkCardCmdToHex()
{
    QJsonObject jsonObj, jsonObj1;

    jsonObj1.insert("name", "1123898");
    jsonObj1.insert("userId", m_userId);
    jsonObj1.insert("loginTime", "2022.10.24:14.26.00");
    jsonObj1.insert("roleId", "收费员");
    jsonObj1.insert("Scheduling", "1");
    jsonObj1.insert("startNo", "123123");

    jsonObj.insert("GoWorkResp", jsonObj1);
    QJsonDocument document;
    document.setObject(jsonObj);
    QByteArray jsonBytes = document.toJson(QJsonDocument::Compact);

    vector<uint8> vec_data = CommonPacketObj::PackBytes(CMD_TYPE1_70,CMD_GoWork_Resp,jsonBytes.data(),jsonBytes.length());
    QByteArray bytes(reinterpret_cast<char*>(vec_data.data()), vec_data.size());

    QString hexstr;
    hexstr.append(bytes.toHex(' ').toUpper());

    QString strJson = QString::fromUtf8(jsonBytes);
    qDebug() << __LINE__ << __FUNCTION__ << "打包上班应答命令" << strJson;
    qDebug() << __LINE__ << __FUNCTION__ << "Data:" << hexstr;

    return hexstr;
}

//下班应答
QString HeNanCommand::WorkOffCmdToHex()
{
    QJsonObject jsonObj, jsonObj1;

    jsonObj1.insert("info", "成功");
    jsonObj1.insert("receiveTime", "2022-10-27T17:37:41");

    jsonObj.insert("WorkOffResp", jsonObj1);
    QJsonDocument document;
    document.setObject(jsonObj);
    QByteArray jsonBytes = document.toJson(QJsonDocument::Compact);

    vector<uint8> vec_data = CommonPacketObj::PackBytes(CMD_TYPE1_70,CMD_WorkOff_Resp,jsonBytes.data(),jsonBytes.length());
    QByteArray bytes(reinterpret_cast<char*>(vec_data.data()), vec_data.size());

    QString hexstr;
    hexstr.append(bytes.toHex(' ').toUpper());

    QString strJson = QString::fromUtf8(jsonBytes);
    qDebug() << __LINE__ << __FUNCTION__ << "打包降杆请求命令" << strJson;
    qDebug() << __LINE__ << __FUNCTION__ << "Data:" << hexstr;

    return hexstr;
}

//参数下载应答
QString HeNanCommand::DownloadParamCmdToHex()
{
    QJsonObject jsonObj, jsonObj1;
    QJsonArray jsonArray;

    jsonObj1.insert("userId", m_userId);
    jsonObj1.insert("AreaID", "4401");
    jsonObj1.insert("ProvinceName", "河南");
    jsonObj1.insert("ProvinceNo", "4401");
    jsonObj1.insert("LaneNo", "003");
    jsonObj1.insert("LaneHex", m_LaneHex);
    jsonObj1.insert("StationNo", "06");
    jsonObj1.insert("StationName", "鲁山");
    jsonObj1.insert("RoadName", "迎宾大道北");
    jsonObj1.insert("RoadNo", "1123907");
    jsonObj1.insert("CurrentTime", QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    jsonObj1.insert("laneType", 2);
    jsonObj.insert("LaneInfoResp",jsonObj1);

    QJsonDocument document;
    document.setObject(jsonObj);
    QByteArray jsonBytes = document.toJson(QJsonDocument::Compact);

    vector<uint8> vec_data = CommonPacketObj::PackBytes(CMD_TYPE1_70,CMD_LaneInfo_Resp,jsonBytes.data(),jsonBytes.length());
    QByteArray bytes(reinterpret_cast<char*>(vec_data.data()), vec_data.size());

    QString hexstr;
    hexstr.append(bytes.toHex(' ').toUpper());

    QString strJson = QString::fromUtf8(jsonBytes);
    qDebug() << __LINE__ << __FUNCTION__ << "参数下载应答命令" << strJson;
    qDebug() << __LINE__ << __FUNCTION__ << "Data:" << hexstr;

    return hexstr;
}

//车道初始化应答
QString HeNanCommand::LandInitLoadCmdToHex()
{
    QJsonObject jsonObj, jsonObj1;

    jsonObj1.insert("info", "成功");
    jsonObj1.insert("receiveTime", "2022-10-27T17:37:41");

    jsonObj.insert("LaneInitResp", jsonObj1);
    QJsonDocument document;
    document.setObject(jsonObj);
    QByteArray jsonBytes = document.toJson(QJsonDocument::Compact);

    vector<uint8> vec_data = CommonPacketObj::PackBytes(CMD_TYPE1_70,CMD_Lane_Init_Resp,jsonBytes.data(),jsonBytes.length());
    QByteArray bytes(reinterpret_cast<char*>(vec_data.data()), vec_data.size());

    QString hexstr;
    hexstr.append(bytes.toHex(' ').toUpper());

    QString strJson = QString::fromUtf8(jsonBytes);
    qDebug() << __LINE__ << __FUNCTION__ << "打包车道初始化应答命令" << strJson;
    qDebug() << __LINE__ << __FUNCTION__ << "Data:" << hexstr;

    return hexstr;
}

//节假日控制接口应答
QString HeNanCommand::HoliDayCmdToHex()
{
    QJsonObject jsonObj, jsonObj1;

    jsonObj1.insert("info", "成功");
    jsonObj1.insert("receiveTime", "2022-10-27T17:37:41");

    jsonObj.insert("MtcHolidayResp", jsonObj1);
    QJsonDocument document;
    document.setObject(jsonObj);
    QByteArray jsonBytes = document.toJson(QJsonDocument::Compact);

    vector<uint8> vec_data = CommonPacketObj::PackBytes(CMD_TYPE1_70,CMD_Holidays_Resp,jsonBytes.data(),jsonBytes.length());
    QByteArray bytes(reinterpret_cast<char*>(vec_data.data()), vec_data.size());

    QString hexstr;
    hexstr.append(bytes.toHex(' ').toUpper());

    QString strJson = QString::fromUtf8(jsonBytes);
    qDebug() << __LINE__ << __FUNCTION__ << "打包节假日控制接口应答命令" << strJson;
    qDebug() << __LINE__ << __FUNCTION__ << "Data:" << hexstr;

    return hexstr;
}

//队列列表查询应答
QString HeNanCommand::QueueQueryCmdToHex()
{
    QJsonObject jsonObj, jsonObj1, jsonObj11;
    QJsonArray array;

    jsonObj11.insert("name","黄村");
    jsonObj11.insert("queueNum", 1);
    jsonObj11.insert("isEtc", true);
    jsonObj11.insert("obuMac", "F568AF203D");
    jsonObj11.insert("startTime", 1);
    jsonObj11.insert("plateNum", "粤A 8305B");
    jsonObj11.insert("plateColor", 1);
    jsonObj11.insert("vehicleType", 1);
    jsonObj11.insert("capPlateNum", "粤A 8305B");
    jsonObj11.insert("capPlateColor", 1);
    jsonObj11.insert("capVehicleType", 1);
    jsonObj11.insert("enterFlag", true);
    jsonObj11.insert("allowPass", true);

    array.append(jsonObj11);
    jsonObj1.insert("list", array);
    jsonObj1.insert("hasData", true);

    jsonObj.insert("QueueListResp", jsonObj1);
    QJsonDocument document;
    document.setObject(jsonObj);
    QByteArray jsonBytes = document.toJson(QJsonDocument::Compact);

    vector<uint8> vec_data = CommonPacketObj::PackBytes(CMD_TYPE1_70,CMD_QueueList_Resp,jsonBytes.data(),jsonBytes.length());
    QByteArray bytes(reinterpret_cast<char*>(vec_data.data()), vec_data.size());

    QString hexstr;
    hexstr.append(bytes.toHex(' ').toUpper());

    QString strJson = QString::fromUtf8(jsonBytes);
    qDebug() << __LINE__ << __FUNCTION__ << "打包队列列表查询回复命令" << strJson;
    qDebug() << __LINE__ << __FUNCTION__ << "Data:" << hexstr;

    return hexstr;
}

//队列添加请求应答
QString HeNanCommand::QueueAddCmdToHex()
{
    QJsonObject jsonObj, jsonObj1;

    jsonObj1.insert("info", "成功");
    jsonObj1.insert("receiveTime", "2022-10-27T17:37:41");

    jsonObj.insert("QueueAddResp", jsonObj1);
    QJsonDocument document;
    document.setObject(jsonObj);
    QByteArray jsonBytes = document.toJson(QJsonDocument::Compact);

    vector<uint8> vec_data = CommonPacketObj::PackBytes(CMD_TYPE1_70,CMD_QueueAdd_Resp,jsonBytes.data(),jsonBytes.length());
    QByteArray bytes(reinterpret_cast<char*>(vec_data.data()), vec_data.size());

    QString hexstr;
    hexstr.append(bytes.toHex(' ').toUpper());

    QString strJson = QString::fromUtf8(jsonBytes);
    qDebug() << __LINE__ << __FUNCTION__ << "打包队列添加请求回复命令" << strJson;
    qDebug() << __LINE__ << __FUNCTION__ << "Data:" << hexstr;

    return hexstr;
}

//队列删除请求应答
QString HeNanCommand::QueueDelCmdToHex()
{
    QJsonObject jsonObj, jsonObj1;

    jsonObj1.insert("info", "成功");
    jsonObj1.insert("receiveTime", "2022-10-27T17:37:41");

    jsonObj.insert("QueueDeleteResp", jsonObj1);
    QJsonDocument document;
    document.setObject(jsonObj);
    QByteArray jsonBytes = document.toJson(QJsonDocument::Compact);

    vector<uint8> vec_data = CommonPacketObj::PackBytes(CMD_TYPE1_70,CMD_QueueDelete_Resp,jsonBytes.data(),jsonBytes.length());
    QByteArray bytes(reinterpret_cast<char*>(vec_data.data()), vec_data.size());

    QString hexstr;
    hexstr.append(bytes.toHex(' ').toUpper());

    QString strJson = QString::fromUtf8(jsonBytes);
    qDebug() << __LINE__ << __FUNCTION__ << "打包队列删除请求回复命令" << strJson;
    qDebug() << __LINE__ << __FUNCTION__ << "Data:" << hexstr;

    return hexstr;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//心跳包
QString HeNanCommand::PackHeartBeat()
{
    QJsonObject jsonObj, jsonObj1;

    jsonObj1.insert("status", "0");
    jsonObj.insert("HeartBeat", jsonObj1);

    QJsonDocument document;
    document.setObject(jsonObj);
    QByteArray jsonBytes = document.toJson(QJsonDocument::Compact);

    vector<uint8> vec_data = CommonPacketObj::PackBytes(CMD_TYPE1_80,CMD_HeartBeat_Req,jsonBytes.data(),jsonBytes.length());
    QByteArray bytes(reinterpret_cast<char*>(vec_data.data()), vec_data.size());

    QString hexstr;
    hexstr.append(bytes.toHex(' ').toUpper());

    QString strJson = QString::fromUtf8(jsonBytes);
    qDebug() << __LINE__ << __FUNCTION__ << "打包心跳包命令" << strJson;
    qDebug() << __LINE__ << __FUNCTION__ << "Data:" << hexstr;

    return hexstr;
}

//备卡请求
QString HeNanCommand::PrepareCardCmdToHex(QString VehType)
{
    QJsonObject jsonObj, jsonObj1;

    jsonObj1.insert("stationName", "黄村");
    jsonObj1.insert("vehPlate", "粤A 8305Z");
    jsonObj1.insert("vehPlateColor", "1");
    jsonObj1.insert("vehType", VehType); //车型 (m_vehicleType>=11&&m_vehicleType<=16)||(m_vehicleType>=21&&m_vehicleType<=26) ==> 货车
    jsonObj1.insert("vehClass", "0");
    jsonObj.insert("PrepareCard", jsonObj1);

    QJsonDocument document;
    document.setObject(jsonObj);
    QByteArray jsonBytes = document.toJson(QJsonDocument::Compact);

    vector<uint8> vec_data = CommonPacketObj::PackBytes(CMD_TYPE1_80,CMD_PrepareCard_Req,jsonBytes.data(),jsonBytes.length());
    QByteArray bytes(reinterpret_cast<char*>(vec_data.data()), vec_data.size());

    QString hexstr;
    hexstr.append(bytes.toHex(' ').toUpper());

    QString strJson = QString::fromUtf8(jsonBytes);
    qDebug() << __LINE__ << __FUNCTION__ << "打包备卡请求命令" << strJson;
    qDebug() << __LINE__ << __FUNCTION__ << "Data:" << hexstr;

    return hexstr;
}

//读卡状态(回收卡片)
QString HeNanCommand::CardRecycleCmdToHex(QString strNum)
{
    QString hexstr;

    QJsonObject jsonObj, jsonObj1;

    if(strNum.toInt()>=1 && strNum.toInt()<=4)
    {
        if(strNum.toInt() == 1)
        {
            jsonObj1.insert("channelId", "1");
        }
        else if(strNum.toInt() == 2)
        {
            jsonObj1.insert("channelId", "2");
        }
        else if(strNum.toInt() == 3)
        {
            jsonObj1.insert("channelId", "3");
        }
        else if(strNum.toInt() == 4)
        {
            jsonObj1.insert("channelId", "4");
        }
        jsonObj1.insert("status", "1");
    }
    else if(strNum.toInt()>=5 && strNum.toInt()<=8)
    {
        if(strNum.toInt() == 5)
        {
            jsonObj1.insert("channelId", "1");
        }
        else if(strNum.toInt() == 6)
        {
            jsonObj1.insert("channelId", "2");
        }
        else if(strNum.toInt() == 7)
        {
            jsonObj1.insert("channelId", "3");
        }
        else if(strNum.toInt() == 8)
        {
            jsonObj1.insert("channelId", "4");
        }
        jsonObj1.insert("status", "0");
    }
    jsonObj.insert("ReadCard", jsonObj1);

    QJsonDocument document;
    document.setObject(jsonObj);
    QByteArray jsonBytes = document.toJson(QJsonDocument::Compact);

    vector<uint8> vec_data = CommonPacketObj::PackBytes(CMD_TYPE1_80,CMD_ReadCard,jsonBytes.data(),jsonBytes.length());
    QByteArray bytes(reinterpret_cast<char*>(vec_data.data()), vec_data.size());


    hexstr.append(bytes.toHex(' ').toUpper());

    QString strJson = QString::fromUtf8(jsonBytes);
    qDebug() << __LINE__ << __FUNCTION__ << "读卡状态请求命令" << strJson;
    qDebug() << __LINE__ << __FUNCTION__ << "Data:" << hexstr;


    return hexstr;
}

//写卡完成
QString HeNanCommand::WriteCardCmdToHex(QString strNum)
{
    QJsonObject jsonObj, jsonObj1;
    //通道号1-上左 2-上右(未用) 3-下左 4-下右
    if(strNum.toInt()>=1 && strNum.toInt()<=4)
    {
        if(strNum.toInt() == 1)
        {
            jsonObj1.insert("channelId", "1");
        }
        else if(strNum.toInt() == 2)
        {
            jsonObj1.insert("channelId", "2");
        }
        else if(strNum.toInt() == 3)
        {
            jsonObj1.insert("channelId", "3");
        }
        else if(strNum.toInt() == 4)
        {
            jsonObj1.insert("channelId", "4");
        }
        jsonObj1.insert("status", "1");
    }
    else if(strNum.toInt()>=5 && strNum.toInt()<=8)
    {
        if(strNum.toInt() == 5)
        {
            jsonObj1.insert("channelId", "1");
        }
        else if(strNum.toInt() == 6)
        {
            jsonObj1.insert("channelId", "2");
        }
        else if(strNum.toInt() == 7)
        {
            jsonObj1.insert("channelId", "3");
        }
        else if(strNum.toInt() == 8)
        {
            jsonObj1.insert("channelId", "4");
        }
        jsonObj1.insert("status", "0");
    }
    jsonObj.insert("WriteCard", jsonObj1);

    QJsonDocument document;
    document.setObject(jsonObj);
    QByteArray jsonBytes = document.toJson(QJsonDocument::Compact);

    vector<uint8> vec_data = CommonPacketObj::PackBytes(CMD_TYPE1_80,CMD_WriteCard_Req,jsonBytes.data(),jsonBytes.length());
    QByteArray bytes(reinterpret_cast<char*>(vec_data.data()), vec_data.size());

    QString hexstr;
    hexstr.append(bytes.toHex(' ').toUpper());

    QString strJson = QString::fromUtf8(jsonBytes);
    qDebug() << __LINE__ << __FUNCTION__ << "打包写卡完成完成命令" << strJson;
    qDebug() << __LINE__ << __FUNCTION__ << "Data:" << hexstr;

    return hexstr;
}

//文字播音
QString HeNanCommand::TextBroadCastCmdToHex(QString text)
{
    QJsonObject jsonObj, jsonObj1;

    jsonObj1.insert("text", text);

    jsonObj.insert("TextBroadCast", jsonObj1);
    QJsonDocument document;
    document.setObject(jsonObj);
    QByteArray jsonBytes = document.toJson(QJsonDocument::Compact);

    vector<uint8> vec_data = CommonPacketObj::PackBytes(CMD_TYPE1_80,CMD_TextBroadCast,jsonBytes.data(),jsonBytes.length());
    QByteArray bytes(reinterpret_cast<char*>(vec_data.data()), vec_data.size());

    QString hexstr;
    hexstr.append(bytes.toHex(' ').toUpper());

    QString strJson = QString::fromUtf8(jsonBytes);
    qDebug() << __LINE__ << __FUNCTION__ << "打包文字播音命令" << strJson;
    qDebug() << __LINE__ << __FUNCTION__ << "Data:" << hexstr;

    return hexstr;
}

//车辆（交易）信息
QString HeNanCommand::TradeInfoCmdToHex(QString strNum)
{
    QJsonObject jsonObj, jsonObj1;

    jsonObj1.insert("vehPlate", "粤A12345_0");
    jsonObj1.insert("vehType", "1");

    if(strNum.toInt() == 1)
    {
        qDebug() << __LINE__ << __FUNCTION__ << "缴费信息";
        jsonObj1.insert("entryStation", "鲁山");
        jsonObj1.insert("payAmount", "23.6");
    }
    else if(strNum.toInt() == 2)
    {
        qDebug() << __LINE__ << __FUNCTION__ << "车辆信息";
        jsonObj1.insert("vehAxles", "4");
        jsonObj1.insert("vehWeight", "14000");
    }
    else if(strNum.toInt() == 3)
    {
        qDebug() << __LINE__ << __FUNCTION__ << "货车超限";
        jsonObj1.insert("vehAxles", "4");
        jsonObj1.insert("vehWeight", "14000");
        jsonObj1.insert("displayMode", "1");
        jsonObj1.insert("vehLimit", "49000");
        jsonObj1.insert("overLimitRate", "10.12%");
    }
    else if(strNum.toInt() == 4)
    {
        qDebug() << __LINE__ << __FUNCTION__ << "限行客车";
        jsonObj1.insert("vehAxles", "4");
        jsonObj1.insert("vehWeight", "14000");
        jsonObj1.insert("displayMode", "2");
    }
    else if(strNum.toInt() == 5)
    {
        qDebug() << __LINE__ << __FUNCTION__ << "限行危险品车";
        jsonObj1.insert("vehAxles", "4");
        jsonObj1.insert("vehWeight", "14000");
        jsonObj1.insert("displayMode", "3");
    }

    jsonObj.insert("TradeInfoReq", jsonObj1);
    QJsonDocument document;
    document.setObject(jsonObj);
    QByteArray jsonBytes = document.toJson(QJsonDocument::Compact);

    vector<uint8> vec_data = CommonPacketObj::PackBytes(CMD_TYPE1_80,CMD_TradeInfo_Req,jsonBytes.data(),jsonBytes.length());
    QByteArray bytes(reinterpret_cast<char*>(vec_data.data()), vec_data.size());

    QString hexstr;
    hexstr.append(bytes.toHex(' ').toUpper());

    QString strJson = QString::fromUtf8(jsonBytes);
    qDebug() << __LINE__ << __FUNCTION__ << "打包交易信息命令" << strJson;
    qDebug() << __LINE__ << __FUNCTION__ << "Data:" << hexstr;

    return hexstr;
}

//交易结果
QString HeNanCommand::TradeResultCmdToHex()
{
    QJsonObject jsonObj, jsonObj1;

    jsonObj1.insert("result", "1");

    jsonObj.insert("TradeResultReq", jsonObj1);
    QJsonDocument document;
    document.setObject(jsonObj);
    QByteArray jsonBytes = document.toJson(QJsonDocument::Compact);

    vector<uint8> vec_data = CommonPacketObj::PackBytes(CMD_TYPE1_80,CMD_TradeResult_Req,jsonBytes.data(),jsonBytes.length());
    QByteArray bytes(reinterpret_cast<char*>(vec_data.data()), vec_data.size());

    QString hexstr;
    hexstr.append(bytes.toHex(' ').toUpper());

    QString strJson = QString::fromUtf8(jsonBytes);
    qDebug() << __LINE__ << __FUNCTION__ << "打包交易结果命令" << strJson;
    qDebug() << __LINE__ << __FUNCTION__ << "Data:" << hexstr;

    return hexstr;
}

QString HeNanCommand::GetSerialNo()
{
    QString serialNo = QString("2F281B97E8C3D83A1C16BAA") + QDateTime::currentDateTime().toString("hhmmsszzz");
    m_serialNo = serialNo;
    return serialNo;
}

QString HeNanCommand::GetSpecialEventNo()
{
    QString specialEventNo = QString("ff9a61bf7cff431880328bd") + QDateTime::currentDateTime().toString("hhmmsszzz");
    m_specialEventNo = specialEventNo;
    return specialEventNo;
}

//特情开始
QString HeNanCommand::SpecialStartCmdToHex()
{
    QJsonObject jsonObj, jsonObj1;

    jsonObj1.insert("laneId", m_LaneHex);
    jsonObj1.insert("user", "123");
    jsonObj1.insert("specialNo", GetSpecialEventNo());

    jsonObj.insert("SpecialEventStart", jsonObj1);
    QJsonDocument document;
    document.setObject(jsonObj);
    QByteArray jsonBytes = document.toJson(QJsonDocument::Compact);

    vector<uint8> vec_data = CommonPacketObj::PackBytes(CMD_TYPE1_80,CMD_SpecialEventStart_Req,jsonBytes.data(),jsonBytes.length());
    QByteArray bytes(reinterpret_cast<char*>(vec_data.data()), vec_data.size());

    QString hexstr;
    hexstr.append(bytes.toHex(' ').toUpper());

    QString strJson = QString::fromUtf8(jsonBytes);
    qDebug() << __LINE__ << __FUNCTION__ << "打包特情开始命令" << strJson;
    qDebug() << __LINE__ << __FUNCTION__ << "Data:" << hexstr;

    return hexstr;
}

//特情结束
QString HeNanCommand::SpecialEndCmdToHex()
{
    QJsonObject jsonObj, jsonObj1;

    jsonObj1.insert("laneId", m_LaneHex);
    jsonObj1.insert("user", "123");
    jsonObj1.insert("specialNo", m_specialEventNo);

    jsonObj.insert("SpecialEventEnd", jsonObj1);
    QJsonDocument document;
    document.setObject(jsonObj);
    QByteArray jsonBytes = document.toJson(QJsonDocument::Compact);

    vector<uint8> vec_data = CommonPacketObj::PackBytes(CMD_TYPE1_80,CMD_SpecialEventEnd_Req,jsonBytes.data(),jsonBytes.length());
    QByteArray bytes(reinterpret_cast<char*>(vec_data.data()), vec_data.size());

    QString hexstr;
    hexstr.append(bytes.toHex(' ').toUpper());

    QString strJson = QString::fromUtf8(jsonBytes);
    qDebug() << __LINE__ << __FUNCTION__ << "打包特情结束命令" << strJson;
    qDebug() << __LINE__ << __FUNCTION__ << "Data:" << hexstr;

    return hexstr;
}

//获取回控数据
QString HeNanCommand::GetBackCodeCmdToHex(QString strNum)
{
    QJsonObject jsonObj, jsonObj1;

    jsonObj1.insert("laneId", m_LaneHex);
    jsonObj1.insert("serialNo", GetSerialNo());

    if(strNum.toInt() == 1)
    {
        QJsonObject jsonObj11, jsonObj12;
        jsonObj11.insert("vehType", "1");               //车型，不存在时默认填空
        jsonObj11.insert("vehAxleType", "11");          //轴型，不存在时填空
        jsonObj11.insert("vehAxles", "2");              //轴数，不存在时填空
        jsonObj11.insert("vehicleId", "豫A97L6G_0");     //车牌，不存在时默认填空

        jsonObj12.insert("vehType", "1");               //车型，不存在时默认填空
        jsonObj12.insert("vehAxleType", "11");          //轴型，不存在时填空
        jsonObj12.insert("vehAxles", "2");              //轴数，不存在时填空
        jsonObj12.insert("vehicleId", "豫A97L6G_0");     //车牌，不存在时默认填空
        jsonObj1.insert("code", strNum);
        jsonObj1.insert("entryInfo", jsonObj11);
        jsonObj1.insert("exitInfo", jsonObj12);
    }
    else if(strNum.toInt() == 2)
    {
        QJsonObject jsonObj11, jsonObj12;
        jsonObj11.insert("vehicleId", "豫A97L6B_0");     //车牌，不存在时默认填空
        jsonObj12.insert("vehicleId", "豫A97L6G_0");     //车牌，不存在时默认填空
        jsonObj1.insert("code", strNum);
        jsonObj1.insert("entryInfo", jsonObj11);
        jsonObj1.insert("exitInfo", jsonObj12);
    }
    else if(strNum.toInt() == 3)
    {
        QJsonObject jsonObj11, jsonObj12;
        jsonObj11.insert("stationHex", "");            //收费站 Hex 码，不存在时填空
        jsonObj11.insert("stationName", "");           //收费站名，不存在时填空
        jsonObj11.insert("tollLaneId", "");            //收费车道编码，国标编码，不存在时填空
        jsonObj11.insert("laneNo", "");                //收费车道号，十进制编码，不存在时填空
        jsonObj11.insert("passTime", "");              //过车时间，格式: “YYYY-MM-DDThh:mm:ss”，不存在时填空
        jsonObj11.insert("vehType", "1");              //车型，不存在时默认填空车型
        jsonObj11.insert("vehicleId", "豫A97L6G_0");    //车牌，不存在时默认填空

        jsonObj12.insert("stationHex", "41011779");                 //收费站 Hex 码，不存在时填空收费站 Hex 码
        jsonObj12.insert("stationName", "06009");                   //收费站名，不存在时填空收费站名
        jsonObj12.insert("tollLaneId", "S00884100200302010030");    //收费车道编码，国标编码，不存在时填空收费车道编码
        jsonObj12.insert("laneNo", "103");                          //收费车道号，十进制编码，不存在时填空收费车道号
        jsonObj12.insert("passTime", "2023-05-15T17:33:25");        //过车时间，格式: “YYYY-MM-DDThh:mm:ss”，不存在时填空
        jsonObj12.insert("vehType", "1");                           //车型，不存在时默认填空车型
        jsonObj12.insert( "vehicleId", "豫A97L6G_0");                 //车牌，不存在时默认填空
        jsonObj1.insert("code", strNum);
        jsonObj1.insert("entryInfo", jsonObj11);
        jsonObj1.insert("exitInfo", jsonObj12);

    }
    else if(strNum.toInt() == 4)
    {
        QJsonObject jsonObj11, jsonObj12;
        jsonObj11.insert("vehClass", "0");              //车种，不存在时默认填空
        jsonObj11.insert("vehicleId", "豫A97L6B_0");     //车牌，不存在时默认填空
        jsonObj12.insert("vehClass", "10");             //车种，不存在时默认填空
        jsonObj12.insert("vehicleId", "豫A97L6G_0");     //车牌，不存在时默认填空
        jsonObj1.insert("code", strNum);
        jsonObj1.insert("entryInfo", jsonObj11);
        jsonObj1.insert("exitInfo", jsonObj12);

    }
    else if(strNum.toInt() == 5)
    {
        QJsonObject jsonObj11, jsonObj12;
        jsonObj11.insert("vehAxleType", "11");          //轴型，不存在时填空
        jsonObj11.insert("vehAxles", "2");              //轴数，不存在时填空
        jsonObj11.insert("vehicleId", "豫A97L6G_0");     //车牌，不存在时默认填空

        jsonObj12.insert("vehAxleType", "11");          //轴型，不存在时填空
        jsonObj12.insert("vehAxles", "2");              //轴数，不存在时填空
        jsonObj12.insert("vehicleId", "豫A97L6G_0");     //车牌，不存在时默认填空
        jsonObj1.insert("code", strNum);
        jsonObj1.insert("entryInfo", jsonObj11);
        jsonObj1.insert("exitInfo", jsonObj12);
    }
    else if(strNum.toInt() == 6)
    {
        jsonObj1.insert("code", strNum);
        jsonObj1.insert("reqReason", "无车型");        // 原因
        jsonObj1.insert("vehType", "0");            // 车型
        jsonObj1.insert("weight", "48");            // 重量
        jsonObj1.insert("axleType", "157");         // 轴型
        jsonObj1.insert("axisCount", "6");          // 轴数
        jsonObj1.insert("limitWeight", "52");       // 限重
        jsonObj1.insert("specialVehClass", "25");   // 1-危化品 25-大件运输 99-未知

    }
    else if(strNum.toInt() == 7)
    {
        jsonObj1.insert("code", strNum);
        jsonObj1.insert("reqReason", "无车牌");    // 原因
        jsonObj1.insert("vehType", "1");    // 车型
        jsonObj1.insert("vehPlate", "");    //车牌
    }
    else if(strNum.toInt() == 8)
    {
        jsonObj1.insert("code", strNum);
        jsonObj1.insert("reqReason", "账号密码授权确认");  // 原因
        jsonObj1.insert("operatorNo", "2022034651");
        jsonObj1.insert("authInfo", "最小费额授权");
    }
    else if(strNum.toInt() == 9)
    {
    }
    else if(strNum.toInt() == 10)
    {
        jsonObj1.insert("code", strNum);
        jsonObj1.insert("reqReason", "无称重信息");  // 原因
        jsonObj1.insert("weight", "");
        jsonObj1.insert("axleType", "157");
        jsonObj1.insert("axisCount", "6");
        jsonObj1.insert("limitWeight", "52");
    }
    else if(strNum.toInt() == 11)
    {
        jsonObj1.insert("vehicleId", "粤A12345_0");  //车牌，不存在时默认填空
    }
    else if(strNum.toInt() == 12)
    {
        jsonObj1.insert("code", strNum);
        jsonObj1.insert("reqReason", "车牌重复");   // 原因
        jsonObj1.insert("vehPlate", "粤A12345_0");
    }
    else if(strNum.toInt() == 13)
    {
        jsonObj1.insert("code", strNum);
        jsonObj1.insert("reqReason", "拖挂车称重确认");  // 原因
        jsonObj1.insert("weight", "45");
        jsonObj1.insert("limitWeight", "52");
        jsonObj1.insert("axisCount", "6");
    }
    else if(strNum.toInt() == 14)
    {
        jsonObj1.insert("code", strNum);
        jsonObj1.insert("reqReason", "车型车轴不符");   // 原因
        jsonObj1.insert("vehType", "1");            // 车型
        jsonObj1.insert("weight", "2.3");           // 重量
        jsonObj1.insert("axleType", "11");           // 轴型
        jsonObj1.insert("axisCount", "6");          // 轴数
        jsonObj1.insert("limitWeight", "4");        // 限重
    }
    else if(strNum.toInt() == 15)
    {
        jsonObj1.insert("code", strNum);
        jsonObj1.insert("reqReason", "货车超限");       // 原因
        jsonObj1.insert("axleType", "157");           // 轴型，选项为修改重量信息时有效
        jsonObj1.insert("axisCount", "6");          // 轴数，选项为修改重量信息时有效
        jsonObj1.insert("weight", "55");            // 重量，单位：kg，选项为修改重量信息时有效
        jsonObj1.insert("limitWeight", "52");       //限重，单位：kg，选项为修改重量信息时有效
        jsonObj1.insert("license", "YQ235465");
        QJsonObject jsonObj11;
        jsonObj11.insert("itemId", "1");
        jsonObj11.insert("itemText", "劝返");
        QJsonObject jsonObj12;
        jsonObj12.insert("itemId", "2");
        jsonObj12.insert("itemText", "改轴");
        QJsonObject jsonObj13;
        jsonObj13.insert("itemId", "3");
        jsonObj13.insert("itemText", "大件运输车");
        QJsonObject jsonObj14;
        jsonObj14.insert("itemId", "4");
        jsonObj14.insert("itemText", "继续发卡");
        QJsonArray array;
        array.append(jsonObj11);
        array.append(jsonObj12);
        array.append(jsonObj13);
        array.append(jsonObj14);
        jsonObj1.insert("selectInfo",array);
    }
    else if(strNum.toInt() == 16)
    {
        jsonObj1.insert("code", strNum);
        jsonObj1.insert("reqReason", "大件运输许可证确认");  // 原因
        jsonObj1.insert("license", "YQ235465");
    }

    jsonObj.insert("GetBackCode", jsonObj1);
    QJsonDocument document;
    document.setObject(jsonObj);
    QByteArray jsonBytes = document.toJson(QJsonDocument::Compact);

    vector<uint8> vec_data = CommonPacketObj::PackBytes(CMD_TYPE1_80,CMD_GetBackCode_Req,jsonBytes.data(),jsonBytes.length());
    QByteArray bytes(reinterpret_cast<char*>(vec_data.data()), vec_data.size());

    QString hexstr;
    hexstr.append(bytes.toHex(' ').toUpper());

    QString strJson = QString::fromUtf8(jsonBytes);
    qDebug() << __LINE__ << __FUNCTION__ << "打包回控数据请求1命令" << strJson;
    qDebug() << __LINE__ << __FUNCTION__ << "Data:" << hexstr;

    return hexstr;
}

//确认信息回控请求
QString HeNanCommand::CheckMsgCtrlCmdToHex()
{
    QJsonObject jsonObj, jsonObj1;

    jsonObj1.insert("opStatus", "0");
    jsonObj1.insert("laneId", m_LaneHex);
    jsonObj1.insert("serialNo", GetSerialNo());
    jsonObj1.insert("type", "2");
    jsonObj1.insert("dlgName", "标题");
    jsonObj1.insert("dlgText", "车辆已经通过");
    jsonObj1.insert("dlgCode", "889");

    jsonObj.insert("CheckMsgCtrl", jsonObj1);
    QJsonDocument document;
    document.setObject(jsonObj);
    QByteArray jsonBytes = document.toJson(QJsonDocument::Compact);

    vector<uint8> vec_data = CommonPacketObj::PackBytes(CMD_TYPE1_80,CMD_CheckMsgCtrl_Req,jsonBytes.data(),jsonBytes.length());
    QByteArray bytes(reinterpret_cast<char*>(vec_data.data()), vec_data.size());

    QString hexstr;
    hexstr.append(bytes.toHex(' ').toUpper());

    QString strJson = QString::fromUtf8(jsonBytes);
    qDebug() << __LINE__ << __FUNCTION__ << "打包确认信息回控请求命令" << strJson;
    qDebug() << __LINE__ << __FUNCTION__ << "Data:" << hexstr;

    return hexstr;
}

//选项信息回控请求
QString HeNanCommand::SelectMsgCtrlCmdToHex()
{
    QJsonObject jsonObj, jsonObj1, jsonObj12, jsonObj13;
    QJsonArray array1, array2, array21;

    jsonObj1.insert("laneId", m_LaneHex);
    jsonObj1.insert("serialNo", GetSerialNo());
    jsonObj1.insert("dlgName", "入口超限");
    jsonObj1.insert("dlgText", "入口超限选择处理");
    jsonObj1.insert("dlgCode", "9999");

    array1.append("入口超限");
    //array1.append("232323");
    jsonObj1.insert("params", array1);

    //selectInfo
    //选项1
    jsonObj12.insert("itemId", "1");
    jsonObj12.insert("itemText", "大件运输车");
    QJsonObject jsonObj121, jsonObj122, jsonObj123, jsonObj124;
    jsonObj121.insert("expectId", "0");
    jsonObj121.insert("valueType", "string");
    jsonObj121.insert("expectValue", "vehAxles");
    jsonObj122.insert("expectId", "1");
    jsonObj122.insert("valueType", "string");
    jsonObj122.insert("expectValue", "vehAxleType");
    jsonObj123.insert("expectId", "2");
    jsonObj123.insert("valueType", "string");
    jsonObj123.insert("expectValue", "vehWeight");
    jsonObj124.insert("expectId", "3");
    jsonObj124.insert("valueType", "string");
    jsonObj124.insert("expectValue", "vehLimit");
    array21.append(jsonObj121);
    array21.append(jsonObj122);
    array21.append(jsonObj123);
    array21.append(jsonObj124);
    jsonObj12.insert("returnExpect", array21);

    //选项2
    jsonObj13.insert("itemId", "2");
    jsonObj13.insert("itemText", "劝返");

    array2.append(jsonObj12);
    array2.append(jsonObj13);

    jsonObj1.insert("selectInfo", array2);

    jsonObj.insert("SelectMsgCtrl", jsonObj1);
    QJsonDocument document;
    document.setObject(jsonObj);
    QByteArray jsonBytes = document.toJson(QJsonDocument::Compact);

    vector<uint8> vec_data = CommonPacketObj::PackBytes(CMD_TYPE1_80,CMD_SelectMsgCtrl_Req,jsonBytes.data(),jsonBytes.length());
    QByteArray bytes(reinterpret_cast<char*>(vec_data.data()), vec_data.size());

    QString hexstr;
    hexstr.append(bytes.toHex(' ').toUpper());

    QString strJson = QString::fromUtf8(jsonBytes);
    qDebug() << __LINE__ << __FUNCTION__ << "打包选项信息回控请求命令" << strJson;
    qDebug() << __LINE__ << __FUNCTION__ << "Data:" << hexstr;

    return hexstr;
}

/***************************************************************** websocketserver *****************************************************************/
QJsonObject HeNanCommand::PackagingExternJson(QString StrApiKey, QJsonObject Obj)
{
    QJsonObject jsonObj;
    jsonObj.insert("bizContent",Obj);
    jsonObj.insert("apiKey",StrApiKey);         //接口唯一标识
    jsonObj.insert("msgId",msgId);
    jsonObj.insert("time",QDateTime::currentDateTime().toString("yyyy-MM-ddThh:mm:ss"));
    jsonObj.insert("enExitType",enExitType);    //0-入口, 1-出口
    jsonObj.insert("bizType",bizType);
    jsonObj.insert("sign",sign);
    bizContentObj = QJsonObject();  //清空
    return jsonObj;
}

//车辆信息确认回复
QString HeNanCommand::PackagingCheckPlateInfo()
{
    bizContentObj.insert("specialEventNo",m_specialEventNo);
    bizContentObj.insert("laneId",m_LaneHex);
    bizContentObj.insert("vehPlate",vehPlate);
    bizContentObj.insert("vehPlateColor",1);
    bizContentObj.insert("vehClass",1);
    bizContentObj.insert("vehType",1);
    bizContentObj.insert("axisCount",2);
    bizContentObj.insert("axleType","11");
    bizContentObj.insert("weight",3.2);
    bizContentObj.insert("limitWeight",4.5);
    bizContentObj.insert("code","");
    QJsonObject jsonObj = PackagingExternJson("ENTRY_CHECK_PLATE_INFO_CONFIRM",bizContentObj);

    QJsonDocument document;
    document.setObject(jsonObj);
    QByteArray bytes = document.toJson(QJsonDocument::Compact);
    return QString::fromUtf8(bytes);
}

//称重信息确认回复
QString HeNanCommand::PackagingCheckWeightInfoConfirm()
{
    bizContentObj.insert("specialEventNo",m_specialEventNo);
    bizContentObj.insert("laneId",m_LaneHex);
    bizContentObj.insert("vehPlate",vehPlate);
    bizContentObj.insert("axisCount",2);
    bizContentObj.insert("axleType","11");
    bizContentObj.insert("weight",3.2);
    bizContentObj.insert("limitWeight",4.5);
    bizContentObj.insert("code","");
    QJsonObject jsonObj = PackagingExternJson("ENTRY_CHECK_WEIGHT_INFO_CONFIRM",bizContentObj);

    QJsonDocument document;
    document.setObject(jsonObj);
    QByteArray bytes = document.toJson(QJsonDocument::Compact);
    return QString::fromUtf8(bytes);
}

//队列确认回复
QString HeNanCommand::PackagingCheckQueueInfoConfirm()
{
    bizContentObj.insert("specialEventNo",m_specialEventNo);
    bizContentObj.insert("laneId",m_LaneHex);
    //bizContentObj.insert("optType",3);     //WebSocketMsgBox中定义
    bizContentObj.insert("userId",m_userId);
    bizContentObj.insert("isEtc",false);
    bizContentObj.insert("obuMac","F568AF203D");
    bizContentObj.insert("plateNum","粤A 8305B");
    bizContentObj.insert("plateColor",1);
    bizContentObj.insert("vehicleType","微型");
    bizContentObj.insert("capPlateNum","粤A 8305B");
    bizContentObj.insert("capPlateColor",1);
    bizContentObj.insert("capVehicleType","微型");
    bizContentObj.insert("allowPass",true);
    QJsonObject jsonObj = PackagingExternJson("ENTRY_CHECK_QUEUE_INFO_CONFIRM",bizContentObj);

    QJsonDocument document;
    document.setObject(jsonObj);
    QByteArray bytes = document.toJson(QJsonDocument::Compact);
    return QString::fromUtf8(bytes);
}

//业务授权确认回复
QString HeNanCommand::PackagingAuthorizeConfirm()
{
    bizContentObj.insert("specialEventNo",m_specialEventNo);
    bizContentObj.insert("laneId",m_LaneHex);
    bizContentObj.insert("vehPlate",vehPlate);
    //bizContentObj.insert("bussinessAuthorizType",6);
    //bizContentObj.insert("authorizeOption","确认已交易");
    QJsonObject jsonObj = PackagingExternJson("ENTRY_AUTHORIZE_CONFIRM",bizContentObj);

    QJsonDocument document;
    document.setObject(jsonObj);
    QByteArray bytes = document.toJson(QJsonDocument::Compact);
    return QString::fromUtf8(bytes);
}

//费额追缴确认回复
QString HeNanCommand::PackagingUnpaidConfirm()
{
    bizContentObj.insert("specialEventNo",m_specialEventNo);
    bizContentObj.insert("laneId",m_LaneHex);
    bizContentObj.insert("vehPlate",vehPlate);
    //bizContentObj.insert("payResult",0);
    QJsonObject jsonObj = PackagingExternJson("ENTRY_UNPAID_CONFIRM",bizContentObj);

    QJsonDocument document;
    document.setObject(jsonObj);
    QByteArray bytes = document.toJson(QJsonDocument::Compact);
    return QString::fromUtf8(bytes);
}

//账号密码授权确认回复
QString HeNanCommand::PackagingAccountPasswdAuthorizeResp()
{
    QString StrUC = "0000";
    QByteArray StrTemp = StrUC.toLocal8Bit();
    QByteArray StrPwd = StrTemp.toBase64();

    bizContentObj.insert("specialEventNo",m_specialEventNo);
    bizContentObj.insert("laneId",m_LaneHex);
    bizContentObj.insert("user",m_userId);
    bizContentObj.insert("password",QString::fromUtf8(StrPwd));
    QJsonObject jsonObj = PackagingExternJson("ENTRY_ACCOUNTPASSWD_AUTHORIZE_RESP",bizContentObj);

    QJsonDocument document;
    document.setObject(jsonObj);
    QByteArray bytes = document.toJson(QJsonDocument::Compact);
    return QString::fromUtf8(bytes);
}

//大件运输许可证确认回复
QString HeNanCommand::PackagingLargeLicense()
{
    bizContentObj.insert("specialEventNo",m_specialEventNo);
    bizContentObj.insert("laneId",m_LaneHex);
    bizContentObj.insert("license","564653654");
    QJsonObject jsonObj = PackagingExternJson("ENTRY_LARGELICENSE_RESP",bizContentObj);

    QJsonDocument document;
    document.setObject(jsonObj);
    QByteArray bytes = document.toJson(QJsonDocument::Compact);
    return QString::fromUtf8(bytes);
}

//云坐席信息确认回控回复
QString HeNanCommand::PackagingCheckMsgCtrl()
{
    bizContentObj.insert("specialEventNo",m_specialEventNo);
    bizContentObj.insert("laneId",m_LaneHex);
    //bizContentObj.insert("confirm","1");
    bizContentObj.insert("dlgName","回控测试");
    bizContentObj.insert("dlgCode","11");
    QJsonObject jsonObj = PackagingExternJson("ENTRY_CHECK_MSG_CTRL_RESP",bizContentObj);

    QJsonDocument document;
    document.setObject(jsonObj);
    QByteArray bytes = document.toJson(QJsonDocument::Compact);
    return QString::fromUtf8(bytes);
}

//选项信息回控回复
QString HeNanCommand::PackagingSelectMsgCtrlResp()
{
    QJsonObject jsonObj11,jsonObj12;
    QJsonArray array;
    bizContentObj.insert("specialEventNo",m_specialEventNo);
    bizContentObj.insert("laneId",m_LaneHex);
    //bizContentObj.insert("confirm","1");
    bizContentObj.insert("dlgName","回控测试");
    bizContentObj.insert("dlgCode","11");

    jsonObj11.insert("expectId","001");
    jsonObj11.insert("expectValue","测试001");
    jsonObj11.insert("expectData","001001");
    array.append(jsonObj11);
    jsonObj12.insert("expectId","002");
    jsonObj12.insert("expectValue","测试002");
    jsonObj12.insert("expectData","002002");
    array.append(jsonObj12);
    bizContentObj.insert("returnExpect",array);

    QJsonObject jsonObj = PackagingExternJson("ENTRY_SELECT_MSG_CTRL_RESP",bizContentObj);

    QJsonDocument document;
    document.setObject(jsonObj);
    QByteArray bytes = document.toJson(QJsonDocument::Compact);
    return QString::fromUtf8(bytes);
}

//云坐席主动发起指令
QString HeNanCommand::PackagingEntryUpCmdJSON()
{
    bizContentObj.insert("specialEventNo",m_specialEventNo);
    bizContentObj.insert("laneId",m_LaneHex);
    //bizContentObj.insert("cmdType",cmdType);
    //bizContentObj.insert("cmdDesc",cmdDesc);
    QJsonObject jsonObj = PackagingExternJson("ENTRY_UP_CMD",bizContentObj);

    QJsonDocument document;
    document.setObject(jsonObj);
    QByteArray bytes = document.toJson(QJsonDocument::Compact);
    return QString::fromUtf8(bytes);
}
