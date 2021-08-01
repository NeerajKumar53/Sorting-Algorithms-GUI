#ifndef SORTINGTHREAD_H
#define SORTINGTHREAD_H

#include <QObject>
#include <QThread>

const int ANIM_SPEED_STEP=100;
const int NUMBER_SIZE_DEFAULT=117;

class SortingThread:public QThread
{
    Q_OBJECT

    public:
        explicit SortingThread(QObject *parent=nullptr);
        QStringList getAlgos()
        {
            return algos;
        }
        void run() override;
        void setNumSize(int size)
        {
            this->size=size;
        }
        void setAlg(QString algoName)
        {
            algo=algoName;
        }
        void GenerateNumbers();
        int getDefaultNumberSize()
        {
            return NUMBER_SIZE_DEFAULT;
        }
        void BubbleSort(QList<int> &);
        void SelectionSort(QList<int> &);
        void InsertionSort(QList<int> &);
        void MergeSort(QList<int> &list, int, int);
        void QuickSort(QList<int> &, int, int);
        void ShellSort(QList<int> &);
    private:
        void merge(QList<int> &,int,int,int);
        int partition(QList<int> &,int,int );
        QObject *parent;
        QString algo;
        QStringList algos={"BubbleSort","SelectionSort","InsertionSort","MergeSort","QuickSort","ShellSort"};
        QList<int> numbers;
        int size=NUMBER_SIZE_DEFAULT;
        unsigned long animDelay=ANIM_SPEED_STEP;
        int numberMin=10;
        int numberMax=700;
        void swap(int a,int b,QList<int> &list);
        void shuffle();
        void updateUI(QList<int> numbers, QList<int> colorIndices);
    signals:
        void NumbersChanged(QList<int> numbers,QList<int> indices);
        void SortingFinished();
};
#endif // SORTINGTHREAD_H
