#include <iostream>
#include <unordered_set>
#include <vector>

using std::vector, std::unordered_set;

struct ListNode {
  int val;
  ListNode* next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class Solution {
 public:
  ListNode* deleteDuplicates(ListNode* head) {
    if (head == nullptr) return nullptr;

    ListNode* left = nullptr;
    ListNode* dummyHead = head;
    // Iterate Linked list, update left right before reaching new number

    int currentNumber{-999};

    while (dummyHead != nullptr) {
      // Walks to the end looking for the next unique linked list node, and
      // stitches left to the unique one, if one is found. Does nothing if not
      // found
      if (dummyHead->val == currentNumber) {
        while (dummyHead != nullptr) {
          if (dummyHead->val != currentNumber) {
            // Stitch left
            if (left == nullptr) {
              head = dummyHead;
            } else {
              left->next = dummyHead;
              currentNumber = dummyHead->val;
            }
            break;
          }

          dummyHead = dummyHead->next;
        }
      }
      if (dummyHead == nullptr) {
        if (left == nullptr) return nullptr;
        left->next = nullptr;
        return head;
      }

      currentNumber = dummyHead->val;

      if (dummyHead->next != nullptr) {
        if (dummyHead->next->val != currentNumber) left = dummyHead;
      }

      dummyHead = dummyHead->next;
    }
    return head;
  }
};

int main(int argc, char* argv[]) {}