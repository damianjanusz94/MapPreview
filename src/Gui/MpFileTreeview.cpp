#include "MpFileTreeview.h"

#include <QtCore\QFile>

MpFileTreeview::MpFileTreeview(QWidget* parent) : QTreeView(parent)
{
    QFile file("C:\\Qt\\Examples\\Qt-6.3.2\\widgets\\itemviews\\simpletreemodel\\default.txt");
    file.open(QIODevice::ReadOnly);
    fileTreeModel = std::make_unique<FileTreeModel>(file.readAll(), this);
    file.close();

    setModel(fileTreeModel.get());
    setHeaderHidden(true);
}
