#include <iostream>

using namespace std;

struct Interval {
    int left, right, maxRight;
    Interval *leftSubTree, *rightSubTree, *parent;

    Interval() : leftSubTree(nullptr), rightSubTree(nullptr), parent(nullptr) {}

    Interval(int left, int right, int maxRight) :
            left(left), right(right), maxRight(maxRight), leftSubTree(nullptr), rightSubTree(nullptr),
            parent(nullptr) {}
};

class IntervalTree {
    Interval *root{};

    void linkTwoIntervals(Interval *parent, int dirIndicator, Interval *child) {
        if (dirIndicator)
            parent->rightSubTree = child;
        else
            parent->leftSubTree = child;
        child->parent = parent;
    }

    void insertInterval(Interval *curr, Interval *target) {
        if (target->left < curr->left) {
            if (curr->leftSubTree)
                insertInterval(curr->leftSubTree, target);
            else
                linkTwoIntervals(curr, 0, target);
        } else if (target->left > curr->left) {
            if (curr->rightSubTree)
                insertInterval(curr->rightSubTree, target);
            else
                linkTwoIntervals(curr, 1, target);
        } else {
            if (target->right < curr->right) {
                if (curr->leftSubTree)
                    insertInterval(curr->leftSubTree, target);
                else
                    linkTwoIntervals(curr, 0, target);
            } else {
                if (curr->rightSubTree)
                    insertInterval(curr->rightSubTree, target);
                else
                    linkTwoIntervals(curr, 1, target);
            }
        }
    }

    void reCalculateMax(Interval *curr, const int &insertedRight) {
        if (insertedRight > curr->maxRight)
            curr->maxRight = insertedRight;
        if (curr->parent)
            reCalculateMax(curr->parent, insertedRight);
    }


    Interval *searchInterval(Interval *curr, int &l, int &r) {
        if(curr->leftSubTree && curr->leftSubTree->maxRight >= l)
            return searchInterval(curr->leftSubTree, l, r);
        else if(curr->right >= l)
            return curr;
        if(curr->rightSubTree)
            return searchInterval(curr->rightSubTree, l, r);
        return nullptr;
    }


public:
    void insert(int l, int r) {
        Interval *newInterval = new Interval({l, r, r});
        if (!root)
            root = newInterval;
        else
            insertInterval(root, newInterval);
        reCalculateMax(newInterval, newInterval->right);
    }

    Interval *search(int l, int r) {
        if (!root)
            return nullptr;
        else {
            return searchInterval(root, l, r);
        }
    }
};

int main() {
    IntervalTree intervalTree;
    intervalTree.insert(5, 9);
    intervalTree.insert(6, 18);
    intervalTree.insert(4, 6);
    intervalTree.insert(1, 6);
    intervalTree.insert(2, 40);

    Interval* interval = intervalTree.search(3, 9);

    if(interval)
        cout << interval->left << ' ' << interval->right << endl;
    else
        cout << "NOT FOUND" << endl;
    return 0;
}
