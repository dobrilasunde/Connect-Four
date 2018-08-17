#pragma once
#include <vector>

class BoardState
{
public:
	enum SquareState { Empty, Red, Yellow};
	BoardState();
	std::vector<BoardState*> GetPossibleMoves(SquareState player) const;
	bool IsTerminal() const;
	float GetScore() const;

	SquareState mBoard[6][7];

protected:
	bool IsFull() const;
	int GetFourInARow() const;
	float CalculateHeuristic() const;
};

bool TryPlayerMove(class BoardState* state, int column);
void CPUMove(class BoardState* state);
BoardState* AlphaBetaDecide(const BoardState* root, int maxDepth);
float AlphaBetaMax(const BoardState* node, int depth, float alpha, float beta);
float AlphaBetaMin(const BoardState* node, int depth, float alpha, float beta);

