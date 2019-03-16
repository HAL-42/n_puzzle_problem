#pragma once
#include "aStar_everything.h"

const Action kRight = 0;
const Action kUp = 1;
const Action kLeft = 2;
const Action kDown = 3;
const Action kNoAction = 4;

using ptrToNPuzzleStRecord = NPuzzleStRecord;
using NPuzzleSt_p = ptrToNPuzzleStRecord;
using NPuzzleArray_p = unsigned char*;

class NPuzzleStRecord : public AStarStRecord {
	// Inherit from AStarStRecord
public:
	bool operator==(const AStarStRecord & rhs) const override;
	int PrintState() const override;
	AStarSt_p StateAfterAction(const Action action) const override;
	int GetHeuristicValue() const override;
	ptrToHashFunc GetHashFunc() const;

	NPuzzleStRecord(const int npuzzle_size, const NPuzzleArray_p npuzzle_array);
	NPuzzleStRecord(const NPuzzleStRecord& rhs);
	NPuzzleStRecord& operator = (const NPuzzleStRecord& rhs) = delete;		//Disable operator =
	~NPuzzleStRecord();
	int GetNPuzzleSize() const;
	NPuzzleArray_p GetNPuzzleArray() const;
	int GetZeroX() const;
	int GetZeroY() const;

private:
	const NPuzzleArray_p npuzzle_array_;
	const int npuzzle_size_;
	int zero_x_;
	int zero_y_;
	static size_t Hash(AStarSt_p st);
};

