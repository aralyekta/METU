#include "the7.cpp"

int main()
{
    int n, s, d, x, y, m;
    std::vector<Road> roads;
    scanf("%d", &n);
    scanf("%d %d ", &s, &d);
    scanf("%d %d ", &x, &y);
    scanf("%d ", &m);
    for (int i = 0; i < m; i++)
    {
        int first, second, time;
        scanf("%d %d %d", &first, &second, &time);
        std::pair<int, int> pair = std::make_pair(first, second);
        Road road(pair, time);
        roads.push_back(road);
    }

    FindRoute(n, roads, s, d, x, y);
    return 0;
}