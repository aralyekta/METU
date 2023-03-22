#include "the7.h"

/* Notes:
Since 1 <= T <= 250, every road must increase the path cost. This means
S -> X -> Y > S -> X. Because X->Y > 0.

The algo is to first do Dijkstra and then pick the min cost between these two:
S -> X -> Y -> D (w(S,X) + w(X,Y) + w(Y,D))
S -> Y -> X -> D (w(S,Y) + w(Y,X) + w(X,D))

*/

// std::tuple<int, int, int> popMin(std::vector<std::tuple<int, int, int>> pq)
// {
// 	std::vector<std::tuple<int, int, int>>::iterator toBeDeleted;
// 	int minCost = -1;
// 	std::tuple<int, int, int> returnTuple;
// 	std::vector<std::tuple<int, int, int>>::iterator itr = pq.begin();
// 	for (int count = 0; itr != pq.end(); count++, itr++)
// 	{
// 		if (count == 0)
// 		{
// 			std::tuple<int, int, int> tuple = *itr;
// 			toBeDeleted = itr;
// 			minCost = std::get<1>(tuple);
// 			returnTuple = tuple;
// 		}
// 		else
// 		{
// 			std::tuple<int, int, int> tuple = *itr;
// 			if (std::get<1>(tuple) < minCost)
// 			{
// 				toBeDeleted = itr;
// 				minCost = std::get<1>(tuple);
// 				returnTuple = tuple;
// 			}
// 		}
// 	}
// 	pq.erase(toBeDeleted);
// 	return returnTuple;
// }

bool checkIfContains(std::vector<int> vect, int val)
{
	std::vector<int>::iterator itr = vect.begin();
	for (; itr != vect.end(); itr++)
	{
		if (*itr == val)
			return true;
	}
	return false;
}

// Returns the index with the minimum cost and adds it to the popped vector
int popMin(int *costArr, int n, std::vector<int> &popped)
{
	int minCost = -1;
	int result = -1;
	bool gotFirst = false;
	for (int i = 0; i < n; i++)
	{
		if (!checkIfContains(popped, i))
		{
			if (!gotFirst)
			{
				minCost = costArr[i];
				result = i;
				gotFirst = true;
			}
			else if (costArr[i] < minCost)
			{
				minCost = costArr[i];
				result = i;
			}
		}
	}
	popped.push_back(result);
	return result;
}

void Dijkstra(int n, int *minCost, int *pred, int s, int **adjMatrix)
{
	std::vector<int> popped;

	// Initialization for Dijkstra
	for (int i = 0; i < n; i++)
	{
		minCost[i] = INT_MAX;
	}
	minCost[s] = 0;

	for (int i = 0; i < n; i++)
	{
		pred[i] = -2;
	}
	pred[s] = -1;

	// Dijkstra
	// std::cout << "Starting Dijkstra\n";
	for (int i = 0; i < n; i++)
	{
		int poppedMin = popMin(minCost, n, popped);
		for (int j = 0; j < n; j++)
		{
			int edgeCost = adjMatrix[poppedMin][j];
			if (edgeCost != 0 && minCost[poppedMin] + edgeCost < minCost[j])
			{
				minCost[j] = minCost[poppedMin] + edgeCost;
				pred[j] = poppedMin;
			}
		}
	}
}

