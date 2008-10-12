/************************************************************************
Main function.
Apr 2 2008, HE Zhao
http://hezhao.net
he@hezhao.net
************************************************************************/

#include <iostream>
#include "getopt.h"
#include "quadrics.h"
#include "MxTimer.h"
#include "matrix.h"
using namespace std;

#define TIME(t, cmd) { t=mx_get_time(); cmd; t=mx_get_time() - t; }

int face_target;
char* input_file = NULL;
char* output_file = NULL;
double compactness_ratio = 0.0;

static char **global_argv;
static char *options = "O:B:W:t:Fo:m:c:rjI:M:qh";

static char *usage_string =
"-t <n>         Set the target number of faces.\n"
"-o <file>      Output final model to the given file.\n"
"-c <ratio>     Set the desired compactness ratio.\n"
"-h             Print help.\n";

static void print_usage()
{
	cout << endl;
	cout << endl << "usage: " << global_argv[0]
	<< " <options> [filename]" << endl;
	cout << endl
		<< "Available options:" << endl
		<< usage_string << endl;
	system("PAUSE");
}

static void usage_error(char *msg=NULL)
{
	if( msg )  cout << "Error: " << msg << endl;
	print_usage();
	exit(1);
}

void process_cmdline(int argc, char **argv)
{
	int opt;
	global_argv = argv;
	
	if (argc == 1)
	{
		print_usage();
		exit(1);
	}
	input_file = argv[1];
	while( (opt = getopt(argc, argv, options)) != EOF )
	{
		switch( opt )
		{
		case 't':  face_target = atoi(optarg); break;
		case 'o':  output_file = optarg; break;
		case 'c':  compactness_ratio = atof(optarg); break;
		case 'h':  print_usage(); exit(0); break;
		default:   usage_error("Malformed command line."); break;
		}
	}
}

int main(int argc, char** argv)
{
	Quadrics q;
	double input_time, init_time, slim_time, output_time;

	process_cmdline(argc, argv);
	
	TIME(input_time, q.read_smf(input_file));
	
	if (compactness_ratio > 0.0 && compactness_ratio <= 1.0) 
		face_target = q.get_face_num() * compactness_ratio;

	TIME(init_time, q.initial_quadrics());
	TIME(slim_time, q.construct_n_contract(face_target));
	TIME(output_time, q.write_smf(output_file));

	cout << "+ Running time" << endl;
	cout << "    Setup      : " << input_time << " sec" << endl;
	cout << "    PM init : " << init_time << " sec" << endl;
	cout << "    PM run  : " << slim_time << " sec" << endl;
	cout << "    Output     : " << output_time << " sec" << endl;
	cout << endl;
	cout << "    Total      : "
		<< input_time+init_time+slim_time+output_time << endl;
}
