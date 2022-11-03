#pragma once

#include <QtWidgets\QWidget>

class ColorEditor : public QWidget
{
    Q_OBJECT
public:
    ColorEditor(QWidget* parent = nullptr);

    void setButtonColor(const QColor& color);
    QColor getColor() { return buttonColor; }
    void mousePressEvent(QMouseEvent* event) override;

signals:
    void editingFinished();

private:
    QColor buttonColor;
};

