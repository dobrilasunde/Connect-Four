#include "Board.hpp"
#include "Random.hpp"
#include<algorithm>
#include<iostream>
BoardState::BoardState()
{
	for (int i = 0; i < 6; ++i)
	{
		for (int j = 0; j < 7; ++j)
		{
			mBoard[i][j] = Empty;
		}
	}
}

std::vector<BoardState*> BoardState::GetPossibleMoves(SquareState player) const
{
	std::vector<BoardState*> retVal;

	for (int col = 0; col < 7; col++)
	{
		for (int row = 5; row >= 0; row--)
		{
			if (mBoard[row][col] == BoardState::Empty)
			{
				retVal.emplace_back(new BoardState(*this));
				retVal.back()->mBoard[row][col] = player;
				break;
			}
		}
	}

	return retVal;
}

bool BoardState::IsTerminal() const
{
	if (IsFull())
	{
		return true;
	}

	int fourInRow = GetFourInARow();
	if (fourInRow != 0)
	{
		return true;
	}

	return false;
}

float BoardState::GetScore() const
{
	if (IsFull())
	{
		return 0.0f;
	}

	int fourInRow = GetFourInARow();
	if (fourInRow != 0)
	{
		return static_cast<float>(fourInRow);
	}

	return CalculateHeuristic();
}

bool BoardState::IsFull() const
{
	bool isFull = true;
	for (int i = 0; i < 6; ++i)
	{
		for (int j = 0; j < 7; ++j)
		{
			if (mBoard[i][j] == Empty)
			{
				isFull = false;
			}
		}
	}

	return isFull;
}

int BoardState::GetFourInARow() const
{
	//returns -1 if yellow wins, 1 if red wins, 0 if its a draw

	//check rows for four in a row
	for (int row = 0; row < 6; ++row)
	{
		for (int col = 0; col < 4; ++col)
		{
			if (mBoard[row][col] == mBoard[row][col + 1] && mBoard[row][col] == mBoard[row][col + 2] && mBoard[row][col] == mBoard[row][col + 3])
			{
				if (mBoard[row][col] == BoardState::Yellow)
				{
					return -1000;
				}
				else if (mBoard[row][col] == BoardState::Red)
				{
					return 1000;
				}
			}
		}
	}

	//check columns for four in a row
	for (int col = 0; col < 7; ++col)
	{
		for (int row = 0; row < 3; ++row)
		{
			if (mBoard[row][col] == mBoard[row+1][col] && mBoard[row][col] == mBoard[row + 2][col] && mBoard[row][col] == mBoard[row + 3][col])
			{
				if (mBoard[row][col] == BoardState::Yellow)
				{
					return -1000;
				}
				else if (mBoard[row][col] == BoardState::Red)
				{
					return 1000;
				}
			}
		}
	}

	//check right diagonal
	for (int col = 0; col < 4; ++col)
	{
		for (int row = 0; row < 3; ++row)
		{
			if (mBoard[row][col] == mBoard[row + 1][col + 1] && mBoard[row][col] == mBoard[row + 2][col + 2] && mBoard[row][col] == mBoard[row + 3][col + 3])
			{
				if (mBoard[row][col] == BoardState::Yellow)
				{
					return -1000;
				}
				else if (mBoard[row][col] == BoardState::Red)
				{
					return 1000;
				}
			}
		}
	}

	//check left diagonal
	for (int col = 0; col < 4; ++col)
	{
		for (int row = 3; row < 6; ++row)
		{
			if (mBoard[row][col] == mBoard[row - 1][col + 1] && mBoard[row][col] == mBoard[row - 2][col + 2] && mBoard[row][col] == mBoard[row - 3][col + 3])
			{
				if (mBoard[row][col] == BoardState::Yellow)
				{
					return -1000;
				}
				else if (mBoard[row][col] == BoardState::Red)
				{
					return 1000;
				}
			}
		}
	}

	return 0;
}

