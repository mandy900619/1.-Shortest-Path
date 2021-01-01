#include <iostream>
#include <vector>

using namespace std;
class node {
public:
	long int label;
	int nodeName;
	int pathNUM;
	int lastnode;
	bool inShortestpath;
	vector<pair<int, int>> path; // des,weight
	node(int i) {
		nodeName = i + 1;
		label = NULL;
		inShortestpath = false;
		pathNUM = 0;
		lastnode = 0;
	}
};
int main() {
	int m, n, A, B;
	long int ta, tb, tc;
	cin >> m >> n >> A >> B;
	vector<node> NODE;
	vector<node> ShortestPath;
	for (int i = 0; i < m; i++) {
		node temp(i);
		if (i + 1 == A)
			temp.label = 0;
		NODE.push_back(temp);
	}
	for (int i = 0; i < n; i++) {
		cin >> ta >> tb >> tc;
		pair<int, int> temp(tb, tc);
		NODE[ta - 1].path.push_back(temp);
		NODE[ta - 1].pathNUM++;
	}
	int shortestNUM = 1;
	long int miniWeight = 0;
	vector<int> chooseNode;
	int choosenum = 0;
	ShortestPath.push_back(NODE[A - 1]);
	while (ShortestPath[shortestNUM - 1].nodeName != B) {
		int u = 1;
		while (shortestNUM - u >= 0) {
			int currentnode = 0;
			int currentnextnode = 0;
			int pos = 0;
			while (ShortestPath[shortestNUM - u].pathNUM >= pos + 1) {
				currentnode = ShortestPath[shortestNUM - u].nodeName;
				currentnextnode = NODE[currentnode - 1].path[pos].first;
				if (!NODE[currentnextnode - 1].inShortestpath) {
					chooseNode.push_back(currentnextnode);
					choosenum++;
					if (NODE[currentnextnode - 1].label == NULL) {
						NODE[currentnextnode - 1].label = NODE[currentnode - 1].label + NODE[currentnode - 1].path[pos].second;
						NODE[currentnextnode - 1].lastnode = currentnode;
					}
					else {
						long int templable = NODE[currentnode - 1].label + NODE[currentnode - 1].path[pos].second;
						if (templable < NODE[currentnextnode - 1].label) {
							NODE[currentnextnode - 1].label = templable;
							NODE[currentnextnode - 1].lastnode = currentnode;
						}
					}
				}
				pos++;
			}
			u++;
		}
		int insertednode = NODE[chooseNode[0] - 1].nodeName;
		miniWeight = NODE[chooseNode[0] - 1].label;
		for (int p = 1; p < choosenum; p++) {
			if (NODE[chooseNode[p] - 1].label < miniWeight) {
				miniWeight = NODE[chooseNode[p] - 1].label;
				insertednode = NODE[chooseNode[p] - 1].nodeName;
			}
		}
		ShortestPath.push_back(NODE[insertednode - 1]);
		NODE[insertednode - 1].inShortestpath = true;
		shortestNUM++;
		choosenum = 0;
		chooseNode.clear();
	}
	vector<int> output;
	int num = 0;
	int q = B;
	while (q != A) {
		output.push_back(q);
		num++;
		q = NODE[q - 1].lastnode;
	}
	output.push_back(q);
	num++;
	cout << output[num - 1];
	for (int i = num - 2; i >= 0; i--) {
		cout << " " << output[i];
	}
	cout << endl;
	cout << miniWeight;
}