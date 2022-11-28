#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>
#include <vector>

using namespace std;

void make_prism_shell(int n, vector<vector<double>> polygon,
                      vector<double> offset, vector<vector<double>> &vertices,
                      vector<vector<int>> &faces) {
  for (auto v : polygon) {
    vertices.push_back(v);
  }
  for (int i = 0; i < n; i++) {
    vector<double> vertex(3);
    vertex[0] = polygon[i][0] + offset[0];
    vertex[1] = polygon[i][1] + offset[1];
    vertex[2] = polygon[i][2] + offset[2];
    vertices.push_back(vertex);
  }
  for (int i = 1; i <= n; i++) {
    int i1 = i;
    int i2 = (i+1)%(n+1);
    if(i2 == 0)
      i2=1;
    int i3 = (i+1+n)%(2*n+1);
    if(i3 == 0)
      i3=5;
    int i4 = (i + n)%(2*n+1);
    vector<int> f {i1, i2, i3, i4};
    faces.push_back(f);
  }
}

void make_prism(int n, vector<vector<double>> polygon, vector<double> offset,
                vector<vector<double>> &vertices, vector<vector<int>> &faces) {

  make_prism_shell(n, polygon, offset, vertices, faces);
  vector<int> base(n);
  vector<int> down(n);
  for(int i=0; i<n; i++)
  {
    base[i] = n-i;
    down[i] = i+n+1;
  }
  faces.push_back(base);
  faces.push_back(down);
}

void make_pyramid(int n, vector<vector<double>> polygon, vector<double> appex,
                  vector<vector<double>> &vertices, vector<vector<int>> &faces)
{
    for (int i = 0; i < n; i++)
        vertices.push_back(polygon[i]);

    /*
    vector<double> middle{(polygon[0][0] + polygon[1][0]) / 2, (polygon[1][1] + polygon[2][1]) / 2, polygon[0][2]};
    vector<double> vertex(3);
    vertex[0] = middle[0];
    vertex[1] = middle[1];
    vertex[2] = middle[2] + appex[2];
    vertices.push_back(vertex);
    */
    vertices.push_back(appex);

    // obtenir le contour de la pyramide
    for (int i = 1; i <= n; i++)
    {
        int i1 = i % (n + 1);
        int i2 = (i + 1) % n;
        if (i2 == 0)
            i2 = 4;
        int i3 = n + 1;
        vector<int> f{i1, i2, i3};
        faces.push_back(f);
    }

    // la base(4,3,2,1)
    vector<int> base(n);
    for (int i = 0; i < n; i++)
        base[i] = n - i;
    faces.push_back(base);
}
