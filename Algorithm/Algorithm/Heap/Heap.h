#pragma once

#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <iostream>
#include <stdexcept>
#include <cassert>

template <typename ElementType>
class HeapNode
{
private:
	ElementType Data;

public:
	HeapNode() {}
	HeapNode(ElementType InData)
		: Data(InData) {
	}

	ElementType GetData() const { return Data; }
};

template <typename ElementType, bool bIsMaxHeap = true>
class Heap
{
private:
	HeapNode<ElementType>* pNode;
	int iCapacity;
	int iUsedSize;

protected:
	inline int GetParent(int iIndex) const { return (iIndex-1)/2; }
	inline int GetLeftChild(int iIndex) const { return 2*iIndex+1; }
	inline int GetRightChild(int iIndex) const { return 2*iIndex+2; }

	void HeapifyUp(int iIndex)
	{
		while(0 < iIndex){
			// Get Root(First) Index
			int iParentIndex = GetParent(iIndex);

			if(bIsMaxHeap==true && pNode[iIndex]->GetData()>pNode[iParentIndex]->GetData()
			||bIsMaxHeap==false && pNode[iIndex]->GetData()<pNode[iParentIndex]->GetData()){
				std::swap(pNode[iIndex], pNode[iParentIndex]);
				iIndex = iParentIndex;
			}
			else{
				break;
			}
		}
	}
	void HeapifyDown(int iIndex)
	{
		// Get Extreme(Last) Index
		int iExtremeIndex = iIndex;
		do{
			iIndex = iExtremeIndex;

			int iLeftChildIndex = GetLeftChild(iIndex);
			if(iLeftChildIndex<iUsedSize &&
			(bIsMaxHeap==true && pNode[iLeftChildIndex]->GetData()>pNode[iExtremeIndex]->GetData()||
			bIsMaxHeap==false && pNode[iLeftChildIndex]->GetData()<pNode[iExtremeIndex]->GetData()))
				iExtremeIndex = iLeftChildIndex;

			int iRightChildIndex = GetRightChild(iIndex);
			if(iRightChildIndex<iUsedSize &&
			(bIsMaxHeap==true && pNode[iRightChildIndex]->GetData()>pNode[iExtremeIndex]->GetData()||
			bIsMaxHeap==false && pNode[iRightChildIndex]->GetData()<pNode[iExtremeIndex]->GetData()))
				iExtremeIndex = iRightChildIndex;

			if(iExtremeIndex != iIndex)
				std::swap(pNode[iIndex], pNode[iExtremeIndex]);

		}while(iIndex != iExtremeIndex);
	}

public:
	Heap(int iInCapacity) : iCapacity(iInCapacity), iUsedSize(0){
		pNode = new HeapNode<ElementType>[iInCapacity];
	}
	~Heap(){
		iCapacity = 0;
		iUsedSize = 0;
		delete[] pNode;
	}

	void Insert(ElementType InElement)
	{
		assert(iUsedSize<iCapacity && "Heap Capacity Exceeded.");

		pNode[iUsedSize] = HeapNode<ElementType>(InElement);
		HeapifyUp(iUsedSize++);
	}
	ElementType Extract()
	{
		assert(iUsedSize>0 && "Heap is Empty.");

		ElementType Root = pNode[0]->GetData();

		pNode[0] = pNode[--iUsedSize];
		HeapifyDown(0);

		return Root;
	}

	bool IsEmpty() const { return iUsedSize==0; }
	int GetUsedSize() const { return iUsedSize; }
	int GetCapacity() const { return iCapacity; }
};