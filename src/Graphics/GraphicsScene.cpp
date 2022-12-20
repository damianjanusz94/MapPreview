#include "GraphicsScene.h"
#include <QtWidgets\QGraphicsSceneMouseEvent>

void GraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
	infoToolbar->setCoordinatesLabel(QString("Coordinates: %1, %2").arg(mouseEvent->scenePos().x()).arg(mouseEvent->scenePos().y()));
}
