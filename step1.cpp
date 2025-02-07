C++

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
        std::vector<int> val_already_used;
        int current_val;
        bool used;
        ListNode *current_ptr = head;

        while (current_ptr != NULL) {
            current_val = current_ptr->val;

            used = ( std::find(val_already_used.begin(), val_already_used.end(), current_val) != std::end(val_already_used) );
            if ( used == true) {
                return true;
            }

            val_already_used.push_back(current_val);
            current_ptr = current_ptr->next;
        }

        return false;

        
    }
};
