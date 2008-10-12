/************************************************************************
Quadric error metrics header file.
Apr 2 2008, HE Zhao
http://hezhao.net
he@hezhao.net
************************************************************************/

#ifndef _QUADRICS_H_
#define _QUADRICS_H_

#include <map>
#include <deque> 
#include "matrix.h"

typedef struct _vertex
{
	double x;
	double y;
	double z;
} Vertex;

typedef struct _face
{
	unsigned int id_vertex[3];
	double plane[4];		/* p = [a b c d] */
} Face;

typedef struct _vsplit		/* (v1, v2) -> vf(vx, vy, vz) */
{
	Vertex v1;
	Vertex v2;
	Vertex vf;
} Vsplit;

typedef std::map<int, Vertex> Vertices;
typedef std::deque<Face> Faces;
typedef std::pair<int, int> Pair;
typedef std::map<Pair, double> Errors;
typedef std::deque<Vsplit> Vsplits;
typedef std::map<int, Matrix> Matrices;

class Quadrics
{
public:
	Quadrics();
	~Quadrics();
	int get_face_num();
	void read_smf(char* filename);
	void initial_quadrics(void);
	void construct_n_contract(int target_num_faces);
	void write_smf(char* filename);
private:
	// fields
	Vertices vertices;
	Faces faces;
	Matrices quadrics;		/* quadric for each vertex */
	Errors errors;
	Vsplits vsplits;
	// methods
	void parse(FILE* file);
	void select_pair();
	double calculate_error(int id_v1, int id_v2, double* vx=0, double* vy=0, double* vz=0);
	// inline methods
	double distance(Vertex v1, Vertex v2);
	double vertex_error(Matrix q, double vx, double vy, double vz);
};

#endif