void FindRoute(int n, std::vector<Road> roads, int s, int d, int x, int y)
{
	std::vector<int> path;
	std::vector<int>::iterator beginItr = path.begin();
	int cost = INT_MAX;

	// Adjacency matrix, alloc it and initialize it
	int **adjMatrix = new int *[n];
	for (int i = 0; i < n; i++)
	{
		adjMatrix[i] = new int[n];
		for (int j = 0; j < n; j++)
		{
			adjMatrix[i][j] = 0;
		}
	}

	// Set the adjacency matrix according to the given roads, also do it in reverse as the roads are double sided edges
	std::vector<Road>::iterator itr = roads.begin();
	for (; itr != roads.end(); itr++)
	{
		int first = itr->endpoints.first;
		int second = itr->endpoints.second;
		int time = itr->time;
		adjMatrix[first][second] = time;
		adjMatrix[second][first] = time;
	}

	// Do Dijkstra for S, X, Y
	// Then check for S -> X -> Y -> D
	// and S -> Y -> X -> D

	int *minCostS = new int[n];
	int *predS = new int[n];
	int *minCostX = new int[n];
	int *predX = new int[n];
	int *minCostY = new int[n];
	int *predY = new int[n];

	Dijkstra(n, minCostS, predS, s, adjMatrix);
	Dijkstra(n, minCostX, predX, x, adjMatrix);
	Dijkstra(n, minCostY, predY, y, adjMatrix);

	// std::cout << "Dijkstras are done\n";

	// for (int i = 0; i < n; i++)
	// {
	// 	std::cout << predS[i] << " ";
	// }
	// std::cout << "\n";

	// for (int i = 0; i < n; i++)
	// {
	// 	std::cout << minCostS[i] << " ";
	// }
	// std::cout << "\n";

	// for (int i = 0; i < n; i++)
	// {
	// 	std::cout << predX[i] << " ";
	// }
	// std::cout << "\n";

	// for (int i = 0; i < n; i++)
	// {
	// 	std::cout << minCostX[i] << " ";
	// }
	// std::cout << "\n";

	// for (int i = 0; i < n; i++)
	// {
	// 	std::cout << predY[i] << " ";
	// }
	// std::cout << "\n";

	// for (int i = 0; i < n; i++)
	// {
	// 	std::cout << minCostY[i] << " ";
	// }
	// std::cout << "\n";

	int cost1 = minCostS[x] + minCostX[y] + minCostY[d];
	int cost2 = minCostS[y] + minCostY[x] + minCostX[d];

	// std::cout << cost1 << " and " << cost2 << "\n";

	if (cost1 < cost2)
	{
		// S -> X -> Y -> D
		cost = cost1;
		int vertex3 = d;

		while (predY[vertex3] >= 0)
		{
			// std::cout << "inserted " << vertex3 << "\n";
			path.insert(beginItr, vertex3);
			beginItr = path.begin();
			vertex3 = predY[vertex3];
		}

		int vertex2 = y;

		while (predX[vertex2] >= 0)
		{
			// std::cout << "inserted " << vertex2 << "\n";
			path.insert(beginItr, vertex2);
			beginItr = path.begin();
			vertex2 = predX[vertex2];
		}

		int vertex1 = x;

		while (predS[vertex1] >= 0)
		{
			// std::cout << "inserted " << vertex1 << "\n";
			path.insert(beginItr, vertex1);
			beginItr = path.begin();
			vertex1 = predS[vertex1];
		}

		// std::cout << "inserted " << s << "\n";
		path.insert(beginItr, s);
	}
	else
	{
		// S -> Y -> X -> D
		cost = cost2;
		int vertex3 = d;

		while (predX[vertex3] >= 0)
		{
			path.insert(beginItr, vertex3);
			beginItr = path.begin();
			vertex3 = predX[vertex3];
		}

		int vertex2 = x;

		while (predY[vertex2] >= 0)
		{
			path.insert(beginItr, vertex2);
			beginItr = path.begin();
			vertex2 = predY[vertex2];
		}

		int vertex1 = y;

		while (predS[vertex1] >= 0)
		{
			path.insert(beginItr, vertex1);
			beginItr = path.begin();
			vertex1 = predS[vertex1];
		}

		path.insert(beginItr, s);
	}

	for (int i = 0; i < n; i++)
	{
		delete[] adjMatrix[i];
	}
	delete[] adjMatrix;
	delete[] minCostS;
	delete[] predS;
	delete[] minCostX;
	delete[] predX;
	delete[] minCostY;
	delete[] predY;
	// Your output should be like this. You can change this as long as you keep
	// the output format. PrintRange function helps you print elements of
	// containers with iterators (e.g., std::vector).

	std::cout << cost << " ";
	PrintRange(path.begin(), path.end());
	std::cout << std::endl;
}

int main()
{
	int n, s, d, x, y, m;
	std::vector<Road> roads;
	scanf("%d ", &n);
	scanf("%d %d ", &s, &d);
	scanf("%d %d ", &x, &y);
	scanf("%d ", &m);
	for (int i = 0; i < m; i++)
	{
		int first, second, time;
		scanf("%d %d %d ", &first, &second, &time);
		std::pair<int, int> pair = std::make_pair(first, second);
		Road road(pair, time);
		roads.push_back(road);
	}

	FindRoute(n, roads, s, d, x, y);
	return 0;
}