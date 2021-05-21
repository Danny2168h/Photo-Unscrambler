#include "chain.h"
#include <cmath>
#include <iostream>


// PA1 functions

/**
 * Destroys the current Chain. This function should ensure that
 * memory does not leak on destruction of a chain.
 */
Chain::~Chain() {
  clear();
}
 
/**
 * Inserts a new node after the node pointed to by p in the
 * chain (so p->next is the new node) and returns a pointer to
 * the newly created node.
 * If p is NULL, inserts a new head node to the chain.
 * This function **SHOULD** create a new Node and increase length_.
 *
 * @param p = The new node should be pointed to by p->next.
 *            If p is NULL, the new node becomes the head of the chain.
 * @param ndata = The data to be inserted.
 */
Chain::Node * Chain::insertAfter(Node * p, const Block &ndata) {
  if (p != NULL) {
    if (p->next == NULL) {
      length_++;
      Node * newNode = new Node(ndata);
      p->next = newNode;
      newNode->prev = p;
      return newNode;
    } else {
      length_++;
      Node * newNode = new Node(ndata);
      Node * pNextNode = p->next;
      p->next->prev = newNode;
      p->next = newNode;
      newNode->next = pNextNode;
      newNode->prev = p;
      return newNode;
    }
  } else if (head_ != NULL){
    length_++;
    Node * newNode = new Node(ndata);
    head_->next->prev = newNode;
    newNode->next = head_;
    head_ = newNode;
    return newNode;
  } else {
    length_++;
    Node * newNode = new Node(ndata);
    head_ = newNode;
    return head_;
  }
}
 
/**
 * Swaps the position in the chain of the two nodes pointed to
 * by p and q.
 * If p or q is NULL or p==q, do nothing.
 * Change the chain's head pointer if necessary.
 */
void Chain::swap(Node *p, Node *q) {
  if (p != NULL && q != NULL && p != q) {
     Node* pPrev = p->prev;
     Node* pNext = p->next;
     Node* qPrev = q->prev;
     Node* qNext = q->next;

     if (p -> next == q) {
       if (p -> prev == NULL && q -> next == NULL) {
         p -> next = NULL;
         q -> prev = NULL;
         q -> next = p;
         p -> prev = q;
         head_ = q;
         } else if (q -> next == NULL) {
          p -> prev = q;
          q -> prev = pPrev;
          pPrev -> next = q;
          p -> next = NULL;
          q -> next = p;
          } else if (p -> prev == NULL) {
            head_ = q;
            p->prev = q;
            p -> next = qNext;
            qNext -> prev = p;
            q -> next = p;
            q -> prev = pPrev;
            } else {
              p -> prev = q;
              q -> prev = pPrev;
              qNext -> prev = p;
              pPrev -> next = q;
              p -> next = qNext;
              q -> next = p;
            }
     } else if (q -> next == p) {
       if (q -> prev == NULL && p -> next == NULL) {
         q -> next = NULL;
         p -> prev = NULL;
         p -> next = q;
         q -> prev = p;
         head_ = p;
       } else if (p -> next == NULL) {
         q -> prev = p;
         p -> prev = qPrev;
         qPrev -> next = p;
         q -> next = pNext;
         p -> next = q;
         } else if (q -> prev == NULL) {
           head_ = p;
           q->prev = p;
           q -> next = pNext;
           pNext -> prev = q;
           p -> next = q;
           p -> prev = qPrev;
           } else {
             q -> prev = p;
             p -> prev = qPrev;
             pNext -> prev = q;
             qPrev -> next = p;
             q -> next = pNext;
             p -> next = q;
           }
     } else if (q -> prev == NULL && p -> next == NULL) {
       head_ = p;
       pPrev -> next = q;
       q -> next = pNext;
       p -> next = qNext;
       p -> prev = NULL;
       qNext -> prev = p;
       q -> prev = pPrev;
       } else if (p -> prev == NULL && q -> next == NULL) {
         head_ = q;
       qPrev -> next = p;
       p -> next = NULL;
       q -> next = pNext;
       q -> prev = NULL;
       pNext -> prev = q;
       p -> prev = qPrev; 
         } else if (p-> prev == NULL) {
           head_ = q;
           p -> next = qNext;
           qPrev -> next = p;
           qNext -> prev = p;
           p -> prev = qPrev;
           pNext -> prev = q;
           q -> next = pNext;
           q->prev = NULL;
           } else if (q -> prev == NULL) {
             head_ = p;
           q -> next = pNext;
           pPrev -> next = q;
           pNext -> prev = q;
           q -> prev = pPrev;
           qNext -> prev = p;
           p -> next = qNext;
           p->prev = NULL;
     } else if (q -> next == NULL) {
       p->prev = qPrev;
       p->next = NULL;
       qPrev->next = p;

       q->prev = pPrev;
       q->next = pNext;
       pPrev->next = q;
       pNext->prev = q;
     } else if (p -> next == NULL) {
       q->prev = pPrev;
       q->next = pNext;
       pPrev->next = q;

       p->prev = qPrev;
       p->next = qNext;
       qPrev->next = p;
       qNext->prev = p;
     } else {
       p->prev = qPrev;
       p->next = qNext;
       qPrev->next = p;
       qNext->prev = p;

       q->prev = pPrev;
       q->next = pNext;
       pPrev->next = q;
       pNext->prev = q;
     }
  }
}
 
