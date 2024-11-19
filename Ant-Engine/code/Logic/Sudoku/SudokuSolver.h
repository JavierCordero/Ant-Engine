
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "../../EngineCore/EngineCore.h"
#include "../../EngineCore/LogicEngine/LogicEngine.h"
#include <Windows.h>

using namespace std;

class Sudoku
{

	struct Number {
		int finalNumber;
		bool originalNumber = false;
	};

public:
	Sudoku()
	{
		for (int i = 0; i < numCells; ++i)
		{
			for (int j = 0; j < numCells; ++j)
			{
				myTable[i][j].finalNumber = 0;
			}
		}
	}

	Sudoku(const char* _filename)
	{
		ReadTableFromFile(_filename);
	}

	void PrintTable()
	{
		for (int i = 0; i < numCells; ++i)
		{
			if (i % 3 == 0 && i != 0)
			{
				//Aqui para espacios entre filas
			}

			//Comienza fila
			for (int j = 0; j < numCells; ++j)
			{
				if (j % 3 == 0 && j != 0)
				{
					//Aqui para espacios entre columnas
				}
				int number = myTable[i][j].finalNumber;
				if (number != 0)
				{
					Text3D text;
					text.position = glm::vec3(-410 + j * 100, 390 + -i * 100, 25.f);
					text.text = std::to_string(myTable[i][j].finalNumber);
					text.color = glm::vec3(0.0f, 0.0f, 0.0f);

					if (!myTable[i][j].originalNumber)
					{
						text.color = glm::vec3(0.0f, 0.5f, 0.8f);
					}
					if (myTable[i][j].finalNumber == 0)
					{
						text.color = glm::vec3(1.0f, 0.0f, 0.0f);
					}

					LogicLib::text3D.push_back(text);
				}
			}
			//Termina fila
		}
		//Termina sudoku

		Text3D text;

		if (!m_TriedToSolve)
		{
			text.position = glm::vec3(-900, 390, 0.0f);
			text.text = "Press 'Y' to solve sudoku.";
			text.color = glm::vec3(0.0f, 0.0f, 0.0f);
		}

		else
		{
			if (m_CanBeSolved)
			{
				text.position = glm::vec3(-900, 390, 0.0f);
				text.text = "Sudoku solved successfully!";
				text.color = glm::vec3(0.0f, 0.0f, 0.0f);
			}

			else
			{
				text.position = glm::vec3(-900, 390, 0.0f);
				text.text = "Sudoku can't be solved!";
				text.color = glm::vec3(0.0f, 0.0f, 0.0f);
			}
		}
		LogicLib::text3D.push_back(text);
	}

	void ReadTableFromFile(const char* _filename)
	{
		ifstream myfile;

		strcpy_s(m_TextureFolder, EngineCore::GetResourceFolder());

		strcpy_s(m_TextureFilename, _filename);

		char filename[MAX_PATH];
		strcpy_s(filename, m_TextureFolder);
		strcat_s(filename, m_TextureFilename);

		myfile.open(filename, ios::in);

		if (myfile.is_open()) {
			string line;
			int fil = 0;
			int row = 0;
			while (getline(myfile, line)) {
				for (char c : line)
				{
					int number = (int)c - 48;
					myTable[fil][row].finalNumber = number;

					if (number != 0)
					{
						myTable[fil][row].originalNumber = true;
					}

					row++;
				}
				fil++;
				row = 0;
			}
			myfile.close();
		}
	}

	bool CheckIsCorrectAnswer(int& _i, int& _j)
	{
		for (_i = 0; _i < numCells; ++_i)
		{
			for (_j = 0; _j < numCells; ++_j)
			{
				if (myTable[_i][_j].finalNumber == 0)
					return true;
			}
		}

		return false;
	}

	void SolveSudoku()
	{
		m_CanBeSolved = SolveSudoku_Recursive();
	}

	bool SolveSudoku_Recursive()
	{
		int i, j;
		if (!CheckIsCorrectAnswer(i, j))
			return true;

		for (int num = 1; num <= 9; num++) {
			if (CheckHorizontal(i, num) && CheckVertical(j, num) && CheckSquare(i, j, num))
			{
				myTable[i][j].finalNumber = num;
				if (SolveSudoku_Recursive())
					return true;
				myTable[i][j].finalNumber = 0;
			}
		}
		return false;
	}

private:
	static const int numCells = 9;
	int subCellNumber = 3;
	Number myTable[numCells][numCells];

	char m_TextureFolder[MAX_PATH];
	char m_TextureFilename[64];

	bool m_CanBeSolved = false;
	bool m_TriedToSolve = false;

	bool CheckHorizontal(int _verticalNumber, int _number)
	{
		for (int i = 0; i < numCells; ++i)
		{
			if (myTable[_verticalNumber][i].finalNumber == _number)
			{
				return false;
			}
		}
		return true;
	};

	bool CheckVertical(int _horizontalNumber, int _number)
	{
		for (int i = 0; i < numCells; ++i)
		{
			if (myTable[i][_horizontalNumber].finalNumber == _number)
			{
				return false;
			}
		}
		return true;
	};

	bool CheckSquare(int _i, int _j, int _number)
	{
		int auxStartX = _i / 3;
		int auxStartY = _j / 3;
		auxStartX *= 3;
		auxStartY *= 3;

		for (int i = 0; i < subCellNumber; ++i)
		{
			for (int j = 0; j < subCellNumber; ++j)
			{
				if (myTable[auxStartX + i][auxStartY + j].finalNumber == _number)
				{
					return false;
				}
			}
		}

		return true;
	};
};