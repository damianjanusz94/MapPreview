#include "ColorEditor.h"

#include <QtWidgets\QColorDialog>

ColorEditor::ColorEditor(QWidget* parent) : QWidget(parent)
{
    setFocusPolicy(Qt::StrongFocus);
}

void ColorEditor::setButtonColor(const QColor& color)
{
    buttonColor = color;
}

void ColorEditor::mousePressEvent(QMouseEvent* event)
{
    QColor newColor = QColorDialog::getColor(buttonColor, this, "Pick a color");
    if (newColor.isValid())
    {
        setButtonColor(newColor);
    }
    emit editingFinished();
    QWidget::mousePressEvent(event);
}

