#pragma once
#include <QtWidgets\QPlainTextEdit>

class MessageWindow : public QPlainTextEdit
{
public:
    MessageWindow();

    void AddInfo(const QString& text);

private:
    void AddText(const QColor& color, const QString& text);
};

