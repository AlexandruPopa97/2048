#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <conio.h>  
#include <ctype.h>  
#include <cstdio>
#include <string>
#include <fstream>
#include <malloc.h>
#include <cstdlib>
#include <time.h> 
#include <iomanip>  
#include <algorithm>
#include <vector>  

using namespace std;

class joc_2048{
	int m[4][4];
public:
	void init_0( int (*m)[4]);
	void afis(int(*m)[4]);
	void sus(int(*m)[4]);
	void dreapta(int(*m)[4]);
	void jos(int(*m)[4]);
	void stanga(int(*m)[4]);
	void Switch(int(*m)[4]);
	void pune_2_sau_4(int(*m)[4]);
	void pune_primii_2(int(*m)[4]);
};
void aranj_dreapta(int v[])
{
	int k, j;
	for (int i = 1; i < 4; i++)
	{
		k = v[i];
		if (k > 0)
			continue;
		j = i - 1;
		while (j >= 0 && v[j] > 0)
		{
			v[j + 1] = v[j];
			j = j - 1;
		}
		v[j + 1] = k;
	}
}
void aranj_stanga(int v[])
{
	int j;
	for (int k = 0; k < 2; k++)
		for (int i = 0; i < 4; i++)
		{
			if (v[i] == 0)
			{
				for ( j = i; j < 3; j++)
					v[j] = v[j+1];
				v[j] = 0;
			}
		}
}
int castiga(int(*m)[4])
{
	int max = m[0][0];
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
		{
			if (m[i][j] > max)
				max = m[i][j];
		}
	return max;
}
int pierde(int(*m)[4])
{
	int ok = 1;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 3; j++)
		{
			if (m[i][j] == m[i][j + 1])
				ok = 0;
		}
	for (int j = 0; j < 4; j++)
		for (int i = 0; i < 3; i++)
		{
			if (m[i][j] == m[i + 1][j])
				ok = 0;
		}
	return ok;
}
void joc_2048::init_0( int(*m)[4])
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			m[i][j] = 0;
}
void joc_2048::afis(int(*m)[4])
{
	std::cout << std::setw(3);
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
			if (m[i][j] == 0)
				std::cout << "_" << std::setw(3);
				else 
					std::cout << m[i][j] << std::setw(3);
		cout << std::endl;
	}
}
void joc_2048::sus(int(*m)[4])
{
	int *v;
	int ok = 0;
	int **M = new int*[4];
	for (int i = 0; i < 4; i++)
		M[i] = new int[4];
	for (int j = 0; j < 4; j++)
		for (int i = 0; i < 4; i++)
			M[i][j] = m[i][j];
	v = (int*)malloc(4 * sizeof(int));
	for (int j = 0; j < 4; j++)
	{
		for (int i = 0; i < 4; i++)
		{
			v[i] = m[i][j];
		}
		aranj_dreapta(v);
		aranj_stanga(v);
		for (int i = 0; i < 4; i++)
		{
			m[i][j] = v[i];
		}
	}
	for (int j = 0; j < 4; j++)
		for (int i = 0; i < 4; i++)
		{
			if (m[i][j] == m[i + 1][j] && i != 3)
			{
				if ((m[i][j] != 0) || (m[i+1][j] != 0))
					ok = 2;
				m[i][j] = m[i][j] * 2;
				for (int k = i + 1; k <4; k++)
				{
					m[k][j] = m[k+1][j];
					if (k == 3)
						m[k][j] = 0;
				}
			}
		}
	for (int i = 0; i < 4; i++)
	{
		for (int k = 0; k < 4; k++)
		{
			if (M[i][k] != m[i][k])
				ok = 3;
		}
	}
	for (int i = 0; i < 4; ++i)
		delete[] M[i];
	delete[] M;
	free(v);
	if (ok)joc_2048::pune_2_sau_4(m);
	joc_2048::afis(m);
}
void joc_2048::jos(int(*m)[4])
{
	int *v;
	int ok = 0;
	int **M=new int*[4];
	for (int i = 0; i < 4; i++)
		M[i] = new int[4];
	for (int j = 0; j < 4; j++)
		for (int i = 0; i < 4; i++)
			M[i][j] = m[i][j];
	v = (int*)malloc(4 * sizeof(int));
	for (int j = 0; j < 4; j++)
	{
		for (int i = 0; i < 4; i++)
		{
			v[i] = m[i][j];
		}
		aranj_dreapta(v);
		for (int i = 0; i < 4; i++)
		{
			m[i][j] = v[i];
		}
	}
	for (int j = 0; j < 4; j++)
	{
		for (int i = 3; i >= 0; i--)
		{
			if (m[i][j] == m[i - 1][j] && i != 0)
			{
				if ((m[i][j] != 0) || (m[i - 1][j] != 0))
					ok = 2;
				m[i][j] = m[i][j] * 2;
				for (int k = i - 1; k >= 0; k--)
				{
					if (k == 0)
						m[k][j] = 0;
					else
						m[k][j] = m[k - 1][j];
				}
			}
		}
	}
	for (int i = 0; i < 4; i++)
	{
		for (int k = 0; k < 4; k++)
		{
			if (M[i][k] != m[i][k])
				ok = 3;
		}
	}
	for (int i = 0; i < 4; ++i)
		delete[] M[i];
	delete[] M;
	free(v);
	if (ok)joc_2048::pune_2_sau_4(m);
	joc_2048::afis(m);
}
void joc_2048::dreapta(int(*m)[4])
{
	int *v;
	int ok = 0;
	int **M = new int*[4];
	for (int i = 0; i < 4; i++)
		M[i] = new int[4];
	for (int j = 0; j < 4; j++)
		for (int i = 0; i < 4; i++)
			M[i][j] = m[i][j];
	v = (int*)malloc(4 * sizeof(int));
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			v[j] = m[i][j];
		}
		aranj_dreapta(v);
		for (int j = 0; j < 4; j++)
		{
			m[i][j] = v[j];
		}
	}
	for (int i = 0; i < 4; i++)
		for (int j = 3; j >= 0; j--)
		{
			if (m[i][j] == m[i][j - 1])
			{
				if ((m[i][j] != 0) || (m[i][j - 1] != 0))
					ok=2;
				m[i][j] = m[i][j] * 2;
				for (int k = j - 1; k >= 0; k--)
				{
					if (k == 0)
						m[i][k] = 0;
					else
					m[i][k] = m[i][k - 1];
				}
			}
		}
	for (int i = 0; i < 4; i++)
	{
		for (int k = 0; k < 4; k++)
		{
			if (M[i][k] != m[i][k])
				ok = 3;
		}
	}
	for (int i = 0; i < 4; ++i)
		delete[] M[i];
	delete[] M;
	free(v);
	if (ok)joc_2048::pune_2_sau_4(m);
	joc_2048::afis(m);

}
void joc_2048::stanga(int(*m)[4])
{
	int *v;
	int ok = 0;
	int **M = new int*[4];
	for (int i = 0; i < 4; i++)
		M[i] = new int[4];
	for (int j = 0; j < 4; j++)
		for (int i = 0; i < 4; i++)
			M[i][j] = m[i][j];
	v = (int*)malloc( 4 * sizeof(int));
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			v[j] = m[i][j];
		}
		aranj_dreapta(v);
		aranj_stanga(v);
		for (int j = 0; j < 4; j++)
		{
			m[i][j] = v[j];
		}
	}
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
		{
			if (m[i][j] == m[i][j + 1] && j != 3)
			{
				if ((m[i][j] != 0) || (m[i][j + 1] != 0))
					ok = 2;
				m[i][j] = m[i][j] * 2;
				for (int k = j+1; k <4 ; k++)
				{
					if (k == 3)
						m[i][k] = 0;
					else
						m[i][k] = m[i][k + 1];
				}
			}
		}
	for (int i = 0; i < 4; i++)
	{
		for (int k = 0; k < 4; k++)
		{
			if (M[i][k] != m[i][k])
				ok = 3;
		}
	}
	for (int i = 0; i < 4; ++i)
		delete[] M[i];
	delete[] M;
	free(v);
	if (ok)joc_2048::pune_2_sau_4(m);
	joc_2048::afis(m);

}
void joc_2048::pune_2_sau_4(int(*m)[4])
{
	int i, r1, r2, j, nr = 0, k = 0;
	int *v;
	srand(time(NULL));
	r1 = rand() % 10;
	v = (int*)malloc(16 * sizeof(int));
	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
		{
			if (m[i][j]==0)
			{
				v[k] = nr;
				k++;
			}
			nr++;
		}
	nr = 0;
	r2 = rand() % k + 1;
	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
		{
			if (nr == v[r2] && ((k == 8) || (k == 9)))
				m[i][j] = 4;
			else if (nr == v[r2])
				m[i][j] = 2;
		nr++;
		}
	free(v);
}
void joc_2048::Switch(int(*m)[4])
{
	const char sus = 'w';
	const char jos = 's';
	const char dreapta = 'd';
	const char stanga = 'a';
	char ch;
	int ok = 0;
	if (pierde(m) == 0)
	{
		do
		{
			ch = _getch();
			cout << "Ai apasat tasta:" << ch << endl;
			switch (ch)
			{
			case sus:
				joc_2048::sus(m);
				break;
			case jos:
				joc_2048::jos(m);
				break;
			case stanga:
				joc_2048::stanga(m);
				break;
			case dreapta:
				joc_2048::dreapta(m);
				break;
			default:
				cout << "Caracter incorect!" << endl;
				break;
			}

			if (castiga(m) == 2048)
			{
				std::cout << "Ai castigat !";
				break;
			}
		} while (ch == 'w' || ch == 's' || ch == 'a' || ch == 'd' || ch > 'b' || ch < 'z');

	}
	else
	{
		std::cout << "Ai pierdut" << endl;
	}
}
void joc_2048::pune_primii_2(int(*m)[4])
{
	int x, y,nr=0;
	int k; // probabiliatea de 20% ca un element sa fie 4 
	srand(time(NULL));
	do
	{
		x = rand() % 16;
		y = rand() % 16;
		k = rand() % 10;
	} while (x == y);
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
		{
			if ((nr == x || nr == y) && (k == 9 || k == 8))
				m[i][j] = 4;
			else if (nr == x || nr == y)
				m[i][j] = 2;
			nr++;
		}
	joc_2048::afis(m);
}

int main(int argc, int **argv)
{
	int m[4][4];
	joc_2048 joc;
	char c;
	std::cout << "Vrei sa joci 2048 ?(apasa d sau D pentru da ,pentru nu apasa alt caracter)"; std::cin >> c;
	if (c == 'd' || c == 'D')
		do
		{
			joc.init_0(m);
			joc.pune_primii_2(m);
			joc.Switch(m);
			std::cout << "Vrei sa mai joci ?(apasa d sau D pentru da ,pentru nu apasa alt caracter)"; std::cin >> c;
		} while (c == 'd' || c == 'D');
	else
		return 0;
}
