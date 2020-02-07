#include <bits/stdc++.h>
using namespace std;

// Essentials
#define AI 2
#define Human 1

int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};

int Weight1[8][8] = {
	{4, -3, 2, 2, 2, 2, -3, 4},
	{-3, -4, -1, -1, -1, -1, -4, -3},
	{2, -1, 1, 0, 0, 1, -1, 2},
	{2, -1, 0, 1, 1, 0, -1, 2},
	{2, -1, 0, 1, 1, 0, -1, 2},
	{2, -1, 1, 0, 0, 1, -1, 2},
	{-3, -4, -1, -1, -1, -1, -4, -3},
	{4, -3, 2, 2, 2, 2, -3, 4}
}; 

// Main Code
class Oh__Othello {
private:
	int player;	
	int x, y;
	int value;
	vector<vector<int>> Board;
	map<pair<int, int>, pair<int, int>> Valids;
public:
	Oh__Othello(int player) {
		this->player =  player;
		Board.resize(8, vector<int>(8));
		Valids.clear();
		x = y = 0;
		value = 0;
	}	
	Oh__Othello() {
		Board.resize(8, vector<int>(8));
		Valids.clear();
		x = y = 0;
		value = 0;
	}	
	bool ok(int x, int y) {
		return x >= 0 and x < 8 and y >= 0 and y < 8;
	}
	void reset() {
		Board.resize(8, vector<int>(8));
		Board[3][3] = Board[4][4] = 1;
		Board[4][3] = Board[3][4] = 2;
		Valids.clear();							
	}
	// void reset(Oh__Othello obj) {
		
	void show() {
		for (int i = 1; i <= 8; ++i) cout << "  " << i << "";
		cout << endl;
		int j = 1;
		for (auto row : Board) {
		cout << j++;
		for (auto col : row) {
			//cout << col << " ";
			if (col == 1) cout << " " <<(char) 220 << " ";
			else if (col == 2) cout << " " << (char) 157 << " ";
				else if (col == 3) cout << " " << 'o' << " ";
				else cout << " " << (char) 176 << " ";
			}
			cout << endl << endl;
		}
	}
	void clean() {
	 	Valids.clear();
		for (int row = 0; row < 8; ++row) {
			for (int col = 0; col < 8; ++col) {
				if (Board[row][col] == 3) Board[row][col] = 0;
			}
		}
	}
	bool operator < (const Oh__Othello a) {
	 	return a.value > this->value;
	}
	Oh__Othello create_board(pair<pair<int, int>, pair<int, int>>);
	void play();
	void valid_moves();
	bool possible(int, int);
	void refresh(int, int);
	Oh__Othello Oh__AI(Oh__Othello, int, int);
};
void Oh__Othello::refresh(int x, int y) {
	pair<int, int> ax = Valids[{x, y}];

	// if(player == AI) cout << " FROM " << ax.first + 1 << " " << ax.second + 1 << endl;
	if (ax.first == x) {
		for (int i = min(ax.second, y); i <= max(ax.second, y); ++i) {
			Board[x][i] = player;
		}
	} else if(ax.second == y) {
		for (int i = min(ax.first, x); i <= max(ax.first, x); ++i) {
			Board[i][y] = player;
		}
	} else {
		int a = ax.first;
		int b = ax.second;

		if (x > a) {
			// Niche Ache
			if (y < b) {
				// Left e Ache
				while (x != a and y != b) {
					a += 1;
					b -= 1;
					Board[a][b] = player;
				}
			} else {
				// Right e Ache
				while (x != a and y != b) {
					a += 1;
					b += 1;
					Board[a][b] = player;
				}
			}
		} else {
			// Upore Ache
			if (y < b) {
				// Left e Ache
				while (x != a and y != b) {
					a -= 1;
					b -= 1;
					Board[a][b] = player;
				}
			} else {
				// Right e Ache
				while (x != a and y != b) {
					a -= 1;
					b += 1;
					Board[a][b] = player;
				}
			}
		}	
	}
	clean();
}
bool Oh__Othello::possible(int row, int col) {
	for (int i = 0; i < 8; ++i) {
		int x = row + dx[i];
		int y = col + dy[i];

		if (ok(x, y) and Board[x][y] == 3 - player) {
			bool ret = false;
			
			x += dx[i];
			y += dy[i];
			while (ok(x, y)) {
				if (Board[x][y] == player) {
					Valids[{row, col}] = {x, y};
					ret = true;
					break;
				}
				else if (Board[x][y] == 0) break;
				else if (Board[x][y] == 3) break;
				x += dx[i];
				y += dy[i];
			}
			if (ret) return true;
		}		
    }
    return false;
}	
void Oh__Othello::valid_moves() {
	// if (player == AI) this->show();
	Valids.clear();
	for (int row = 0; row < 8; ++row) {
		for (int col = 0; col < 8; ++col) {
			if (Board[row][col] == 0) {
				if (possible(row, col)) {
					Board[row][col] = 3;
				}
			}
		}
	}
	// if (player == AI) this->show();
}	
							
