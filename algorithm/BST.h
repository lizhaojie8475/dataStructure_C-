#ifndef __BST_H__
#define __BST_H__

#include<iostream>
using namespace std;

template<typename Elem>
class BST{
    struct TreeNode{
        Elem val;
        TreeNode* left, right;
        TreeNode(Elem e): val(e), left(nullptr), right(nullptr){}
    };
    TreeNode* root;
    bool findTarget(Elem target, TreeNode* root_node){
        if(root_node == nullptr)
            return false;
        if(root_node->val == target)
            return true;
        else if(target < root_node->val)
            return (target, root_node->left);
        else
            return (target, root_node->right);
    }
    TreeNode* insertBST(TreeNode* root_node, Elem val) {
        // 找到空位置插入新节点
        if (root_node == nullptr) return new TreeNode(val);
        
        if (root_node->val < val) 
            root_node->right = insertIntoBST(root->right, val);
        if (root_node->val > val) 
            root_node->left = insertIntoBST(root->left, val);
        return root_node;
    }
    TreeNode* getMin(TreeNode* node) {
        // BST 最左边的就是最小的
        while (node->left != nullptr) node = node->left;
        return node;
    }
    TreeNode* deleteNode(Elem val, TreeNode* root_node);

public:
    BST(): root(new TreeNode(0)){}
    BST(TreeNode* node): root(node){}
    static bool isBST(TreeNode* root_node, Elem min, Elem max){
        if(root_node == nullptr)
            return true;
        else if((min != nullptr && min > root_node->val) || (max != nullptr && max < root_node->val))
            return false;
        
        return isBST(root_node->left, min, root_node->val) && isBST(root_node->right, root_node->val, max);
    }

    bool findTarget(Elem target){
        return findTarget(target, root);
    }
    void insertNode(Elem val){
        this->root = insertBST(this->root, val);
    };
    void deleteNode(Elem val){
        this->root = deleteNode(val, this->root);
    }
    
};

template<typename Elem>
typename BST<Elem>::TreeNode* BST<Elem>::deleteNode(Elem val, TreeNode* root_node){
    if (root_node == nullptr) return nullptr;
    if (root_node->val == val) {
        // 如果要删除的节点没有左右任何一个子节点，都返回他的另一个有的子节点来代替他。当然如果两个都没有，就返回null
        if (root_node->left == nullptr) return root_node->right;
        if (root_node->right == nullptr) return root_node->left;
        // 如果这个节点左右子节点都有，就用右子树的最小节点或者左子树的最大节点来代替他。
        TreeNode* minNode = getMin(root_node->right);
        minNode->left = root_node->left;
        minNode->right = deleteNode(root_node->right, minNode->val);
        root_node = minNode;
    } else if (root_node->val > val) {
        root_node->left = deleteNode(root_node->left, val);
    } else if (root_node->val < val) {
        root_node->right = deleteNode(root_node->right, val);
    }
    return root_node;
}




#endif