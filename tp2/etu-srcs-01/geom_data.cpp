#include <iostream>
#include <vector>
#include <iterator>

#include "geom_data.h"

using namespace std;

int
geom_read_prism_data(vector <vector<double>> &polygon, vector<double>  &offset, const char* file_name_in)
{
  cout << file_name_in << " read \n";
  std::ifstream file_in;
  file_in.open (file_name_in);
  int num_v= 0;std::string _token;
  if(!file_in.good())
    {file_in.clear();
      cout<< ": file_in problems \n";
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
      polygon.push_back(vertex);
    }
    if(_token=="offset"){
      file_in >> offset[0] >> offset[1] >> offset[2];
    }
  }
  return  num_v++;
}

int
geom_read_pyramid_data(vector <vector<double>> &polygon, vector<double>  &offset, const char* file_name_in)
{
  // TO DO
  return -1;;
}
