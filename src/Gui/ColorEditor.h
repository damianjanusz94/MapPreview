#pragma once

#include <QtWidgets\QPushButton>

class ColorEditor : public QPushButton
{
    Q_OBJECT
public:
    ColorEditor(QWidget* parent = nullptr);

    void setButtonColor(const QColor& color);
    QColor getColor() { return buttonColor; }
    void mouseReleaseEvent(QMouseEvent* event) override;

signals:
    void editingFinished();

private:
    int starAtPosition(int x) const;

    QColor buttonColor;
};

