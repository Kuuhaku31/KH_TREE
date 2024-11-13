
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

    Camera camera;
    camera.set_size(Vector2(GRAPH_WIDE, GRAPH_HIGH));
    camera.set_position(Vector2(0, 0));

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
            break;

            case 'c':
            {
                std::cout << "Move camera to where? (x y): ";
                int x, y;
                std::cin >> x >> y;
                camera.look_at(Vector2(x, y));
            }

            default:
            {
            }
            break;
        }

        ExMessage msg;

        bool is_roop = true;
        BeginBatchDraw();
        while(is_roop)
        {
            while(peekmessage(&msg))
            {
                switch(msg.message)
                {
                    case WM_KEYDOWN:
                    {
                        switch(msg.ch)
                        {
                            case VK_UP:
                            {
                                camera.set_position(camera.get_position() + Vector2(0, -10));
                            }
                            break;

                            case VK_DOWN:
                            {
                                camera.set_position(camera.get_position() + Vector2(0, 10));
                            }
                            break;

                            case VK_LEFT:
                            {
                                camera.set_position(camera.get_position() + Vector2(-10, 0));
                            }
                            break;

                            case VK_RIGHT:
                            {
                                camera.set_position(camera.get_position() + Vector2(10, 0));
                            }
                            break;

                            case 'P':
                            {
                                is_roop = false;
                            }

                            default:
                            {
                            }
                            break;
                        }
                    }
                    break;

                    default:
                    {
                    }
                    break;
                }
            }

            cleardevice();
            DrawTree(camera, Vector2(0, 0), root, 3000);
            FlushBatchDraw();
        }
        EndBatchDraw();

        std::cout << "Input command: ";
        std::cin >> ch;
    } while(ch != 'q');
    std::cout << "Bye!" << std::endl;

    closegraph();

    return 0;
}
