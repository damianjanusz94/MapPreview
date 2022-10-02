#include "MpInfoToolbar.h"

MpInfoToolbar::MpInfoToolbar(QWidget* parent) : QToolBar(parent)
{
    setWindowTitle("InfoToolbar");
    setObjectName("Info toolbar");

    QLabel* coordinatesLabel = new QLabel("Coordinates");
    addWidget(coordinatesLabel);
}
