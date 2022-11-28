#include "vef.h"
#include "wavefront_io.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

tuple<int, int, int> vef_from_wavefront(struct vef& v_e_f,
                                        const char* file_name)
{
    vector<vector<double>> vertices;
    vector<vector<int>> faces;
    tuple<int, int> data = wf_read_from_wavefront(vertices, faces, file_name);
    int num_v = get<0>(data);
    int num_f = get<1>(data);
    cout << "vertices: " << num_v << " faces: " << num_f << endl;
    // contains vertex, vertex, face containing both vertex
    // e.g : e1 -> (v1, v2), (f5)
    vector<tuple<int, int, int>> edges_v;
    // e.g : e1 ->(v1, v2) (f1, -1), (f2, 1)
    vector<vector<tuple<int, int>>> edges_f;
    // e.g : f1 -> (v1, v2, v3, v4), (e7, e8, e9, e10)
    vector<vector<tuple<int, int, int, int>>> face_e_f;

    vector<megatuple> vertex_f_e;
    construct_edges(edges_v, edges_f, faces);
    construct_faces(face_e_f, edges_f, faces);
    construct_vertices(vertex_f_e, vertices, edges_f, face_e_f);
    int num_e = edges_v.size();

    // -----Populate vef structure-----
    // verticesEF
    v_e_f.verticesEF.reserve(vertex_f_e.size());
    for (long unsigned int i = 0; i < vertex_f_e.size(); i++)
    {
        vef_vertex vef_vertex;
        megatuple t = vertex_f_e[i];
        vef_vertex.ind = i + 1;
        tuple<double, double, double> t_coord = get<0>(t);
        tuple<int, int, int> t_edge = get<1>(t);
        tuple<int, int, int> t_face = get<2>(t);
        vector<double> v_coord{get<0>(t_coord), get<1>(t_coord),
                               get<2>(t_coord)};
        vector<int> v_edge{get<0>(t_edge), get<1>(t_edge), get<2>(t_edge)};
        vector<int> v_face{get<0>(t_face), get<1>(t_face), get<2>(t_face)};
        vef_vertex.coordinates = v_coord;
        vef_vertex.edges = v_edge;
        vef_vertex.faces = v_face;
        v_e_f.verticesEF.push_back(vef_vertex);
    }

    // edgesVF
    v_e_f.edgesVF.reserve(edges_f.size());
    for (long unsigned int i = 0; i < edges_f.size(); i++)
    {
        vef_edge vef_edge;
        vef_edge.ind = i + 1;
        tuple<int, int> vertices = edges_f[i][0];
        tuple<int, int> fac_1 = edges_f[i][1];
        tuple<int, int> fac_2 = edges_f[i][2];
        vector<int> v{get<0>(vertices), get<1>(vertices)};
        vef_edge.vertices = v;
        vector<pair<int, int>> fc;
        fc.push_back(make_pair(get<0>(fac_1), get<1>(fac_1)));
        fc.push_back(make_pair(get<0>(fac_2), get<1>(fac_2)));
        vef_edge.faces = fc;
        v_e_f.edgesVF.push_back(vef_edge);
    }

    // facesVE
    v_e_f.facesVE.reserve(face_e_f.size());
    for (long unsigned int i = 0; i < face_e_f.size(); i++)
    {
        vef_face vef_face;
        vef_face.ind = i + 1;
        tuple<int, int, int, int> vert = face_e_f[i][0];
        tuple<int, int, int, int> edg = face_e_f[i][1];
        vector<int> vertices;
        vector<int> edges;
        vertices = {get<0>(vert), get<1>(vert), get<2>(vert), get<3>(vert)};
        edges = {get<0>(edg), get<1>(edg), get<2>(edg), get<3>(edg)};
        vef_face.vertices = vertices;
        vef_face.edges = edges;
        v_e_f.facesVE.push_back(vef_face);
    }

    return make_tuple(num_v, num_e, num_f);
}

