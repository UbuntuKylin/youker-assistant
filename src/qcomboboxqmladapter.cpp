#include "qcomboboxqmladapter.h"
//http://ruedigergad.com/2011/08/06/qcombobox-for-qml/
QComboBoxQmlAdapter::QComboBoxQmlAdapter(QGraphicsItem *parent) :
    QGraphicsProxyWidget(parent)
{
    m_comboBox = new CustomComboBox(0);
    m_comboBox->setEditable(true);

    QFont font = QFont(m_comboBox->font().family(), 17);
    m_comboBox->setFont(font);
    m_comboBox->setFrame(false);

#ifdef MEEGO_EDITION_HARMATTAN
    m_comboBox->setStyleSheet("QComboBox { border: 3px solid gray; border-radius: 18px; padding: 8px 20px 6px 8px; margin-top: 2px; border-color: lightgray; border-bottom-color: white; background: white; selection-background-color: rgb(70, 140, 250) }"
                              "QComboBox:focus { border-color: rgb(70, 140, 250) }"
                              "QComboBox::drop-down { subcontrol-origin: padding; subcontrol-position: top right; width: 40px; border-style: none; padding-right 10px; selection-background-color: rgb(70, 140, 250) }"
                              "QComboBox::down-arrow { image: url(/usr/share/themes/blanco/meegotouch/icons/icon-m-toolbar-down.png); }"
                              "QListView { selection-background-color: rgb(70, 140, 250); }"
                              );
#elif defined(Q_WS_MAEMO_5)
    m_comboBox->setStyleSheet("QComboBox { border: 3px solid gray; border-radius: 18px; padding: 2px 20px 2px 8px; border-color: lightgray; background: white; selection-background-color: rgb(70, 140, 250) }"
                              "QComboBox:focus { border-color: rgb(70, 140, 250) }"
                              "QComboBox::drop-down { subcontrol-origin: padding; subcontrol-position: top right; width: 40px; border-style: none; padding-right 10px; selection-background-color: rgb(70, 140, 250) }"
                              "QComboBox::down-arrow { image: url(/usr/share/themes/default/images/ComboBoxButtonNormal.png); }"
                              "QListView { selection-background-color: rgb(70, 140, 250); }"
                              );
#else
    m_comboBox->setStyleSheet("QComboBox { border: 3px solid gray; border-radius: 18px; padding: 8px 20px 8px 8px; border-color: lightgray; background: white; selection-background-color: rgb(70, 140, 250) }"
                              "QComboBox:focus { border-color: rgb(70, 140, 250) }"
                              "QComboBox::drop-down { subcontrol-origin: padding; subcontrol-position: top right; width: 40px; border-style: none; padding-right 10px; selection-background-color: rgb(70, 140, 250) }"
                              "QListView { selection-background-color: rgb(70, 140, 250); }"
                              );
#endif

    connect(m_comboBox, SIGNAL(focusIn()), this, SIGNAL(focusIn()));
    connect(m_comboBox, SIGNAL(focusOut()), this, SIGNAL(focusOut()));
    connect(m_comboBox, SIGNAL(currentIndexChanged(QString)), this, SIGNAL(textChanged(QString)));

    setWidget(m_comboBox);
}

QComboBoxQmlAdapter::~QComboBoxQmlAdapter(){
    delete m_comboBox;
}

void QComboBoxQmlAdapter::setItems(const QStringList &items){
    QString temp = m_comboBox->currentText();
    m_comboBox->clear();
    m_comboBox->addItems(items);
    m_comboBox->setEditText(temp);
}
