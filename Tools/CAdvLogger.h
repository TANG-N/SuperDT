#ifndef CADVLOGING_H
#define CADVLOGING_H

/* Func:实现日志的高级输出 txt db 文件名 行号等
 * Note:使用方法
 *      1.调用CAdvLogger::getInstance()->installAdvaLoging()安装高级日志器  直接使用qDebug qInfo..即可打印
 *      2.配置文件可写在 Config.xml 或 LogWinConfig.xml  配置本文件见末尾  直接创建xml文件  复制进去即可
 *
 *      !!!注意:在日志器的实现中，不能使用qDebug及qInfo...打印，会造成程序死递归
 *
 */
#include <QObject>
#include <QMutex>
#include <QMutexLocker>
#include <QApplication>

#include <QDateTime>
#include <QFile>
#include <iostream>
#include <QDomDocument>
#include <QDir>
#include <QTimer>
#include <QDate>
#include <QTextStream>

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMutex>
#include <QDomElement>
#include <QVector>
#include <QFileInfo>
#include <QStringList>

#include <QDockWidget>
#include <QTextEdit>
#include <QMainWindow>
#include <QAbstractScrollArea>
#include <QPalette>
#include <QPushButton>
#include <QStyle>
#include <QSpinBox>
#include <QStyleFactory>
#include <QDesktopWidget>

#define ONE_HOUR_MSEC (60*60*1000)


struct StLogContext{
    int m_nLevel;
    QString m_strLevel;
    QString m_strDateTime;
    QString m_strFile;
    QString m_strFunc;
    QString m_strLine;
    QString m_strMsg;
    void load(int nLevel,QString strLevel,QString strDateTime,QString strFile,
              QString strFunc,QString strLine,QString strMsg){
        m_nLevel = nLevel;
        m_strLevel = strLevel;
        m_strDateTime = strDateTime;
        m_strFile = strFile;
        m_strFunc = strFunc;
        m_strLine = strLine;
        m_strMsg = strMsg;
    }
};

void outputMsg(QtMsgType type, const QMessageLogContext &context, const QString &msg);


/*CAdvLogger****************************************************/

class CAdvLogger : public QObject
{
    Q_OBJECT
public:
    struct StLogConfig{
        bool bIsOutConsole;
        bool bIsOutTxt;
        bool bIsOutDB;
        bool bIsOutWindw;

        QString strDBType;
        QString strDBPath;
        QString strDBUser;
        QString strDBPwd;

        QString strTxtPath;

        int nPriority; //输出优先级 0~5

        int nNewLogDays; //多少天创建一个新的日志文件
        int nCheckCacheHours; //检查缓存周期
        int nMaxLogCount; //日志最大个数
    }m_config;

public:
    explicit CAdvLogger(QObject *parent = nullptr);
    static CAdvLogger* getInstance();

    void installAdvaLoging();
    void uninstallAdvaLoging();
private:
    bool stringToBool(QString strText){if("true" == strText) return true; else return false;}
    void initConfig();

public:
    StLogContext m_stLogContex;
};





/*Abs****************************************************/

class AbsOutputLog{
    virtual void outputLog(StLogContext context) = 0;
};


/*txt****************************************************/

class CLogForTxt: public QObject,public AbsOutputLog{
    Q_OBJECT
public:
    CLogForTxt(){
        init();
    }
    ~CLogForTxt(){
        m_pFileLog->close();
    }
    void outputLog(StLogContext context){
        QString strMsg = QString("[%1 %2 %3 %4 %5] %6\n")
                .arg(context.m_strLevel)
                .arg(context.m_strDateTime)
                .arg(context.m_strFile)
                .arg(context.m_strFunc)
                .arg(context.m_strLine)
                .arg(context.m_strMsg);

        m_textStream<<strMsg;
        if(m_pFileLog->isOpen()){
            m_textStream.flush();
        }
    }

