#include <pcl/point_cloud.h>
#include <pcl/io/ply_io.h>
#include <pcl/visualization/pcl_visualizer.h>

#include <iostream>
#include <filesystem>
#include <stdio.h>
#include <thread>

using namespace std;
using namespace pcl;
using namespace pcl::io;
using namespace pcl::visualization;

bool spin;

void decidePCLFate(const filesystem::directory_entry &entry){
    char key;
    cin >> key;
    if (key == 'n'){
        remove(entry.path());
        cout << entry.path() << " - deleted" << endl;
    }
    spin = false;
}

int main(int argc, char**argv) {
    if(argc < 2) {
        cout << "Usage: " << argv[0] << " <path/to/ply_files>" << endl;
        return 0;
    }

    string path = argv[1];
    for (const auto & entry : filesystem::directory_iterator(path)) {
        // Load
        PointCloud<PointNormal>::Ptr object(new PointCloud <PointNormal>);
        loadPLYFile(entry.path(), *object);

        // New point cloud
        PointCloud<PointNormal>::Ptr reduced_object(new PointCloud <PointNormal>);
        for (int i = 0; i < object->size(); ++i) {
            if (object->points[i].z > -1.5) {
                reduced_object->push_back(object->points[i]);
            }
        }
        spin = true;
        thread t(decidePCLFate,entry);

        PCLVisualizer v("PointCloud");
        v.addPointCloud<PointNormal>(object, "object");
        while (spin){
            v.spinOnce(10);
        }
        t.join();
    }
}
