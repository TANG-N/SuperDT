#include "TSplitter.h"

#include <QApplication>
#include <QLabel>
#include <QDebug>
#include <QThread>

TSplitter::TSplitter(QWidget *parent) : QWidget(parent)
{

    initVal();
    initUI();
}

void TSplitter::addWidget(QWidget *parent)
{
    //暂未实现  重载该函数实现任意widget的分屏
}

void TSplitter::initVal()
{
    m_pOldFocusWidget = nullptr;
    m_pNowFocusWidget = nullptr;
    m_pParentSplitter = nullptr;
    m_pGrandpaSplitter = nullptr;
    m_pBrotherWidget = nullptr;
    m_pUncleSplitter = nullptr;
    m_pGrandgrandfather = nullptr;
}

void TSplitter::initUI()
{
    this->setObjectName("WidgetMain");

    /*初始化一个主分割器 和 一个主文本编辑器*/
    m_pSplitterMain = new QSplitter(Qt::Vertical,this);
    m_pSplitterMain->setObjectName("m_pSplitterMain");
    m_plistSplitter.append(m_pSplitterMain);

    m_pWidgetMain = new QWidget(m_pSplitterMain);
    m_pWidgetMain->setObjectName("m_pWidgetMain");
    m_listWidget.append(m_pWidgetMain);

    m_pNowFocusWidget = m_pWidgetMain; //初始化选中的编辑器为主编辑器

    m_pHLayout = new QHBoxLayout(this);
    m_pHLayout->setContentsMargins(0,0,0,0);
    m_pHLayout->addWidget(m_pSplitterMain);
    this->setLayout(m_pHLayout);

    /*绑定 焦点部件改变 的信号  获取当前鼠标所在的Widget 保存鼠标最后选中的编辑器用于分屏等操作*/
    connect(qApp,SIGNAL(focusChanged(QWidget *,QWidget *)),this,SLOT(slotFocusChange(QWidget *,QWidget *)));
}

QSplitter *TSplitter::creatSplitter(Qt::Orientation orientation, QWidget *parent)
{
    QSplitter *splitter = new QSplitter(orientation,parent);
    splitter->setObjectName("splitter" + QString::number(m_plistSplitter.size()));
    m_plistSplitter.append(splitter);

    return splitter;
}

void TSplitter::creatWidget(QWidget *parent)
{
    QWidget *textEditor = new QWidget(parent);
    textEditor->setObjectName("textEditor" + QString::number(m_listWidget.size()));
    m_listWidget.append(textEditor);
    emit sigNewWidget(textEditor);
}

void TSplitter::removeWidget(QWidget *rmWidget)
{
    if((nullptr == rmWidget) || (0 == m_listWidget.count()))
        return ;

    /*遍历链表  删除项*/
    QWidget *tmpWidget;
    foreach(tmpWidget,m_listWidget){
        if(tmpWidget == rmWidget)
        {
            m_listWidget.removeOne(rmWidget);
            delete rmWidget;
            qDebug()<<"从链表里删除一个Editor!";
            qDebug()<<"还有：" <<m_listWidget.count()<<" 个textEditor";

            foreach(tmpWidget,m_listWidget){
                qDebug()<<"还存在的textEditor: "<< tmpWidget->objectName();
            }

            return;
        }
    }


}

void TSplitter::removeSplitter(QSplitter *rmSplitter)
{
    if((nullptr == rmSplitter) || (0 == m_plistSplitter.count()))
        return ;

    /*遍历链表  删除项*/
    QSplitter *tmpSplitter;
    foreach(tmpSplitter,m_plistSplitter){
        if(tmpSplitter == rmSplitter)
        {
            m_plistSplitter.removeOne(rmSplitter);
            delete rmSplitter;
            qDebug()<<"从链表里删除一个Splitter!";
            qDebug()<<"还有：" << m_plistSplitter.count() <<" 个Splitter";

            /*调试*/
            foreach(tmpSplitter,m_plistSplitter){
                qDebug()<<"还存在的Splitter: "<< tmpSplitter->objectName();
            }

            return;
        }
    }

}

void TSplitter::removeLastWidget()
{
    QWidget *tmpWidget;
    tmpWidget = m_listWidget.last();
    m_listWidget.removeLast(); //删除指针
    delete tmpWidget;          //释放资源
    tmpWidget = nullptr;
}

void TSplitter::removeLastSplitter()
{
    QSplitter *tmpSplitter;
    tmpSplitter = m_plistSplitter.last();
    m_plistSplitter.removeLast();
    delete tmpSplitter;
    tmpSplitter = nullptr;
}

