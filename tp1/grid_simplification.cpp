#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/grid_simplify_point_set.h>
#include <CGAL/IO/read_points.h>
#include <CGAL/IO/write_points.h>
#include <vector>
#include <fstream>
// types
typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;
typedef Kernel::Point_3 Point;
int main(int argc, char*argv[])
{
  const std::string fname = (argc>1) ? argv[1] : "../data/CQ500-CT-0.xyz";
  // Reads a point set file in points[].
  std::vector<Point> points;
  if(!CGAL::IO::read_points(fname, std::back_inserter(points)))
  {
    std::cerr << "Error: cannot read file " << fname << std::endl;
    return EXIT_FAILURE;
  }
  // simplification by clustering using erase-remove idiom
  double cell_size = 10;
  points.erase(CGAL::grid_simplify_point_set(points, cell_size), points.end());
  // Optional: after erase(), shrink_to_fit to trim excess capacity
  points.shrink_to_fit();
  CGAL::IO::write_points("../data/out.xyz", points, CGAL::parameters::stream_precision(17));
  return EXIT_SUCCESS;
}

