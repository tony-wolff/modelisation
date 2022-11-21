#include "main.h"

using namespace std;


int main()
{
  struct vef vef;
  struct vef &v_e_f = vef;;
  {
    vector<double> v_off(3);
    vector <vector<double>> polygon;
    vector <vector<double>> vertices;
    vector <vector<int>> faces;
    int n= geom_read_prism_data(polygon, v_off,"./DAT/prism_01.dat"); 
    make_prism(n , polygon, v_off, vertices, faces);
    wf_write_to_wavefront(vertices, faces, "./OBJ/prism_01.obj");
    vef_from_wavefront(v_e_f, "./OBJ/prism_01.obj");
    vef_to_vef(v_e_f, "./VEF/prism_01.vef");
  }
  {
    vector<double> v_off(3);
    vector <vector<double>> polygon;
    vector <vector<double>> vertices;
    vector <vector<int>> faces;
    int n= geom_read_pyramid_data(polygon, v_off,"./DAT/pyramid_01.dat"); 
    make_pyramid(n , polygon, v_off, vertices, faces);
    wf_write_to_wavefront(vertices, faces, "./OBJ/pyramid_01.obj");
    vef_from_wavefront(v_e_f, "./OBJ/pyramid_01.obj");
    vef_to_vef(v_e_f, "./VEF/pyramid_01.vef");
  }
  {
    vector<double> v_off(3);
    vector <vector<double>> polygon;
    vector <vector<double>> vertices;
    vector <vector<int>> faces;
    int n= geom_read_prism_data(polygon, v_off,"./DAT/prism_01.dat"); 
    make_prism_shell(n , polygon, v_off, vertices, faces);
    wf_write_to_wavefront(vertices, faces, "./OBJ/prism_shell_01.obj");
    vef_from_wavefront(v_e_f, "./OBJ/prism_shell_01.obj");
    vef_to_vef(v_e_f, "./VEF/prism_shell_01.vef");
  }
  cout << " SUCCESS \n";
  return 0;
}
