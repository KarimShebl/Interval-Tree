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
        if (curr->leftSubTree && curr->leftSubTree->maxRight >= l)
            return searchInterval(curr->leftSubTree, l, r);
        else if (curr->right >= l && curr->left <= r)
            return curr;
        if (curr->rightSubTree)
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

void print(Interval* interval)
{
    if(interval)
        cout << "The Smallest Left Overlapping Interval : " << interval->left << ' ' << interval->right << endl;
    else
        cout << "NOT FOUND" << endl;
}

int main() {
    IntervalTree intervalTree;
    intervalTree.insert(2, 5);
    print(intervalTree.search(2, 5));
    intervalTree.insert(3, 7);
    print(intervalTree.search(0, 1)); // NOT FOUND
    intervalTree.insert(10, 20);
    print(intervalTree.search(21, 26)); // NOT FOUND
    intervalTree.insert(8, 12);
    print(intervalTree.search(10, 15));
    intervalTree.insert(25, 30);
    print(intervalTree.search(22, 28));
    intervalTree.insert(15, 22);
    print(intervalTree.search(14, 21));
    intervalTree.insert(17, 25);
    print(intervalTree.search(18, 24));
    intervalTree.insert(30, 35);
    print(intervalTree.search(32, 34));
    intervalTree.insert(40, 50);
    print(intervalTree.search(51, 66)); // NOT FOUND
    intervalTree.insert(38, 42);
    print(intervalTree.search(41, 44));
    intervalTree.insert(60, 70);
    print(intervalTree.search(55, 65));
    intervalTree.insert(55, 65);
    print(intervalTree.search(58, 62));
    intervalTree.insert(52, 58);
    print(intervalTree.search(56, 59));
    intervalTree.insert(80, 90);
    print(intervalTree.search(75, 85));
    intervalTree.insert(78, 82);
    print(intervalTree.search(80, 83));
    intervalTree.insert(92, 98);
    print(intervalTree.search(88, 94));
    intervalTree.insert(85, 95);
    print(intervalTree.search(87, 92));
    intervalTree.insert(100, 110);
    print(intervalTree.search(105, 108));
    intervalTree.insert(102, 112);
    print(intervalTree.search(115, 116)); // NOT FOUND
    intervalTree.insert(115, 120);
    print(intervalTree.search(112, 118));
    intervalTree.insert(122, 128);
    print(intervalTree.search(118, 125));
    intervalTree.insert(130, 140);
    print(intervalTree.search(135, 138));
    intervalTree.insert(125, 135);
    print(intervalTree.search(132, 136));
    intervalTree.insert(150, 160);
    print(intervalTree.search(145, 155));
    intervalTree.insert(145, 155);
    print( intervalTree.search(150, 154));
    intervalTree.insert(142, 148);
    print(intervalTree.search(146, 149));
    intervalTree.insert(165, 175);
    print(intervalTree.search(160, 170));
    intervalTree.insert(162, 172);
    print(intervalTree.search(168, 174));
    intervalTree.insert(180, 190);
    print(intervalTree.search(175, 185));
    intervalTree.insert(176, 182);
    print(intervalTree.search(178, 184));
    return 0;
}
