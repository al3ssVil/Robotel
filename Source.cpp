#include <iostream>
#include <fstream>
#include <cstdlib>
#include <stack>

class Robotel
{
private:
	int m, n, ** matrice;
public:
	void citireMatrice()
	{
		std::ifstream f("harta.txt");
		f >> m >> n;
		matrice = new int* [m];
		for (int i = 0; i < m; i++)
			matrice[i] = new int[m];
		for (int i = 0; i < m; i++)
			for (int j = 0; j < n; j++)
				f >> matrice[i][j];
		f.close();
	}
	int random()
	{
		int x = rand() % 4;
		return x;
	}
	void deplasare_stanga(int& puncte, int& k, std::stack<std::pair<int, int>>& stiva, std::pair<int, int>& robot)
	{
		while (robot.second - 1 > 0&&matrice[robot.first][robot.second - 1] != -1 && k != 0)
		{
			robot.second--;
			stiva.push(robot);
			k--;
			puncte++;
		}
		if (matrice[robot.first + 1][robot.second] != -1 && k != 0)
			deplasare_jos(puncte, k, stiva, robot);
		else
			if (matrice[robot.first - 1][robot.second] != -1 && k != 0)
				deplasare_sus(puncte, k, stiva, robot);
	}
	void deplasare_jos(int& puncte, int& k, std::stack<std::pair<int, int>>& stiva, std::pair<int, int>& robot)
	{
		while (robot.first + 1 < m - 1&&matrice[robot.first + 1][robot.second] != -1 && k != 0)
		{
			robot.first++;
			stiva.push(robot);
			k--;
			puncte++;
		}
		if (matrice[robot.first][robot.second + 1] != -1 && k != 0)
			deplasare_dreapta(puncte, k, stiva, robot);
		else
			if (matrice[robot.first][robot.second - 1] != -1 && k != 0)
				deplasare_sus(puncte, k, stiva, robot);
	}
	void deplasare_dreapta(int& puncte, int& k, std::stack<std::pair<int, int>>& stiva, std::pair<int, int>& robot)
	{
		while (robot.second + 1 < n - 1&&matrice[robot.first][robot.second + 1] != -1 && k != 0)
		{
			robot.second++;
			stiva.push(robot);
			k--;
			puncte++;
		}
		if (matrice[robot.first - 1][robot.second] != -1 && k != 0)
			deplasare_jos(puncte, k, stiva, robot);
		else
			if (matrice[robot.first + 1][robot.second] != -1 && k != 0)
				deplasare_sus(puncte, k, stiva, robot);
	}
	void deplasare_sus(int& puncte, int& k, std::stack<std::pair<int, int>>& stiva, std::pair<int, int>& robot)
	{
		while (robot.first - 1 >0 && matrice[robot.first - 1][robot.second] != -1 && k != 0)
		{
			robot.first--;
			stiva.push(robot);
			k--;
			puncte++;
		}
		if (matrice[robot.first][robot.second - 1] != -1 && k != 0)
			deplasare_jos(puncte, k, stiva, robot);
		else
			if (matrice[robot.first][robot.second + 1] != -1 && k != 0)
				deplasare_sus(puncte, k, stiva, robot);
	
	}
	void drum(std::stack<std::pair<int, int>>& stiva, int k)
	{
		std::pair<int, int> robot = { m / 2, n / 2 };
		std::cout << "Robotelul se afla la pozitiile " << robot.first << ' ' << robot.second << std::endl;
		int puncte = 0, t = k / 2;
		stiva.push({ m / 2, n / 2 });
		if (random() == 0)
		{
			std::cout << "O ia la stanga\n";
			deplasare_stanga(puncte, t, stiva, robot);
		}
		else
			if (random() == 1)
			{
				std::cout << "O ia in jos\n";
				deplasare_jos(puncte, t, stiva, robot);
			}
			else
				if (random() == 2)
				{
					std::cout << "O ia spre dreapta\n";
					deplasare_dreapta(puncte, t, stiva, robot);
				}
				else
				{
					std::cout << "O ia in sus\n";
					deplasare_sus(puncte, t, stiva, robot);
				}
		std::cout << "Puncte" << puncte << '\n';
		while (!stiva.empty())
		{
			std::cout << stiva.top().first << ' ' << stiva.top().second << '\n';
			stiva.pop();
		}
		std::cout << std::endl;
	}
};

int main()
{
	srand(time(NULL));
	Robotel Robotel;
	int k;
	std::stack<std::pair<int, int>> stiva;
	Robotel.citireMatrice();
	std::cin >> k;
	for (int i = 0; i < 3; i++)
	{
		Robotel.drum(stiva, k);
	}
	return 0;
}