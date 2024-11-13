
#pragma once

#include "camera.h"

#include <graphics.h>
#include <iostream>

#define GRAPH_WIDE 2500
#define GRAPH_HIGH 600

struct TreeNode
{
    int       val;   // 节点的值
    TreeNode* left;  // 左子树
    TreeNode* right; // 右子树

    static int       GetHight(TreeNode* root);
    static TreeNode* MakeEmpty(TreeNode* root);
    static TreeNode* Find(int x, TreeNode* root);
    static TreeNode* FindMin(TreeNode* root);
    static TreeNode* FindMax(TreeNode* root);
    static TreeNode* Insert(int x, TreeNode* root);
    static TreeNode* Delete(int x, TreeNode* root);
};

struct AVLTreeNode : public TreeNode
{
    int hight; // 节点的高度

    static int          GetBalance(AVLTreeNode* root);
    static AVLTreeNode* LeftRotate(AVLTreeNode* root);
    static AVLTreeNode* RightRotate(AVLTreeNode* root);
    static AVLTreeNode* Insert(int x, AVLTreeNode* root);
    static AVLTreeNode* Delete(int x, AVLTreeNode* root);
};

void
DrawTree(const Camera& camera, const Vector2& pos, TreeNode* root, int tree_wide);
