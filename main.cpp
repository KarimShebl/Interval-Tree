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
};

int main() {
    IntervalTree intervalTree;
    return 0;
}
