#include <iostream>
#include <functional>

template <typename T>
class BinaryTree {
public:
    class TreeNode;
    BinaryTree(): head_(nullptr) {
        callBack_ = [](TreeNode* node) {
            std::cout<< "," << node->value_;
        };
    }
     ~BinaryTree(){
        auto current = head_;
        std::cout << "delete function" << current->value_;
    }
    void AddNode(const T& x) {
        TreeNode* newNode = new TreeNode(x);
        if (head_ == nullptr) {
            head_ = newNode;
        } else {
            auto current = &head_;
            while((*current) != nullptr) {
                if ((*current)->value_ < x) {
                    current = &((*current)->Right_);
                } else {
                    current = &((*current)->Left_);
                }
            }
            *current = newNode;
        }
    }
    void Preorder(TreeNode* root) {
        if (root != nullptr) {
            callBack_(root);
            Preorder(root->Left_);
            Preorder(root->Right_);
        }
    }
    void Inorder(TreeNode* root) {
        if (root != nullptr) {
            Inorder(root->Left_);
            callBack_(root);
            Inorder(root->Right_);
        }
    }

    void Postorder(TreeNode* root) {
        if (root != nullptr) {
            Postorder(root->Left_);
            Postorder(root->Right_);
            callBack_(root);
        }
    }

    TreeNode* RootNode() {
        return head_;
    } 
private:
    TreeNode* head_;
    std::function<void (TreeNode* node)> callBack_;
};

template <typename T>
class BinaryTree<T>::TreeNode {
public:
    T value_;
    TreeNode* Left_;
    TreeNode* Right_;
    TreeNode(T x) : value_(x), Left_(nullptr), Right_(nullptr) {}
};

int main() {
    BinaryTree<int> a;
    a.AddNode(5);
    a.AddNode(6);
    a.AddNode(4);
    a.AddNode(7);
    a.AddNode(3);
    a.Postorder( a.RootNode());
}