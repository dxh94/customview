#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_SIZE 100

int a;

typedef struct {
    int x;
    int y;
} Point;

bool isValidMove(int x, int y, int m, int n, int obstacles[MAX_SIZE][MAX_SIZE], bool visited[MAX_SIZE][MAX_SIZE]) {
    return x >= 0 && x < m && y >= 0 && y < n && obstacles[x][y] == 0 && !visited[x][y];
}

int shortestPath(int m, int n, int obstacles[MAX_SIZE][MAX_SIZE], Point start, Point end) {
    bool visited[MAX_SIZE][MAX_SIZE] = {false};
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};
    
    typedef struct {
        int x, y, dist;
    } QueueItem;
    
    QueueItem queue[MAX_SIZE * MAX_SIZE];
    int front = 0, rear = 0;
    
    queue[rear++] = (QueueItem){start.x, start.y, 0};
    visited[start.x][start.y] = true;

    while (front < rear) {
        QueueItem current = queue[front++];
        
        if (current.x == end.x && current.y == end.y)
            return current.dist;

        for (int i = 0; i < 4; ++i) {
            int new_x = current.x + dx[i];
            int new_y = current.y + dy[i]; 
            
            if (isValidMove(new_x, new_y, m, n, obstacles, visited)) {
                visited[new_x][new_y] = true;
                queue[rear++] = (QueueItem){new_x, new_y, current.dist + 1};
            }
        }
    }

    return -1; 
}

int main() {
    int m, n;
    printf("Nhap kich thuoc ban co (m n): ");
    scanf("%d %d", &m, &n);
    
    int obstacles[MAX_SIZE][MAX_SIZE] = {0}; 
    
    int num_obstacles;
    printf("Nhap so luong vat can: ");
    scanf("%d", &num_obstacles);
    printf("Nhap toa do cac vat can (x y):\n");
    for (int i = 0; i < num_obstacles; ++i) {
        int x, y;
        scanf("%d %d", &x, &y);
        obstacles[x][y] = 1;
    }

    Point start, end; 
    printf("Nhap toa do diem bat dau (x y): ");
    scanf("%d %d", &start.x, &start.y);
    printf("Nhap toa do diem ket thuc (x y): ");
    scanf("%d %d", &end.x, &end.y);

    printf("So buoc ngan nhat: %d\n", shortestPath(m, n, obstacles, start, end));

    return 0;
}