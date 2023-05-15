#pragma once
#include "Agent.h"


class Maze;
class MazeBuilder: public Agent //mazeBuilder
{

	
public:
	MazeBuilder() : Agent(1, 1, 2) {};
	~MazeBuilder() {  }
	
	
	virtual void update() override;
	virtual void onComplete() override;
	void removeWall(D nd);
	
	static void build();
};