    static CLogForTxt *getInstance()
    {
        static CLogForTxt* m_pInstance = nullptr;
        if(m_pInstance == nullptr){
            static QMutex mutex;
            static QMutexLocker locker(&mutex);
            if(m_pInstance == nullptr){
                m_pInstance = new CLogForTxt();
            }
        }
        return m_pInstance;
    }
private:
    void init(){
        QDir tempDir;
        if(!tempDir.exists(m_logger.m_config.strTxtPath))
        {
            std::cout<<"不存在日志文件夹 创建 "<<std::endl;
            tempDir.mkpath(m_logger.m_config.strTxtPath);
        }

        /*启动清理多余日志*/
        clearFile(m_logger.m_config.strTxtPath,m_logger.m_config.nMaxLogCount);
        /*打开新的日志*/
        openFile(m_logger.m_config.strTxtPath);

        QTimer *pHourTimer = new QTimer(this);
        pHourTimer->setInterval(ONE_HOUR_MSEC);
        pHourTimer->start();
        connect(pHourTimer,&QTimer::timeout,[=]{
            /*检查日志缓存*/
            m_nHoursCheckLog++;
            if(m_nHoursCheckLog >= m_logger.m_config.nCheckCacheHours){
                m_nHoursCheckLog = 0;

                clearFile(m_logger.m_config.strTxtPath,m_logger.m_config.nMaxLogCount);
            }
            m_nHoursNewLog++;
            if(m_nHoursNewLog/24 >= m_logger.m_config.nNewLogDays){
                m_nHoursNewLog = 0;

                openFile(m_logger.m_config.strTxtPath);
            }
        });
    }
    void openFile(QString strPath){
        QString strFile = strPath + QDateTime::currentDateTime().toString("yyyy-MM-dd") + "log.txt";
        std::cout<<QDir::currentPath().toStdString()<<"Create log txt :"<<strFile.toStdString()<<std::endl;
        /*启动初始化*/
        if(nullptr == m_pFileLog){
            m_pFileLog = new QFile;
        }else{
            if(m_pFileLog->isOpen())
                m_pFileLog->close();
        }

        m_pFileLog->setFileName(strFile);
        if(!m_pFileLog->open(QIODevice::ReadWrite|QIODevice::Append)){
            std::cout<<strFile.toStdString() <<":Log txt open failed!"<<std::endl;
            m_pFileLog = nullptr;
            return ;
        }else{
            std::cout<<"Open log file :"<<m_pFileLog->fileName().toStdString()<<" success.";
        }

        m_textStream.setDevice(m_pFileLog);
    }

    void clearFile(QString strPath,int nCount){ //第二个参数代表清理到多少个文件
        if(nCount <= 0)
            nCount =  1;

        QDir tmpDir(strPath);
        int nDirFileCount = tmpDir.entryInfoList(QDir::Files).count();
        while(nDirFileCount > nCount){
            /*获取文件列表  日期排序*/
            QStringList fileNameList = tmpDir.entryList(QDir::Files|QDir::Dirs|QDir::NoDotAndDotDot,QDir::Time);

            /*按旧日期在前  删除一个最旧的日志文件*/
            QString strFileName;
            strFileName = fileNameList.at(fileNameList.count()-1); //获取最旧的日志文件
            QFile::remove(strPath+strFileName);

            nDirFileCount = tmpDir.entryInfoList(QDir::Files).count();
        }
    }

private:
    CAdvLogger m_logger;
    int m_nHoursCheckLog = 0;
    int m_nHoursNewLog = 0;

    QFile *m_pFileLog = nullptr;
    QTextStream m_textStream;
};








/*DB****************************************************/

class CLogForDB: public QObject, public AbsOutputLog{

    Q_OBJECT


public:
    CLogForDB(){
        init();
    }
    ~CLogForDB(){
        if(m_sqlDataBase.isOpen())
            m_sqlDataBase.close();
    }
    static CLogForDB *getInstance()
    {
        static CLogForDB* m_pInstance = nullptr;
        if(m_pInstance == nullptr){
            static QMutex mutex;
            static QMutexLocker locker(&mutex);
            if(m_pInstance == nullptr){
                m_pInstance = new CLogForDB();
            }
        }
        return m_pInstance;
    }