void TSplitter::slotVSplitScreen()
{
    // Qt::Vertical   垂直
    // Qt::Horizontal 水平
    qDebug("垂直分屏");

    if(nullptr == m_pNowFocusWidget)
        return ;

    m_pParentSplitter = qobject_cast<QSplitter *>(m_pNowFocusWidget->parentWidget());
    if(nullptr == m_pParentSplitter)
        return ;

    /*m_pParentSplitter
      * 1.如果是水平分割器 设置为垂直分割器  是垂直分割器不用管
      * 2.new 两个垂直分割器(水平分割器也可以 因为无法预料下次分割是水平还是垂直)
      * 3.将 m_pNowFocusWidget(当前选中的编辑器) 移到其中一个分割器
      * 4.new 一个编辑器 到另一个分割器
      * 5.添加这两个分割器到 m_pParentSplitter(选中编辑器所在的分割器中) */

    if(Qt::Vertical != m_pParentSplitter->orientation()){
        qDebug("所在Splitter是水平分割器!");
        m_pParentSplitter->setOrientation(Qt::Vertical); //设置为垂直分割器
    }

    QSplitter *splitterFirst = creatSplitter(Qt::Vertical,m_pParentSplitter);
    QSplitter *splitterSecond = creatSplitter(Qt::Vertical,m_pParentSplitter);

    m_pNowFocusWidget->setParent(splitterFirst);

    creatWidget(splitterSecond);

    m_pParentSplitter->addWidget(splitterFirst);
    m_pParentSplitter->addWidget(splitterSecond);

    /*设置分割比例  目前无效  @bug*/
    m_pParentSplitter->setStretchFactor(0,1);
    m_pParentSplitter->setStretchFactor(1,1);
}

void TSplitter::slotHSplitScreen()
{
    qDebug("水平分屏");
    if(nullptr == m_pNowFocusWidget)
        return ;

    m_pParentSplitter = qobject_cast<QSplitter *>(m_pNowFocusWidget->parentWidget());
    if(nullptr == m_pParentSplitter)
        return ;

    /*m_pParentSplitter
     * 1.如果垂直分割器 设置为水平分割器 水平则不设置
     * 2.new 两个水平分割器(垂直分割器也可以 因为无法预料下次分割是水平还是垂直)
     * 3.将 m_pNowFocusWidget(当前选中的编辑器) 移到其中一个分割器
     * 4.new 一个编辑器 到另一个分割器
     * 5.添加这两个分割器到 m_pParentSplitter(选中编辑器所在的分割器中) */
    if(Qt::Horizontal != m_pParentSplitter->orientation()){
        qDebug("所在Splitter是垂直分割器!");
        m_pParentSplitter->setOrientation(Qt::Horizontal); //设置为 水平 分割器
    }

    QSplitter *splitterFirst = creatSplitter(Qt::Horizontal,m_pParentSplitter);
    QSplitter *splitterSecond = creatSplitter(Qt::Horizontal,m_pParentSplitter);

    m_pNowFocusWidget->setParent(splitterFirst);

    creatWidget(splitterSecond);

    m_pParentSplitter->addWidget(splitterFirst);
    m_pParentSplitter->addWidget(splitterSecond);

    /*设置分割比例  目前无效  @bug*/
    m_pParentSplitter->setStretchFactor(0,1);
    m_pParentSplitter->setStretchFactor(1,1);
}

