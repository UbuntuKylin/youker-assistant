#include "mydialog.h"
#include "mytristatebutton.h"

#include <QLabel>
#include <QDebug>
#include <QCloseEvent>
#include <QApplication>
#include <QDesktopWidget>
#include <QScreen>
#include <QAction>
#include <QPushButton>
#include <QAbstractButton>
#include <QPainter>

MyDialog::MyDialog(const QString &title, const QString &message, QWidget *parent) :
    QDialog(parent)
   , mousePressed(false)
{
    this->setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint/*  | Qt::WindowCloseButtonHint*/);
//    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint);//Attention: Qt::WindowCloseButtonHint make showMinimized() valid

    this->setAttribute(Qt::WA_TranslucentBackground);
//    this->setAttribute(Qt::WA_DeleteOnClose, false);
    this->setAttribute(Qt::WA_Resized, false);

    m_topLayout = new QHBoxLayout;
    m_topLayout->setContentsMargins(20, 14, 20, 14);
    m_topLayout->setSpacing(20);

    m_titleLabel = new QLabel;
    m_titleLabel->setStyleSheet("QLabel{padding-top:3px;padding-bottom:3px;font-size:18px;color:#000000;}");
    m_titleLabel->hide();
    m_titleLabel->setAttribute(Qt::WA_TransparentForMouseEvents);

    m_messageLabel = new QLabel;
    m_messageLabel->setStyleSheet("QLabel{padding-top:3px;padding-bottom:3px;font-size:12px;color:#000000;}");
    m_messageLabel->hide();
    m_messageLabel->setAttribute(Qt::WA_TransparentForMouseEvents);

    QVBoxLayout *textLayout = new QVBoxLayout;
    textLayout->setContentsMargins(0, 0, 0, 0);
    textLayout->setSpacing(5);
    textLayout->addWidget(m_titleLabel, 0, Qt::AlignLeft);
    textLayout->addWidget(m_messageLabel, 0, Qt::AlignLeft);
    textLayout->addStretch();

    m_topLayout->addLayout(textLayout);

    closeButton = new MyTristateButton(this);
    closeButton->setObjectName("CloseButton");
    connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));
//    connect(closeButton, &MyTristateButton::clicked, this, [=] {
//        this->close();
//    });
    closeButton->setAttribute(Qt::WA_NoMousePropagation);

    m_buttonLayout = new QHBoxLayout;
    m_buttonLayout->setMargin(0);
    m_buttonLayout->setSpacing(0);
    m_buttonLayout->setContentsMargins(20, 14, 20, 14);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(10);

    mainLayout->addWidget(closeButton, 0, Qt::AlignTop | Qt::AlignRight);
    mainLayout->addLayout(m_topLayout);
    mainLayout->addLayout(m_buttonLayout);

    QAction *button_action = new QAction(this);
    button_action->setShortcuts(QKeySequence::InsertParagraphSeparator);
    button_action->setAutoRepeat(false);
    connect(button_action, SIGNAL(triggered(bool)), this, SLOT(onDefaultButtonTriggered()));

    this->setLayout(mainLayout);
    this->addAction(button_action);
    this->setFocusPolicy(Qt::ClickFocus);
    this->setFocus();

    setTitle(title);
    setMessage(message);

    this->moveToCenter();
}

MyDialog::~MyDialog()
{
    delete m_messageLabel;
    delete m_titleLabel;
    delete closeButton;

    QLayoutItem *child;
    while ((child = m_topLayout->takeAt(0)) != 0) {
        if (child->widget())
            child->widget()->deleteLater();
        delete child;
    }

    this->buttonList.clear();
    while ((child = m_buttonLayout->takeAt(0)) != 0) {
        if (child->widget())
            child->widget()->deleteLater();
        delete child;
    }
//    while(this->m_buttonLayout->count()) {
//        QLayoutItem *item = this->m_buttonLayout->takeAt(0);
//        item->widget()->deleteLater();
//        delete item;
//    }
}

void MyDialog::updateSize()
{
    if (!this->testAttribute(Qt::WA_Resized)) {
        QSize size = this->sizeHint();
        size.setWidth(qMax(size.width(), 234));
        size.setHeight(qMax(size.height(), 196));
        this->resize(size);
        this->setAttribute(Qt::WA_Resized, false);
    }
}

void MyDialog::onButtonClicked()
{
    QAbstractButton *button = qobject_cast<QAbstractButton*>(this->sender());
    if(button) {
        clickedButtonIndex = buttonList.indexOf(button);
        emit this->buttonClicked(clickedButtonIndex, button->text());
        this->done(clickedButtonIndex);//cancel:0   ok:1
    }
}

void MyDialog::onDefaultButtonTriggered()
{
    QAbstractButton *button = qobject_cast<QAbstractButton*>(this->focusWidget());

    if (button)
        button->click();
    else if (defaultButton)
        defaultButton->click();
}

int MyDialog::buttonCount() const
{
    return this->buttonList.count();
}

