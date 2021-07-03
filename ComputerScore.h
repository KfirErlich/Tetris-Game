#ifndef _ComputerScore_
#define _ComputerScore_

class ComputerScore {

	int height;
	int completeLines;
	int score; 
	int holes;
	int bumpiness;
	int heightAfterSet;
	

public:

	void setHeight(const int _height) { height = _height; }
	void setNewHeight(const int _newHeight) { heightAfterSet = _newHeight; }
	void setCompleteLines(const int _completeLines) { completeLines = _completeLines; }
	void setScore(const int _score) { score = _score; }
	void setHoles(const int _holes) { holes = _holes; }
	void setBumpiness(const int _bumpiness) { bumpiness = _bumpiness; }
	int getCompleteLines() { return completeLines; }
	int getheight() { return height; }
	int getNewHeight() { return heightAfterSet; }
	int getScore() { return score; }
	int getBumpiness() { return bumpiness; }
	int getHoles() { return holes; }



};







#endif