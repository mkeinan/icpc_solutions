/* ICPC-6885 ::: UVA-12878 ::: Flowery Trails */
// goal: find all edges in the graph that lie on a shortest path between two
// given points. solution: use dijkstra twice to compute shortest distances of
// every point from each of the two given points. then iterate over all the
// edges and decide for each of them whether it is on a shortest path.
#include <iostream>
#include <vector>
#include <cstdio>
using namespace std;
#define MAX_TRAIL_LENGTH 20000000	// "Infinity" to initiate dijkstra
#define MAX_NUM_OF_POINTS 10000

typedef struct Edge_t {		// describes edges in the graph
	int to;		// target vertex (point) of the edge
	int weight;	// weight (trail length) of the edge
} Edge;

vector<int> arranged(MAX_NUM_OF_POINTS);

// function performs dijkstra's algorithm for shortest paths. assumes one of the
// distances in the vector min_dists is 0 (start point) and the rest are
// "Infinity". in the end of the function min_dists will contain the shortest
// path values from the start point, to every point in the graph. each index of
// the vector min_dists corresponds to the point in the graph with that index.
void dijkstra(vector<vector<Edge>>* graph, vector<int>* min_dists) {
	vector<int> unscanned(arranged.begin(), arranged.begin() + graph->size());
	int point;	// the next point dijkstra will scan its edges
	int index;	// index of the point, to erase it from the unscanned points set
	while (!unscanned.empty()) {
		index = 0;
		point = unscanned[0];
		// find the unscanned point with the minimal distance:
		for (int i = 0; i < (int) unscanned.size(); i++) {
			if ((*min_dists)[unscanned[i]] < (*min_dists)[point]) {
				index = i;
				point = unscanned[i];
			}
		}
		unscanned.erase(unscanned.begin() + index);
		Edge* iter = NULL;
		// relax edges exiting the current processed point:
		for (int i = 0; i < (int) (*graph)[point].size(); i++) {
			iter = &(*graph)[point][i];
			if ((*min_dists)[iter->to] > (*min_dists)[point] + iter->weight) {
				(*min_dists)[iter->to] = (*min_dists)[point] + iter->weight;
			}
		}
	}
}

// this function solves each test case:
// P = the number of points in the graph
// T = the number of edges in the graph
void solve(int P, int T) {
	vector<vector<Edge>> graph(P);	// maps every point to its edges
	int point1, point2, weight;	// variables to handle input
	Edge temp;
	for (int i = 0; i < T; i++) {
		scanf("%d %d %d", &point1, &point2, &weight);	// input reception
		if (point1 == point2) {
			continue;	// optimization - don't care about self loops
		}
		// representing each undirected edge as two directed edges:
		temp.weight = weight;
		temp.to = point2;
		graph[point1].push_back(temp);
		temp.to = point1;
		graph[point2].push_back(temp);
	}
	// setting up vectors of minimum distances for running Dijkstra:
	vector<int> min_dist_from_start(P, MAX_TRAIL_LENGTH);
	min_dist_from_start[0] = 0;
	vector<int> min_dist_from_end(P, MAX_TRAIL_LENGTH);
	min_dist_from_end[P - 1] = 0;
	// all shortest paths from the entrance of the park (the "start" point):
	dijkstra(&graph, &min_dist_from_start);
	int dist_start_to_end = min_dist_from_start[P - 1];
	// all shortest paths from the highest peak in the park (the "end" point):
	dijkstra(&graph, &min_dist_from_end);
	int sum = 0;	// to sum the lengths of trails that are on shortest paths
	// iterate over all the edges (trails) of the park:
	for (int i = 0; i < (int) graph.size(); i++) {
		for (int j = 0; j < (int) graph[i].size(); j++) {
			// an edge from S to T is on a shortest path from A to B if:
			// min_dist(A->S) + edge's weight + min_dist(T->B) == min_dist(A->B)
			if (min_dist_from_start[i] + graph[i][j].weight
					+ min_dist_from_end[graph[i][j].to] == dist_start_to_end) {
				sum += graph[i][j].weight;
			}
		}
	}
	printf("%d\n", 2 * sum);	// printing result for test case
}

int main() {
	// setting up a vector of the form {0, 1, 2, ..., 10000}
	// Dijkstra will later copy it to create a set of points quickly
	for (int i = 0; i < (int) arranged.size(); i++) {
		arranged[i] = i;
	}
	int P;	// number of points
	int T;	// number of trails
	while (scanf("%d %d", &P, &T) != EOF) {
		solve(P, T);
	}
	return 0;
}
