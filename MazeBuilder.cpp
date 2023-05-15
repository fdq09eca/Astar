#include "MazeBuilder.h"
#include "App.h"

void MazeBuilder::build() { 
	MazeBuilder mb;
	while (!mb.complete) {
		mb.update();
	}
}


void MazeBuilder::update() {
	if (complete) return;

	D nd = nextDirection();

	if (nd == D::NA) {

		nd = backtrack();

		if (nd == D::NA) {
			onComplete();
			return;
		}
	}

	move(nd);
	removeWall(opposite(nd));
}

void MazeBuilder::onComplete() {
	complete = true;
	maze().restart();
	//maze().gen();
	//init(1, 1, 2);
}

void MazeBuilder::removeWall(D nd) {
	Cell* p = peek(nd, 1);
	if (p && p->isBlock()) {
		p->setBlock(false);
		p->setVisit(true);
	}
}


