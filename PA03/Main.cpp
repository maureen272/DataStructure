#include <bits/stdc++.h>
using namespace std;

void insert(map<int, string> &tree, const string& name, int node) {
	 if (tree.find(node) == tree.end()) {
		 tree[node] = name; //트리에 해당 노드가 없으면 이름을 추가
		 return; 
	 }
	 if (tree[node] > name) {
		insert(tree, name, node * 2); // 삽입하려는 이름이 현재 노드의 이름보다 작으면 왼쪽 자식 노드로 이동
	 } 
	 else {
		insert(tree, name, node * 2 + 1); // 위와 동일 (작으면 -> 크면, 왼 -> 오)
	 }
}

int findIndex(map<int, string>& m, const string& name) {
	 for(auto [k, v] : m) {
		 if (v == name) { // 이름이 일치하면 해당 노드의 인덱스 반환
			 return k;
			}
	 	}
	 return -1;
}

vector<int> findCommonAncestor(int firstIdx, int secondIdx) {
	vector<int> firstPath, secondPath, commonAncestors;
	while(firstIdx) {
		firstPath.push_back(firstIdx); // 첫번째 사람의 조상 경로를 지정
		firstIdx /= 2;
	}
	while(secondIdx) {
		secondPath.push_back(secondIdx); // 두번째 사람의 조상 경로를 지정
		secondIdx /= 2;
	}

	for(auto i : firstPath) {
		if(find(secondPath.begin(), secondPath.end(), i) != secondPath.end()) {
			commonAncestors.push_back(i); // 공통 조상을 찾아 저장
		}
	}
	return commonAncestors;
}


void printAncestors(map<int, string>& m, vector<int>& ancestors) {
	 for(int i = ancestors.size() - 1 ; i >= 0 ; --i) {
		cout << m[ancestors[i]] << "\n"; // 공통조상 출력
	 }
}

int main() {
	 string firstPersonName, secondPersonName;
	 getline(cin, firstPersonName);
	 getline(cin, secondPersonName);

	 int N;
	 cin >> N;
	 cin.ignore();

	 map<int, string> tree;
	 for(int i=0 ; i<N ; i++) {
		string newName;
		getline(cin, newName);
		insert(tree, newName, 1);
	 }

	 int firstIdx = findIndex(tree, firstPersonName);
	 int secondIdx = findIndex(tree, secondPersonName);

	 vector<int> ancestors = findCommonAncestor(firstIdx, secondIdx);

	 printAncestors(tree, ancestors);

	 return 0;
}
