#include "NPuzzle.h"
#include <iostream>
#include <iomanip>

static inline int Square(int n) {
	return n * n;
}

static inline int GetElement(NPuzzleArray_p array , int size, int i, int j) {
	return *(array + i * size + j);
}

static inline void CopyArray(int size ,NPuzzleArray_p dest, NPuzzleArray_p ref) {
	for (int i = 0; i < Square(size); i++) {
		dest[i] = ref[i];
	}
}

static inline int Abs(int n) {
	return n > 0 ? n : (-n);
}

bool NPuzzleStRecord::operator==(const AStarStRecord & rhs) const
{
	NPuzzleArray_p ref_array = ((NPuzzleSt_p) rhs).GetNPuzzleArray();
	for (int i = 0; i <= Square(npuzzle_size_); i++) {
		if (npuzzle_array_[i] != ref_array[i]) return false;
	}
	return true;
}

int NPuzzleStRecord::PrintState() const
{
	cout << "Current State Is:" << endl;
	cout << " " << endl;
	int i, j;
	for (i = 0; i < npuzzle_size_; i++) {
		for (j = 0; j < npuzzle_size_; j++) {
			//cout << setw(2) << *(npuzzle_array_ + i * npuzzle_size_ + j) << " " << endl;
			cout << setw(2) << GetElement(npuzzle_array_, npuzzle_size_, i, j) << " " << endl;
		}
		cout << endl;
	}
	cout << "--------------------CURRENT STATE PRINT END----------------------" << endl;
	return 0;
}

AStarSt_p NPuzzleStRecord::StateAfterAction(const Action action) const
{
	switch (action) {
	case kRight:
		if (zero_y_ == npuzzle_size_ - 1) return NULL;
		break;
	case kLeft:
		if (0 == zero_y_) return NULL;
		break;
	case kUp:
		if (0 == zero_x_) return NULL;
	case kDown:
		if (zero_x_ == npuzzle_size_ - 1) return NULL;
		break;
	case kNoAction:
		break;
	default:
		cerr << "Undefined Action!" << endl;
		return NULL;
		break;
	}
	NPuzzleArray_p next_array = new unsigned char[Square(npuzzle_size_)];
	CopyArray(npuzzle_size_, next_array, npuzzle_array_);
	switch(action) {
	case kRight:
		*(next_array + zero_x_ * npuzzle_size_ + zero_y_) = GetElement(next_array, npuzzle_size_, 
																		zero_x_, zero_y_ + 1);
		*(next_array + zero_x_ * npuzzle_size_ + zero_y_ + 1) = 0;
		break;
	case kUp:
		*(next_array + zero_x_ * npuzzle_size_ + zero_y_) = GetElement(next_array, npuzzle_size_,
			zero_x_ - 1, zero_y_);
		*(next_array + (zero_x_ - 1) * npuzzle_size_ + zero_y_) = 0;
		break;
	case kLeft:
		*(next_array + zero_x_ * npuzzle_size_ + zero_y_) = GetElement(next_array, npuzzle_size_,
			zero_x_, zero_y_ - 1);
		*(next_array + (zero_x_) * npuzzle_size_ + zero_y_ - 1) = 0;
		break;
	case kDown:
		*(next_array + zero_x_ * npuzzle_size_ + zero_y_) = GetElement(next_array, npuzzle_size_,
			zero_x_ + 1, zero_y_);
		*(next_array + (zero_x_ + 1) * npuzzle_size_ + zero_y_) = 0;
		break;
	case kNoAction:
		break;
	default:
		break;
	}
	return new NPuzzleStRecord(npuzzle_size_, next_array);
}

int NPuzzleStRecord::GetHeuristicValue() const
{
	int h_value = 0;
	int current_value;
	int x, y;
	for (x = 0; x < npuzzle_size_; x++) {
		for (y = 0; y < npuzzle_size_; y++) {
			current_value = GetElement(npuzzle_array_, npuzzle_size_, x, y);
			h_value += Abs(current_value / npuzzle_size_ - x);
			h_value += Abs(current_value % npuzzle_size_ - y);
		}
	}
	return h_value;
}

inline ptrToHashFunc NPuzzleStRecord::GetHashFunc() const {
	return Hash;
}

inline NPuzzleStRecord::NPuzzleStRecord(const int npuzzle_size, const NPuzzleArray_p npuzzle_array):
	npuzzle_size_(npuzzle_size), npuzzle_array_(npuzzle_array)
{
	for (zero_x_ = 0; zero_x_ < npuzzle_size_; zero_x_++) {
		for (zero_y_ = 0; zero_y_ < npuzzle_size_; zero_y_++) {
			if (0 == GetElement(npuzzle_array_, npuzzle_size_, zero_x_, zero_y_)) break;
		}
	}
}

NPuzzleStRecord::NPuzzleStRecord(const NPuzzleStRecord & rhs):
	npuzzle_size_(rhs.GetNPuzzleSize()), npuzzle_array_(new unsigned char [Square(npuzzle_size_)])
{
	NPuzzleArray_p ref_array = rhs.GetNPuzzleArray();
	CopyArray(npuzzle_size_, npuzzle_array_, ref_array);
	zero_x_ = rhs.GetZeroX();
	zero_y_ = rhs.GetZeroY();
}

inline NPuzzleStRecord::~NPuzzleStRecord()
{
	delete[]npuzzle_array_;
}

inline int NPuzzleStRecord::GetNPuzzleSize() const
{
	return npuzzle_size_;
}

inline NPuzzleArray_p NPuzzleStRecord::GetNPuzzleArray() const
{
	return npuzzle_array_;
}

inline int NPuzzleStRecord::GetZeroX() const
{
	return zero_x_;
}

inline int NPuzzleStRecord::GetZeroY() const
{
	return zero_y_;
}

size_t NPuzzleStRecord::Hash(AStarSt_p st)
{
	//Liner Diophantine Equations with solution within 0 ~ 15 is almost unique
	size_t hash_value = 0;
	NPuzzleArray_p array = st->GetNPuzzleArray();
	for (int i = 0; i < Square(st->GetNPuzzleSize()); i++) {
		hash_value += i * array[i];
	}
	return hash_value;
}
