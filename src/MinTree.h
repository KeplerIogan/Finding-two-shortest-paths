#pragma once

namespace StudyingPractice_MinTree
{
    class MinTree
    {
    private:

        int n, m, **graph;

    public:

        MinTree();

        void Print();
        int min_tree(int*** min_matrix);
        int Print_min_tree(int*** min_matrix, int sum);

        ~MinTree();
    };
}

struct rebro {

    int end1;
    int end2;
    int weight;

};