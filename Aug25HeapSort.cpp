// Youtube video http://xoax.net/ heap and heapsort
#include <iostream>

int Left(int iIndex) {
	return ((iIndex << 1) + 1);
}

int Right(int iIndex) {
	return ((iIndex << 1) + 2);
}

int Parent(int iIndex) {
	return ((iIndex - 1) >> 1);
}

void Swap(int& irX, int& irY) {
	int iTemp = irX;
	irX = irY;
	irY = iTemp;
}

int SwapWithChild(int iIndex, int* ipHeap, int iSize) {
	int iLeft		= Left(iIndex);
	int iRight		= Right(iIndex);
	int iLargest	= iIndex;
	if (iRight < iSize) {
		if (ipHeap[iLeft] < ipHeap[iRight]) {
			iLargest = iRight;
		} else {
			iLargest = iLeft;
		}
		if (ipHeap[iIndex] > ipHeap[iLargest]) {
			iLargest = iIndex;
		}
	} else if (iLeft < iSize) {
		if (ipHeap[iIndex] < ipHeap[iLeft]) {
			iLargest = iLeft;
		}
	}
	if (ipHeap[iIndex] < ipHeap[iLargest]) {
		Swap(ipHeap[iIndex], ipHeap[iLargest]);
	}
	return iLargest;
}

void RemoveRoot(int* ipHeap, int iSize) {
	// Swap the last element with the root
	Swap(ipHeap[0], ipHeap[iSize - 1]);
	--iSize;
	int iLasti = 0;
	int i = SwapWithChild(0, ipHeap, iSize);
	while (i != iLasti) {
		iLasti = i;
		i = SwapWithChild(i, ipHeap, iSize);
	}
}

int SwapWithParent(int i, int* ipHeap) {
	if (i < 1) {
		return i;
	}
	int iParent = Parent(i);
	if (ipHeap[i] > ipHeap[iParent]) {
		Swap(ipHeap[i], ipHeap[iParent]);
		return iParent;
	} else {
		return i;
	}
}

void AddElement(int iNewEntry, int* ipHeap, int iSize) {
	ipHeap[iSize] = iNewEntry;
	int iLasti = iSize;
	int i = SwapWithParent(iLasti, ipHeap);
	while (iLasti != i) {
		iLasti = i;
		i = SwapWithParent(i, ipHeap);
	}
}

void OutputArray(int* ipArray, int iBar, int iSize) {
	using namespace std;
	for (int i = 0; i < iSize; ++i) {
		if (i == iBar) {
			cout << "|  ";
		}
		cout << ipArray[i] << "  ";
	}
	cout << endl;
}

int main() {
	using namespace std;

	srand(1);

	int iaArray[15];
	for (int i = 0; i < 15; ++i) {
		iaArray[i] = (rand() % 100);
	}

	 // Output the heap after each element that we add
	for (int i = 0; i < 15; ++i) {
		AddElement(iaArray[i], iaArray, i);
		OutputArray(iaArray, i + 1, 15);
		cout << endl;
		cout << "---------------------------------------------" << endl;
	}
		cout << "--------------------Done---------------------" << endl;
	 // Output the heap after each element that we remove
	for (int i = 0; i < 14; ++i) {
		RemoveRoot(iaArray, 15 - i);
		OutputArray(iaArray, 14 - i, 15);
		cout << endl;
		cout << "---------------------------------------------" << endl;
	}

    return 0;
}