/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* middleNode(ListNode* head) {
        int size = 0;
        ListNode* node = head;
        while(node != nullptr) {
            node = node->next;
            ++size;
        }
        
        size >>= 1;
        
        node = head;
        while(size--) {
            node = node->next;
        }
        return node;
    }
};
