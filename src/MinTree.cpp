#include <fstream>
#include <iostream>

#include "MinTree.h"

using namespace std;

ifstream in("in.txt");
ofstream out("out.txt");

namespace StudyingPractice_MinTree
{
    MinTree::MinTree()
        {
        int vertex1, vertex2, weight;

        in >> n >> m;

        graph = new int* [n];

        for (int i = 0; i < n; ++i)
        {
            graph[i] = new int[n];

            for (int j = 0; j < n; ++j) { graph[i][j] = 0; }
        }

        for (int i = 0; i < m; ++i)
        {
            in >> vertex1 >> vertex2 >> weight;

            --vertex1;
            --vertex2;

            graph[vertex1][vertex2] = weight;
            graph[vertex2][vertex1] = weight;
        }
    }

    void MinTree::Print()
    {
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j) { out << graph[i][j] << ' '; }

            out << endl;
        }
    }

    MinTree::~MinTree()
    {
        for (int i = 0; i < n; ++i) { delete[] graph[i]; }

        delete[] graph;
    }

//++++++++++++++++++++++++++++++++++++++++++++++
//Поиск двух минимальных деревьев поиска
//++++++++++++++++++++++++++++++++++++++++++++++

    int MinTree::min_tree(int*** min_matrix) {

        int lenght = 0, gg = 0, colore = 0;
        struct rebro *all_reb = new rebro[m];
        int check;

//----------------------------------------------
//Создаём структурный массив для сортировки и дальнейшей работы по алгоритму Карскала

        for (int i = 0; i < n; i++) {
            for (int j = n - 1; j > i; j--) {

                if (graph[i][j] != 0) {

                    all_reb[lenght].weight = graph[i][j];
                    all_reb[lenght].end1 = i;
                    all_reb[lenght].end2 = j;
                    lenght++;
                }
            }
        }

//Сортируем массив рёбер

        struct rebro swap;

        for (int i = 0; i < m; i++) {
            for (int j = i; j < m; j++) {

                if (all_reb[i].weight > all_reb[j].weight) {

                    swap = all_reb[i];
                    all_reb[i] = all_reb[j];
                    all_reb[j] = swap;
                }
            }
        }

        for (int i = 0; i < m; i++) {

            printf("%d ", all_reb[i].weight);
        }
//----------------------------------------------
//Создаём матрицы для хранения 2-х минимальных остовных дерева

        int **check_matrix = new int * [n];

        for (int i = 0; i < n; i++) {

            check_matrix[i] = new int [n];

        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {

                check_matrix[i][j] = 0;
            }
        }

        min_matrix = new int ** [2];
        min_matrix[0] = new int * [n];
        min_matrix[1] = new int * [n];

        for (int i = 0; i < n; i++) {

            min_matrix[0][i] = new int[n];
            min_matrix[1][i] = new int[n];
        }


        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < n; j++) {
                for (int k = 0; k < n; k++) {

                    min_matrix[i][j][k] = 0;
                }

                check_matrix[i][j] = 0;

            }
        }

