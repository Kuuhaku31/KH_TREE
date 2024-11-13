
#include "drawTree.h"

#define TREE_TYPE AVLTreeNode

int
main()
{
    TREE_TYPE* root = nullptr;
    int        a[]  = { 5, 3, 7, 2, 4, 6, 8 };
    for(int i = 0; i < 7; i++)
    {
        root = TREE_TYPE::Insert(a[i], root);
    }

    initgraph(GRAPH_WIDE, 600);
    setbkcolor(LIGHTGRAY);

    char ch = 0;
    do
    {
        switch(ch)
        {
            case 'e':
            {
                std::cout << "Sure to make empty? (y/n): ";
                char c;
                std::cin >> c;
                if(c == 'y')
                {
                    root = (TREE_TYPE*)TREE_TYPE::MakeEmpty(root);
                }
            }
            break;

            case 'f':
            {
                std::cout << "Input a number to find: ";
                int x;
                std::cin >> x;
                if(TREE_TYPE::Find(x, root))
                {
                    std::cout << "Find " << x << std::endl;
                }
                else
                {
                    std::cout << "Not find " << x << std::endl;
                }
            }
            break;

            case 'm':
            {
                std::cout << "The min number is " << TREE_TYPE::FindMin(root)->val << std::endl;
            }
            break;

            case 'M':
            {
                std::cout << "The max number is " << TREE_TYPE::FindMax(root)->val << std::endl;
            }
            break;

            case 'i':
            {
                std::cout << "Input a number to insert: ";
                int y;
                std::cin >> y;
                root = TREE_TYPE::Insert(y, root);
            }
            break;

            case 'd':
            {
                std::cout << "Input a number to delete: ";
                int z;
                std::cin >> z;
                root = TREE_TYPE::Delete(z, root);
            }
            break;

            case 'h':
            {
                int hight = TREE_TYPE::GetHight(root);
                std::cout << "The hight of the tree is " << hight << std::endl;
            }
            break;

            case 'r':
            {
                std::cout << "Sure to make random tree? (y/n): ";
                char c;
                std::cin >> c;
                if(c == 'y')
                {
                    std::cout << "Making random tree for how many times? ";
                    int count = 0;
                    std::cin >> count;
                    root = (TREE_TYPE*)TREE_TYPE::MakeEmpty(root);
                    for(int i = 0; i < count; i++)
                    {
                        int random = rand() % 1000;

                        root = TREE_TYPE::Insert(random, root);
                    }
                }
            }

            default:
            {
            }
            break;
        }

        cleardevice();
        DrawTree(root, GRAPH_WIDE / 2, 10, 0, GRAPH_WIDE);

        std::cin >> ch;
    } while(ch != 'q');
    std::cout << "Bye!" << std::endl;

    closegraph();

    return 0;
}
