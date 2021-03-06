#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>

const int N = 50;

int n, match[N];
bool graph[N][N], visited[N];

bool find(int i) {
    if (visited[i]) {
        return false;
    }
    visited[i] = true;
    for (int j = 0; j < n; ++ j) {
        if (graph[i][j] && (match[j] == -1 || find(match[j]))) {
            match[j] = i;
            return true;
        }
    }
    return false;
}

int main()
{
    int m[2];
    while (scanf("%d%d%d", &n, m, m + 1) == 3) {
        std::vector <int> lower_bound(n, 0),
                          upper_bound(n, n - 1),
                          begin(n, 0),
                          end(n, n);
        for (int i = 0; i < 2; ++ i) {
            for (int _ = 0; _ < m[i]; ++ _) {
                int a, b, c;
                scanf("%d%d%d", &a, &b, &c);
                a --;
                c --;
                for (int j = a; j < b; ++ j) {
                    if (i == 0) { // min
                        lower_bound[j] = std::max(lower_bound[j], c);
                    } else { // max
                        upper_bound[j] = std::min(upper_bound[j], c);
                    }
                }
                begin[c] = std::max(begin[c], a);
                end[c] = std::min(end[c], b);
            }
        }
        for (int i = 0; i < n; ++ i) {
            for (int j = 0; j < n; ++ j) {
                graph[i][j] = lower_bound[i] <= j && j <= upper_bound[i] && begin[j] <= i && i < end[j];
            }
        }
        memset(match, -1, sizeof(*match) * n);
        bool valid = true;
        for (int i = n - 1; i >= 0 && valid; -- i) {
            memset(visited, 0, sizeof(*visited) * n);
            valid &= find(i);
        }
        if (valid) {
            std::vector <int> result(n);
            for (int i = 0; i < n; ++ i) {
                result[match[i]] = i;
            }
            for (int i = 0; i < n; ++ i) {
                printf("%d%c", 1 + result[i], " \n"[i == n - 1]);
            }
        } else {
            puts("-1");
        }
    }
    return 0;
}
