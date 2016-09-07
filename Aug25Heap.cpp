//Youtube video http://xoax.net/ heap and heapsort
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
	 // Put the last element at the root
	ipHeap[0] = ipHeap[iSize - 1];
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

void OutputHeap(int* ipHeap, int iSize) {
	using namespace std;

	 // Find the largest power of two, That is the depth
	int iDepth = 0;
	int iCopy = iSize;
	while (iCopy > 0) {
		iCopy >>= 1;
		++iDepth;
	}

	int iMaxWidth = (1 << iDepth);
	int iCharWidth = 4*iMaxWidth;
	int iEntry = 0;

	for (int i = 0; i < iDepth; ++i) {
		int iPowerOf2 = (1 << i);
		for (int j = 0; j < iPowerOf2; ++j) {
			int iSpacesBefore = ((iCharWidth/(1 << (i + 1))) - 1);
			 // Spaces before number
			for (int k = 0; k < iSpacesBefore; ++k) {
				cout << " ";
			}
			 // Output an extra space if the number is less than 10
			if (ipHeap[iEntry] < 10) {
				cout << " ";
			}
			 // Output the entry and the spaces after it
			cout << ipHeap[iEntry];
			++iEntry;
			if (iEntry >= iSize) {
				cout << endl;
				return;
			}
			for (int k = 0; k < iSpacesBefore; ++k) {
				cout << " ";
			}
		}
		cout << endl << endl;
	}
}

void OutputArray(int* ipArray, int iSize) {
	using namespace std;
	for (int i = 0; i < iSize; ++i) {
		cout << ipArray[i] << "  ";
	}
	cout << endl;
}

int main() {
	using namespace std;

	srand(1);
	//int iaArray[15];
	// int iaArray[] = {-2, -1, 0, 0, -1, 0, 1, 1, 2};
	int iaArray[] = {0, -1, +1, -2, 0, 0, 2, -1, 1};
	// for (int i = 0; i < 8; ++i) {
	// 	iaArray[i] = (rand() % 100);
	// }

	 // Output the heap after each element that we add
	for (int i = 0; i < 9; ++i) {
		AddElement(iaArray[i], iaArray, i);
		OutputArray(iaArray, i + 1);
		cout << endl;
		OutputHeap(iaArray, i + 1);
		cout << "---------------------------------------------" << endl;
	}
		cout << "-----------------------Done-------------------" << endl;

	 // Output the heap after each element that we remove
	for (int i = 0; i < 14; ++i) {
		RemoveRoot(iaArray, 15 - i);
		OutputArray(iaArray, 14 - i);
		cout << endl;
		OutputHeap(iaArray, 14 - i);
		cout << "---------------------------------------------" << endl;
	}

    return 0;
}

// 93  92  90  86  83  86  77  15  49  21  62  27  35  59  63  

//                                93                               

//                92                              90               

//        86              83              86              77       

//    15      49      21      62      27      35      59      63