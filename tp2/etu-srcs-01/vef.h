#ifndef VEF_H
#define VEF_H

using namespace std;

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
 

#endif /*  VEF_H */
