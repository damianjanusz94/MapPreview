#include "ColorDelegate.h"

#include <QtWidgets\QWidget>
#include <QtGui\QPainter>

#include "../Gui/ColorEditor.h"

constexpr int PaintingScaleFactor = 20;

void ColorDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    if (index.data().canConvert<QString>() && index.data().toString() == "")
    {
        QStyledItemDelegate::paint(painter, option, index);
        return;
    }

    if (index.column() == 1 && index.data().canConvert<QColor>())
    {
        auto starRating = qvariant_cast<QColor>(index.data());
        
        painter->save();
        
        painter->setRenderHint(QPainter::Antialiasing, true);
        painter->setPen(Qt::NoPen);
        painter->setBrush(starRating);
        
        const int yOffset = (option.rect.height() - PaintingScaleFactor) / 2;
        painter->translate(option.rect.x(), option.rect.y() + yOffset);
        painter->scale(PaintingScaleFactor, PaintingScaleFactor);
        painter->drawRect(colorRect);
        painter->translate(1.0, 0.0);
        painter->restore();
        return;
    }
 
    QStyledItemDelegate::paint(painter, option, index);
}

QWidget* ColorDelegate::createEditor(QWidget* parent,
    const QStyleOptionViewItem& option,
    const QModelIndex& index) const

{
    if (index.data().canConvert<QColor>() && index.column() == 1)
    {
        ColorEditor* editor = new ColorEditor(parent);
        connect(editor, &ColorEditor::editingFinished, this, &ColorDelegate::commitAndCloseEditor);
        return editor;
    }
    return QStyledItemDelegate::createEditor(parent, option, index);
}

void ColorDelegate::setEditorData(QWidget* editor, const QModelIndex& index) const
{
    if (index.data().canConvert<QColor>())
    {
        auto color = qvariant_cast<QColor>(index.data());
        ColorEditor* colorEditor = qobject_cast<ColorEditor*>(editor);
        colorEditor->setButtonColor(color);
    }
    else 
    {
        QStyledItemDelegate::setEditorData(editor, index);
    }
}

void ColorDelegate::setModelData(QWidget* editor, QAbstractItemModel* model,
    const QModelIndex& index) const
{
    if (index.data().canConvert<QColor>()) 
    {
        ColorEditor* colorEditor = qobject_cast<ColorEditor*>(editor);
        model->setData(index, QVariant::fromValue(colorEditor->getColor()), -10);
    }
    else 
    {
        QStyledItemDelegate::setModelData(editor, model, index);
    }
}

void ColorDelegate::commitAndCloseEditor()
{
    ColorEditor* editor = qobject_cast<ColorEditor*>(sender());

    emit commitData(qobject_cast<QWidget*>(editor));
    emit closeEditor(qobject_cast<QWidget*>(editor));
}