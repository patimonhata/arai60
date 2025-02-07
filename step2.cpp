/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    bool hasCycle(ListNode *head) {
        ListNode *slow_ptr = head;
        ListNode *fast_ptr = head;
        
        if (head == NULL) return false; 
        //論理の「ならば」と同様に考えるのならば true とするのが望ましい？

        while (fast_ptr != NULL) {
            if (fast_ptr->next == NULL) break;

            slow_ptr = slow_ptr->next;
            fast_ptr = fast_ptr->next->next;
            
            if (fast_ptr == slow_ptr) return true; //if there is a cycle
        }
        
        return false;
    }
};
