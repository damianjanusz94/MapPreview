#include "MpMainToolbar.h"

MpMainToolbar::MpMainToolbar(QWidget* parent, std::shared_ptr<MessageWindow> messageWindow) : QToolBar(parent)
{
    msgWindow = messageWindow;
    setWindowTitle("MainToolbar");
    setObjectName("Main toolbar");

    settingsDialog = std::make_unique<MpSettingsDialog>(messageWindow);

    settingsBtn = new QPushButton();
    settingsBtn->setIcon(QIcon(QDir::currentPath() + "\\plugins\\MapPreview\\icons\\services-24.png"));
    settingsBtn->setFlat(true);
    settingsBtn->setToolTip("Settings");
    addWidget(settingsBtn);

    connect(settingsBtn, &QPushButton::released, this, &MpMainToolbar::settingsDialogOpen);
}

void MpMainToolbar::settingsDialogOpen()
{
    settingsDialog->show();
}