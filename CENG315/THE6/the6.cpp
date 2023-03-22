#include "the6.h"
// Don't add any additional includes

/*
  N: Number of racers
  updates: Updates you have heard
*/

void printVec(std::vector<int> vect) {
  std::vector<int>::iterator itr = vect.begin();
  for (; itr != vect.end(); itr++) {
    std::cout << *itr << " ";
  }
  std::cout << "\n";
}

bool checkIfContains(std::vector<int> vect, int val) {
  std::vector<int>::iterator itr = vect.begin();
  for (; itr != vect.end(); itr++) {
    if (*itr == val) return true;
  }
  return false;
}

std::pair<int, int> DFS(std::vector<int> &finishedList, int** adjMatrix, int node, std::vector<int> &visitedList, 
        int N, std::vector<int> &finishedThisItr) {
  int resultEventual = 1;
  int nodeResult = node;
//   std::cout << "Entered DFS for " << node << "\n";
//   printVec(finishedList);
//   printVec(visitedList);
  bool visited = checkIfContains(visitedList, node);
  bool finished = checkIfContains(finishedList, node);
  bool loop = visited && !finished;
  if (visited) {
    //   std::cout << node << " is already visited\n";
    if (loop) {
      finishedList.insert(finishedList.begin(), node);
      finishedThisItr.insert(finishedThisItr.begin(), node);
      return {-1, nodeResult};
    }
    else {
      return {1, nodeResult};
    }
  }
  std::vector<int> finishedThisItrNew;
  visitedList.push_back(node);
  for (int i = 0; i < N; i++) {
    if (adjMatrix[node][i] == 1) {
        // std::cout << "Will call DFS of " << i << " from " << node << "\n";
      std::pair<int, int> result = DFS(finishedList, adjMatrix, i, visitedList, N, finishedThisItrNew);
    //   std::cout << "Exited DFS for " << i << " and status: " << result.first << " and the ret node: " << result.second << "\n";
      if (result.first != 1) {
        // std::cout << "FOUND LOOP for " << node << "\n";
        nodeResult = result.second;
        finishedThisItr = finishedThisItrNew;
        if (result.first == -1) {
            // std::cout << "Result was -1\n";
          resultEventual = -1;
          finishedThisItr.insert(finishedThisItr.begin(), node);
          if (result.second == node) {
            resultEventual = 0;
          }
        }
        else if (result.first == 0) {
          resultEventual = 0;
        }
        break;
      }
    }
  }
//   std::cout << "Returning " << resultEventual << " for " << node << "\n";
  finishedList.insert(finishedList.begin(), node);
  return {resultEventual, nodeResult};
}


std::pair<bool, std::vector<int>>
RaceResult(int N, std::vector<std::pair<int, int>> updates) {
/*
* Do a topological sort (with DFS)
* If you encounter a cycle, finish the loop and return immediately 
*/

  // Alloc and initialize adjacency matrix
  int** adjMatrix = new int*[N];
  for (int i = 0; i < N; i++) {
    adjMatrix[i] = new int[N];
    for (int j = 0; j < N; j++) {
      adjMatrix[i][j] = 0;
    }
  }

  // Construct the vectors for DFS
  std::vector<int> finishedList;
  std::vector<int> visitedList;

  // Iterate the updates and update the adjacency matrix
  std::vector<std::pair<int,int>>::iterator itr = updates.begin();
  for (; itr != updates.end(); itr++) {
    int src = itr->first;
    int dst = itr->second;
    adjMatrix[src][dst] = 1;
  }

    bool loopExists = true;
  // Perform DFS
  for (int i = 0; i < N; i++) {
    if (checkIfContains(visitedList, i)) {
      continue;
    }
    std::vector<int> finishedThisItr;
    // std::cout << "Calling for i: " << i << "\n";
    //printVec(finishedList);
    //printVec(visitedList);
    std::pair<int, int> result = DFS(finishedList, adjMatrix, i, visitedList, N, finishedThisItr);
    int status = result.first;
    // std::cout << "Exited from main itr, status:" << status << "\n";
    if (status != 1) {
        loopExists = false;
      finishedList = finishedThisItr;
      break;
    }
  }
  
//   std::cout << loopExists << "\n";
//   printVec(finishedList);
  // Free the adjacency matrix
  for (int i = 0; i < N; i++) {
    delete[] adjMatrix[i];
  }
  delete[] adjMatrix;

  return {loopExists, finishedList};
}

int main() {

//   int N = 5;
//   std::vector<std::pair<int, int>> updates = {{0,2}, {0,1}, {1,3}, {1,2}, {2,3}};

//   int N = 5;
//   std::vector<std::pair<int, int>> updates = {{0,2}, {0,1}, {1,3}, {1,2}, {2,3}, {3,0}};

//   int N = 10;
//   std::vector<std::pair<int, int>> updates = {{0, 5}, {1, 0}, {1, 7}, {2, 4}, {2, 0}, {3, 4}, {3, 5}, {3, 7}, {3, 6}, {4, 7}, {4, 1}, {6, 2}, {6, 5}, {6, 9}, {7, 9}, {7, 5}, {8, 3}};

//   int N = 10;
//   std::vector<std::pair<int, int>> updates = {{0, 5}, {1, 0}, {1, 7}, {2, 4}, {2, 0}, {3, 4}, {3, 5}, {3, 7}, {3, 6}, {4, 7}, {4, 1}, {6, 2}, {6, 5}, {6, 9}, {7, 9}, {7, 5}, {7, 3}, {8, 3}};

  int N = 5;
  std::vector<std::pair<int, int>> updates = {{0,1}, {0,4}, {4,2}, {2,3}, {3,4}};

  std::pair<bool, std::vector<int>> result = RaceResult(N, updates);
  // //std::cout << "bool: " << result.first << "\n";
  // std::vector<int>::iterator itr = result.second.begin();
  // for (; itr != result.second.end(); itr++) {
  //   //std::cout << *itr << " ";
  // }
  // //std::cout << "\n";
  return 0;
}