#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>

const int w = 1;

bool is_empty(std::ifstream& pFile)
{
    return pFile.peek() == std::ifstream::traits_type::eof();
}

int main() {
	std::ifstream inf("input.txt");
	if (!inf.is_open()) {
		std::cerr << "Could not open input file. Please make sure the input file is input.txt and try again." << std::endl;
		return 1;
	} else if (is_empty(inf)) {
		std::cerr << "File is empty. Please make sure that input.txt contains valid yvalue data and try again." << std::endl;
		return 1;
	}

	std::string inputLine;
	std::vector<int> yvalues;
	while (inf >> inputLine) {
		yvalues.push_back(std::stoi(inputLine));
	}
	int upperNwLimit = yvalues.size() - 1;
	
	std::cout << "Input file opened successfully. " << std::to_string(yvalues.size()) << " values found." << std::endl;

	inf.close();
	
	// Enter nw
	std::cout << "Please enter the number of points Nw to consider in the moving average (odd numbers between 3 and " << upperNwLimit << ", inclusive): ";
	int nw;
	while (true) {
		std::cin >> nw;
		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Invalid input. Please enter an integer: ";
		} else if (nw >= 3 &&  nw <= upperNwLimit) {
			break;
		} else {
			std::cout << "nw is out of range. Enter a number between 3 and " << upperNwLimit << "." << std::endl;
		}
	}

	// NOTE: Keep in mind that std::vectors start at index 0.
	// we start at index wh = (Nw-1)/2 because moving averages 
	// don't exist before that (values to the left are needed).
	// Similarly, we end at index Ny-wh-1 because moving averages
	// don't exist after that (values to the right are needed)
	std::vector<double> avgs;
	int wh = (nw - 1)/2;
	for (int x = wh; x <= yvalues.size()-wh-1; x++) {
		double z_ma = 0;
		for (int j = x - wh; j <= x + wh; j++) {
			// convert yvalue into floating-point first
			double yval = yvalues[j];
			z_ma += yval/nw; // Accumulate the moving avg
			std::cout << "z_ma is " << z_ma << std::endl;
		}
		avgs.push_back(z_ma); // Add to storage container
	}

	std::cout << "The moving averages are, starting from z_" << (wh + 1) << " to z_" << (yvalues.size()-wh) << ":" << std::endl;
	std::cout << "{";
	for (int i = 0; i < avgs.size(); i++) {
		std::cout << avgs[i];
		if (i != avgs.size() - 1) {
			std::cout << ", ";
		}
	}
	std::cout << "}" << std::endl;

	return 0;
}