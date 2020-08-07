#include "CAdvLogger.h"
#include <QThread>

CAdvLogger::CAdvLogger(QObject *parent) : QObject(parent)
{
    initConfig(); //初始化日志配置
}

CAdvLogger *CAdvLogger::getInstance()
{
    static CAdvLogger* pInstance = nullptr;
    if(nullptr == pInstance){
        static QMutex mutex;
        static QMutexLocker locker(&mutex);
        pInstance = new CAdvLogger();
    }
    return pInstance;
}

void outputMsg(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{


    //enum QtMsgType { QtDebugMsg, QtWarningMsg, QtCriticalMsg, QtFatalMsg, QtInfoMsg, QtSystemMsg = QtCriticalMsg };
    int nPriority = CAdvLogger::getInstance()->m_config.nPriority;
    int arr[] = {4,2,1,0,3};
    if(nPriority < arr[type]) //优先级判断 因为QtMsgType 枚举中Info级别高于Fatal 重新设置为以下顺序 QtDebugMsg,QtInfoMsg, QtWarningMsg, QtCriticalMsg, QtFatalMsg
        return ;

    QStringList strListStyle = {"\033[37m","\033[33m","\033[36m","\033[34m","\033[32m"};// 默认 绿 黄 白 红
    QStringList strListLevel = {"DEBUG","WARRING","CRITI","FATAL","INFO"};


    QString strLevel = strListLevel.at(type);
    QString strDateTime = QDateTime::currentDateTime().toString(" hh:mm:ss A");

    QString strPath =  QString(context.file);
    int nPos = strPath.lastIndexOf('\\');
    strPath = strPath.mid(nPos + 1,strPath.size() - nPos + 2);

    QString strFunc = QString(context.function);
    strFunc = strFunc.left( strFunc.indexOf('('));

    QString strLine = QString::number(context.line);

    static QMutex mutex;
    mutex.lock();
    CAdvLogger::getInstance()->m_stLogContex.load(arr[type],strLevel,strDateTime,strPath,strFunc,strLine,msg);
    mutex.unlock();

    /*控制台输出*/
    if(CAdvLogger::getInstance()->m_config.bIsOutConsole){
        mutex.lock();

        //QString strMsg = "[" + strListStyle.at(type) + strLevel + strFunc + strLine + msg + "] " + "\n\033[0m"; //重设控制属性到缺省
        QString strMsg = QString("[%1 %2 %3 %4] %5\n\033[0m").arg(strListStyle.at(type)).arg(strLevel).arg(strFunc).arg(strLine).arg(msg);
        fprintf(stdout,"%s",strMsg.toLocal8Bit().constData());
        fflush(stdout);
        mutex.unlock();
    }
    /*文本输出*/
    if(CAdvLogger::getInstance()->m_config.bIsOutTxt){
        mutex.lock();
        CLogForTxt::getInstance()->outputLog(CAdvLogger::getInstance()->m_stLogContex);
        mutex.unlock();
    }

    /*数据库输出*/
    if(CAdvLogger::getInstance()->m_config.bIsOutDB){
        mutex.lock();
        CLogForDB::getInstance()->outputLog(CAdvLogger::getInstance()->m_stLogContex);
        mutex.unlock();
    }

    /*界面输出*/
    if(CAdvLogger::getInstance()->m_config.bIsOutWindw){
        mutex.lock();
        CLogForWindow::getInstance()->outputLog(CAdvLogger::getInstance()->m_stLogContex);
        mutex.unlock();
    }
}

void CAdvLogger::installAdvaLoging()
{
    qInstallMessageHandler(outputMsg);
}

void CAdvLogger::uninstallAdvaLoging()
{
    qInstallMessageHandler(0);
}

void CAdvLogger::initConfig()
{
    /*默认日志设置*/
    m_config.bIsOutConsole = true;
    m_config.bIsOutDB = false;
    m_config.bIsOutTxt = false;
    m_config.bIsOutWindw = false;
    m_config.strDBType = "QSQLITE";
    m_config.strDBPath = "./Log/log.db";
    m_config.strDBPwd = "123456";
    m_config.strDBUser = "admin";
    m_config.strTxtPath = "./Log/";
    m_config.nPriority = 4; //优先级  0~4
    m_config.nNewLogDays = 1; //新日志
    m_config.nMaxLogCount = 10; //最多个数
    m_config.nCheckCacheHours = 1; //小时检查一次日志个数

    /*查找配置文件*/
    QString strLogConfigFile = QApplication::applicationDirPath()+"/LogConfig.xml";
    QString strConfigFile = QApplication::applicationDirPath()+"/Config.xml";
    QFile file(strLogConfigFile);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        std::cout<<"CAdvLogger::No find "<<strLogConfigFile.toStdString()<<",find Config.xml ,try to open it."<< std::endl;

        file.setFileName(strConfigFile);
        if(!file.open(QFile::ReadOnly | QFile::Text)){
            std::cout<<"CAdvLogger::No find Config.xml. "<<strConfigFile.toStdString()<<",Use default config setting!"<< std::endl;
            return;
        }else{
            std::cout<<"CAdvLogger::Open file Config.xml success! "<< std::endl;
        }

    }else{
        std::cout<<"CAdvLogger::Find "<<strLogConfigFile.toStdString()<<" ,start parse config!"<< std::endl;
    }

    /*读出文件*/
    QString errorStr;
    int errorLine;
    int errorColumn;
    QDomDocument doc;
    if (!doc.setContent(&file, false, &errorStr, &errorLine, &errorColumn))
        return ;
    QDomElement root = doc.documentElement();
    if(root.tagName() != "Config")
        return;
    file.close();


    /*解析标签*/
    QDomElement node = root.firstChildElement();
    while (!node.isNull())
    {
        QDomElement element = node.toElement();
        if (!element.isNull())
        {
            if(element.tagName() == "AbleOutDB"){
               m_config.bIsOutDB = stringToBool(element.text());
            }else if(element.tagName() == "AbleOutWindow"){
               m_config.bIsOutWindw = stringToBool(element.text());
            }else if(element.tagName() == "AbleOutConsole"){
               m_config.bIsOutConsole = stringToBool(element.text());
            }else if(element.tagName() == "AbleOutTxt"){
               m_config.bIsOutTxt = stringToBool(element.text());
            }else if(element.tagName() == "LogDatabaseType"){
               m_config.strDBType = element.text();
            }else if(element.tagName() == "LogDatabasePath"){
                m_config.strDBPath = element.text();
            }else if(element.tagName() == "LogDatabaseUser"){
                m_config.strDBUser = element.text();
            }else if(element.tagName() == "LogDatabasePwd"){
               m_config.strDBPwd = element.text();
            }else if(element.tagName() == "TxtDirPath"){
                m_config.strTxtPath = (element.text());
            }else if(element.tagName() == "OutPriority"){
                m_config.nPriority = element.text().toInt();
            }else if(element.tagName() == "NewLogDays"){
                m_config.nNewLogDays = element.text().toInt();
            }else if(element.tagName() == "CheckCacheHours"){
                m_config.nCheckCacheHours = element.text().toInt();
            }else if(element.tagName() == "MaxLogCount"){
                m_config.nMaxLogCount = element.text().toInt();
            }
            node = node.nextSiblingElement();
        }
    }

    std::cout<<"Log config load completed, The configuration below.................................."<<std::endl;
    std::cout<<"DB Out: "<<m_config.bIsOutDB<<" Window Out: "<<m_config.bIsOutWindw <<" Console Out: "<<m_config.bIsOutConsole<<
               " Txt Out: "<<m_config.bIsOutTxt<<std::endl;
    std::cout<<"DB Type: "<<m_config.strDBType.toStdString()<<" DB Path: "<<m_config.strDBPath.toStdString()<<
               m_config.strDBUser.toStdString()<<m_config.strDBPwd.toStdString()<<" Txt log path: "<<
               m_config.strTxtPath.toStdString()<<std::endl;
    std::cout<<"Priority: "<<m_config.nPriority<<" NewLogDays: "<<m_config.nNewLogDays<<" CheckCacheHours: "<<
               m_config.nCheckCacheHours<<" MaxLogCount: "<<m_config.nMaxLogCount<<std::endl;
    std::cout<<"Log config print end................................................................"<<std::endl;
}

