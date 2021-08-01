#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H

#include <QObject>
#include <QWidget>
#include <QPainter>

const QColor defaultLineColor=Qt::black;
const QColor defaultBgColor=Qt::lightGray;

class PaintWidget:public QWidget
{
    Q_OBJECT
    public:
        explicit PaintWidget(QWidget *parent=nullptr);
        void setLinecolor(QColor col)
        {
            lineColor=col;
        }
        void setAnim(bool isAnim)
        {
            animate=isAnim;
        }
        void SetPaintData(QList<int>,QList<int>);
        void setPenWidth(int w)
        {
            penWidth=w;
        }
        void resetColor()
        {
            lineColor=defaultLineColor;
        }
    protected:
        void paintEvent(QPaintEvent *event) override;
    public slots:
        void onNumberSizeChange(int size);
    private:
        QPen pen;
        QBrush brush;
        QPalette palette;
        QColor lineColor=defaultLineColor;
        QColor backgroundColor=defaultBgColor;
        QList<QColor> colorList {Qt::darkCyan,Qt::darkMagenta,Qt::darkYellow};
        bool animate;
        int penWidth;
        int spacing;
        QList<int> numbers;
        QList<int> indices;
        void setPen(const QPen &pen);
        void setBrush(const QBrush &brush);
};
#endif // PAINTWIDGET_H
