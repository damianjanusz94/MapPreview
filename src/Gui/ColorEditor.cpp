#include "ColorEditor.h"

#include <QtWidgets\QColorDialog>

ColorEditor::ColorEditor(QWidget* parent) : QPushButton(parent)
{
    setMouseTracking(true);
    setAutoFillBackground(true);
}

void ColorEditor::setButtonColor(const QColor& color)
{
    buttonColor = color;
}

void ColorEditor::mouseReleaseEvent(QMouseEvent* event)
{
    QColor newColor = QColorDialog::getColor(buttonColor, nullptr, "Pick a color");
    if (!newColor.isValid())
    {
        return;
    }

    emit editingFinished();
    QWidget::mouseReleaseEvent(event);
}

