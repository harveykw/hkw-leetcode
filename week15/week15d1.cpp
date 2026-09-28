#include <iostream>
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
  ListNode* rotateRight(ListNode* head, int k) {
    if (head == nullptr) return nullptr;

    int length{0};
    // Traverse linked list once to get the length
    ListNode* dummyHead = head;
    while (dummyHead != nullptr) {
      length++;
      dummyHead = dummyHead->next;
    }

    k = k % length;
    if (length == 1 || k == 0) return head;

    // Traverse linked list to k + 1, then stitch k + 1 nodes to the end from
    // the head. We save the original head
    ListNode* originalHead = head;

    // we advance head to the new head
    for (int i{0}; i < length - k; i++) {
      head = head->next;
    }

    // we advance to the end of the linked list
    dummyHead = head;
    while (dummyHead->next != nullptr) {
      dummyHead = dummyHead->next;
    }

    /*
    Note contiguous nodes are already stitched, there is no need to stitch every
    single one. I just need traverse to the end.

    */
    // stitch k+1 nodes to the end
    for (int i{0}; i < length - k; i++) {
      dummyHead->next = originalHead;
      originalHead = originalHead->next;
      dummyHead = dummyHead->next;
    }
    dummyHead->next = nullptr;

    return head;
  }
};

int main(int argc, char* argv[]) {}