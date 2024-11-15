
// graph.cpp

#include <iostream>

struct node
{
    int src;
    int dst;
    int weight;
};

class Graph
{
public:
    Graph(int vertices)
        : VERTICES(vertices)
    {
        matrix = new int*[vertices];
        for(int i = 0; i < vertices; i++)
        {
            matrix[i] = new int[vertices];
            for(int j = 0; j < vertices; j++)
            {
                matrix[i][j] = 0;
            }
        }
    }

    ~Graph()
    {
        for(int i = 0; i < VERTICES; i++)
        {
            delete[] matrix[i];
        }
        delete[] matrix;
    }

    bool
    IsInGraph(int src, int dest) const
    {
        if(src >= 0 && src < VERTICES && dest >= 0 && dest < VERTICES)
        {
            return true;
        }
        else
        {
            std::cout << "Invalid vertex: (" << src << ", " << dest << ")" << std::endl;
            return false;
        }
    }

    void
    AddEdge(int src, int dest, int weight)
    {
        if(IsInGraph(src, dest))
        {
            matrix[src][dest] = weight;
        }
    }

    void
    AddEdges(node* edges, int n)
    {
        for(int i = 0; i < n; i++)
        {
            AddEdge(edges[i].src, edges[i].dst, edges[i].weight);
        }
    }

    void
    RemoveEdge(int src, int dest)
    {
        if(IsInGraph(src, dest))
        {
            matrix[src][dest] = 0;
        }
    }

    int
    GetWeight(int src, int dest) const
    {
        if(IsInGraph(src, dest))
        {
            return matrix[src][dest];
        }
        else
        {
            return 0;
        }
    }

    void
    PrintGraph() const
    {
        using namespace std;

        cout << "Graph: " << VERTICES << " vertices" << endl;
        cout << "\\ ";
        for(int i = 0; i < VERTICES; i++)
        {
            cout << i << " ";
        }
        cout << endl;

        for(int i = 0; i < VERTICES; i++)
        {
            cout << i << " ";
            for(int j = 0; j < VERTICES; j++)
            {
                cout << matrix[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

public:
    const int VERTICES; // 顶点数

private:
    int** matrix; // 邻接矩阵
};

// 无权图
void
MakeWeightOne(Graph& g)
{
    for(int i = 0; i < g.VERTICES; i++)
    {
        for(int j = 0; j < g.VERTICES; j++)
        {
            if(g.GetWeight(i, j) != 0)
            {
                g.AddEdge(i, j, 1);
            }
        }
    }
}

// 拓扑排序
void
Topsort(const Graph& g)
{
    // 记录每个顶点的入度
    int* in_degree = new int[g.VERTICES];
    for(int i = 0; i < g.VERTICES; i++)
    {
        in_degree[i] = 0;
    }

    for(int i = 0; i < g.VERTICES; i++)
    {
        for(int j = 0; j < g.VERTICES; j++)
        {
            if(g.GetWeight(i, j) != 0)
            {
                in_degree[j]++;
            }
        }
    }

    // 队列
    int* queue = new int[g.VERTICES];
    int  front = 0, rear = 0; // 队列的头和尾

    // 将一个入度为 0 的顶点入队
    for(int i = 0; i < g.VERTICES; i++)
    {
        if(in_degree[i] == 0)
        {
            queue[rear++] = i;
        }
    }

    std::cout << "queue: ";

    // 依次输出入度为 0 的顶点，并将其邻接点的入度减 1
    int count = 0;
    while(front != rear)
    {
        int v = queue[front++];
        std::cout << v << " ";
        count++;

        // 将 v 的邻接点的入度减 1
        bool flag = true;
        for(int i = 0; i < g.VERTICES; i++)
        {
            // 如果 v 与 i 之间有边，则 i 的入度减 1
            if(g.GetWeight(v, i) != 0)
            {
                // 如果 i 的入度减 1 后为 0，则将 i 入队
                if(--in_degree[i] == 0)
                {
                    flag          = false;
                    queue[rear++] = i;
                }
            }
        }
    }

    // 如果输出的顶点数不等于图的顶点数，则图中有环
    if(count != g.VERTICES)
    {
        std::cout << "Graph has a cycle" << std::endl;
    }

    delete[] in_degree;
    delete[] queue;
}

int
main()
{
    Graph g(8);

    node nodes[] = {
        { 1, 2, 6 },
        { 4, 3, 2 },
        { 1, 3, 2 },
        { 1, 4, 1 },
        { 2, 4, 3 },
        { 5, 4, 3 },
        { 2, 5, 4 },
        { 3, 6, 5 },
        { 4, 6, 7 },
        { 7, 6, 2 },
        { 4, 7, 3 },
        { 5, 7, 8 }
    };
    int node_count = sizeof(nodes) / sizeof(node);

    g.AddEdges(nodes, node_count);

    g.PrintGraph();

    Topsort(g);

    return 0;
}
