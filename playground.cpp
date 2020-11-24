#include <pcl/point_cloud.h>
#include <pcl/io/pcd_io.h>
#include <pcl/io/ply_io.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <fstream>

using namespace std;
using namespace pcl;
using namespace pcl::io;
using namespace pcl::visualization;

int main(int argc, char**argv) {
    if(argc < 2) {
        cout << "Usage: " << argv[0] << " <object>" << endl;
    }
    
    // Load
    PointCloud<PointXYZRGBA>::Ptr object(new PointCloud<PointXYZRGBA>);
    loadPLYFile(argv[1], *object);

    float minZ = 1000000;
    float maxZ = 0;
    for (int i = 0; i < object->size(); ++i) {
        PointXYZRGBA point = object->points[i];
        if(point.z > maxZ) {
            maxZ = point.z;
        } else if (point.z < minZ) {
            minZ = point.z;
        }
    }

    cout << "Number of points: " <<  object->size() << endl;

    PointCloud<PointXYZRGBA>::Ptr reduced_object(new PointCloud<PointXYZRGBA>);
    for (int i = 0; i < object->size(); ++i) {
        if(object->points[i].z > -1.5){
            reduced_object->push_back(object->points[i]);
        }
    }

    // Show
    PCLVisualizer v("PointCloud");
    v.addPointCloud<PointXYZRGBA>(reduced_object, "object");
    v.spin();
}
