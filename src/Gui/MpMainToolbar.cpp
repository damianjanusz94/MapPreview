#include "MpMainToolbar.h"

MpMainToolbar::MpMainToolbar(QWidget* parent) : QToolBar(parent)
{
    setWindowTitle("MainToolbar");
    setObjectName("Main toolbar");

    setIconSize(QSize(32, 32));

    QPushButton* button = new QPushButton("Settings", this);
    addWidget(button);
}
