#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>
#include <string>
#include <cstring>
#include <cmath>
#include <stack>

using namespace std;

int inp;
int ind;
int endInd;
int wordInd;
const int MAX = 256;
const int ident = 10;

struct binTree {
	string info;
	string key;
	binTree* left = nullptr;
	binTree* right = nullptr;
	binTree* parent = nullptr;
};

struct inNode {
	binTree* info;
	int level = 0;
};

binTree* insertWord(binTree* root, string key, string info) {
	binTree* curr = root;
	binTree* par = nullptr;
	int ind = 0;
	while (curr) {
		par = curr;
		if (curr->key < key) {
			curr = curr->right;
			ind = 1;
		}
		else if (curr->key == key) {
			if (curr->info == info) {
				wordInd = 1;
				return root;
			}
			curr = curr->right;
			ind = 1;
		}
		else {
			curr = curr->left;
			ind = -1;
		}
	}
	curr = new binTree();
	curr->info = info;
	curr->key = key;
	curr->parent = par;
	if (ind == 0) root = curr;
	else if (ind == -1) par->left = curr;
	else par->right = curr;
	return root;
}

void getTranslate(binTree* root, string key) {
	binTree* curr = root;
	int ind = 0;
	while (curr) {
		if (key < curr->key) curr = curr->left;
		else if (curr->key < key) curr = curr->right;
		else {
			ind = 1;
			cout << curr->info << endl;
			curr = curr->right;
		}
	}
	if (!ind) {
		cout << "Given word does not exist";
		cout << endl;
	}
}

void inorderPrint(binTree* root) {
	stack<binTree*> s;
	binTree* node = root;
	while (true) {
		while (node) {
			s.push(node);
			node = node->left;
		}
		if (!s.empty()) {
			node = s.top();
			s.pop();
			//procedure start
			cout << node->key << " --> " << node->info;
			cout << endl;
			//procedure end
			node = node->right;
		}
		else {
			break;
		}
	}
}

int getMax(binTree* root) {
	stack<binTree*> s;
	binTree* node = root;
	binTree* prev = nullptr;
	int counter, maxCounter;
	while (true) {
		while (node) {
			s.push(node);
			node = node->left;
		}
		if (!s.empty()) {
			node = s.top();
			s.pop();
			//procedure start
			if (!prev) {
				counter = 1;
				maxCounter = 1;
			}
			else {
				if (prev->key == node->key) counter++;
				else {
					if (counter > maxCounter) maxCounter = counter;
					counter = 1;
				}
			}
			prev = node;
			//procedure end
			node = node->right;
		}
		else {
			break;
		}
	}
	if (counter > maxCounter) maxCounter = counter;
	return maxCounter;
}

void inorderGetMax(binTree* root, int maxCounter) {
	stack<binTree*> s;
	binTree* node = root;
	binTree* prev = nullptr;
	int counter;
	while (true) {
		while (node) {
			s.push(node);
			node = node->left;
		}
		if (!s.empty()) {
			node = s.top();
			s.pop();
			//procedure start
			if (!prev) counter = 1;
			else {
				if (prev->key == node->key) counter++;
				else {
					if (counter == maxCounter) cout << prev->key << endl;
					counter = 1;
				}
			}
			prev = node;
			//procedure end
			node = node->right;
		}
		else {
			break;
		}
	}
	if (counter == maxCounter) cout << prev->key << endl;
}

binTree* deleteWord(binTree* root, string key) {
	binTree* p = root;
	binTree* q = nullptr;
	binTree* rp = nullptr;
	binTree* f = nullptr;
	binTree* s = nullptr;
	while (p and (key != p->key)) {
		q = p;
		if (key < p->key) p = p->left;
		else p = p->right;
	}
	if (!p) {
		ind = 0;
		return root;
	}
	else if (!p->left) rp = p->right;
	else if (!p->right) rp = p->left;
	else {
		f = p;
		rp = p->right;
		s = rp->left;
		while (s) {
			f = rp;
			rp = s;
			s = rp->left;
		}
		if (f != p) {
			f->left = rp->right;
			rp->right = p->right;
		}
		rp->left = p->left;
	}
	if (!q) root = rp;
	else if (p == q->left) q->left = rp;
	else q->right = rp;
	ind = 1;
	delete p;
	return root;
}

binTree* postorderDelete(binTree* root) {
	stack<binTree*> s1;
	stack<int> s2;
	binTree* node = root;
	int temp;
	while (node) {
		s1.push(node);
		s2.push(1);
		node = node->left;
	}
	while (!s1.empty()) {
		node = s1.top(); s1.pop();
		temp = s2.top(); s2.pop();
		if (temp == 1) {
			s1.push(node);
			s2.push(-1);
			node = node->right;
			while (node) {
				s1.push(node);
				s2.push(1);
				node = node->left;
			}
		}
		else {
			binTree* par = node->parent;
			if (par) {
				par->left = nullptr;
				par->right = nullptr;
			}
			delete node;
		}
	}
	return nullptr;
}

