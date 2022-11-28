#ifndef VEF_H
#define VEF_H

using namespace std;
typedef tuple<tuple<double, double, double> , tuple<int, int, int>, tuple<int, int, int>> megatuple;
struct vef_vertex{
  int ind;
  vector<double> coordinates;
  vector <int> edges;
  vector <int> faces;
};

struct vef_edge{
  int ind;
  vector <int> vertices;// ind(v0) < ind(v1) 
  vector <pair<int,int>> faces; //  if v0->v1 then (ind(f), +1) else (ind(f), -1)
};

struct vef_face{
  int ind;
  vector <int> vertices;
  vector <int> edges;
};

struct vef{
  vector <vef_vertex> verticesEF;
  vector <vef_edge> edgesVF;
  vector <vef_face> facesVE;
};

extern tuple <int, int, int>  vef_from_wavefront(struct vef &vef, const char* file_name);
extern int vef_to_vef(struct vef &v_e_f, const char* file_name);
extern tuple <int, int> read_wavefront(const char* file_name, vector<vector<double>> &vertices, vector<vector<int>> &faces);
extern void construct_edges(vector<tuple<int, int, int>> &edges_v, vector<vector<tuple<int, int>>> &edges_f, vector<vector<int>> &faces);
void construct_faces(vector<vector<tuple<int, int, int, int>>> &face_e_f, vector<vector<tuple<int, int>>> &edges_f, vector<vector<int>> &faces);
void construct_vertices(vector<tuple<tuple<double, double, double> , tuple<int, int, int>, tuple<int, int, int>>> &vertex_f_e,
vector<vector<double>> &vertices, vector<vector<tuple<int, int>>> &edges_f, vector<vector<tuple<int, int, int, int>>> &face_e_f);
#endif /*  VEF_H */