int vef_to_vef(struct vef& v_e_f, const char* file_name)
{
    ofstream f;
    cout << file_name << endl;
    f.open(file_name);
    f << "# " << file_name << "\n";
    cout << "size of vertices : " << v_e_f.verticesEF.size()<< endl;
    // First write vertices e_f
    for (size_t i = 0; i < v_e_f.verticesEF.size(); i++)
    {
        vef_vertex vef_vertex = v_e_f.verticesEF[i];
        // Coordinates
        f << "v " << vef_vertex.ind << " "
          << "<";
        for (int j = 0; j < 3; j++)
        {
            f << " " << vef_vertex.coordinates[j];
        }
        f << "> <";

        // edges
        for(size_t j=0; j<vef_vertex.edges.size(); j++)
        {
          f << " e" << vef_vertex.edges[i];
        }
        f << " > <";

        //faces
        for(size_t j = 0; j<vef_vertex.faces.size(); j++)
        {
          f << " f" << vef_vertex.faces[i];
        }
        f << " >\n";
    }
    f << "\n";

    //Write edges v_f
    for (size_t i = 0; i < v_e_f.edgesVF.size(); i++)
    {
      vef_edge vef_edge = v_e_f.edgesVF[i];
      f << "e" << vef_edge.ind;
      //vertices
      f << "< v" << vef_edge.vertices[0] <<" v" << vef_edge.vertices[1] <<" > <";
      //faces
      for(size_t j = 0; j < vef_edge.faces.size(); j++)
      {
        f << " (f" << vef_edge.faces[j].first << "," << vef_edge.faces[j].second <<") ";
      }
      f << ">\n";
    }
    f << "\n";

    //write faces v_e

    for(size_t i = 0; i< v_e_f.facesVE.size(); i++)
    {
      vef_face vef_face = v_e_f.facesVE[i];
      f << "f" << vef_face.ind << " <";
      //Vertices
      for(size_t j = 0; j<vef_face.vertices.size(); j++)
      {
        if(vef_face.vertices[j] != -1)
            f << " v" << vef_face.vertices[j];
      }
      f << " > <";

      //Edges
      for(size_t j = 0; j<vef_face.edges.size(); j++)
      {
        if(vef_face.edges[j] != -1)
            f << " e" << vef_face.edges[j];
      }
      f << " >\n";
    }

    cout << file_name << " created \n";
    return 0;
}
// Construction of edges_v, edges_f
void construct_edges(vector<tuple<int, int, int>>& edges_v,
                     vector<vector<tuple<int, int>>>& edges_f,
                     vector<vector<int>> &faces)
{
    int face_idx = 0;
    for (auto v : faces)
    {
        face_idx++;
        for (long unsigned int i = 0; i < v.size(); i++)
        {
            tuple<int, int, int> e;
            if (i + 1 == v.size()) // If end of vector, link last vertex with
                                   // first vertex
                e = make_tuple(v[i], v[0], face_idx);
            else
                e = make_tuple(v[i], v[i + 1], face_idx);
            edges_v.push_back(e);
        }
    }

    // Fill edges_f which list which faces belong to which edges and their
    // direction (-1 or 1)
    for (vector<tuple<int, int, int>>::iterator it = edges_v.begin();
         it != edges_v.end(); ++it)
    {
        int v1 = get<0>(*it);
        int v2 = get<1>(*it);
        vector<tuple<int, int>> v;
        v.push_back(make_tuple(v1, v2));
        for (vector<tuple<int, int, int>>::iterator it2 = it + 1; it2 != edges_v.end();)
        {
            if ((get<0>(*it2) == v2) && (get<1>(*it2) == v1))
            {
                tuple<int, int> t1 = make_tuple(get<2>(*it), 1);
                tuple<int, int> t2 = make_tuple(get<2>(*it2), -1);
                v.push_back(t1);
                v.push_back(t2);
                edges_f.push_back(v);
                it2 = edges_v.erase(it2);
            }
            else
              ++it2;
        }
    }
}

