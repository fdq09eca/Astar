#pragma once
#include "Agent.h"

class AgentAstar : public Agent //https://www.youtube.com/watch?v=-L-WgKMFuhE
{
public:;
	Index goal;


	AgentAstar(int r = 1, int c = 1, int stepSize = 1, Cell* goal_ = nullptr) {
		Agent::init(r, c, stepSize); 
		if (goal_) { 
			setGoal(goal_);
		} else {
			setRandomGoal();
		}
	};



	void setSrc(int r_, int c_) { r = r_; c = c_; }
	
	Index cellPtrToIndex(Cell* p);

	void setRandomGoal();
	void setGoal(Cell* p);

	D nextDirection() override {
		auto ds = possibleDirections();

		return D::NA;
	}
	
	inline int distance(int r0, int c0, int r1, int c1) { return abs(r0 - r1) + abs(c0 + c1); }
	inline int distance(Index i0, Index i1) { return distance(i0.r, i0.c, i1.r, i1.c); }


	
};

