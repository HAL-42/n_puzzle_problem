#pragma once
#include <vector> 


using namespace std;

using Action = int;

using ptrToAStarStRecord = AStarStRecord*;
using AStarSt_p = AStarStRecord;
using ptrToHashFunc = size_t(*)(AStarSt_p);
class AStarStRecord{
public:
	virtual bool operator==(const AStarStRecord& rhs) const = 0;
	virtual int PrintState() const = 0;
	virtual AStarSt_p StateAfterAction(const Action action) const = 0;
	virtual int GetHeuristicValue() const = 0;
	virtual ptrToHashFunc GetHashFunc() const= 0;
};

using ptrToAStarNodeRecord = AStarNodeRecord * ;
using AStarNd_p = ptrToAStarNodeRecord;
class AStarNodeRecord {
public:
	bool operator>(const AStarNodeRecord& rhs) const;
	bool operator<(const AStarNodeRecord& rhs) const;
	virtual vector<AStarNd_p> GetSuccessor() = 0;
	AStarSt_p GetCurrentState() const;
	int GetAStarValue() const;
	~AStarNodeRecord();
private:
	vector<AStarNd_p> successors_list_;
	AStarNd_p parent_;
	int heuristic_value_;
	int current_cost_;
	int AStar_value_;
	Action last_action;
	AStarSt_p current_state_;
};

class AStarMinHeap {
public:
	//AStarMinHeap();
	int push(const AStarNd_p node_to_push);
	AStarNd_p pop();
	bool IsEmpty() const;
	int Update(AStarNd_p node_to_update);
private:
	static bool Compare(const AStarNd_p n1, const AStarNd_p n2) {return *n1 > *n2; };
	vector<AStarNd_p> vec_;
};

class AStarSolver {
public:
	static AStarNd_p GraphSearch(AStarNd_p start_node, const AStarSt_p goal_state);
	static AStarNd_p OptimGraphSearch(AStarNd_p start_node, const AStarSt_p goal_state);
	static AStarNd_p TreeSearch(AStarNd_p start_node, const AStarSt_p goal_state);
};




