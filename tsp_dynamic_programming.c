// Codigo base obtenido de https://ide.codingblocks.com/s/3899
// Este problema entrega la solucion minima de pasar por todos los nodos partiendo desde cualquier nodo

#include <stdio.h>
#define INT_MAX 999999

// INPUT
// *******************************************************************
// ESTO ES LO UNICO QUE SE EDITA PARA CADA PROBLEMA: n, Adj Matrix y dp

//Numero nodos

//uint32_t n = 5;
//
//// Adj Matrix
//uint32_t dist[5][5] = {
//		{0, 4, 12, 23, 3},
//		{3, 0, 5, 352, 4},
//		{24, 42, 0, 1, 23},
//		{2, 6, 7, 0, 2},
//		{43, 6, 78, 3, 0}};
//
//// Este valor depende de n
//// dp[2 elevado a n][n][n+1], son los estados posibles (programacion dinamica)
//uint32_t dp[32][5][6];

// *****************************************************************

// Funcion recursiva que resuelve problema

void convert(const char *line, uint32_t n, uint32_t array[n][n])
{
	int num, i = 0, len;
	while (sscanf(line, "%d%n", &num, &len) == 1)
	{
		array[i / n][i % n] = num;
		line += len;
		i++;
	}
}

// INPUT, elementos separados por espacios, y tambien n= numero nodos

void tsp(uint32_t mask, uint32_t pos, uint32_t arr[], uint32_t n, uint32_t dist[n][n], uint32_t dp[][n][n + 1])
{

	// Ya visitamos todos los nodos
	if (mask == (1 << n) - 1)
	{
		arr[0] = 0;
		arr[n] = pos;
		return;
	}

	// Conjunto ya visitado
	if (dp[mask][pos][0] != -1)
	{
		arr[0] = dp[mask][pos][0];
		for (uint32_t i = 1; i < n + 1; i++)
		{
			if (arr[i] == -1)
				arr[i] = dp[mask][pos][i];
		}
		return;
	}

	// Visitar todas las ciudades no visitadas y elegir la mejor
	uint32_t ans = INT_MAX;
	uint32_t city_index = -1;
	uint32_t aux[n + 1];
	for (uint32_t city = 0; city < n; city++)
	{

		// Ciudad city no esta visitada
		if ((mask & (1 << city)) == 0 && dist[pos][city] != 0)
		{

			uint32_t arr2[n + 1];
			for (uint32_t i = 1; i < n + 1; i++)
				arr2[i] = arr[i];
			for (uint32_t i = 1; i < n + 1; i++)
			{
				if (arr2[i] == -1)
				{
					arr2[i] = pos;
					break;
				}
			}

			tsp(mask | (1 << city), city, arr2, n, dist, dp);
			uint32_t newAns = dist[pos][city] + arr2[0];

			if (newAns < ans)
			{
				ans = newAns;
				for (uint32_t i = 1; i < n + 1; i++)
				{
					aux[i] = arr2[i];
				}
			}
		}
	}
	arr[0] = ans;
	dp[mask][pos][0] = ans;
	for (uint32_t i = 1; i < n + 1; i++)
	{
		if (arr[i] == -1)
			arr[i] = aux[i];
		dp[mask][pos][i] = aux[i];
	}
}

uint32_t main_fun(uint32_t n, char distS[])
{
	uint32_t dp[8][n][n + 1];

	// Se crea array y con funcion convert se le asignan valores
	uint32_t dist[n][n];
	convert(distS, n, dist);

	for (int i = 0; i < n * n; i++)
	{
		printf("array[%d] = %d\n", i, dist[i / n][i % n]);
	}

	// Inicializar Base de Datos Dinamica
	for (uint32_t i = 0; i < (1 << n); i++)
	{
		for (uint32_t j = 0; j < n; j++)
		{
			dp[i][j][0] = -1;
		}
	}

	// OUTPUT
	// ***********************************************************************
	// Esto sera la solucion del programa
	uint32_t route[n];
	uint32_t cost = INT_MAX;
	// ***********************************************************************

	// Resolvemos el problema partiendo desde diferentes nodos
	for (uint32_t start = 0; start < n; start++)
	{
		// Inicializamos un array que nos dara el return de la funcion, arr[0] = costo total, arr[1..n] = ruta
		uint32_t arr[n + 1];
		for (uint32_t i = 0; i < n + 1; i++)
			arr[i] = -1;

		// Resolvemos el problema partiendo desde un cierto nodo
		tsp(1 << start, start, arr, n, dist, dp);

		// Evaluamos si es la mejor solucion
		if (arr[0] < cost)
		{
			cost = arr[0];
			for (uint32_t i = 0; i < n; i++)
				route[i] = arr[i + 1];
		}
	}

	// Imprimimos output
	printf("Route: ");
	for (uint32_t city = 0; city < n; city++)
	{
		printf("%d ", route[city]);
	}
	printf("\n");
	printf("Total cost: %d\n", cost);

	return 0;
}
