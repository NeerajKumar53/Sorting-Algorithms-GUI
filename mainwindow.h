#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "sortingthread.h"
#include "paintwidget.h"
#include <QTime>

namespace Ui
{
    class MainWindow;
}

Q_DECLARE_METATYPE(QList<int>)

class MainWindow:public QMainWindow
{
    Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent=nullptr);
        ~MainWindow();


    private:
        Ui::MainWindow *ui;
        SortingThread *sThread;
        PaintWidget paintwidget;
        QTime execTimer;
        bool isRunning = false;

    public slots:
        void onNumbersChanged(QList<int>, QList<int>);
        void onChangeAlgo(QString);
        void onSortingFinished();
        void onNumberSizeChange(int);

    private slots:
        void on_buttonStart_pressed();

        void on_buttonShuffle_pressed();

    signals:
        void StartSorting();
};
#endif // MAINWINDOW_H
