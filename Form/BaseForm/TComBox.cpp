#include "TComBox.h"
#include <QApplication>

TComBox::TComBox(QWidget *parent)
    : QComboBox(parent)
{
    m_strAppPath = QApplication::applicationDirPath() + "/";
    initUI();
}

void TComBox::initUI()
{
    this->setFixedHeight(30);
    //this->setAttribute(Qt::AA_AttributeCount);
    this->setStyleSheet("QComboBox{background:#ffffff;"
                        "border-radius:5px;"
                        "pading:1px;"
                       "border: 4px solid #ffffff;"
//                        "border-radius:5px;"
//                        "border-top-left-radius:5px;"
//                        "border-top-right-radius:5px;"
//                        "border-bottom-left-radius:5px;"
//                        "border-bottom-right-radius:5px;"
                        "color:#000000;"
                        "}"
                        "QComboBox::drop-down{"
                            "background-color:transparent;"
                            "width:20px;"
                            "top:4px;"
                            "height:15px;"
                            "right:4px;"
                        "}"
                        "QComboBox::down-arrow {"
                            "image:url(" + m_strAppPath + "image/form/combox-drop.png);"
                        "}"
                        );

    this->setEditable(true);
}