float BoardState::CalculateHeuristic() const
{

	float retVal = 0.0f;

	for (int row = 0; row < 6; ++row)
	{
		for (int col = 0; col < 4; ++col)
		{
			if (mBoard[row][col] != BoardState::Yellow && mBoard[row][col + 1] != BoardState::Yellow && mBoard[row][col + 2] != BoardState::Yellow && mBoard[row][col + 3] != BoardState::Yellow)
			{
				retVal++;
			}
			if (mBoard[row][col] != BoardState::Red && mBoard[row][col + 1] != BoardState::Red && mBoard[row][col + 2] != BoardState::Red && mBoard[row][col + 3] != BoardState::Red)
			{
				retVal--;
			}
		}
	}

	//check columns for four in a row
	for (int col = 0; col < 7; ++col)
	{
		for (int row = 0; row < 3; ++row)
		{
			if (mBoard[row][col] == mBoard[row + 1][col] && mBoard[row][col] == mBoard[row + 2][col] && mBoard[row][col] == mBoard[row + 3][col])
			{
				if (mBoard[row][col] != BoardState::Yellow && mBoard[row][col + 1] != BoardState::Yellow && mBoard[row][col + 2] != BoardState::Yellow && mBoard[row][col + 3] != BoardState::Yellow)
				{
					retVal++;
				}
				if (mBoard[row][col] != BoardState::Red && mBoard[row][col + 1] != BoardState::Red && mBoard[row][col + 2] != BoardState::Red && mBoard[row][col + 3] != BoardState::Red)
				{
					retVal--;
				}
			}
		}
	}

	//check right diagonal
	for (int col = 0; col < 4; ++col)
	{
		for (int row = 0; row < 3; ++row)
		{
			if (mBoard[row][col] != BoardState::Yellow && mBoard[row + 1][col + 1] != BoardState::Yellow && mBoard[row + 2][col + 2] != BoardState::Yellow && mBoard[row + 3][col + 3] != BoardState::Yellow)
			{
				retVal++;
			}
			if (mBoard[row][col] != BoardState::Red && mBoard[row + 1][col + 1] != BoardState::Red && mBoard[row + 2][col + 2] != BoardState::Red && mBoard[row + 3][col + 3] != BoardState::Red)
			{
				retVal--;
			}
		}
	}

	//check left diagonal
	for (int col = 0; col < 4; ++col)
	{
		for (int row = 3; row < 6; ++row)
		{
			if (mBoard[row][col] != BoardState::Yellow && mBoard[row - 1][col + 1] != BoardState::Yellow && mBoard[row - 2][col + 2] != BoardState::Yellow && mBoard[row - 3][col + 3] != BoardState::Yellow)
			{
				retVal++;
			}
			if (mBoard[row][col] != BoardState::Red && mBoard[row - 1][col + 1] != BoardState::Red && mBoard[row - 2][col + 2] != BoardState::Red && mBoard[row - 3][col + 3] != BoardState::Red)
			{
				retVal--;
			}
		}
	}

	return retVal;
}

bool TryPlayerMove(BoardState* state, int column)
{
	for (int row = 5; row >= 0; --row)
	{
		if (state->mBoard[row][column] == BoardState::Empty)
		{
			state->mBoard[row][column] = BoardState::Yellow;
			return true;
		}
	}

	return false;
}

void CPUMove(BoardState* state)
{
	std::vector<BoardState*> moves = state->GetPossibleMoves(BoardState::Red);

	BoardState* result = AlphaBetaDecide(state, 5);
	*state = *result;
	for (auto state : moves)
	{
		delete state;
	}
}

BoardState* AlphaBetaDecide(const BoardState* root, int maxDepth)
{
	BoardState* choice = nullptr;

	float maxValue = -std::numeric_limits<float>::infinity();
	float beta = std::numeric_limits<float>::infinity();
	for (BoardState* child : root->GetPossibleMoves(BoardState::Red))
	{
		float v = AlphaBetaMin(child, maxDepth - 1, maxValue, beta);
		if (v > maxValue)
		{
			maxValue = v;
			choice = child;
		}
	}
	return choice;
}


float AlphaBetaMax(const BoardState* node, int depth, float alpha, float beta)
{
	if (depth == 0 || node->IsTerminal())
	{
		return node->GetScore();
	}
	float maxValue = -std::numeric_limits<float>::infinity();
	for (const BoardState* child : node->GetPossibleMoves(BoardState::Red))
	{
		maxValue = std::max(maxValue, AlphaBetaMin(child, depth - 1, alpha, beta));
		if (maxValue >= beta)
		{
			return maxValue;
		}
		alpha = std::max(maxValue, alpha);
	}
	return maxValue;
}


float AlphaBetaMin(const BoardState* node, int depth, float alpha, float beta)
{
	if (depth == 0 || node->IsTerminal())
	{
		return node->GetScore();
	}
	float minValue = std::numeric_limits<float>::infinity();
	for (const BoardState* child : node->GetPossibleMoves(BoardState::Yellow))
	{
		minValue = std::min(minValue, AlphaBetaMax(child, depth - 1, alpha, beta));
		if (minValue <= alpha)
		{
			return minValue;
		}
		beta = std::min(minValue, beta);
	}
	return minValue;
}
