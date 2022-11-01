#include "ColorEditor.h"

#include <QtWidgets\QColorDialog>

ColorEditor::ColorEditor(QWidget* parent) : QWidget(parent)
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
    QColor newColor = QColorDialog::getColor(buttonColor, this, "Pick a color");
    if (!newColor.isValid())
    {
        return;
    }

    setButtonColor(newColor);

    emit editingFinished();
    QWidget::mouseReleaseEvent(event);
}



