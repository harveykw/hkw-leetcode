#include <iostream>
#include <stack>
#include <vector>

using std::vector, std::stack;

struct ListNode {
  int val;
  ListNode* next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class Solution {
 public:
  ListNode* removeNthFromEnd(ListNode* head, int n) {
    if (head == nullptr) return nullptr;

    vector<ListNode*> listVec{};
    ListNode* dummyHead = head;

    while (dummyHead != nullptr) {
      listVec.push_back(dummyHead);
      dummyHead = dummyHead->next;
    }

    int count = listVec.size();
    int indexOfRemoval = count - n;

    // At head
    if (indexOfRemoval == 0) {
      head = head->next;
      return head;
    }
    // At tail
    if (indexOfRemoval == count - 1) {
      listVec.at(count - 2)->next = nullptr;
      return head;
    }

    // General case
    listVec.at(indexOfRemoval - 1)->next = listVec.at(indexOfRemoval + 1);
    return head;
  }

  ListNode* reverseBetween(ListNode* head, int left, int right) {
    if (head == nullptr) return nullptr;

    stack<ListNode*> nodeStack{};
    ListNode* iterHead = head;
    ListNode* leftNode = nullptr;

    int currentPosition{1};  // Position is one indexed
    while (iterHead != nullptr) {
      if (currentPosition == left) {
        // Add reversible range to stack
        ListNode* dummyHead = iterHead;
        while (currentPosition <= right) {
          nodeStack.push(dummyHead);
          currentPosition++;
          dummyHead = dummyHead->next;
        }

        // Stitch nodes from stack onto left of range and right of range
        while (!nodeStack.empty()) {
          // Consider the case where the head is part of the reversible range.
          if (leftNode == nullptr) {
            leftNode = nodeStack.top();
            nodeStack.pop();
            head = leftNode;

          } else {
            leftNode->next = nodeStack.top();
            nodeStack.pop();
            leftNode = leftNode->next;
          }
        }
        leftNode->next = dummyHead;
        return head;
      }

      // get next position and save current node if next is start of reversible
      // range
      currentPosition++;
      if (currentPosition == left) {
        leftNode = iterHead;
      }

      // advance to next
      iterHead = iterHead->next;
    }

    // We shouldnt reach this point if there was a valid range given
    return head;
  }
};

int main(int argc, char* argv[]) {}