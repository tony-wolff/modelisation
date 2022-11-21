#include <vector>
#include <iostream>
#include <fstream>


#include "wavefront_io.h"

using namespace std;
std::pair <int,int>
wf_read_from_wavefront(vector <vector<double>> &vertices,
			    vector <vector<int>> &faces, const char* file_name_in){
  std::ifstream file_in;
  file_in.open (file_name_in);
  int num_v= 0;
  int num_f= 0;
  // http://saurabhg.com/programming/wavefront-obj-reader-building-cgalpolyhedron_3/
   
  std::string _token;
   if(!file_in.good())
     {file_in.clear();
       cout<< "wf_read_from_wavefront: file_in problems"<<"\n";
       exit(1);
     }
  file_in.seekg(0);
  while(!file_in.eof()){
      _token = ""; // Reset token.
      file_in >> _token;
      if(_token=="v"){
	  vector<double> vertex(3);
	  file_in >> vertex[0] >> vertex[1] >> vertex[2];
	  num_v++;
	  vertices.push_back(vertex);
	}
      else if(_token=="f"){
	  std::string _line;
	  getline(file_in, _line);
	  std::istringstream _stream(_line);
	  std::vector<std::string> _vertices;
	  std::copy(std::istream_iterator<std::string>(_stream), 
		    std::istream_iterator<std::string>(), 
		    std::back_inserter(_vertices));
	  vector<int> vertices(_vertices.size());
	  for(size_t i=0 ; i<_vertices.size() ; ++i) {
	    std::string::size_type _pos = _vertices[i].find('/', 0);
	    std::string _indexStr = _vertices[i].substr(0, _pos);
	    vertices[i]= stoi(_indexStr);
	  }
	  num_f++;
	  faces.push_back(vertices);
      }
  }
  file_in.close();
  return make_pair(num_v,num_f);
}

std::pair <int,int>
wf_write_to_wavefront(vector <vector<double>> &vertices,
		       vector <vector<int>> &faces, const char* file_name){
  ofstream f;
  f.open (file_name);
  f << "# " << file_name << "\n";
  for(size_t i=0; i<vertices.size(); i++){
   f << "v "<< vertices[i][0]<< " "<< vertices[i][1]<< " " << vertices[i][2] << "\n";
  }
  for(size_t i=0; i<faces.size(); i++){
    f << 'f';f << ' ';
    for(size_t j=0; j<faces[i].size(); j++){
      f << faces[i][j] << ' ';
    }
    f << "\n";
  }
  cout << file_name << " created \n";
  return make_pair (vertices.size(),faces.size());
}

