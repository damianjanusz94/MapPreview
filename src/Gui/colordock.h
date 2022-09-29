#pragma once
#include <QtWidgets\QFrame>

class ColorDock : public QFrame
{
    Q_OBJECT
public:
    explicit ColorDock(const QString& c, QWidget* parent);

    QSize sizeHint() const override { return szHint; }
    QSize minimumSizeHint() const override { return minSzHint; }

    void setCustomSizeHint(const QSize& size);

public slots:
    void changeSizeHints();

protected:
    void paintEvent(QPaintEvent*) override;

private:
    const QString color;
    QSize szHint;
    QSize minSzHint;
};