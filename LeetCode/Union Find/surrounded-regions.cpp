#include <vector>
#include <queue>
#include <utility>
using std::vector;
using std::queue;
using std::pair;
using std::make_pair;
// https://leetcode.com/discuss/42445/a-really-simple-and-readable-c-solution%EF%BC%8Conly-cost-12ms DFS, 潜在的递归层数过深……
// https://leetcode.com/discuss/6285/solve-it-using-union-find
class Solution {
public:
	// Runtime: 16 ms
	void solve(vector<vector<char>>& board) {
		if (board.empty() || board[0].empty()) {
			return;
		}
		int ROW = board.size(), COL = board[0].size();
		queue<pair<int, int>> q;
		for (int i = 0; i < ROW; i++) {
			if (board[i][0] == 'O') {
				q.push(make_pair(i, 0));
				board[i][0] = '.';
			}
			if (board[i][COL - 1] == 'O') {
				q.push(make_pair(i, COL - 1));
				board[i][COL - 1] = '.';
			}
		}
		for (int j = 1; j < COL - 1; j++) {
			if (board[0][j] == 'O') {
				q.push(make_pair(0, j));
				board[0][j] = '.';
			}
			if (board[ROW - 1][j] == 'O') {
				q.push(make_pair(ROW - 1, j));
				board[ROW - 1][j] = '.';
			}
		}

		while (!q.empty()) {
			pair<int, int> p = q.front();
			q.pop();
			int i = p.first, j = p.second;
			if (i > 0 && board[i - 1][j] == 'O') {
				q.push(make_pair(i - 1, j));
				board[i - 1][j] = '.';
			}
			if (i < ROW - 1 && board[i + 1][j] == 'O') {
				q.push(make_pair(i + 1, j));
				board[i + 1][j] = '.';
			}
			if (j > 0 && board[i][j - 1] == 'O') {
				q.push(make_pair(i, j - 1));
				board[i][j - 1] = '.';
			}
			if (j < COL - 1 && board[i][j + 1] == 'O') {
				q.push(make_pair(i, j + 1));
				board[i][j + 1] = '.';
			}
		}

		for (int i = 0; i < ROW; i++) {
			for (int j = 0; j < COL; j++) {
				if (board[i][j] == 'O') {
					board[i][j] = 'X';
				}
				else if (board[i][j] == '.') {
					board[i][j] = 'O';
				}
			}
		}
	}

	// Runtime: 20 ms
	// void solve(vector<vector<char>>& board) {
	//     if (board.empty() || board[0].empty()) {
	//         return;
	//     }
	//     int ROW = board.size(), COL = board[0].size();
	//     queue<pair<int, int>> q;
	//     for (int i = 0; i < ROW; i++) {
	//         if (board[i][0] == 'O') 
	//             q.push(make_pair(i, 0));
	//         if (board[i][COL - 1] == 'O')
	//             q.push(make_pair(i, COL - 1));
	//     }
	//     for (int j = 1; j < COL - 1; j++) {
	//         if (board[0][j] == 'O')
	//             q.push(make_pair(0, j));
	//         if (board[ROW - 1][j] == 'O')
	//             q.push(make_pair(ROW - 1, j));
	//     }

	//     while (!q.empty()) {
	//         pair<int, int> p = q.front();
	//         q.pop();
	//         int i = p.first, j = p.second;
	//         board[i][j] = '.';
	//         if (i > 0 && board[i - 1][j] == 'O') {
	//             q.push(make_pair(i - 1, j));
	//         }
	//         if (i < ROW - 1 && board[i + 1][j] == 'O') {
	//             q.push(make_pair(i + 1, j));
	//         }
	//         if (j > 0 && board[i][j - 1] == 'O') {
	//             q.push(make_pair(i, j - 1));
	//         }
	//         if (j < COL - 1 && board[i][j + 1] == 'O') {
	//             q.push(make_pair(i, j + 1));
	//         }
	//     }

	//     for (int i = 0; i < ROW; i++) {
	//         for (int j = 0; j < COL; j++) {
	//             if (board[i][j] == 'O') {
	//                 board[i][j] = 'X';
	//             } else if (board[i][j] == '.') {
	//                 board[i][j] = 'O';
	//             }
	//         }
	//     }
	// }

