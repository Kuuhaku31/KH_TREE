
#include "drawTree.h"

#include <random>
#include <vector>

// 获取树的高度
int
TreeNode::GetHight(TreeNode* root)
{
    if(root == nullptr)
    {
        return -1;
    }
    else
    {
        return std::max(GetHight(root->left), GetHight(root->right)) + 1;
    }
}

// 清空二叉树
TreeNode*
TreeNode::MakeEmpty(TreeNode* root)
{
    if(root != nullptr)
    {
        MakeEmpty(root->left);
        MakeEmpty(root->right);
        delete root;
    }
    return nullptr;
}

// 查询
TreeNode*
TreeNode::Find(int x, TreeNode* root)
{
    if(root == nullptr)
    {
        return nullptr;
    }
    if(x < root->val)
    {
        return Find(x, root->left);
    }
    else if(x > root->val)
    {
        return Find(x, root->right);
    }
    else
    {
        return root;
    }
}

// 查找最小值
TreeNode*
TreeNode::FindMin(TreeNode* root)
{
    if(root == nullptr)
    {
        return nullptr;
    }
    else if(root->left == nullptr)
    {
        return root;
    }
    else
    {
        return FindMin(root->left);
    }
}

// 查找最大值
TreeNode*
TreeNode::FindMax(TreeNode* root)
{
    if(root != nullptr)
    {
        while(root->right != nullptr)
        {
            root = root->right;
        }
    }
    return root;
}

// 插入
TreeNode*
TreeNode::Insert(int x, TreeNode* root)
{
    if(root == nullptr)
    {
        root = new TreeNode;
        if(root == nullptr)
        {
            std::cerr << "Out of space!" << std::endl;
            exit(1);
        }
        else
        {
            root->val   = x;
            root->left  = nullptr;
            root->right = nullptr;
        }
    }
    else if(x < root->val)
    {
        root->left = Insert(x, root->left);
    }
    else if(x > root->val)
    {
        root->right = Insert(x, root->right);
    }
    return root;
}

// 删除
TreeNode*
TreeNode::Delete(int x, TreeNode* root)
{
    TreeNode* tmpCell;

    if(root == nullptr)
    {
        std::cerr << "Element not found" << std::endl;
    }
    else if(x < root->val)
    {
        root->left = Delete(x, root->left);
    }
    else if(x > root->val)
    {
        root->right = Delete(x, root->right);
    }
    else if(root->left && root->right)
    {
        tmpCell     = FindMin(root->right);
        root->val   = tmpCell->val;
        root->right = Delete(root->val, root->right);
    }
    else
    {
        tmpCell = root;
        if(root->left == nullptr)
        {
            root = root->right;
        }
        else if(root->right == nullptr)
        {
            root = root->left;
        }
        delete tmpCell;
    }
    return root;
}
