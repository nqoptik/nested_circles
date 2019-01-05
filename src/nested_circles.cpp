#include <cstdlib>
#include <string>
#include <cmath>

#define swap(type, a, b) \
    {                    \
        type temp = a;   \
        a = b;           \
        b = temp;        \
    }

const int maxNumberOfCircle = 1000000;

int n, length, count;
int rank[maxNumberOfCircle][3], detail[maxNumberOfCircle];

float X, Y;
float x[maxNumberOfCircle + 2], y[maxNumberOfCircle + 2], r[maxNumberOfCircle + 2];

float distance(float x1, float y1, float x2, float y2);
bool pointIsInCircle(float x1, float y1, float x2, float y2, float r2);
bool circleIsInCircle(float x1, float y1, float r1, float x2, float y2, float r2);
void quickSort(int left, int right);
void getPoint();
void getAndSortCircles(std::string fileName);
void buildGraph();
void saveGraph(std::string fileName);
void loadGraph(std::string fileName);
void find();

int main(int argc, char** argv) {
    getAndSortCircles("data.txt");
    buildGraph();
    saveGraph("graph.txt");
    loadGraph("graph.txt");
    int next = 1;
    while (next == 1) {
        getPoint();
        find();
        for (int i = 0; i < count; i++) {
            printf("%10.3f%10.3f%11.3f\n", x[detail[i]], y[detail[i]], r[detail[i]]);
        }
        printf("Length of longest sequence: %3d\n", count);
        printf("-------------------------------\n");
        printf("Want to search more?(1/0): ");
        if (scanf("%d", &next) < 1) {
            printf("Failed to scan next.\n");
        }
    }
    getchar();
    return 0;
}

float distance(float x1, float y1, float x2, float y2) {
    float result = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
    return result;
}

bool pointIsInCircle(float x1, float y1, float x2, float y2, float r2) {
    if (distance(x1, y1, x2, y2) <= r2)
        return true;
    else
        return false;
}

bool circleIsInCircle(float x1, float y1, float r1, float x2, float y2, float r2) {
    if (distance(x1, y1, x2, y2) <= r2 - r1)
        return true;
    else
        return false;
}

void quickSort(int left, int right) {
    float key = r[(left + right) / 2];
    int i = left, j = right;

    while (i <= j) {
        while (r[i] < key)
            i++;
        while (r[j] > key)
            j--;
        if (i <= j) {
            if (i < j) {
                swap(float, r[i], r[j]);
                swap(float, x[i], x[j]);
                swap(float, y[i], y[j]);
            }
            i++;
            j--;
        }
    }

    if (left < j)
        quickSort(left, j);
    if (i < right)
        quickSort(i, right);
}

void getAndSortCircles(std::string fileName) {
    printf("Loading and Sorting circle...");
    FILE* file;
    file = fopen(fileName.c_str(), "r");
    if (file == NULL) {
        printf("Error.\n");
    } else {
        if (fscanf(file, "%d\n", &n) < 1) {
            printf("Failed to scan n.\n");
        }
        for (int i = 1; i < n + 1; i++) {
            if (fscanf(file, "%f%f%f\n", &x[i], &y[i], &r[i]) < 3) {
                printf("Failed to scan x, y, z.\n");
            }
        }
        fclose(file);
    }
    quickSort(1, n);

    x[0] = x[n + 1] = x[1];
    y[0] = y[n + 1] = y[1];
    r[0] = 0;
    r[n + 1] = 999999;
    printf("done.\n");
}

void saveGraph(std::string fileName) {
    printf("Saving graph...");
    FILE* file;
    file = fopen(fileName.c_str(), "w");
    if (file == NULL) {
        printf("Error.\n");
    } else {
        fprintf(file, "%d\n", n);
        for (int i = 0; i <= n; i++) {
            fprintf(file, "%10d %10d% 10d\n", rank[i][0], rank[i][1], rank[i][2]);
        }
        fclose(file);
    }
    printf("done.\n");
}

void loadGraph(std::string fileName) {
    printf("Loading graph...");
    FILE* file;
    file = fopen(fileName.c_str(), "r");
    if (file == NULL) {
        printf("Error.\n");
    } else {
        if (fscanf(file, "%d\n", &n) < 1) {
            printf("Failed to scan n.\n");
        }
        for (int i = 0; i <= n; i++) {
            if (fscanf(file, "%d%d%d\n", &rank[i][0], &rank[i][1], &rank[i][2]) < 3) {
                printf("Failed to scan x, y, z.\n");
            }
        }
        fclose(file);
    }
    printf("done.\n");
}

void getPoint() {
    printf("Enter searching point: \n");
    printf("X = ");
    if (scanf("%f", &X) < 1) {
        printf("Failed to enter X.\n");
    }
    printf("Y = ");
    if (scanf("%f", &Y) < 1) {
        printf("Failed to enter Y.\n");
    }
}

void buildGraph() {
    printf("bulding graph...");
    length = 1;
    rank[0][0] = n + 1;
    rank[0][1] = 0;
    rank[0][2] = n + 2;

    for (int vertex = n; vertex > 0; vertex--) {
        bool stop = false;
        int i = length;
        while (!stop) {
            i--;
            if (circleIsInCircle(x[vertex], y[vertex], r[vertex], x[rank[i][0]], y[rank[i][0]], r[rank[i][0]])) {
                int t = i + 1;
                if (i == length - 1) {
                    t = length;
                } else {
                    while (rank[t][1] == rank[i][1]) {
                        t++;
                    }
                }
                for (int j = length + 1; j > t; j--) {
                    rank[j][0] = rank[j - 1][0];
                    rank[j][1] = rank[j - 1][1];
                    rank[j][2] = rank[j - 1][2];
                }
                rank[t][0] = vertex;
                rank[t][1] = rank[i][1] + 1;
                rank[t][2] = rank[i][0];
                length++;

                stop = true;
            }
        }
    }
    printf("done.\n");
}

void find() {
    int temp = n + 1;
    bool stop = false;
    while (!stop) {
        temp--;
        if (circleIsInCircle(X, Y, 0, x[rank[temp][0]], y[rank[temp][0]], r[rank[temp][0]])) {
            stop = true;
        }
    }

    count = 0;
    int downIndex = temp;
    while (temp != 0) {
        downIndex--;
        if (rank[temp][2] == rank[downIndex][0]) {
            detail[count] = rank[temp][0];
            count++;
            temp = downIndex;
        }
    }
}
