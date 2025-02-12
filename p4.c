//saja nazih asfour
//1210737
//sec4
//P4
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//the Max Number of City
#define CITIES 500
#define INFINITY 9999
//set a new name to use
typedef struct Edge * ptr;
//struct for edge between City
struct Edge {
    char city[20];
    int Distance;
    ptr next;
};
//struct for a City
struct CityNode {
    char City_Name[20];
    ptr edges;
};
struct Graph {
    struct CityNode City[CITIES];
    int NumOfCity;
};
//function definition
void Dijkstra(struct Graph* graph,const char* City1, const char* City2);
void BFS(struct Graph* graph, const char* City1, const char* City2);
int main() {
    struct Graph graph;
    graph.NumOfCity = 0;

    int op;
    char SourceCity[100];
    char end[100];
    do {
        printf("Enter your choice: \n");
        printf("1. Loads the file and construct the graph\n");
        printf("2. Enter the source city \n");
        printf("3. Enter the destination city \n");
        printf("4. Exit\n");
        scanf("%d", &op);
        switch (op) {
            case 1:;
                //open the file
                FILE* in=fopen("cities.txt", "r");
                //if the file does not exist
                if (in == NULL)
                    printf("can not open this file\n");
                char line[100];
                char* city1;
                char* city2;
                char* distance_str;
                //this for distance between city
                int distance;
                //read from file  and insert to the graph until the end of File
                while (fgets(line, sizeof(line), in) != NULL) {
                    city1 = strtok(line, "\t");
                    city2 = strtok(NULL, "\t");
                    distance_str = strtok(NULL, "\n");
                    distance = atoi(distance_str);
                    //index for city
                    int x1=-1;
                    int x2=-1;
                    for (int i = 0; i < graph.NumOfCity; i++) {
                        if (strcmp(graph.City[i].City_Name, city1) == 0) {
                            x1 = i;
                        }
                        if (strcmp(graph.City[i].City_Name, city2) == 0) {
                            x2 = i;
                        }
                    }
                    //if city1 is not found in the graph
                    if (x1 == -1) {
                        //add the first city to the graph
                        strcpy(graph.City[graph.NumOfCity].City_Name, city1);
                        graph.City[graph.NumOfCity].edges = NULL;
                        x1 = graph.NumOfCity++;
                    }
                    //if city2 is not found in the graph
                    if (x2 == -1) {
                        //add the city2 to graph
                        strcpy(graph.City[graph.NumOfCity].City_Name, city2);
                        graph.City[graph.NumOfCity].edges = NULL;
                        x2 = graph.NumOfCity++;
                    }
                    //add edges between the two city
                    ptr edge1 = (ptr)malloc(sizeof(struct Edge));
                    strcpy(edge1->city, city2);
                    edge1->Distance = distance;
                    edge1->next = graph.City[x1].edges;
                    graph.City[x1].edges = edge1;
                    ptr edge2 = (ptr)malloc(sizeof(struct Edge));
                    strcpy(edge2->city, city1);
                    edge2->Distance = distance;
                    edge2->next = graph.City[x2].edges;
                    graph.City[x2].edges = edge2;
                }
                //close the file
                fclose(in);
                printf("Cities loaded from the file\n");
                break;
            case 2:
                printf("Enter source city: \n");
                scanf("%s", SourceCity);
                break;
            case 3:
                printf("Enter destination city: ");
                scanf("%s", end);
                Dijkstra(&graph, SourceCity, end);
                BFS(&graph, SourceCity, end);
                break;
            case 4:
                printf("Thank you!!");
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    } while (op != 4);
    return 0;
}
//function to find the short path by dikstra and print it
void Dijkstra(struct Graph* graph,const char* City1, const char* City2) {
    //define this to initalized the graph
    int distances[CITIES];
    int CheckVisit[CITIES];
    int previous[CITIES];
    int NumOfCity = 0;
    int i;
    //initalized all city in the graph
    for (i = 0; i < graph->NumOfCity; i++) {
        distances[i] = INFINITY;
        CheckVisit[i] = 0;
        previous[i] = -1;
    }
    //here x1,x2 to find the index for City1 and City 2 in Graph
   // int X1 = GetIndexByName(graph,City1);
   // int X2 = GetIndexByName(graph,City2) ;
    int X1 = -1;
    int X2 = -1;
    for (i = 0; i < graph->NumOfCity; i++) {
        if (strcmp(graph->City[i].City_Name, City1) == 0) {
            X1 = i;
        }
        if (strcmp(graph->City[i].City_Name, City2) == 0) {
            X2 = i;
        }
    }

    if (X1 == -1 || X2 == -1) {
        printf("Invalid source or destination city\n");
        return;
    }
    //set the distance for city1 to 0
    distances[X1] = 0;
    //iterates over all cities in the graph
    while (NumOfCity < graph->NumOfCity) {
        //initializes the variable MIN with INFINITY as a placeholder to find the minimum distance
        int Min = INFINITY;
        //initializes the variable curr as -1, indicating that no city has been selected yet
        int curr = -1;
        //iterates over all cities in the graph
        for (i = 0; i < graph->NumOfCity; i++) {
            //checks if the city i has not been visited and if its distance is smaller than the current minimum distance
            if (!CheckVisit[i] && distances[i] < Min) {
                //updates the curr variable with the index of the city with the new minimum distance
                curr = i;
                //the current city i becomes the city with the new minimum distance
                Min = distances[i];
            }
        }
        if (curr == -1) {
            break;
        }
        // Mark the current city as visited
        CheckVisit[curr] = 1;
        NumOfCity++;
        //define an edge between the city
        ptr NEweEdge = graph->City[curr].edges;
        while (NEweEdge != NULL) {
            //define an index for edge
            int X3 = -1;
            //loop to  iterates over each city in the Cities array of the graph
            for (i = 0; i < graph->NumOfCity; i++) {
                if (strcmp(graph->City[i].City_Name, NEweEdge->city) == 0) {
                    //if it found return the index
                    X3 = i;
                }
            }
            //if it found and not visit
            if (X3 != -1 && !CheckVisit[X3]) {
                //indicating connection from x1 to x2
                int Dis = distances[curr] + NEweEdge->Distance;
                if (Dis < distances[X3]) {
                    distances[X3] = Dis;
                    previous[X3] = curr;
                }
            }
            //go to the next edge
            NEweEdge = NEweEdge->next;
        }
    }
    //if there is no city pre of city2
    if (previous[X2] == -1) {
        printf("There is no path from %s to %s\n", City1, City2);
        return;
    }
    int ShorPath[CITIES];
    int LengthOfPath = 0;
    //check all the pre city of the city2 to city1
    for (i = X2; i != -1; i = previous[i]) {
        ShorPath[LengthOfPath++] = i;
    }
    //print the path
    printf("Dijkstra path: ");
    for (i = LengthOfPath - 1; i >= 0; i--) {
        printf("%s", graph->City[ShorPath[i]].City_Name);
        if (i > 0) {
            printf(" -> ");
        }
    }
    printf("\nDijkstra distance: %d\n", distances[X2]);
    //print the path to file
    FILE* out = fopen("shortest_distance.txt", "a");
    if (out == NULL)
        printf("Failed to create shortest_distance.txt\n");
    for (i = LengthOfPath - 1; i >= 0; i--) {
        fprintf(out,"%s", graph->City[ShorPath[i]].City_Name);
        if (i > 0) {
            fprintf(out," -> ");
        }
    }
    fprintf(out,"\nDijkstra distance: %d\n", distances[X2]);
}
//function to find the short path by BFS and print it
void BFS(struct Graph* graph, const char* City1, const char* City2) {
    //this to point the visit city
    int visited[CITIES];
    //this to find the previous city
    int previous[CITIES];
    // Create a queue for BFS
    //the queue is used to store the cities that need to be visited and explored
    int Q[CITIES];
    //The front variable points to the index of the front element in the queue, which is the element to be dequeued next
    int front = 0;
    //The rear variable points to the index where the next element will be inserted into the queue
    int rear = 0;
    //The loop iterates over all cities in the graph to initialized it
    for (int i = 0; i < graph->NumOfCity; i++) {
        //define as unvisited
        visited[i] = 0;
        //define as no node pre it
        previous[i] = -1;
    }
    //find the index for each city
    int x1 = -1;
    int x2 = -1;
    for (int i = 0; i < graph->NumOfCity; i++) {
        if (strcmp(graph->City[i].City_Name, City1) == 0) {
            x1 = i;
        }
        if (strcmp(graph->City[i].City_Name, City2) == 0) {
            x2 = i;
        }
    }
    if (x1 == -1 || x2 == -1) {
        printf("Invalid source or destination city\n");
        return;
    }
    // Mark the  city1 as visited and enqueue it
    visited[x1] = 1;
    //When the source city is enqueued, rear is incremented
    Q[rear++] = x1;
    //while  there are still elements in the queue that need to be processed
    //the loop continues until the queue becomes empty
    while (front != rear) {
        // Dequeue a city from the queue
        int curr = Q[front++];
        //define an edge between the city
        ptr NewEdge =graph->City[curr].edges;
        while (NewEdge != NULL) {
            //define an index for edge
            int EdgeIndex = -1;
            //loop to  iterates over each city in the Cities array of the graph
            for (int i = 0; i < graph->NumOfCity; i++) {
                if (strcmp(graph->City[i].City_Name, NewEdge->city) == 0) {
                    //if it found return the index
                    EdgeIndex = i;
                }
            }
            //if it found and not visit
            if (EdgeIndex != -1 && !visited[EdgeIndex]) {
                //mark it as visit
                visited[EdgeIndex] = 1;
                // sets the previous city index for city i to curr to keep track of the shortest path
                previous[EdgeIndex] = curr;
                // enqueues city i by adding it to the end of the queue
                Q[rear++] = EdgeIndex;
            }
            //go to the next edge
            NewEdge = NewEdge->next;
        }
    }
    //if there is no city pre of city2
    if (previous[x2] == -1) {
        printf("There is no path from %s to %s\n", City1, City2);
        return;
    }
    int ShortPath[CITIES];
    int LengthOfPath = 0;
    //check all the pre city of the city2 to city1
    for (int i = x2; i != -1; i = previous[i]) {
        ShortPath[LengthOfPath++] = i;
    }
    printf("BFS path: ");
    for (int i = LengthOfPath - 1; i >= 0; i--) {
        printf("%s", graph->City[ShortPath[i]].City_Name);
        if (i > 0) {
            printf(" -> ");
        }
    }
    printf("\nBFS cost: %d\n", LengthOfPath - 1);
    FILE* out = fopen("shortest_distance.txt", "a");
    if (out == NULL)
        printf("Failed to create shortest_distance.txt\n");
    fprintf(out,"\nBFS path: ");
    for (int i = LengthOfPath - 1; i >= 0; i--) {
        fprintf(out,"%s", graph->City[ShortPath[i]].City_Name);
        if (i > 0) {
            fprintf(out," -> ");
        }
    }
    fprintf(out,"\nBFS cost: %d\n", LengthOfPath - 1);
}