//日志配置文件书写方式  保存到Config.xml  或 LogConfig.xml 没有配置文件  默认配置
#if 0
<?xml version='1.0' encoding='UTF-8'?>
<Config>
    <!--日志配置-->
    <!--输出方式-->
    <AbleOutDB>false</AbleOutDB>
    <AbleOutWindow>false</AbleOutWindow>
    <AbleOutConsole>true</AbleOutConsole>
    <AbleOutTxt>false</AbleOutTxt>

    <!--数据库路径配置-->
    <LogDatabaseType>sqlite</LogDatabaseType><!--sqlite或mysql-->
    <LogDatabasePath>C:/DB/LogWin.db</LogDatabasePath>
    <LogDatabaseUser>admin</LogDatabaseUser>
    <LogDatabasePwd>111111</LogDatabasePwd>
    <!--日志路径配置 只写路径 如 ./Log/ -->
    <TxtDirPath>./Log/</TxtDirPath>

    <!--输出优先级 (0~4) 4代表输出所有级别-->
    <OutPriority>4</OutPriority>

    <!--产生新的日志文件的周期-->
    <NewLogDays>1</NewLogDays> <!--单位是天-->

    <!--检查缓存周期-->
    <CheckCacheHours>12</CheckCacheHours>

    <!--保留日志个数-->
    <MaxLogCount>10</MaxLogCount>

</Config>

#endif
