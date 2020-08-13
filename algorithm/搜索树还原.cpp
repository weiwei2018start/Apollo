
/*
 题目地址：https://www.nowcoder.com/questionTerminal/4582efa5ffe949cc80c136eeb78795d6
题目描述
一棵二叉树原本是搜索二叉树，但是其中有两个节点调换了位置，使得这棵二叉树不再是搜索二叉树，请按升序输出这两个错误节点的值。(每个节点的值各不相同)
示例1
输入
{1,2,3}
输出
[1,2]
 
解题思路：
 1：找到出问题的两个节点(搜索树的中序遍历是一次增大的)
 2：交换两个节点的值
*/

struct TreeNode {
    int val;
    struct TreeNode *left;
struct TreeNode *right;
};

class Solution {
public:
    /**
     *
     * @param root TreeNode类 the root
     * @return int整型vector
     */
    TreeNode* pre = NULL;
    TreeNode* first = NULL;
    TreeNode* second = NULL;
    
    vector<int> findError(TreeNode* root) {
        dfs(root);
        vector<int> ret;
        ret.push_back(second->val);
        ret.push_back(first->val);
        
        return ret;
    }
    
    void dfs(TreeNode* root) {
        if (root == NULL) {
            return;
        }
        
        dfs(root->left);
        if (pre != NULL && root->val < pre->val) {
            if (first == NULL) {
                first = pre;
            }
            second = root;
        }
        pre = root;
        dfs(root->right);
    }
};