Oh__Othello Oh__Othello::create_board(pair<pair<int, int>, pair<int, int>> mv) {
	// return *this;
	// return x, y					
	// calculate value
	// return this setup
	Oh__Othello NBoard = *this; // copy the current board
	// execute the move
	pair<int, int> ax = mv.second;
	int x = mv.first.first;
	int y = mv.first.second;
	if (ax.first == x) {
		for (int i = min(ax.second, y); i <= max(ax.second, y); ++i) {
			NBoard.Board[x][i] = player;
			NBoard.value += Weight1[x][i];
		}
	} else if(ax.second == y) {
		for (int i = min(ax.first, x); i <= max(ax.first, x); ++i) {
			NBoard.Board[i][y] = player;
			NBoard.value += Weight1[x][i];
		}
	} else {
		int a = ax.first;
		int b = ax.second;

		if (x > a) {
			// Niche Ache
			if (y < b) {
				// Left e Ache
				NBoard.value += Weight1[a][b];
				while (x != a and y != b) {
					a += 1;
					b -= 1;
					NBoard.Board[a][b] = player;
					NBoard.value += Weight1[a][b];
				}	
			} else {
				// Right e Ache
				NBoard.value += Weight1[a][b];
				while (x != a and y != b) {
					a += 1;
					b += 1;
					NBoard.Board[a][b] = player;
					NBoard.value += Weight1[a][b];
				}
			}
		} else {
			// Upore Ache
			if (y < b) {
				// Left e Ache
				NBoard.value += Weight1[a][b];
				while (x != a and y != b) {
					a -= 1;
					b -= 1;
					NBoard.Board[a][b] = player;
					NBoard.value += Weight1[a][b];
				}
			} else {
				// Right e Ache
				NBoard.value += Weight1[a][b];
				while (x != a and y != b) {
					a -= 1;
					b += 1;
					NBoard.Board[a][b] = player;
					NBoard.value += Weight1[a][b];
				}
			}	
		}	
	}
	return NBoard;	
}
Oh__Othello Oh__Othello::Oh__AI(Oh__Othello child, int level, int target) {
    if (target == level) {
       return child;
	}
 	child.valid_moves();
 	// child.show();
 	// cout << child.Valids.size() << endl;
 	vector<Oh__Othello> all;
 	for (auto mv : child.Valids) {
 		// cout << mv.first.first + 1 << " " << mv.first.second + 1 << endl;
 		Oh__Othello f = child.create_board(mv);
 		// f.x = mv.first.first;
 		// f.y = mv.first.second;
 		f.show();
 		cout << f.value << endl;
 		all.push_back(f);
 		// cout << "Pushed" << endl;
 		Oh__AI(f, level + 1, target);
 	}
 	if (level & 1) {
 		// return min

 		cout << "L E V E L - " << level << endl;
 		if (all.empty()) return 10000;
 		sort(all.begin(), all.end());	
 		// child.x = all[0].x;
 		// child.y = all[0].y;
 		for (auto x : all) {
 			cout << x.value << " ";
 		}
 		cout << endl << "Re Tu Rn Ed " << all[0].value << endl;
 		return all[0];
 	} else {
 		cout << "L E V E L - " << level << endl;
 		// return max
 		if (all.empty()) return -1000;
 		sort(all.begin(), all.end());
		// child.x = all[all.size() - 1].x;
 		// child.y = all[all.size() - 1].y;  
 		for (auto x : all) {
 			cout << x.value << " ";
 		}
 		cout << endl << "Re Tu Rn Ed " << all[all.size()-1].value << endl;	
 		return all[all.size() - 1];
 	}
 	// return child;
}
void Oh__Othello::play() {
	if (player == AI) {
		// AI Will Play
		Oh__Othello best = Oh__AI(*this, 0,  3);
		// best.show();
		// refresh(best.x, best.y);
		// best.clean();
		*this = best;
		// show();
		clean();
		player = Human; 
	}
	valid_moves();
	show();
	cout << "Valid Moves Are: \n";
	for (auto x : Valids) {
		cout << x.first.first + 1 << " " << x.first.second + 1 << endl;
	}
	// cout << "Select Your Move: ";
	int r, c;
	while (cin >> r >> c) {
		if (Board[r - 1][c - 1] == 3) break;
		else cout << "Please Select a Valid Region" << endl;
	}
	refresh(r - 1, c - 1);	
	player = AI;
	play();	
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	Oh__Othello obj(Human);
	obj.reset();
	// obj.show();
	// obj.create_board();
	obj.play();
}	