#include "MessageWindow.h"

#include <QtWidgets/QScrollBar>

MessageWindow::MessageWindow()
{
	this->setReadOnly(true);
}

void MessageWindow::AddInfo(const QString& text)
{
    AddText(QColor(Qt::gray), text);
}

void MessageWindow::AddText(const QColor& color, const QString& text)
{
    QTextCharFormat tf;
    tf = this->currentCharFormat();
    tf.setTextOutline(QPen(color));
    this->setCurrentCharFormat(tf);
    this->appendPlainText(text);
    this->verticalScrollBar()->setValue(this->verticalScrollBar()->maximum());
}
