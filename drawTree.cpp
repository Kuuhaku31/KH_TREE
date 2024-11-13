
#include "drawTree.h"

void
DrawTree(const Camera& camera, const Vector2& pos, TreeNode* root, int tree_wide)
{
    static int current_deep = 0;

    if(root == nullptr)
    {
        return;
    }

    int leafdistance = 50;

    int dy = 20;
    int dx = tree_wide / 4;
    for(int i = 0; i < current_deep; i++)
    {
        dx /= 2;
    }

    bool is_show_text = true;
    int  text_size    = 20;
    for(int i = 0; i < current_deep; i++)
    {
        text_size -= 2;

        if(text_size < 8)
        {
            is_show_text = false;
            break;
        }
    }

    Vector2 left_child_pos  = pos + Vector2(-dx, dy);
    Vector2 right_child_pos = pos + Vector2(dx, dy);

    Vector2 screen_this_pos        = camera.tanslate(pos);
    Vector2 screen_left_child_pos  = camera.tanslate(left_child_pos);
    Vector2 screen_right_child_pos = camera.tanslate(right_child_pos);

    if(root->left != nullptr)
    {
        line(screen_this_pos.vx, screen_this_pos.vy, screen_left_child_pos.vx, screen_left_child_pos.vy);

        current_deep++;
        DrawTree(camera, left_child_pos, root->left, tree_wide);
        current_deep--;
    }
    if(root->right != nullptr)
    {
        line(screen_this_pos.vx, screen_this_pos.vy, screen_right_child_pos.vx, screen_right_child_pos.vy);

        current_deep++;
        DrawTree(camera, right_child_pos, root->right, tree_wide);
        current_deep--;
    }

    if(is_show_text)
    {
        settextstyle(text_size, 0, _T("宋体")); // 设置文字样式
        setcolor(BLACK);                        // 设置文字颜色
        setbkmode(OPAQUE);                      // 背景不透明
        char str[10];
        sprintf(str, "%d", root->val);
        // outtextxy(screen_this_pos.vx, screen_this_pos.vy, (LPTSTR)str);

        // 居中显示
        int text_wide = textwidth((LPTSTR)str);
        int text_high = textheight((LPTSTR)str);
        outtextxy(screen_this_pos.vx - text_wide / 2, screen_this_pos.vy - text_high / 2, (LPTSTR)str);
    }
}