	void solve2(vector<vector<char>>& board) {
		if (board.empty() || board[0].empty()) {
			return;
		}
		int ROW = board.size(), COL = board[0].size();
		for (int i = 0; i < ROW; i++) {
			if (board[i][0] == 'O')
				BFS(board, i, 0, ROW, COL);
			if (board[i][COL - 1] == 'O')
				BFS(board, i, COL - 1, ROW, COL);
		}
		for (int j = 1; j < COL - 1; j++) {
			if (board[0][j] == 'O')
				BFS(board, 0, j, ROW, COL);
			if (board[ROW - 1][j] == 'O')
				BFS(board, ROW - 1, j, ROW, COL);
		}
		for (int i = 0; i < ROW; i++) {
			for (int j = 0; j < COL; j++) {
				if (board[i][j] == 'O') {
					board[i][j] = 'X';
				}
				else if (board[i][j] == '.') {
					board[i][j] = 'O';
				}
			}
		}
	}

	void BFS(vector<vector<char>>& board, int i, int j, int ROW, int COL) {
		// if (board[i][j] == 'O') {
		queue<pair<int, int>> q;
		q.push(make_pair(i, j));
		board[i][j] = '.';
		while (!q.empty()) {
			pair<int, int> p = q.front();
			q.pop();
			// i = p.first;
			// j = p.second;
			// if (i > 0 && board[i - 1][j] == 'O') {
			//     q.push(make_pair(i - 1, j));
			//     board[i - 1][j] = '.';
			// }
			// if (i < ROW - 1 && board[i + 1][j] == 'O') {
			//     q.push(make_pair(i + 1, j));
			//     board[i + 1][j] = '.';
			// }
			// if (j > 0 && board[i][j - 1] == 'O') {
			//     q.push(make_pair(i, j - 1));
			//     board[i][j - 1] = '.';
			// }
			// if (j < COL - 1 && board[i][j + 1] == 'O') {
			//     q.push(make_pair(i, j + 1));
			//     board[i][j + 1] = '.';
			// }


			if (p.first > 0 && board[p.first - 1][p.second] == 'O') {
				q.push(make_pair(p.first - 1, p.second));
				board[p.first - 1][p.second] = '.';
			}
			if (p.first < ROW - 1 && board[p.first + 1][p.second] == 'O') {
				q.push(make_pair(p.first + 1, p.second));
				board[p.first + 1][p.second] = '.';
			}
			if (p.second > 0 && board[p.first][p.second - 1] == 'O') {
				q.push(make_pair(p.first, p.second - 1));
				board[p.first][p.second - 1] = '.';
			}
			if (p.second < COL - 1 && board[p.first][p.second + 1] == 'O') {
				q.push(make_pair(p.first, p.second + 1));
				board[p.first][p.second + 1] = '.';
			}
		}
		// }
	}

	// Runtime Error with DFS
	// void solve(vector<vector<char>>& board) {
	//     if (board.empty() || board[0].empty()) {
	//         return;
	//     }
	//     int ROW = board.size(), COL = board[0].size();
	//     for (int i = 0; i < ROW; i++) {
	//         DFS(board, i, 0, ROW, COL);
	//         DFS(board, i, COL - 1, ROW, COL);
	//     }
	//     for (int j = 1; j < COL - 1; j++) {
	//         DFS(board, 0, j, ROW, COL);
	//         DFS(board, ROW - 1, j, ROW, COL);
	//     }
	//     for (int i = 0; i < ROW; i++) {
	//         for (int j = 0; j < COL; j++) {
	//             if (board[i][j] == 'O') {
	//                 board[i][j] = 'X';
	//             } else if (board[i][j] == '.') {
	//                 board[i][j] = 'O';
	//             }
	//         }
	//     }
	// }
	// void DFS(vector<vector<char>>& board, int i, int j, int ROW, int COL) {
	//     if (board[i][j] == 'O') {
	//         board[i][j] = '.';
	//         if (i > 0) {
	//             DFS(board, i - 1, j, ROW, COL);
	//         }
	//         if (i < ROW - 1) {
	//             DFS(board, i + 1, j, ROW, COL);
	//         }
	//         if (j > 0) {
	//             DFS(board, i, j - 1, ROW, COL);
	//         }
	//         if (j < COL - 1) {
	//             DFS(board, i, j + 1, ROW, COL);
	//         }
	//     }
	// }

	//void DFS(vector<vector<char>>& board, int i, int j, int ROW, int COL) {
	//	if (board[i][j] == 'O') {
	//		board[i][j] = '.';
	//		// if (i > 0) {
	//		if (i > 1) {
	//			DFS(board, i - 1, j, ROW, COL);
	//		}
	//		// if (i < ROW - 1) {
	//		if (i + 1 < ROW) {
	//			DFS(board, i + 1, j, ROW, COL);
	//		}
	//		// if (j > 0) {
	//		if (j > 1) {
	//			DFS(board, i, j - 1, ROW, COL);
	//		}
	//		if (j + 1 < COL) {
	//			DFS(board, i, j + 1, ROW, COL);
	//		}
	//	}
	//}
};