/**
 * Destroys all dynamically allocated memory associated with the
 * current Chain class.
 */
void Chain::clear() {
  while (head_ != NULL) {
    Node* h0 = head_ -> next;
    delete head_;
    head_ = h0;
  }
}
 
/**
 * Makes the current object into a copy of the parameter:
 * All member variables should have the same value as
 * those of other, but the memory should be completely
 * independent. This function is used in both the copy
 * constructor and the assignment operator for Chains.
 */
void Chain::copy(Chain const &other) {
  length_ = other.size();
  if (other.empty()) {
    head_ = NULL;
    return;
  }
  Node * otherHead = other.head_;
  Node * newHead = new Node(otherHead->data);
  newHead->prev = NULL;
  newHead->next = copyHelper(newHead, otherHead->next);
  head_= newHead;
}

Chain::Node * Chain::copyHelper(Node* previous, Node* otherList) {
  if (otherList == NULL) {
    Node* newNode = NULL;
    return newNode;
  } else {
    Node* newNode = new Node(otherList->data);
    newNode->prev = previous;
    newNode->next = copyHelper(newNode, otherList->next);
    return newNode;
  }
}
 
/* Modifies the current chain: 
 * 1) Find the node with the first (leftmost) block in the unscrambled
 *    image and move it to the head of the chain.
 *  This block is the one whose closest match (to the left) is the
 *  largest.  That is, the distance (using distanceTo) to this block 
 *  is big for all other blocks.
 *  For each block B, find the distanceTo B from every other block
 *  and take the minimum of these distances as B's "value".
 *  Choose the block B with the maximum value over all blocks and
 *  swap its node to the head of the chain.
 *
 * 2) Starting with the (just found) first block B, find the node with
 *    the block that is the closest match to follow B (to the right)
 *    among the remaining blocks, move (swap) it to follow B's node,
 *    then repeat to unscramble the chain/image.
 */
void Chain::unscramble() {
  Node * tracker = head_;
  Node * maxMinDistance = NULL;

  double maximumMinSoFar = 0;
  double minWithinList = 2;
 
   while(tracker != NULL) {
     Node * newHead = head_;

     while(newHead != NULL) {
       if (tracker != newHead){
       double value = newHead->data.distanceTo(tracker->data);
       if (value < minWithinList) {
         minWithinList = value;
       }
       }
       newHead = newHead->next;
       }

    if (minWithinList > maximumMinSoFar) {
        maximumMinSoFar = minWithinList;
       maxMinDistance = tracker;
      }
   tracker = tracker->next;
   minWithinList = 2;
   }
 
  swap(head_, maxMinDistance);
 
  minWithinList = 2;
  Node * closestBlock = NULL;
  Node * nextBlock = head_;

  while (nextBlock->next != NULL) {
    Node* tracker = nextBlock->next;

    while(tracker != NULL) {
      double value = nextBlock -> data.distanceTo(tracker -> data);
      if (value < minWithinList) {
        minWithinList = value;
        closestBlock = tracker;
        }
      tracker = tracker -> next;
    }
    
    swap(nextBlock->next, closestBlock);
    nextBlock = nextBlock -> next;
    minWithinList = 2;
    }
}