//Сам алгоритм Карскала

        int *sum_of_touch = new int[n];

        for (int i = 0; i < n; i++) {

            sum_of_touch[i] = 0;
        }

        int full_tree = 0;
        check = 0;

        for (int i = 0; i < m; i++) {

//------------------------------------
//Если оба конца не находятся в дереве

            if ((sum_of_touch[all_reb[i].end1] == 0) && (sum_of_touch[all_reb[i].end2] == 0)){

                colore++;

                min_matrix[0][all_reb[i].end1][all_reb[i].end2] = all_reb[i].weight;
                min_matrix[0][all_reb[i].end2][all_reb[i].end1] = all_reb[i].weight;
                check++;

                sum_of_touch[all_reb[i].end1] = colore;
                sum_of_touch[all_reb[i].end2] = colore;

//----------------------------------------------
//Если один из концов ни в одном дереве

            } else if ((sum_of_touch[all_reb[i].end1] == 0) || (sum_of_touch[all_reb[i].end2] == 0)) {

                if (sum_of_touch[all_reb[i].end1] != 0) {

                    sum_of_touch[all_reb[i].end2] = sum_of_touch[all_reb[i].end1];
                    check++;

                    min_matrix[0][all_reb[i].end1][all_reb[i].end2] = all_reb[i].weight;
                    min_matrix[0][all_reb[i].end2][all_reb[i].end1] = all_reb[i].weight;


                } else {

                    sum_of_touch[all_reb[i].end1] = sum_of_touch[all_reb[i].end2];
                    check++;

                    min_matrix[0][all_reb[i].end1][all_reb[i].end2] = all_reb[i].weight;
                    min_matrix[0][all_reb[i].end2][all_reb[i].end1] = all_reb[i].weight;

                }

//----------------------------------------------
//Если концы ребра находятся в разных деревьях

            } else if (sum_of_touch[all_reb[i].end1] != sum_of_touch[all_reb[i].end2]) {

                check++;

                if (sum_of_touch[all_reb[i].end1] < sum_of_touch[all_reb[i].end2]) {

                    gg = sum_of_touch[all_reb[i].end2];

                    for (int j = 0; j < n; j++) {

                        if (sum_of_touch[j] == gg) {

                            sum_of_touch[j] = sum_of_touch[all_reb[i].end1];


                            min_matrix[0][all_reb[i].end1][all_reb[i].end2] = all_reb[i].weight;
                            min_matrix[0][all_reb[i].end2][all_reb[i].end1] = all_reb[i].weight;

                        }
                    }

                } else {


                    gg = sum_of_touch[all_reb[i].end2];

                    for (int j = 0; j < n; j++) {

                        if (sum_of_touch[j] == gg) {

                            sum_of_touch[j] = sum_of_touch[all_reb[i].end2];

                            min_matrix[0][all_reb[i].end1][all_reb[i].end2] = all_reb[i].weight;
                            min_matrix[0][all_reb[i].end2][all_reb[i].end1] = all_reb[i].weight;


                        }
                    }
                }

//Если оба конца находятся в одном дереве

            } else if (sum_of_touch[all_reb[i].end1] == sum_of_touch[all_reb[i].end2]) {}

//----------------------------------------------
//Проверка на содержание всех точек

            full_tree = 0;

            for (int j = 0; j < n - 1; j++) {

                if (sum_of_touch[j] != sum_of_touch[j + 1]) { full_tree++; }
            }

//Если дерево содержит их все - остановка алгорима

            if (full_tree == 0) { break; }

        }


        if (full_tree != 0) {

            printf("Error! 2 tree! Stop the scan!\n\n");
            return 0;
        }

        for (int i = 0; i < n; i++) {

            sum_of_touch[i] = 0;
        }

