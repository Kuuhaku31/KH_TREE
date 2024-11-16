
// graph.cpp

#include <iomanip>
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

    std::cout << std::endl;

    // 如果输出的顶点数不等于图的顶点数，则图中有环
    if(count != g.VERTICES)
    {
        std::cout << "Graph has a cycle" << std::endl;
    }

    delete[] in_degree;
    delete[] queue;
}

int**
NewTable(const Graph& graph)
{
    const int COLUMNS = 3;

    int** table = new int*[graph.VERTICES];
    for(int i = 0; i < graph.VERTICES; i++)
    {
        table[i]    = new int[COLUMNS];
        table[i][0] = 0;  // 顶点是否被访问
        table[i][1] = -1; // 顶点的距离，-1 表示无穷大
        table[i][2] = 0;  // 顶点的前驱顶点
    }

    return table;
}

void
PrintTable(int** table, int rows)
{
    const int COLUMNS = 3;
    const int WIDTH   = 3; // 设置每个字段的宽度

    for(int i = 0; i < rows; i++)
    {
        std::cout << std::setw(2) << i << ": "; // 设置行号的宽度
        for(int j = 0; j < COLUMNS; j++)
        {
            std::cout << std::setw(WIDTH) << table[i][j] << " "; // 设置每个字段的宽度
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;
}

void
FreeTable(int** table, int rows)
{
    for(int i = 0; i < rows; i++)
    {
        delete[] table[i];
    }
    delete[] table;
}

void
UnweightedShortestPath(const Graph& graph, int start)
{
    int** table = NewTable(graph);

    table[start][1] = 0; // 起点的距离为 0

    // 从起点开始，距离为 0
    // vert_count 表示顶点的个数，即距离的最大可能值
    for(int curr_dist = 0; curr_dist < graph.VERTICES; curr_dist++)
    {
        // 对于每个顶点
        for(int this_vert = 0; this_vert < graph.VERTICES; this_vert++)
        {
            // 如果顶点没有被访问，且距离为 curr_dist
            if(!table[this_vert][0] && table[this_vert][1] == curr_dist)
            {
                table[this_vert][0] = 1; // 标记为已访问

                // 遍历与顶点 i 相邻的顶点
                for(int next_vert = 0; next_vert < graph.VERTICES; next_vert++)
                {
                    // 如果顶点 i 与顶点 j 之间有边
                    if(graph.GetWeight(this_vert, next_vert) != 0)
                    {
                        // 如果顶点 j 的距离为无穷大
                        if(table[next_vert][1] == -1)
                        {
                            table[next_vert][1] = curr_dist + 1; // 更新距离
                            table[next_vert][2] = this_vert;     // 更新前驱顶点
                        }
                    }
                }
            }
        }
        PrintTable(table, graph.VERTICES);
    }

    PrintTable(table, graph.VERTICES);

    FreeTable(table, graph.VERTICES);
}

void
UnweightedShortestPath_A(const Graph& graph, int start)
{
    int** table = NewTable(graph);

    table[start][1] = 0; // 起点的距离为 0

    int* queue = new int[graph.VERTICES];
    int  front = 0, rear = 0;

    queue[rear++] = start; // 将起点入队

    // 只要队列不为空
    while(front != rear)
    {
        int this_vert = queue[front++]; // 出队

        table[this_vert][0] = 1; // 标记为已访问（可以不需要）

        // 遍历与顶点 i 相邻的顶点
        for(int next_vert = 0; next_vert < graph.VERTICES; next_vert++)
        {
            // 如果顶点 i 与顶点 j 之间有边
            if(graph.GetWeight(this_vert, next_vert) != 0)
            {
                // 如果顶点 j 的距离为无穷大
                if(table[next_vert][1] == -1)
                {
                    table[next_vert][1] = table[this_vert][1] + 1; // 更新距离
                    table[next_vert][2] = this_vert;               // 更新前驱顶点
                    queue[rear++]       = next_vert;               // 入队
                }
            }
        }

        PrintTable(table, graph.VERTICES);
    }

    PrintTable(table, graph.VERTICES);

    delete[] queue;

    FreeTable(table, graph.VERTICES);
}

int
main()
{
    Graph g(8);

    node nodes[] = {
        { 3, 1, 1 },
        { 1, 2, 6 },
        { 4, 3, 2 },
        { 1, 4, 1 },
        { 2, 4, 3 },
        { 2, 5, 4 },
        { 4, 5, 4 },
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

    UnweightedShortestPath_A(g, 3);

    return 0;
}
