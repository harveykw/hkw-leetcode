#include <vector>

struct ListNode {
  int val;
  ListNode* next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class Solution {
 public:
  /*
  The idea is to scan through the linked list and connect all nodes with a value
  next than x, then stitch the remaining nodes onto the end of that
  */

  /*
  Consider

  one linked list node -> seems ok
  nonexistent x
  x at extremities
  null access -> seems ok

  */
  ListNode* partition(ListNode* head, int x) {
    if (head == nullptr) return nullptr;

    // First we iterate through the entire linked list

    ListNode dummyHeadBefore{-1, nullptr};
    ListNode* newHeadBefore = &dummyHeadBefore;

    ListNode dummyHeadAfter{-1, nullptr};
    ListNode* newHeadAfter = &dummyHeadAfter;

    while (head != nullptr) {
      if (head->val < x) {
        newHeadBefore->next = head;
        newHeadBefore = newHeadBefore->next;
      } else {
        newHeadAfter->next = head;
        newHeadAfter = newHeadAfter->next;
      }
      head = head->next;
    }

    // Stitch middle
    newHeadBefore->next = dummyHeadAfter.next;
    // Close end
    newHeadAfter->next = nullptr;

    return dummyHeadBefore.next;
  }
};

int main(int argc, char* argv[]) {}