void identationPrint(binTree* node, int h) {
	for (int i = 0; i < h*ident; i++) 
		cout << ' ';
	cout.width(ident); cout << left << node->key + "|" + node->info;
}

void inorderPrintTree(binTree* root) {
	stack<inNode> s1;
	stack<inNode> s2;
	inNode node;
	node.info = root;
	node.level = 0;
	while (true) {
		while (node.info) {
			s1.push(node);
			node.info = node.info->left;
			node.level++;
		}
		if (!s1.empty()) {
			node = s1.top(); s1.pop();
			//procedure start
			s2.push(node);
			//procedure end
			node.info = node.info->right;
			node.level++;
		}
		else {
			break;
		}
	}
	while (!s2.empty()) {
		s1.push(s2.top()); s2.pop();
		while (!s2.empty() and (s1.top().level - s2.top().level > 1)) {
			node = s2.top(); s2.pop();
			s1.top().level -= node.level + 1;
			s1.push(node); 
		}
		while (!s1.empty()) {
			node = s1.top(); s1.pop();
			identationPrint(node.info, node.level);
		}
		cout << endl << endl;
	}
}

void printMenu() {
	cout << "1 - Insert new translate" << endl;
	cout << "2 - Insert translate from file" << endl;
	cout << "3 - Print tree" << endl;
	cout << "4 - Print list of words" << endl;
	cout << "5 - Get translate" << endl;
	cout << "6 - Delete word" << endl;
	cout << "7 - Delete tree" << endl;
	cout << "8 - Most translated word" << endl;
	cout << "0 - End program" << endl;
	cout << "Option? "; cin >> inp; 
	getchar();
}

int main() {
	string word, translate;
	char fileName[MAX];
	char fileWord[MAX], fileTranslate[MAX];
	binTree* root = nullptr;
	FILE* fin;
	while (!endInd) {
		printMenu();
		switch (inp) {
			case 0:
				if (root) root = postorderDelete(root);
				endInd = 1;
				cout << "Enjoy your day! :)";
				cout << endl << endl;
				break;
			case 1:
				cout << "New word? "; getline(cin, word);
				cout << "Translate? "; getline(cin, translate);
				if (word == "" or translate == "") {
					cout << "You have to input non-empty word";
					cout << endl << endl;
				}
				else {
					root = insertWord(root, word, translate);
					if (wordInd) {
						cout << "Given translation already exist";
						wordInd = 0;
					}
					else cout << "Insertion successful";
					cout << endl << endl;
				}
				break;
			case 2:
				cout << "File? ";
				cin.getline(fileName, sizeof(fileName));
				fin = fopen(fileName, "r");
				if (!fin) {
					cout << "File does not exist";
					cout << endl << endl;
				}
				else {
					while (fscanf(fin, "%[^|]|%[^\n]\n", fileWord, fileTranslate) == 2) {
						if (!fileWord or !fileTranslate) continue;
						root = insertWord(root, fileWord, fileTranslate);
					}
					if (wordInd) {
						cout << "Some of translations in file already exist";
						cout << endl;
						wordInd = 0;
					}
					cout << "Insertion successful";
					cout << endl << endl;
					fclose(fin);
				}
				break;
			case 3:
				if (!root) {
					cout << "You have to create tree first";
					cout << endl << endl;
				}
				else {
					inorderPrintTree(root);
					cout << endl;
				}
				break;
			case 4:
				if (!root) {
					cout << "You have to create tree first";
					cout << endl << endl;
				}
				else {
					inorderPrint(root);
					cout << endl;
				}
				break;
			case 5:
				if (!root) {
					cout << "You have to create tree first";
					cout << endl << endl;
				}
				else {
					cout << "Word? ";
					getline(cin, word);
					getTranslate(root, word);
					cout << endl;
				}
				break;
			case 6:
				if (!root) {
					cout << "You have to create tree first";
					cout << endl << endl;
				}
				else {
					cout << "Word? ";
					getline(cin, word);
					root = deleteWord(root, word);
					if (!ind) {
						cout << "Given word does not exist";
						cout << endl << endl;
					}
					else {
						while (ind) root = deleteWord(root, word);
						cout << "Deletion successful";
						cout << endl << endl;
					}
				}
				break;
			case 7:
				if (!root) {
					cout << "You have to create tree first";
					cout << endl << endl;
				}
				else {
					root = postorderDelete(root);
					cout << "Tree successfully deleted";
					cout << endl << endl;
				}
				break;
			case 8:
				if (!root) {
					cout << "You have to create tree first";
					cout << endl << endl;
				}
				else {
					int maxi = getMax(root);
					cout << "Number of translations: ";
					cout << maxi << endl;
					inorderGetMax(root, maxi);
					cout << endl;
				}
				break;
			default:
				cout << "Bad input, try again";
				cout << endl << endl;
				break;
		}
	}
}