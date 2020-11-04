#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include <string>
#include <utility>

using namespace std;

// Function to solve differential equation of f'(x) = g(x)
double h( double x) {
	return x;
}//end my_function

// CSV Creation function
// Inputs:
//	filename: Name of the File
//	dataset: a vector that contains a string and another vector
//		The string is used for the column title
//		The vector is used to store data
void write_csv(string filename, vector<pair<string, vector<double>>> dataset) {

	// Creates file 'filename'
	ofstream myFile(filename);
	
	//Column Names, pulls from dataset.at(i)
	//	So long as we're not at the end of the row of the dataset, insert a comma
	for (int i = 0; i < dataset.size(); ++i) {
		myFile << dataset.at(i).first;
		
		if (i != dataset.size() - 1) {
			myFile << ",";
		}//end if
		
	}//end for
	myFile << "\n";//New Line in file
	
	//Send Data stored in the second entry of dataset
	// Starting at the first entry of the second component of the vector (where the data is stored), iterate through all of these entries.
	// Builds the columns and rows of the system
	for (int i = 0; i < dataset.at(0).second.size(); ++i) {
	
		// Run through all elements of the second components of the vector, adding them to the CSV.
		for (int j = 0; j < dataset.size(); ++j) {
			myFile << dataset.at(j).second.at(i);
			if (j != dataset.size() - 1) {
				myFile << ",";// Add comma unless at end of row
			}
		}//end for
		
		myFile << "\n";//end line
		
	}//end for
	
	myFile.close();

}//end void: write_csv

int main () {

	// Boundaries of the system
	double xmin = 0.0;
	double xmax = 1.0;
	
	//Initial condition at x = 0
	double init_f = 0.0;//f(x=0)
	double init_g = 0.0;//f'(x=0)

	// Number of steps to solve the system over
	//Note: this num_steps needs 1 added to it so that the boundary of the problem is contained.
	int num_steps = 1000;
	double step_size = (xmax-xmin)/static_cast<double>(num_steps);
	
	//Arrays that hold the x values and solution set to the differential equation.
	vector <double> xpoints;// X values of the system
	vector <double> first_order_desol;// First order solution
	vector <double> first_order_dersol;// First order derivative solution
	vector <double> second_order_desol;// Second order solution
	vector <double> second_order_dersol;// Second order derivative solution
	vector <double> third_order_desol;// Third order solution
	vector <double> third_order_dersol;// Third order derivative solution
	
	// Generates the X values, starts at 0 and adds one step size to it every loop.
	for (int i = 0; i < num_steps + 1; ++i) {
	
		if (i == 0) {
			xpoints.push_back(0.0);
		}
		else {
			xpoints.push_back(xpoints[i-1] + step_size);
		}//end if
		
	}//end for
	
	//First Order Solution to f''(x) = h(x)
		// Solves with f'(x) = g(x)
		// And g(x+dx) = g(x) + g'(x)*dx
		// And f(x + dx) = f(x) + f'(x)*dx
		
	//Solving for g(x)
	for (int i = 0; i < num_steps + 1; ++i) {
	
		if (i == 0) {
			first_order_dersol.push_back(
				init_g
			);
		}
		else {
			first_order_dersol.push_back(
				first_order_dersol[i-1] + h(xpoints[i])*step_size
			);
		}//end if
		
	}//end for
	
	//Solving for f(x)
	for (int i = 0; i < num_steps + 1; ++i) {
	
		if (i == 0) {
			first_order_desol.push_back(
				init_f
			);
		}
		else {
			first_order_desol.push_back(
				first_order_desol[i-1] + first_order_desol[i]*step_size
			);
		}//end if
		
	}//end for
	
	
	
	//Second Order Solution to f'(x) = x
		// g(x+dx) = g(x) + h(x)*dx + 0.5*h'(x)*dx**2
		// f'(x) = g(x)
		// Solves with f(x+dx) = f(x) + f'(x)*dx + 0.5*f''(x)*dx**2
	
	//Solving for g(x)	
	for (int i = 0; i < num_steps + 1; ++i) {
	
		if (i==0) {
			second_order_dersol.push_back(
				init_g
			);
		}
		
		else {
			second_order_dersol.push_back(
				second_order_dersol[i-1] + h(xpoints[i])*step_size
				 + 0.5*step_size*(h(xpoints[i+1]) - h(xpoints[i]))
			);
		}//end if
		
	}//end for
	
	// Solving for f(x)
	for (int i = 0; i < num_steps + 1; ++i) {
	
		if (i==0) {
			second_order_desol.push_back(
				init_f
			);
		}
		
		else {
			second_order_desol.push_back(
				second_order_desol[i-1] + second_order_dersol[i]*step_size
				 + 0.5*step_size*h(xpoints[i])
			);
		}//end if
		
	}//end for
	
	//Third Order Solution to f'(x) = x
		// f'(x) = g
		// Solves with f(x+dx) = f(x) + f'(x)*dx + 0.5*f''(x)*dx**2 + (1.0/6.0)*f'''(x)*dx**3
		//Similarly for g(x + dx) = g(x) + g'(x)*dx +0.5g''(x)*dx**2 + ...
	// Solving for g
	for (int i = 0; i < num_steps + 1; ++i) {
	
		if (i==0) {
			third_order_dersol.push_back(
				init_g
			);
		}
		
		else {
			third_order_dersol.push_back(
				third_order_dersol[i-1] + h(xpoints[i])*step_size
				 + 0.5*step_size*(h(xpoints[i+1]) - h(xpoints[i]))
				 + (1.0/6.0)*step_size*(h(xpoints[i+2]) - 2.0*h(xpoints[i+1]) + h(xpoints[i]))
			);
		}//end if
		
	}//end for
	
	// Solving for f
	for (int i = 0; i < num_steps + 1; ++i) {
	
		if (i==0) {
			third_order_desol.push_back(
				init_f
			);
		}
		
		else {
			third_order_desol.push_back(
				third_order_desol[i-1] + third_order_dersol[i]*step_size
				 + 0.5*step_size*h(xpoints[i])
				 + (1.0/6.0)*step_size*(h(xpoints[i+1]) - h(xpoints[i]))
			);
		}//end if
		
	}//end for
	
	//Generates the vector that stores all of the data.
	vector<pair<string, vector<double>>> solution_set = {{"x", xpoints}, {"f(x)one", first_order_desol}, {"df(x)one", first_order_dersol}, {"f(x)two", second_order_desol}, {"df(x)two", second_order_dersol}, {"f(x)three", third_order_desol}, {"df(x)three", third_order_dersol}};
	
	
	//Writes the csv
	write_csv("secsolution.csv", solution_set);
	
	
	
	return 0;

}//end main
