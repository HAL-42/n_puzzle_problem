#include "aStar_everything.h"
#include <algorithm>
#include <iostream>
#include <unordered_map>

inline bool AStarNodeRecord::operator>(const AStarNodeRecord & rhs) const
{
	return AStar_value_ > rhs.AStar_value_;
}

inline bool AStarNodeRecord::operator<(const AStarNodeRecord& rhs) const
{
	return AStar_value_ < rhs.AStar_value_;
}

inline AStarSt_p AStarNodeRecord::GetCurrentState() const
{
	return current_state_;
}

int AStarNodeRecord::GetAStarValue() const
{
	return AStar_value_;
}

inline AStarNodeRecord::~AStarNodeRecord()
{
	delete current_state_;
}

int AStarMinHeap::push(const AStarNd_p node_to_push)
{
	vec_.push_back(node_to_push);
	if (1 == vec_.size) {
		return 0;
	}
	else {
		push_heap(vec_.begin(), vec_.end(), Compare);
	}
	return 0;
}

AStarNd_p AStarMinHeap::pop()
{
	if (!vec_.size()) {
		cerr << "Pop Empty Heap!" << endl;
		return NULL;
	}
	pop_heap(vec_.begin(), vec_.end(), Compare);
	AStarNd_p tmp = vec_.back();
	vec_.pop_back();
	return tmp;
}

inline bool AStarMinHeap::IsEmpty() const
{
	return ! ((bool) vec_.size());
}

int AStarMinHeap::Update(AStarNd_p node_to_update)
{
	auto it = vec_.begin();
	for (; it != vec_.end(); it++) {
		if (*((*it)->GetCurrentState()) == *(node_to_update->GetCurrentState())) break;
	}
	if (it == vec_.end()) {
		vec_.push_back(node_to_update);
		push_heap(vec_.begin(), vec_.end(), Compare);
		return 0;
	}
	else if ((*it)->GetAStarValue() <= node_to_update->GetAStarValue()) {
		return 1;
	}
	else {
		*it = node_to_update;
		return 2;
	}	
}

using AStarMap = unordered_map < AStarSt_p, AStarNd_p, size_t(*)(AStarSt_p), bool(*)(AStarSt_p, AStarSt_p) >;

AStarNd_p AStarSolver::GraphSearch(AStarNd_p start_node, const AStarSt_p goal_state)
{
	AStarMinHeap frontier;
	AStarMap explored_list(4, goal_state->GetHashFunc(), [](AStarSt_p s1,
			AStarSt_p s2)->bool {return *s1 == *s2; });
	frontier.push(start_node);
	
	AStarNd_p current_node;
	vector<AStarNd_p> current_successors;
	AStarMap::const_iterator got;
	while (!frontier.IsEmpty()) {
		current_node = frontier.pop();
		if (*(current_node->GetCurrentState()) == *goal_state) return current_node;
		current_successors = current_node->GetSuccessors();
		for (auto it = current_successors.begin(); it != current_successors.end(); it++) {
			got = explored_list.find((*it)->GetCurrentState());
			if (got == explored_list.end()) frontier.Update(*(it));
		}
		explored_list.insert(make_pair(current_node->GetCurrentState(), current_node));
	}
	cout << "GraphSearch Can't Find a Solution" << endl;
	return NULL;
}
