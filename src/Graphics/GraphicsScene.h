#pragma once
#include <QtWidgets\QGraphicsScene>
#include "../Gui/MpInfoToolbar.h"

class GraphicsScene : public QGraphicsScene
{
	std::shared_ptr<MpInfoToolbar> infoToolbar;

public:
	GraphicsScene(std::shared_ptr<MpInfoToolbar> info_toolbar) : QGraphicsScene(), infoToolbar(info_toolbar) {}

	void mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent) override;
};

