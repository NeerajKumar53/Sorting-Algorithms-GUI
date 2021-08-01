#include "sortingthread.h"
#include <QRandomGenerator>

SortingThread::SortingThread(QObject *parent):QThread(parent){}

void SortingThread::run()
{
    shuffle();

    if (algo=="BubbleSort")
    {
        BubbleSort(numbers);
    }
    if (algo=="SelectionSort")
    {
        SelectionSort(numbers);
    }

    if (algo=="InsertionSort")
    {
        InsertionSort(numbers);
    }

    if (algo=="MergeSort")
    {
        MergeSort(numbers,0,numbers.size()-1);
    }

    if (algo=="QuickSort")
    {
        QuickSort(numbers,0,numbers.size()-1);
    }

    if (algo=="ShellSort")
    {
        ShellSort(numbers);
    }

    emit SortingFinished();
}

//********** BUBBLE SORT **********
void SortingThread::BubbleSort(QList<int> &)
{
    const int N=numbers.size();
    int i,j;
    for (i=0;i<N-1;i++)
    {
        for (j=0;j<N-i-1;j++)
        {
            if (numbers[j]>numbers[j + 1])
            {
                swap(j,j+1,numbers);
            }
            updateUI(numbers,{j+1});
        }
    }
}

//********** SELECTION SORT **********
void SortingThread::SelectionSort(QList<int> &)
{
    const int N=numbers.size();
    for (int i=0;i<N-1;++i)
    {
        int j=0;
        int indexMin=i;
        for (j=i+1;j<N;++j)
        {
            if (numbers[j]<numbers[indexMin])
            {
                indexMin=j;
            }
            updateUI(numbers,{j, i});
        }
        swap(indexMin,i,numbers);
    }
}

//********** INSERTION SORT **********
void SortingThread::InsertionSort(QList<int> &)
{
   int i,j,num;
   for (i=0;i<numbers.size();i++)
   {
       num=numbers[i];
       j=i-1;

       while (j>=0&&numbers[j]>num)
       {
           numbers[j+1]=numbers[j];
           --j;

           updateUI(numbers,{j+1});
       }
       numbers[j+1]=num;
   }
}

//********** MERGE SORT **********
void SortingThread::MergeSort(QList<int> &list,int iLeft,int iRight)
{
    if (iLeft<iRight)
    {
        int Middle=iLeft+(iRight-iLeft)/2;

        MergeSort(list,iLeft,Middle);
        MergeSort(list,Middle+1,iRight);

        merge(list,iLeft,Middle,iRight);
    }
}
void SortingThread::merge(QList<int> &list,int Left,int Middle,int Right)
{
    QList<int> listLeft;
    QList<int> listRight;

    int i,j=0;
    int sizeLeft=Middle-Left + 1;
    int sizeRight=Right-Middle;

    for (i=0;i<sizeLeft;++i)
    {
        listLeft.append(list[Left+i]);
    }
    for ( j = 0; j < sizeRight; ++j)
    {
        listRight.append(list[Middle+1+j]);
    }
    i=j=0;
    int k=Left;
    while (i<sizeLeft&&j<sizeRight)
    {
        if (listLeft[i]<=listRight[j])
        {
            list[k]=listLeft[i];
            i++;
            updateUI(numbers,{k,sizeLeft+k});
        }
        else
        {
            list[k]=listRight[j];
            j++;
            updateUI(numbers,{k,sizeRight+k});
        }
        k++;
    }
    while (i<sizeLeft)
    {
        list[k]=listLeft[i];
        i++;
        k++;
    }
    while (j<sizeRight)
    {
        list[k]=listRight[j];
        j++;
        k++;
    }
}

//********** QUICK SORT **********
void SortingThread::QuickSort(QList<int> &list,int start,int end)
{
   if (start<end)
    {
        int pi=partition(list,start,end);

        QuickSort(list,start,pi-1);
        QuickSort(list,pi+1,end);
    }

}
int SortingThread::partition(QList<int> &list,int start,int end)
{
    int pivot=list[end];
    int i=start-1;

    for (int j=start;j<=end-1;j++)
    {
        if (list[j]<=pivot)
        {
            ++i;
            swap(i,j,list);
            updateUI(numbers,{pivot,i,j});
        }
    }
    swap(i+1,end,list);
    updateUI(numbers,{pivot,i+1,end});
    return (i+1);
}

//********** SHELL SORT **********
void SortingThread::ShellSort(QList<int> &list)
{
    const int N=list.size();
    int out,in;
    for (int gap=N/2;gap>0;gap/=2)
    {
        for (out=gap;out<N;++out)
        {
            int temp=list[out];
            for (in=out;in>=gap&&list[in-gap]>temp; in=in-gap)
            {
                list[in]=list[in-gap];
                updateUI(numbers,{in,in-gap});
            }
            list[in]=temp;
            updateUI(numbers,{in,temp});
        }
    }
}

void SortingThread::swap(int a,int b,QList<int> &list)
{
    int tmp=list[a];
    list[a]=list[b];
    list[b]=tmp;
}

void SortingThread::updateUI(QList<int> numbers,QList<int> colorIndices)
{
    emit NumbersChanged(numbers,colorIndices);
    this->usleep(animDelay);
}

void SortingThread::GenerateNumbers()
{
    numbers.clear();
    numbers.reserve(size);
    int itemStep = (numberMax+1-numberMin)/size;
    numbers.append(itemStep);
    for (int i=1;i<size;++i)
    {
        numbers.append((i+1)*itemStep);
    }
    shuffle();
    emit NumbersChanged(numbers,{0});
}

void SortingThread::shuffle()
{
    for (int i=0;i<numbers.size();++i)
    {
        int rand=QRandomGenerator::global()->bounded(0,numbers.size());
        swap(i,rand,numbers);
    }
}
