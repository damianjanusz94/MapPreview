#include "MpInfoToolbar.h"

MpInfoToolbar::MpInfoToolbar(QWidget* parent, std::shared_ptr<MessageWindow> messageWindow) : QToolBar(parent)
{
    msgWindow = messageWindow;
    setWindowTitle("InfoToolbar");
    setObjectName("Info toolbar");

    QLabel* coordinatesLabel = new QLabel("Coordinates");
    addWidget(coordinatesLabel);
}
