#include <iostream>
#include <vector>
#include <ctime>
#include "../List_Of_Branch/List_Of_Branch.h"

Branch LongestIncreasingSubsequenceFast(std::vector<int> input_array) {
	size_t length_of_longest_increasing_subsequence = LongestIncreasingSubsequenceLength(input_array);
	bool stop_create_new_branch = false;
	std::cout << "Longest Increasing Subsequence Length (just run algorithm find length): " << length_of_longest_increasing_subsequence << std::endl;
	
	clock_t start_funct, end_funct;
	double time_use_funct;

	start_funct = clock();

	std::vector<int> order_element(input_array.size(), 1);
	Branch lis = Branch();

	for (int i = 1; i < input_array.size(); i++) {
		for (int j = 0; j < i; j++) {
			if (input_array[i] > input_array[j] && order_element[i] < order_element[j] + 1) {
				order_element[i] = order_element[j] + 1;
			}
		}
	}

	int lis_length = *std::max_element(order_element.begin(), order_element.end());
	int max_index = std::max_element(order_element.begin(), order_element.end()) - order_element.begin();

	lis.PushBackElementToBranch(input_array[max_index]);
	lis_length -= 1;

	for (int i = max_index - 1; i >= 0; i--) {
		if (input_array[i] < lis.LastElementInBranch() && order_element[i] == lis_length) {
			lis.PushFrontElementToBranch(input_array[i]);
			lis_length -= 1;
		}
	}

	end_funct = clock();
	time_use_funct = (double)(end_funct - start_funct) / CLOCKS_PER_SEC;
	std::cout << "LIS algorithm runtime: " << time_use_funct << "s" << std::endl;

	return lis;
}

int main() {
	// Info
	std::cout << "Program made by Project Hoon (15/09/2023)" << std::endl;
	std::cout << "Longest Increasing Subsequence (LIS) Result" << std::endl;

	// Max number in array (max) & number of element in array (N)
	int max = 0;
	size_t N = 0;

	// Array input

	//std::vector<int> arr = { 3, 4, 6, 3, 5, 6, 8 };
	//std::vector<int> arr = { 10, 22, 9, 33, 21, 50, 41, 60 };
	//std::vector<int> arr = { 10, 11, 13, 45, 47, 95, 22, 9, 10, 33, 21, 50, 51, 52, 41, 42, 49, 53, 100, 102, 60, 61 };
	//std::vector<int> arr = { 13, 26, 26, 38, 38, 39, 43, 16, 4, 50, 41, 2, 40, 38, 10, 29, 34, 15, 38, 13, 28, 4, 0, 44, 3, 7, 42, 2, 7, 25, 39, 39, 35, 3, 46, 30, 49, 49, 41, 2, 28, 24, 24, 28, 21, 0, 44, 17, 22, 25, 10, 10, 4, 5, 12, 25, 9, 10, 19, 9, 3, 36, 5, 47, 50, 49, 19, 9, 47, 8, 42, 24, 46, 49, 18, 15, 24, 18, 43, 43, 34, 3, 19, 20, 45, 14, 32, 14, 44, 48, 31, 26, 36, 20, 33, 25, 44, 36, 10, 22 };
	//std::vector<int> arr = { 440, 901, 307, 910, 961, 700, 373, 414, 639, 834, 760, 14, 531, 27, 767, 469, 89, 789, 864, 516, 131, 54, 364, 896, 376, 864, 596, 379, 24, 454, 139, 140, 491, 772, 327, 775, 186, 840, 396, 504, 941, 620, 198, 502, 709, 636, 101, 102, 422, 128, 532, 650, 702, 240, 64, 699, 704, 70, 596, 28, 347, 672, 923, 178, 423, 733, 727, 342, 836, 648, 439, 969, 212, 9, 541, 60, 225, 419, 801, 555, 416, 48, 984, 575, 415, 501, 297, 496, 868, 51, 451, 197, 920, 218, 276, 977, 591, 583, 764, 966 };

	// Generate a random sequence with n elements, where the maximum value in the sequence is max.
	std::vector<int> arr;
	std::cout << "Enter max number in array: ";
	std::cin >> max;
	std::cout << "Enter number of element in array: ";
	std::cin >> N;

	srand(time(NULL));

	for (size_t i = 0; i < N; i++) {
		arr.push_back((int)(rand() % (max + 1)));
	}

	// Print the input sequence
	for (size_t i = 0; i < arr.size(); i++) {
		std::cout << arr.at(i);
		if (i < arr.size() - 1) {
			std::cout << ", ";
		}
		else {
			std::cout << std::endl;
		}
	}

	// Run LongestIncreasingSubsequence function
	Branch branch = LongestIncreasingSubsequenceFast(arr);

	// Print result
	branch.PrintBranch();
}