int MyDialog::addButton(const QString &text, bool isDefault)
{
    int index = buttonCount();
    QAbstractButton *button = new QPushButton(text);
    button->setFocusPolicy(Qt::NoFocus);
    button->setStyleSheet("QPushButton{font-size:12px;background-color:transparent;border:1px solid #bebebe;color:#000000;}QPushButton:hover{background-color:#ffffff;border:1px solid #3f96e4;color:#000000;}QPushButton:pressed{background-color:#ffffff;border:1px solid #3f96e4;color:#000000;}");
    button->setAttribute(Qt::WA_NoMousePropagation);
    button->setFixedSize(91, 25);

    this->m_buttonLayout->insertWidget(index+1, button);
    this->buttonList << button;
    connect(button, SIGNAL(clicked(bool)), this, SLOT(onButtonClicked()));

    if(isDefault) {
        setDefaultButton(button);
    }
    return index;
}

void MyDialog::setDefaultButton(QAbstractButton *button)
{
    this->defaultButton = button;
}

void MyDialog::setTitle(const QString &title)
{
    if (this->m_title == title)
        return;

    this->m_title = title;
    this->m_titleLabel->setText(title);
    this->m_titleLabel->setHidden(title.isEmpty());
}

void MyDialog::setMessage(const QString &message)
{
    if (this->m_message == message)
        return;
    this->m_message = message;
    this->m_messageLabel->setText(message);
    this->m_messageLabel->setHidden(message.isEmpty());
}

int MyDialog::exec()
{
    this->clickedButtonIndex = -1;
    int ret = QDialog::exec();

    return this->clickedButtonIndex >= 0 ? this->clickedButtonIndex : ret;
}

void MyDialog::showEvent(QShowEvent *event)
{
    QDialog::showEvent(event);
    setAttribute(Qt::WA_Resized, false);
    this->updateSize();
}

void MyDialog::hideEvent(QHideEvent *event)
{
    QDialog::hideEvent(event);
    done(-1);
}

void MyDialog::childEvent(QChildEvent *event)
{
    QDialog::childEvent(event);
    if (event->added()) {
        if (this->closeButton) {
            this->closeButton->raise();
        }
    }
}

QRect MyDialog::getParentGeometry() const
{
    if (this->parentWidget()) {
        return this->parentWidget()->window()->geometry();
    }
    else {
        QPoint pos = QCursor::pos();
        for (QScreen *screen : qApp->screens()) {
            if (screen->geometry().contains(pos)) {
                return screen->geometry();
            }
        }
    }
    return qApp->primaryScreen()->geometry();
}

void MyDialog::moveToCenter()
{
    QRect qr = geometry();
    qr.moveCenter(this->getParentGeometry().center());
    move(qr.topLeft());
}

void MyDialog::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        this->dragPosition = event->globalPos() - frameGeometry().topLeft();
        this->mousePressed = true;
    }
    QDialog::mousePressEvent(event);
}

void MyDialog::mouseReleaseEvent(QMouseEvent *event)
{
    this->mousePressed = false;
    QDialog::mouseReleaseEvent(event);
}

void MyDialog::mouseMoveEvent(QMouseEvent *event)
{
    if (this->mousePressed) {
        move(event->globalPos() - this->dragPosition);
    }
    QDialog::mouseMoveEvent(event);
}

void MyDialog::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    //绘制圆角矩形
    painter.setPen(QPen(QColor("#0d87ca"), 0));//边框颜色
    painter.setBrush(QColor("#e9eef0"));//背景色   #0d87ca
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setOpacity(1);
    QRectF r(0 / 2.0, 0 / 2.0, width() - 0, height() - 0);//左边 上边 右边 下边
    painter.drawRoundedRect(r, 4, 4);


    //绘制背景色
//    QPainterPath path;
//    path.addRect(QRectF(rect()));
//    painter.setOpacity(1);
//    painter.fillPath(path, QColor("#ffffff"));

    QDialog::paintEvent(event);
}

void MyDialog::resizeEvent(QResizeEvent *event)
{
    QDialog::resizeEvent(event);

    this->m_titleLabel->setWordWrap(false);
    int labelMaxWidth = maximumWidth() - this->closeButton->width() - this->m_titleLabel->x();

    if (this->m_titleLabel->sizeHint().width() > labelMaxWidth) {
        this->m_titleLabel->setFixedWidth(labelMaxWidth);
        this->m_titleLabel->setWordWrap(true);
        this->m_titleLabel->setFixedHeight(this->m_titleLabel->sizeHint().height());
    }

    this->m_messageLabel->setWordWrap(false);
    labelMaxWidth = maximumWidth() - this->closeButton->width() - this->m_messageLabel->x();

    if (this->m_messageLabel->sizeHint().width() > labelMaxWidth) {
        this->m_messageLabel->setFixedWidth(labelMaxWidth);
        this->m_messageLabel->setWordWrap(true);
        this->m_messageLabel->setFixedHeight(this->m_messageLabel->sizeHint().height());
    }
}
