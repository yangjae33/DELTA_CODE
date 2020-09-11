//
//  Programmers42892 - 길 찾기 게임.cpp
//  DeltaCode
//
//  Created by 김성헌 on 2020/08/30.
//  Copyright © 2020 김성헌. All rights reserved.
//

#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#include<iostream>
#define MAX 1e5+1
using namespace std;

class Node {
public:
    int value;
    Node* left = NULL;
    Node* right = NULL;
    Node(int value) { this->value = value; }
};


bool compare(vector<int>& a, vector<int>& b) {
    return a[1] == b[1] ? a[0] < b[0] : a[1] > b[1];
}

vector<priority_queue<pair<int, int>>> yList;
int depth = 0;

Node* makeBinaryTree(int maxX, int level) {

    int x = -yList[level].top().first;
    int val = yList[level].top().second;
    yList[level].pop();
    Node* root = new Node(val);
    if (level == depth || yList[level + 1].empty())
        return root;
    int nextX = -yList[level + 1].top().first;
    if (nextX < x)
        root->left = makeBinaryTree(x, level + 1);
    if(yList[level + 1].empty())
        return root;
    nextX = -yList[level + 1].top().first;
    if (x < nextX && nextX < maxX)
        root->right = makeBinaryTree(maxX, level + 1);
    return root;
}

vector<int> preOrder, postOrder;
void setPreOrder(Node* root) {
    if (root == NULL)
        return;
    preOrder.push_back(root->value);
    setPreOrder(root->left);
    setPreOrder(root->right);
}
void setPostOrder(Node* root) {
    if (root == NULL)
        return;
    setPostOrder(root->left);
    setPostOrder(root->right);
    postOrder.push_back(root->value);
}

vector<vector<int>> solution(vector<vector<int>> nodeinfo) {
    vector<vector<int>> answer;
    int beforeY = -1;
    for (int i = 0; i < nodeinfo.size(); i++) {
        nodeinfo[i].push_back(i + 1);
    }

    sort(nodeinfo.begin(), nodeinfo.end(), compare);
    int ind = -1;
    for (int i = 0; i < nodeinfo.size(); i++) {
        int nowY = nodeinfo[i][1];
        if (nowY != beforeY) {
            ind++;
            yList.push_back(priority_queue<pair<int,int>>());
            beforeY = nowY;
        }
        yList[ind].push({ -nodeinfo[i][0], nodeinfo[i][2]});
    }
    depth = ind;

    Node* root = makeBinaryTree(MAX, 0);
    setPreOrder(root);
    setPostOrder(root);
    answer.push_back(preOrder);
    answer.push_back(postOrder);
    return answer;
}
