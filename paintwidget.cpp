#include "paintwidget.h"

PaintWidget::PaintWidget(QWidget *parent):QWidget(parent)
{
    palette.setColor(QPalette::Background,backgroundColor);
    setPalette(palette);
    setAutoFillBackground(true);
    //penWidth=6;
    //spacing=10;
}

void PaintWidget::SetPaintData(QList<int> nums, QList<int> ind)
{
    numbers=nums;
    indices=ind;
}

void PaintWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    int iColor=0;
    for (int i=0;i<numbers.size();++i)
    {
        pen.setColor(lineColor);
        painter.setPen(pen);
        if (animate&&indices.contains(i))
        {
            pen.setColor(colorList[iColor]);
            painter.setPen(pen);
            ++iColor;
        }
        painter.drawLine((i-1)*penWidth,this->height(),(i-1)*penWidth,this->height()-numbers[i]);
    }
}

void PaintWidget::onNumberSizeChange(int size)
{
    penWidth = this->width()/size-spacing;
    this->update();
}

void PaintWidget::setPen(const QPen &pen)
{
    this->pen=pen;
}

void PaintWidget::setBrush(const QBrush &brush)
{
    this->brush=brush;
}
