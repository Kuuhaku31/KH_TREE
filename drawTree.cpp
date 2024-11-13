
#include "drawTree.h"

void
DrawTree(TreeNode* root, int x, int y, int current_hight, int tree_wide)
{
    if(root == nullptr)
    {
        return;
    }

    // 设置文字样式
    settextstyle(12, 0, _T("宋体"));
    setcolor(BLACK);
    setbkmode(OPAQUE); // 背景不透明

    int leafdistance = 50;

    int dy = 20;
    int dx = tree_wide / 4;
    for(int i = 0; i < current_hight; i++)
    {
        dx /= 2;
    }

    if(root->left != nullptr)
    {
        line(x, y, x - dx, y + dy);
        DrawTree(root->left, x - dx, y + dy, current_hight + 1, tree_wide);
    }
    if(root->right != nullptr)
    {
        line(x, y, x + dx, y + dy);
        DrawTree(root->right, x + dx, y + dy, current_hight + 1, tree_wide);
    }

    char str[10];
    sprintf(str, "%d", root->val);
    outtextxy(x - 5, y - 5, (LPCTSTR)str);
}