//----------------------------------------------
//Проверка на наличие альтернативных рёбер

        printf("\n\n%d, %d\n\n", check, m);

        if (check == m) {

            printf("Impossible! Don't have alternative way.");

            Print_min_tree(min_matrix, 1);

            printf("Min tree %d:\n\n", 1);
            for (int j = 0; j < n; j++) {
                for (int k = 0; k < n; k++) {

                    printf("%d ", min_matrix[0][j][k]);
                }

                printf("\n\n");
            }
            printf("\n\n");

            return 0;

        }

        check = 0;
        colore = 0;
        int ctr_check = 0;
        int min_ctr_check = 0;

        for (int i = 0; i < n; i++) {
            for (int j = n - 1; j > i; j--) {

                min_ctr_check += min_matrix[0][i][j];
            }
        }

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//=============================================================================

        for (int i = 0; i < m; i++) {

        colore = 0;

            for (int j = 0; j < m; j++) {

                if (i == j) {} else {

//----------------------------------------------
//Если оба конца не находятся в дереве

                    if ((sum_of_touch[all_reb[j].end1] == 0) && (sum_of_touch[all_reb[j].end2] == 0)){

                        colore++;

                        check_matrix[all_reb[j].end1][all_reb[j].end2] = all_reb[j].weight;
                        check_matrix[all_reb[j].end2][all_reb[j].end1] = all_reb[j].weight;
                        check += all_reb[j].weight;

                        sum_of_touch[all_reb[j].end1] = colore;
                        sum_of_touch[all_reb[j].end2] = colore;

//----------------------------------------------
//Если один из концов ни в одном дереве

                    } else if ((sum_of_touch[all_reb[j].end1] == 0) || (sum_of_touch[all_reb[j].end2] == 0)) {

                        if (sum_of_touch[all_reb[j].end1] != 0) {

                            sum_of_touch[all_reb[j].end2] = sum_of_touch[all_reb[j].end1];

                            check_matrix[all_reb[j].end1][all_reb[j].end2] = all_reb[j].weight;
                            check_matrix[all_reb[j].end2][all_reb[j].end1] = all_reb[j].weight;
                            check += all_reb[j].weight;


                        } else {

                            sum_of_touch[all_reb[j].end1] = sum_of_touch[all_reb[j].end2];

                            check_matrix[all_reb[j].end1][all_reb[j].end2] = all_reb[j].weight;
                            check_matrix[all_reb[j].end2][all_reb[j].end1] = all_reb[j].weight;
                            check += all_reb[j].weight;

                        }

//----------------------------------------------
//Если концы ребра находятся в разных деревьях

                    } else if (sum_of_touch[all_reb[j].end1] != sum_of_touch[all_reb[j].end2]) {

                        if (sum_of_touch[all_reb[j].end1] < sum_of_touch[all_reb[j].end2]) {


                            gg = sum_of_touch[all_reb[j].end2];

                            for (int k = 0; k < lenght; k++) {

                                if (sum_of_touch[k] == gg) {

                                    sum_of_touch[k] = sum_of_touch[all_reb[j].end1];

                                    check_matrix[all_reb[j].end1][all_reb[j].end2] = all_reb[j].weight;
                                    check_matrix[all_reb[j].end2][all_reb[j].end1] = all_reb[j].weight;
                                    check += all_reb[j].weight;

                                }
                            }

                        } else {

                            gg = sum_of_touch[all_reb[j].end1];

                            for (int k = 0; k < lenght; k++) {

                                if (sum_of_touch[k] == gg) {

                                    sum_of_touch[k] = sum_of_touch[all_reb[j].end2];

                                    check_matrix[all_reb[j].end1][all_reb[j].end2] = all_reb[j].weight;
                                    check_matrix[all_reb[j].end2][all_reb[j].end1] = all_reb[j].weight;
                                    check += all_reb[k].weight;


                                }
                            }
                        }

//Если оба конца находятся в одном дереве

                    } else if (sum_of_touch[all_reb[j].end1] == sum_of_touch[all_reb[j].end2]) {}


//----------------------------------------------
//Проверка на содержание всех точек

                    full_tree = 0;

                    for (int f = 0; f < n - 1; f++) {

                        if (sum_of_touch[f] != sum_of_touch[f + 1]) { full_tree++; }
                    }

//Если дерево содержит их все - остановка алгорима

                    if (full_tree == 0) { break; }
                }
            }

            for (int j = 0; j < n; j++) {

                    sum_of_touch[j] = 0;
            }
//----------------------------------------------

            if ((ctr_check == 0) && (full_tree == 0)) {

                ctr_check = check;

                for (int j = 0; j < n; j++) {
                    for (int k = 0; k < n; k++) {

                        min_matrix[1][j][k] = check_matrix[j][k];
                        min_matrix[1][k][j] = check_matrix[k][j];

                    }
                }

            } else if ((check < ctr_check) && (full_tree == 0)) {

                ctr_check = check;

                for (int j = 0; j < n; j++) {
                    for (int k = 0; k < n; k++) {

                        min_matrix[1][j][k] = check_matrix[j][k];
                        min_matrix[1][k][j] = check_matrix[k][j];

                    }
                }
            }

            for (int j = 0; j < n; j++) {
                for (int k = 0; k < n; k++) {

                    check_matrix[j][k] = 0;
                    check_matrix[k][j] = 0;
                }
            }

            check = 0;
//----------------------------------------------
        }
//----------------------------------------------
        Print_min_tree(min_matrix, 2);

        for (int i = 0; i < 2; i++) {

            printf("Min tree %d:\n\n", i + 1);
            for (int j = 0; j < n; j++) {
                for (int k = 0; k < n; k++) {

                    printf("%d ", min_matrix[i][j][k]);
                }

                printf("\n\n");
            }
            printf("\n\n");
        }
//----------------------------------------------

        delete [] sum_of_touch;
        delete [] all_reb;
        delete [] min_matrix;
        delete [] check_matrix;

//----------------------------------------------
        return 0;

    }


    int MinTree::Print_min_tree(int*** min_matrix, int sum) {

        if (sum == 1) {

            out << "\n\nMin Tree №1\n\n";

            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {

                    out << min_matrix[0][i][j] << " ";

                }
                out << "\n";
            }

            return 0;

        } else {

            for (int i = 0; i < 2; i++) {

                out << "\n\nMin Tree №"<< i + 1 << "\n\n";

                for (int j = 0; j < n; j++) {
                    for (int k = 0; k < n; k++) {

                        out << min_matrix[i][j][k] << " ";
                    }
                    out << "\n";
                }
            }

            return 0;

        }
    }
}