    void outputLog(StLogContext context) override{
        QVector<QString> vec;
        QString strId = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss:z");
        vec<< strId <<context.m_strLevel<<context.m_strDateTime<<context.m_strFile<<context.m_strFunc<<context.m_strLine<<context.m_strMsg;
        addRow(vec);
    }

private:
    void init(){
        /*打开数据库*/
        m_sqlDataBase = QSqlDatabase::addDatabase(m_logger.m_config.strDBType);
        m_sqlDataBase.setDatabaseName(m_logger.m_config.strDBPath);
        if(m_sqlDataBase.open()){
            std::cout<<"INFO DB connection success! file: "<<m_logger.m_config.strDBPath.toStdString()<<std::endl;
        }else{
            std::cout<<"Error DB connection failed!!!! file: "<<m_logger.m_config.strDBPath.toStdString()<<std::endl;
        }

        openTable(m_vecColumnName); //表不存在就创建 存在就指向该表


        QTimer *pHourTimer = new QTimer(this);
        pHourTimer->setInterval(ONE_HOUR_MSEC);
        pHourTimer->start();
        connect(pHourTimer,&QTimer::timeout,[=]{
            /*检查日志缓存*/
            m_nHoursCheckLog++;
            if(m_nHoursCheckLog >= m_logger.m_config.nCheckCacheHours){
                m_nHoursCheckLog = 0;

                clearTable(m_sqlDataBase,m_logger.m_config.nMaxLogCount);
            }
            m_nHoursNewLog++;
            if(m_nHoursNewLog/24 >= m_logger.m_config.nNewLogDays){
                m_nHoursNewLog = 0;

                openTable(m_vecColumnName);
            }
        });

    }
    void openTable(QVector<QString> &vecColumnNames){
        QString strTableName = "TABLE_" + QDate::currentDate().toString("yyyy-MM-dd-hh");
        m_strCurrentTableName = strTableName;
        if(isHasTable(strTableName))
            return ; //表存在  直接返回


        if(vecColumnNames.size()<=1){
            std::cout<<"create log table column too few "<<strTableName.toStdString()<<"cloumn count size: "<<vecColumnNames.size()<<std::endl;
            return;
        }

#if 0
        //获取SQL_CREATE_TABLE语句
        QString SQL_CREATE_TABLE = "";
        for(int i = 0; i<vecColumnNames.size(); i++){

            if((i > 0) && (i < vecColumnNames.size() - 1)){
                SQL_CREATE_TABLE += vecColumnNames[i] + " TEXT   NULL," ;
            }else if(i == 0){
                SQL_CREATE_TABLE += "CREATE TABLE " + strTableName + "("+vecColumnNames[i]+" TEXT  NULL," ;
            }else if(i == vecColumnNames.size()-1){
                SQL_CREATE_TABLE += vecColumnNames[i]+" TEXT   NULL)" ;
            }

        }
#endif
        //获取SQL_CREATE_TABLE语句
        QString SQL_CREATE_TABLE = "";
        if(m_vecColumnName.size()<=1){
            //logErrorWin()<<"CTable::CTable 非法的参数,表为"<<m_strTableName<<"大小为"<<m_vecColumnNames.size()<<flushWin;
            return;
        }
        SQL_CREATE_TABLE = "CREATE TABLE " + m_strCurrentTableName +
                "("+m_vecColumnName[0]+" varchar(50)    PRIMARY KEY    NOT NULL," ;
        for(int i=1;i<m_vecColumnName.size()-1;i++){
            SQL_CREATE_TABLE += m_vecColumnName[i]+" TEXT   NULL," ;
        }
        SQL_CREATE_TABLE += m_vecColumnName[m_vecColumnName.size()-1]+" TEXT   NULL)" ;


        QSqlQuery sqlQuery;
        sqlQuery.prepare(SQL_CREATE_TABLE);
        if(!sqlQuery.exec())
            std::cout<< "Error:create table " << strTableName.toStdString() << "  failed!!  "<< SQL_CREATE_TABLE.toStdString() <<std::endl;



    }

    bool isHasTable(QString strTableName){
        bool bIsHas = false;
        QString strSql = "select count(*)  from sqlite_master where type='table' and name='" + strTableName + "';";
        QSqlQuery sqlQuery;
        sqlQuery.prepare(strSql);
        if(sqlQuery.exec()){
            if(sqlQuery.next()){
                if(sqlQuery.value(0).toBool()){
                    bIsHas = true;
                }else{
                    bIsHas = false;
                }
            }
        }

        return bIsHas;
    }

    void removeTable(QString strTableName){
        if(!isHasTable(strTableName))
            return ;                //表不存在  直接返回

        QString strSql = "drop table " + strTableName + ";";
        QSqlQuery sqlQuery;
        sqlQuery.prepare(strSql);
        sqlQuery.exec();
    }

    void addRow(QVector<QString> vecRowValue){

        if(vecRowValue.size() != m_vecColumnName.size()){
            std::cout<<"Error DB add row failed!!!  vector data different columns" << vecRowValue.size()<<m_vecColumnName.size()<<std::endl;
            return ;
        }


        QString strSqlInsert = "INSERT INTO "+m_strCurrentTableName + " (";
        for(int i = 0; i < m_vecColumnName.size(); i++){
            strSqlInsert += m_vecColumnName.at(i);
            if(i != (m_vecColumnName.size()-1))
                strSqlInsert += ",";
            else
                strSqlInsert += ") ";
        }

        strSqlInsert += " VALUES(";
        for(int i=0;i<m_vecColumnName.size();i++){
            strSqlInsert += ":" + m_vecColumnName.at(i);
            if(i < m_vecColumnName.size()-1)
                strSqlInsert += ",";
        }
        strSqlInsert += ")";

        QSqlQuery sqlQuery;
        sqlQuery.prepare(strSqlInsert);
        for(int i = 0; i < vecRowValue.size();i++){
            sqlQuery.bindValue(":" + m_vecColumnName.at(i),vecRowValue.at(i));
        }
        if(!sqlQuery.exec())
            std::cout<<"Error add row!!  Sql: " <<strSqlInsert.toStdString()<<std::endl;

    }


