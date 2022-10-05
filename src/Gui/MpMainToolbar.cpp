#include "MpMainToolbar.h"

MpMainToolbar::MpMainToolbar(QWidget* parent) : QToolBar(parent)
{
    setWindowTitle("MainToolbar");
    setObjectName("Main toolbar");

    settingsDialog = std::make_unique<MpSettingsDialog>();

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