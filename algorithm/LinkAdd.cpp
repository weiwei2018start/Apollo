/*
题目描述
给定两个代表非负数的链表，数字在链表中是反向存储的（链表头结点处的数字是个位数，第二个结点上的数字是十位数...），求这个两个数的和，结果也用链表表示。
输入：(2 -> 4 -> 3) + (5 -> 6 -> 4)
输出： 7 -> 0 -> 8
*/

/**
 * struct ListNode {
 *	int val;
 *	struct ListNode *next;
 * };
 */

class Solution {
public:
    /**
     * 
     * @param l1 ListNode类 
     * @param l2 ListNode类 
     * @return ListNode类
     */
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        if (l1 == NULL) {
            return l2;
        }
        if (l2 == NULL){
            return l1;
        }
        
        int upNuber = 0;
        ListNode *head = new ListNode(-1);
        ListNode *pHead = head;
        
        while (l1 != NULL || l2 != NULL || upNuber != 0) {
            if (l1) {
                upNuber += l1->val;
                l1 = l1->next;
            }
            if (l2) {
                upNuber += l2->val;
                l2 = l2->next;
            }
            ListNode *newNode = new ListNode(upNuber%10);
            upNuber = upNuber / 10;
            pHead->next = newNode;
            pHead = pHead->next;
        }
        
        return head->next;
    }
};