    void clearTable(QSqlDatabase sqlDataBase,int nCount){
        QStringList strlistTables = sqlDataBase.tables();

        while(strlistTables.size() > nCount){
            removeTable(strlistTables.takeFirst());
            strlistTables = sqlDataBase.tables();
        }
    }
private:
    CAdvLogger m_logger;
    int m_nHoursCheckLog = 0;
    int m_nHoursNewLog = 0;

    QString m_strCurrentTableName;
    QVector<QString> m_vecColumnName = {"Id","Level","Date","File","Func","Line","Msg"};
    QSqlDatabase m_sqlDataBase;
};
#define WINDOW_LOG
#ifdef WINDOW_LOG
class CLogForWindow:  public QObject, public AbsOutputLog{

    Q_OBJECT
public:
    CLogForWindow(){
        init();
    }
    ~CLogForWindow(){

    }
    static CLogForWindow *getInstance()
    {
        static CLogForWindow* m_pInstance = nullptr;
        if(m_pInstance == nullptr){
            static QMutex mutex;
            static QMutexLocker locker(&mutex);
            if(m_pInstance == nullptr){
                m_pInstance = new CLogForWindow();
            }
        }
        return m_pInstance;
    }

    void outputLog(StLogContext context) override{
        if(context.m_nLevel > m_nLevel)
            return ;

        QString strMsg = QString("[%1 %2 %3 %4 ] %5")
                .arg(context.m_strLevel)
                .arg(context.m_strFile)
                .arg(context.m_strFunc)
                .arg(context.m_strLine)
                .arg(context.m_strMsg);

        emit sigOutPut(strMsg);
    }
private:
    void init(){
        connect(this,SIGNAL(sigOutPut(QString)),this,SLOT(slotOutPut(QString)));
        QPalette palette;
        palette.setColor(QPalette::Base,QColor(10,10,10,180));//文本背景
        palette.setColor(QPalette::Text,QColor("#00ccff")); //文本色
        palette.setColor(QPalette::Window,QColor("#00ccff"));
        palette.setColor(QPalette::Background,QColor("#00ccff"));

        m_pTextEdit = new QTextEdit;
        m_pTextEdit->setPalette(palette);
        m_pTextEdit->adjustSize();
        m_pTextEdit->setStyleSheet( "QScrollBar:vertical {width:5px;background-color:rgb(13,17,47);border:none;border-radius:2px;}"\
                                    "QScrollBar::handle:vertical {background-color: rgb(74,96,160);min-height:20px;border-radius:2px;}"\
                                    "QScrollBar::add-line:vertical {height: 0px;}"\
                                    "QScrollBar::sub-line:vertical {height: 0px;}"\
                                    "QScrollBar::add-page:vertical {background: none;}"\
                                    "QScrollBar::sub-page:vertical {background: none;}");
        m_pTextEdit->hide();

        QPalette paleteTitle;
        paleteTitle.setColor(QPalette::Base,QColor(10,10,10,120));//文本背景
        paleteTitle.setColor(QPalette::Text,QColor("#ffffff")); //文本色
        //paleteTitle.setColor(QPalette::Window,QColor("#0a0a30"));
        paleteTitle.setColor(QPalette::Background,QColor(10,10,10,120));
        m_pDockWidget = new QDockWidget;
        m_pDockWidget->resize(1000,295);
        m_pDockWidget->setPalette(paleteTitle);
        m_pDockWidget->setWidget(m_pTextEdit);
        m_pDockWidget->setVisible(true);
        m_pDockWidget->setFloating(true);

        m_pDockWidget->setFeatures(QDockWidget::DockWidgetMovable |
                                   QDockWidget::DockWidgetFloatable |
                                   QDockWidget::DockWidgetVerticalTitleBar);
        m_pDockWidget->setStyleSheet("QWidget{border:1px solid #0a0a30;}"
                                     "QPushButton{background:#ffffff;color:#ffffff;}");
        m_pDockWidget->show();

//        m_pDockWidget->hide();
        QPushButton *pBtnCtrl = new QPushButton(m_pDockWidget);
        pBtnCtrl->setGeometry(30,0,30,30);
        pBtnCtrl->setCheckable(true);
        pBtnCtrl->setIcon(QApplication::style()->standardIcon(QStyle::SP_MediaPause));
        pBtnCtrl->setStyleSheet("QPushButton{background-color:rgba(255,255,255,200);border-radius:5px;}");
        connect(pBtnCtrl,&QPushButton::clicked,[=](bool bIsChecked){
            if(bIsChecked){
                pBtnCtrl->setIcon(QApplication::style()->standardIcon(QStyle::SP_MediaPause));
                m_bAbleOut = false;
            }
            else
            {
                m_bAbleOut = true;
                pBtnCtrl->setIcon(QApplication::style()->standardIcon(QStyle::SP_MediaPlay));
                m_pTextEdit->append(m_strCache);
                m_strCache.clear(); //清空缓存
            }

        });

        QPushButton *pBtnClear = new QPushButton(m_pDockWidget);
        pBtnClear->setGeometry(65,0,30,30);
        pBtnClear->setStyleSheet("QPushButton{background-color:rgba(255,255,255,200);border-radius:5px;}");
        pBtnClear->setIcon(QApplication::style()->standardIcon(QStyle::SP_DialogResetButton));
        connect(pBtnClear,&QPushButton::clicked,[=]{
            m_pTextEdit->clear();
        });
        QSpinBox *pSpinBox = new QSpinBox(m_pDockWidget);
        pSpinBox->setGeometry(100,0,40,30);
        pSpinBox->setStyleSheet("QSpinBox{background-color:rgba(255,255,255,200);border-radius:5px;}");
        pSpinBox->setRange(0,4);
        pSpinBox->setValue(CAdvLogger::getInstance()->m_config.nPriority);

//Key:  Windows
//Key:  WindowsXP
//Key:  WindowsVista
//Key:  Fusion
//        pSpinBox->setStyle(QStyleFactory::create("WindowsVista"));
//        foreach(QString key,QStyleFactory::keys()){
//            std::cout<<"Key:  "<<key.toStdString()<<std::endl;
//        }
        connect(pSpinBox,static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),[=](int i){
            m_nLevel = i;
        });


#if 0
        /*待主界面创建之后  把log 窗口附着其上*/
        m_pTimer = new QTimer(this);
        m_pTimer->setInterval(3*1000);
        m_pTimer->start();