void TSplitter::slotMergeScreen()
{
    /* 大于两个编辑器的分屏策略
     * QSplitter Grandgrandfather,*Grandpa,*uncle,*parent;
     * QWidget *brother *Me *uncleEditor;
     *    -----------------------------------------------------
     *  |                  Grandgrandfather                    |
     *  |  -----------------------------   -----------------   |
     *  | |          Grandpa            | |    Grandpa      |  |
     *  | |  -----------   -----------  | |    ---------    |  |
     *  | | |  uncle    | |   parent  | | |   |         |   |  |
     *  | | |  -------  | |  -------  | | |   | uncle   |   |  |
     *  | | | |brother| | | |   Me  | | | |   | Editor  |   |  |
     *  | | |  -------  | |  -------  | | |   |         |   |  |
     *  | | |           | |           | | |    ---------    |  |
     *  | |  -----------   -----------  | |                 |  |
     *  |  -----------------------------   -----------------   |
     *   ------------------------------------------------------
     * 大于两个编辑器删除分屏策略
     * 1.找到 叔叔对象
     * 2.把 叔叔对象 放入祖父里
     * 3.删除选中编辑器、父亲、爷爷
     */


    /* 剩余两个编辑器的分屏状态
     * QWidget *Grandgrandfather;
     * QSplitter *Grandpa,*uncle,*parent;
     * QWidget *brother *Me *uncleEditor;
     *    -----------------------------------------------------
     *  |                  Grandgrandfather                    |
     *  |  -----------------------------   -----------------   |
     *  | |          Grandpa            | |    Grandpa      |  |
     *  | |  -----------   -----------  | |    ---------    |  |
     *  | | |  uncle    | |   parent  | | |   |         |   |  |
     *  | | |  -------  | |  -------  | | |   | uncle   |   |  |
     *  | | | |brother| | | |   Me  | | | |   | Editor  |   |  |
     *  | | |  -------  | |  -------  | | |   |         |   |  |
     *  | | |           | |           | | |    ---------    |  |
     *  | |  -----------   -----------  | |                 |  |
     *  |  -----------------------------   -----------------   |
     *   ------------------------------------------------------
     * 剩余两个编辑器删除分屏策略
     * 1.找到 叔叔对象、兄弟编辑器
     * 2.把 兄弟编辑器放入爷爷里
     * 3.删除选中编辑器、父亲、爷爷
     */

    /*当前未选中窗口  或者只有一个Editor 不操作  退出*/
    if((nullptr == m_pNowFocusWidget) || (1 == m_listWidget.count()))
        return ;


    m_pParentSplitter = qobject_cast<QSplitter *>(m_pNowFocusWidget->parentWidget());   //获取父对象
    m_pGrandpaSplitter = qobject_cast<QSplitter *>(m_pParentSplitter->parentWidget());      //获取爷爷对象
    m_pGrandgrandfather = m_pGrandpaSplitter->parentWidget();                               //获取曾祖父

    if((nullptr == m_pParentSplitter) || (nullptr == m_pGrandpaSplitter) || (nullptr == m_pGrandgrandfather))
        return ;

    /*遍历爷爷对象  找到叔叔对象*/
    for(int i = 0; i < m_pGrandpaSplitter->count(); i++)
    {
        /*每个 爷爷Splitter 里只有两个子对象 */
        if(m_pParentSplitter->objectName() != m_pGrandpaSplitter->widget(i)->objectName()){
            m_pUncleSplitter = qobject_cast<QSplitter *>(m_pGrandpaSplitter->widget(i));
        }
    }

//    /*剩下两个编辑器 的删除方法*/
//    if(3 > m_listWidget.count())
//    {
//        m_pBrotherWidget = qobject_cast<QWidget *>(m_pUncleSplitter->widget(0));//叔叔分割器仅有一个兄弟编辑器
//        m_pBrotherWidget->setParent(m_pGrandpaSplitter);//将兄弟编辑器放入爷爷里

//        removeWidget(m_pNowFocusWidget);
//        removeSplitter(m_pParentSplitter);
//        removeSplitter(m_pUncleSplitter);

//        m_pNowFocusWidget = m_listWidget.last();

//        return ;
//    }
    /*选中编辑器祖父不是Splitter 是主背景Widget 的删除方法*/
    /* 1.删除自己和父亲
     */
    if(m_pSplitterMain ==  m_pGrandpaSplitter)
    {
        removeWidget(m_pNowFocusWidget);
        removeSplitter(m_pParentSplitter);

        m_pNowFocusWidget = m_listWidget.last();
        qDebug()<<"执行删除策略1";
        return ;
    }
    /*大于两个编辑器的删除方法*/
    else
    {
        QSplitter * splitterGrandFather = qobject_cast<QSplitter *>(m_pGrandgrandfather);
        if(nullptr != splitterGrandFather){
            //爷爷index是0 就把叔叔放到0 防止直接放入祖父之后引起布局变化
            if(0 == splitterGrandFather->indexOf(m_pGrandpaSplitter))
                splitterGrandFather->insertWidget(0,m_pUncleSplitter);
            else
                splitterGrandFather->insertWidget(1,m_pUncleSplitter);
        }

        removeWidget(m_pNowFocusWidget);
        removeSplitter(m_pParentSplitter);
        removeSplitter(m_pGrandpaSplitter);

        m_pNowFocusWidget = m_listWidget.last();
        m_pParentSplitter = nullptr;
        m_pGrandpaSplitter = nullptr;
        qDebug()<<"执行删除策略2";
        return ;
    }

}

void TSplitter::slotFocusChange(QWidget *old, QWidget *now)
{
    QWidget *oldWidget = qobject_cast<QWidget *>(old);
    QWidget *nowWidget = qobject_cast<QWidget *>(now);

    /*过滤事件  获取当前光标所在QWidget*/
    if((nullptr == oldWidget) && (nullptr == nowWidget))
    {
        return;
    }

    if(nullptr != nowWidget){
        m_pOldFocusWidget = m_pNowFocusWidget;
        m_pNowFocusWidget = nowWidget;

        if(nullptr != m_pOldFocusWidget){
            //m_pOldFocusWidget->appendPlainText("上次光标在这");
        }
        if(nullptr != m_pNowFocusWidget){
//            m_pNowFocusWidget->appendPlainText("现在光标在这");
            emit sigCurrentWidget(m_pNowFocusWidget);
            qDebug()<<"现在光标在这！";
        }
    }
}

