
// DECLARATION OF THE NODE
template <typename elemType>
struct Node {
    elemType info;
    Node<elemType> *left;
    Node<elemType> *right;
};

// DECLARATION OF THE CLASS
template <typename elemType>
class BinaryTree {

    public:
        BinaryTree();
        ~BinaryTree();
        BinaryTree(const BinaryTree<elemType>& otherTree);
        const BinaryTree<elemType>& operator=(const BinaryTree<elemType>&);
        bool isEmpty();

        void inorderTraversal() const;
        void preorderTraversal() const;
        void postorderTraversal() const;

        int treeHeight() const;
        int treeNodeCount() const;
        int treeLeavesCount() const;
        void destroyTree(); // postcondition: root = nullptr;

    protected:
     Node<elemType> *root;

    private:
        void copyTree(BinaryTree<elemType>* &copiedTreeRoot, BinaryTree<elemType>* &otherTreeRoot);
        void destroy(Node<elemType>*& p); // postcondition: p = nullptr;
        void inorder(Node<elemType>* p) const;
        void preorder(Node<elemType>* p) const;
        void postorder(Node<elemType>* p) const;
        int max(int x, int y) const;  // returns the larger of x and y
        int height(Node<elemType>* p) const;
        int nodeCount(Node<elemType>* p) const;
        int leavesCount(Node<elemType>* p) const;
       
};

// DEFINITION OF THE FUNCTIONS

template <typename elemType> BinaryTree<elemType>::BinaryTree() {
    root = nullptr;
}

template <typename elemType>
void BinaryTree<elemType>::inorderTraversal() const {
    inorder(root);
}

template <typename elemType>
void BinaryTree<elemType>::preorderTraversal() const {
    preorder(root);
}

template <typename elemType>
void BinaryTree<elemType>::postorderTraversal() const {
    postorder(root);
}

template <typename elemType>
void BinaryTree<elemType>::inorder(Node<elemType>* node) const {
    if(node){
        inorder(node->left);
        std::cout << node->info << " ";
        inorder(node->right);
    }
}

template <typename elemType>
void BinaryTree<elemType>::preorder(Node<elemType>* node) const {
    if(node){
        std::cout << node->info << " ";
        preorder(node->left);
        preorder(node->right);
    }
}

template <typename elemType>
void BinaryTree<elemType>::postorder(Node<elemType>* node) const {
    if(node){
        postorder(node->left);
        postorder(node->right);
        std::cout << node->info << " ";
    }
}

int main(){

    BinaryTree<int> tree;
    

}