        connect(m_pTimer,&QTimer::timeout,this,[=](){
            int nArea = 0;

            QWidget *pWidget = qApp->desktop()->screen();
            pWidget->setStyleSheet("QWidget{border:3px red solid;}");

            m_pMainWidget  = qApp->desktop()->screen();
            //找到最大widget  认为其是主窗口
//            foreach (QWidget *w, qApp->topLevelWidgets()){
//                int nTmpArea = w->width() * w->height();
//                if(nTmpArea > nArea)
//                {
//                    nArea = nTmpArea;
//                    m_pMainWidget = w;
//                }
//            }

            if(m_pDockWidget->parent() != m_pMainWidget){
                m_pDockWidget->setParent(m_pMainWidget);
                m_bAbleOut = true;
                m_pTextEdit->append(m_strCache);
                m_strCache.clear(); //清空缓存

                m_pDockWidget->show();
                std::cout<<"Stick to widget: "<< m_pMainWidget->width()  << m_pMainWidget->height() <<std::endl;
                if(!m_pMainWidget->isHidden()){
                    m_pDockWidget->show();
                    std::cout<<"Show logger window: "<<std::endl;
                    m_pTimer->stop();
                }
            }

        });

#endif

    }
signals:
    void sigOutPut(QString strMsg);
private slots:
    void slotOutPut(QString strMsg){
        if(m_bAbleOut){
            m_pTextEdit->append(strMsg);
            m_pTextEdit->moveCursor(QTextCursor::End);
        }else{
            m_strCache.append(strMsg); //窗口没起来的话  先缓存起来
        }
    }
private:
    CAdvLogger m_logger;

    QTimer *m_pTimer = nullptr;
    QDockWidget *m_pDockWidget = nullptr;
    QTextEdit *m_pTextEdit = nullptr;
    QWidget *m_pMainWidget = nullptr;
    QString m_strCache; //缓存启动时的打印信息
    bool m_bAbleOut = false;
    int m_nLevel = 4; //设置输出级别
};
#endif // CADVLOGING_H

#endif
