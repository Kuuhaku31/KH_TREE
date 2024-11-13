
// avl_tree.cpp

#include "drawTree.h"

int
AVLTreeNode::GetBalance(AVLTreeNode* root)
{
    if(root == nullptr)
    {
        return 0;
    }
    else
    {
        return GetHight((AVLTreeNode*)(root->left)) - GetHight((AVLTreeNode*)(root->right));
    }
}

AVLTreeNode*
AVLTreeNode::LeftRotate(AVLTreeNode* root)
{
    AVLTreeNode* tmp = (AVLTreeNode*)(root->right);
    root->right      = tmp->left;
    tmp->left        = root;

    root->hight = std::max(GetHight((AVLTreeNode*)(root->left)), GetHight((AVLTreeNode*)(root->right))) + 1;
    tmp->hight  = std::max(GetHight((AVLTreeNode*)(tmp->left)), GetHight((AVLTreeNode*)(tmp->right))) + 1;

    return tmp;
}

AVLTreeNode*
AVLTreeNode::RightRotate(AVLTreeNode* root)
{
    AVLTreeNode* tmp = (AVLTreeNode*)(root->left);
    root->left       = tmp->right;
    tmp->right       = root;

    root->hight = std::max(GetHight((AVLTreeNode*)(root->left)), GetHight((AVLTreeNode*)(root->right))) + 1;
    tmp->hight  = std::max(GetHight((AVLTreeNode*)(tmp->left)), GetHight((AVLTreeNode*)(tmp->right))) + 1;

    return tmp;
}

AVLTreeNode*
AVLTreeNode::Insert(int x, AVLTreeNode* root)
{
    if(root == nullptr)
    {
        root = new AVLTreeNode;
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
            root->hight = 0;
        }
    }
    else if(x < root->val)
    {
        root->left = Insert(x, (AVLTreeNode*)(root->left));
        if(GetBalance(root) == 2)
        {
            if(x < root->left->val)
            {
                root = RightRotate(root);
            }
            else
            {
                root->left = LeftRotate((AVLTreeNode*)(root->left));
                root       = RightRotate(root);
            }
        }
    }
    else if(x > root->val)
    {
        root->right = Insert(x, (AVLTreeNode*)(root->right));
        if(GetBalance(root) == -2)
        {
            if(x > root->right->val)
            {
                root = LeftRotate(root);
            }
            else
            {
                root->right = RightRotate((AVLTreeNode*)(root->right));
                root        = LeftRotate(root);
            }
        }
    }

    root->hight = std::max(GetHight((AVLTreeNode*)(root->left)), GetHight((AVLTreeNode*)(root->right))) + 1;

    return root;
}

AVLTreeNode*
AVLTreeNode::Delete(int x, AVLTreeNode* root)
{
    if(root == nullptr)
    {
        return nullptr;
    }
    else if(x < root->val)
    {
        root->left = Delete(x, (AVLTreeNode*)(root->left));
        if(GetBalance(root) == -2)
        {
            if(GetBalance((AVLTreeNode*)(root->right)) <= 0)
            {
                root = LeftRotate(root);
            }
            else
            {
                root->right = RightRotate((AVLTreeNode*)(root->right));
                root        = LeftRotate(root);
            }
        }
    }
    else if(x > root->val)
    {
        root->right = Delete(x, (AVLTreeNode*)(root->right));
        if(GetBalance(root) == 2)
        {
            if(GetBalance((AVLTreeNode*)(root->left)) >= 0)
            {
                root = RightRotate(root);
            }
            else
            {
                root->left = LeftRotate((AVLTreeNode*)(root->left));
                root       = RightRotate(root);
            }
        }
    }
    else if(root->left && root->right)
    {
        AVLTreeNode* tmp = (AVLTreeNode*)FindMin((AVLTreeNode*)(root->right));
        root->val        = tmp->val;
        root->right      = Delete(root->val, (AVLTreeNode*)(root->right));
        if(GetBalance(root) == 2)
        {
            if(GetBalance((AVLTreeNode*)(root->left)) >= 0)
            {
                root = RightRotate(root);
            }
            else
            {
                root->left = LeftRotate((AVLTreeNode*)(root->left));
                root       = RightRotate(root);
            }
        }
    }
    else
    {
        AVLTreeNode* tmp = (AVLTreeNode*)root;
        if(root->left == nullptr)
        {
            root = (AVLTreeNode*)(root->right);
        }
        else if(root->right == nullptr)
        {
            root = (AVLTreeNode*)(root->left);
        }
        delete tmp;
    }

    return root;
}
