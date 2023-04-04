#include <vector>
#include <iostream>
#include <algorithm>

struct building
{
    int left, right, height;
};
struct point
{
    int x, y;
};

class Solution
{
    struct bluepoint
    {
        int x, y;
        bool ghost = false;
    };

public:
    // O(buildings * 2 * boundary)
    std::vector<point> getskyline(const std::vector<building> &buildings)
    {
        int boundary = buildings[0].right;
        for (int i = 1; i < buildings.size(); ++i)
        {
            if (boundary < buildings[i].right)
                boundary = buildings[i].right;
        }

        const int scaled = boundary * 2;
        std::vector<int> projectedY(scaled + 1);

        for (int i = 0; i < buildings.size(); ++i)
        {
            for (int x = buildings[i].left * 2; x < buildings[i].right * 2 + 1; ++x)
            {
                if (projectedY[x] < buildings[i].height)
                    projectedY[x] = buildings[i].height;
            }
        }

        std::vector<bluepoint> edges(boundary + 2); // +2 ghosts
        edges[0].x = 0;
        edges[0].y = 0;
        edges[0].ghost = true;
        edges[1].x = 0;
        edges[1].y = projectedY[0];

        int considered_ghost = -1;
        int ghost = 1;
        int edge = 2;
        for (int x = 1; x < scaled; ++x) // scaled = edges.size() - 1
        {
            const int &before = projectedY[x - 1];
            const int &current = projectedY[x];
            const int &after = projectedY[x + 1]; // edge 12: [20, 10]

            if (current > before || current > after)
            {
                edges[edge].x = x / 2;
                edges[edge].y = current;
                ++edge;
            }
            else
            {
                if (current < before)
                {
                    if (current < after)
                    {
                        edges[edge].x = x / 2; // .5
                        edges[edge].y = current;
                        edges[edge].ghost = true;
                        ++edge;

                        ++ghost;
                        considered_ghost = -1;
                    }
                    else
                    {
                        considered_ghost = x;
                    }
                }
                else if (current < after && considered_ghost != -1)
                {
                    edges[edge].x = considered_ghost / 2; // .5
                    edges[edge].y = projectedY[considered_ghost];
                    edges[edge].ghost = true;
                    ++edge;

                    edges[edge].x = x / 2; // .5
                    edges[edge].y = current;
                    edges[edge].ghost = true;
                    ++edge;

                    ghost += 2;
                    considered_ghost = -1;
                }
            }
        }
        edges[edge].x = boundary; // boundary = scaled / 2
        edges[edge].y = projectedY[scaled];
        ++edge;
        edges[edge].x = boundary;
        edges[edge].y = 0;
        edges[edge].ghost = true;

        std::vector<point> points((edge - ghost) * 2);

        int p = 0;
        for (int i = 0; i < edge; ++i)
        {
            const bluepoint &current = edges[i];
            const bluepoint &after = edges[i + 1];

            if (!current.ghost)
            {
                points[p].x = current.x;
                points[p].y = current.y;
                ++p;
            }

            if (current.y == after.y)
            {
                continue;
            }
            else if (current.y < after.y)
            {
                points[p].x = after.x;
                points[p].y = current.y;
            }
            else
            {
                points[p].x = current.x;
                points[p].y = after.y;
            }
            ++p;
        }

        return points;
    }
};

int main()
{
    std::vector<building> buildings1 = {
        {0, 5, 7},
        {4, 10, 6},
        {2, 6, 5}};

    std::vector<building> buildings2 = {
        {16, 20, 6},
        {2, 10, 10},
        {0, 6, 8},
        {1, 4, 13},
        {5, 7, 12},
        {12, 17, 8}};

    Solution sol;
    std::vector<point> points = sol.getskyline(buildings2);

    for (int i = 0; i < points.size(); ++i)
    {
        printf("[%i] x: %i y: %i\n", i, points[i].x, points[i].y);
    }

    printf("\n");

    if (points.size() == 6 &&
        points[0].x == 0 && points[0].y == 0 &&
        points[1].x == 0 && points[1].y == 7 &&
        points[2].x == 5 && points[2].y == 7 &&
        points[3].x == 5 && points[3].y == 6 &&
        points[4].x == 10 && points[4].y == 6 &&
        points[5].x == 10 && points[5].y == 0)
        printf("buildings1: True\n");
    else
        printf("buildings1: False\n");

    if (points.size() == 18 &&
        points[0].x == 0 && points[0].y == 0 &&
        points[1].x == 0 && points[1].y == 8 &&
        points[2].x == 1 && points[2].y == 8 &&
        points[3].x == 1 && points[3].y == 13 &&
        points[4].x == 4 && points[4].y == 13 &&
        points[5].x == 4 && points[5].y == 10 &&
        points[6].x == 5 && points[6].y == 10 &&
        points[7].x == 5 && points[7].y == 12 &&
        points[8].x == 7 && points[8].y == 12 &&
        points[9].x == 7 && points[9].y == 10 &&
        points[10].x == 10 && points[10].y == 10 &&
        points[11].x == 10 && points[11].y == 0 &&
        points[12].x == 12 && points[12].y == 0 &&
        points[13].x == 12 && points[13].y == 8 &&
        points[14].x == 17 && points[14].y == 8 &&
        points[15].x == 17 && points[15].y == 6 &&
        points[16].x == 20 && points[16].y == 6 &&
        points[17].x == 20 && points[17].y == 0)
        printf("buildings2: True\n");
    else
        printf("buildings2: False\n");
}