// Construction of face_v_e;
void construct_faces(vector<vector<tuple<int, int, int, int>>> &face_e_f,
                     vector<vector<tuple<int, int>>> &edges_f,
                     vector<vector<int>> &faces)
{
    for (auto v : faces)
    {
        //Fill vertices
        vector<tuple<int, int, int, int>> fef;
        if(v.size() < 4)
            fef.push_back(make_tuple(v[0], v[1], v[2], -1));
        else
            fef.push_back(make_tuple(v[0], v[1], v[2], v[3]));
        vector<int> f_e;
        for (long unsigned int i = 0; i < v.size(); i++)
        {
            int vertex1 = v[i];
            int vertex2;
            if (i + 1 == v.size())
                vertex2 = v[0];
            else
                vertex2 = v[i + 1];

            // Iterate over each vector of tuples inside vector e
            int edge_idx = 0;
            for (auto e : edges_f)
            {
                edge_idx++;
                int v1 = get<0>(e[0]);
                int v2 = get<1>(e[0]);
                
                if ((v1 == vertex1 && v2 == vertex2) ||
                    (v1 == vertex2 && v2 == vertex1))
                {
                    f_e.push_back(edge_idx);
                }
            }
        }
        if(f_e.size() == 3)
            fef.push_back(make_tuple(f_e[0], f_e[1], f_e[2], -1));
        else if(f_e.size() == 2)
            fef.push_back(make_tuple(f_e[0], f_e[1], -1, -1));
        else
            fef.push_back(make_tuple(f_e[0], f_e[1], f_e[2], f_e[3]));
        face_e_f.push_back(fef);
    }
}

void construct_vertices(vector<megatuple> &vertex_f_e,
                        vector<vector<double>> &vertices,
                        vector<vector<tuple<int, int>>> &edges_f,
                        vector<vector<tuple<int, int, int, int>>> &face_e_f)
{
    int v_idx = 0;
    for (auto v : vertices)
    {
        v_idx++;
        int e_idx = 0;
        tuple<double, double, double> vertex = make_tuple(v[0], v[1], v[2]);
        vector<int> edges;
        vector<int> faces;
        for (auto vec : edges_f)
        {
            e_idx++;
            // edges
            int v1 = get<0>(vec[0]);
            int v2 = get<1>(vec[0]);
            // Find the correct vertices, thanks to it we seek for the faces
            if (v1 == v_idx || v2 == v_idx)
            {
                edges.push_back(e_idx);
                int f1 = get<0>(vec[1]);
                int f2 = get<0>(vec[2]);
                faces.push_back(f1);
                faces.push_back(f2);
                //cout << "v:" <<v1 <<", v:" << v2 << ", v_idx: " << v_idx <<", e_idx; " << e_idx << ", f" << f1 << ", f" << f2 << endl;
            }
        }
        // cleaning the vectors, because there are repeated values
        sort(edges.begin(), edges.end());
        edges.erase(unique(edges.begin(), edges.end()), edges.end());
        
        cout << "edges: " << edges[0] <<", "<< edges[1] <<", " << edges[2] << endl;

        sort(faces.begin(), faces.end());
        faces.erase(unique(faces.begin(), faces.end()), faces.end());

        cout << "faces: " << faces[0] <<", "<< faces[1] <<", " << faces[2] << endl;
        tuple<int, int, int> ed;
        tuple<int, int, int> fac;
        if(edges.size() == 2){
            ed = make_tuple(edges[0], edges[1], -1);
            fac = make_tuple(faces[0], faces[1], -1);
        }
        else if(edges.size() == 1){
            ed = make_tuple(edges[0], -1, -1);
            fac = make_tuple(faces[0], -1, -1);
        }
        else {
            ed = make_tuple(edges[0], edges[1], edges[2]);
            fac = make_tuple(faces[0], faces[1], faces[2]);
        }
        megatuple all = make_tuple(vertex, ed, fac);
        vertex_f_e.push_back(all);
    }
}