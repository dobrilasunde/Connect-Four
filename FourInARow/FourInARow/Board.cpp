#include "Board.hpp"
#include "Random.hpp"

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
			if (mBoard[row][col] == mBoard[row][col + 1] && mBoard[row][col + 2] && mBoard[row][col + 3])
			{
				if (mBoard[row][col] == BoardState::Yellow)
				{
					return -1;
				}
				else if (mBoard[row][col] == BoardState::Red)
				{
					return 1;
				}
			}
		}
	}

	//check columns for four in a row
	for (int col = 0; col < 7; ++col)
	{
		for (int row = 0; row < 3; ++row)
		{
			if (mBoard[row][col] == mBoard[row+1][col] && mBoard[row + 2][col] && mBoard[row + 3][col])
			{
				if (mBoard[row][col] == BoardState::Yellow)
				{
					return -1;
				}
				else if (mBoard[row][col] == BoardState::Red)
				{
					return 1;
				}
			}
		}
	}

	//check right diagonal
	for (int col = 0; col < 4; ++col)
	{
		for (int row = 0; row < 3; ++row)
		{
			if (mBoard[row][col] == mBoard[row + 1][col + 1] && mBoard[row + 2][col + 2] && mBoard[row + 3][col + 3])
			{
				if (mBoard[row][col] == BoardState::Yellow)
				{
					return -1;
				}
				else if (mBoard[row][col] == BoardState::Red)
				{
					return 1;
				}
			}
		}
	}

	//check left diagonal
	for (int col = 0; col < 4; ++col)
	{
		for (int row = 3; row < 6; ++row)
		{
			if (mBoard[row][col] == mBoard[row - 1][col + 1] && mBoard[row - 2][col + 2] && mBoard[row - 3][col + 3])
			{
				if (mBoard[row][col] == BoardState::Yellow)
				{
					return -1;
				}
				else if (mBoard[row][col] == BoardState::Red)
				{
					return 1;
				}
			}
		}
	}

	return 0;
}

float BoardState::CalculateHeuristic() const
{
	return 0.0f;
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

	int index = Random::GetIntRange(0, moves.size() - 1);

	*state = *moves[index];
	for (auto state : moves)
	{
		delete state;
	}
}