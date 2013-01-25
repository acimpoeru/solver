#include "mesh.h"
#include "prepare.h"

using namespace std;

/*decompose application*/
int main(int argc,char* argv[]) {
	/*input stream*/
	ifstream input(argv[1]);

	/*cmd line*/
	int work = 0;
	Int start_index = 0;
	for(int i = 1;i < argc;i++) {
		if(!strcmp(argv[i],"-merge")) {
			work = 1;
		} else if(!strcmp(argv[i],"-vtk")) {
			work = 2;
		} else if(!strcmp(argv[i],"-poly")) {
			Vtk::write_polyhedral = true;
		} else if(!strcmp(argv[i],"-start")) {
			i++;
			start_index = atoi(argv[i]);
		}
	}

    /*read mesh & fields*/
	input >> Mesh::gMeshName;
	Mesh::readMesh();
	Mesh::initGeomMeshFields(work != 0);
	IntVector n;
	input >> n;
	vector<string> fields;
	input >> fields;
	cout << "fields " << fields << endl;

	/*decomposition,mergin and vtk*/
	if(work == 1) {
		Prepare::merge(Mesh::gMesh,&n[0],fields,Mesh::gMeshName,start_index);
	} else if(work == 2) {
		Prepare::convertVTK(Mesh::gMesh,fields,start_index);
	} else{
		Prepare::decomposeXYZ(Mesh::gMesh,&n[0]);
		Prepare::decomposeFields(fields,Mesh::gMeshName,start_index);
	} 
	return 0;
}
