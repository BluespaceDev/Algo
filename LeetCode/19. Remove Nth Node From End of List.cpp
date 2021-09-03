class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        int size = 0;
        ListNode* node = head;
        while(node != nullptr) {
            node = node->next;
            ++size;
        }
        
        size -= n;
        if (size == 0)
            return head->next;
        
        node = head;
        for (int i = 1; i < size; ++i)
            node = node->next;
        
        node->next = node->next->next;
        return head;
    }
};
