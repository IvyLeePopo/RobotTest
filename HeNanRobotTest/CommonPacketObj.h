#ifndef COMMONPACKETOBJ_H
#define COMMONPACKETOBJ_H

#include "CommandDef.h"
#include <QByteArray>

#define PACKAGE_VER 0   //协议版本号，当前为0x00
#define CRC_POLYNOM     0x8408
#define CRC_INIVAL      0xFFFF

class CommonPacketObj
{
public:
    CommonPacketObj();

public:
    vector<uint8> &GetObjectBytes();
    //数据处理
    static bool CheckPackage(const std::vector<uint8>& vecData);        //CRC校验判断
    static vector<uint8> CalcCRC16(vector<uint8> &crc_data, uint32 crc_dataLen);
    static vector<uint8> CRC_16(vector<uint8> &byte, uint32 len);       //CRC校验
    static uint8 XORVerifyArithmetic_SiChuan(vector<uint8>& Verify);    //异或校验
    static vector<uint8> unEscapeComProtocol(vector<uint8> &lpData, uint32 len, uint32 bSendState);   //转译，bSendState：1发送，0接收
    //编码格式转换
    static QByteArray UTF8ToGBK(string data);
    static QByteArray GBKToUTF8(string data);
    static QByteArray UTF8ToGBK(const char *msg, int len);
    static QByteArray GBKToUTF8(const char *msg, int len);
    static vector<uint8> VectorUTF8ToGBK(char *msg, int len);
    static QByteArray BytesUTF8ToGBK(char *msg, int len);
    static vector<uint8> VectorGBKToUTF8(char *msg, int len);
    static QByteArray BytesGBKToUTF8(char *msg, int len);
    //打包解包
    static vector<uint8> PackBytes(DevFunctionType1 actionType, uint8 objectType, char *msg, int len);
    static vector<vector<uint8>> UnPackBytes(vector<uint8>& vecSource);

public:
    vector<uint8> m_objectBytes;
    static uint8 m_seq;     //帧序号
};

#endif // COMMONPACKETOBJ_H
