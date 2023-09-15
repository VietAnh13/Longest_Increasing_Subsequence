#include <iostream>
#include <vector>
#include <list>
#include <cstdlib>
#include <ctime>
#include <set>
#include "../List_Of_Branch/List_Of_Branch.h"

// Program made by Project Hoon

// Funtion LongestIncreasingSubsequence - find all longest increasing subsequence (LIC) in input array
ListOfBranch LongestIncreasingSubsequence(std::vector<int> input_array) {

	size_t length_of_longest_increasing_subsequence = LongestIncreasingSubsequenceLength(input_array);
	bool stop_create_new_branch = false;
	std::cout << "Longest Increasing Subsequence Length (just run algorithm find length): " << length_of_longest_increasing_subsequence << std::endl;

	clock_t start_funct, end_funct, start_current_loop, end_current_loop;
	double time_use_funct, time_use_loop;

	start_funct = clock();

	ListOfBranch list_of_branch = ListOfBranch();
	int current_element = input_array.at(0);
	list_of_branch.PushBackBranchWithInitElementToList(current_element);

	size_t max_size = input_array.size();
	size_t rest_size = 0;
	size_t num_of_branch = 0;

	for (size_t i = 1; i < max_size; i++) {

		start_current_loop = clock(); 

		current_element = input_array.at(i);
		num_of_branch = list_of_branch.Num_Of_Branch();

		// Calculate the number of remaining elements of the input array
		rest_size = max_size - i - 1;

		if (rest_size < length_of_longest_increasing_subsequence) {
			stop_create_new_branch = true;
		}

		// Add an element to the end of the branch (if the element is greater than the last element of the branch)
		for (size_t j = 0; j < num_of_branch; j++) {
			Branch current_branch = list_of_branch.BranchAtPostion(j);
			int last_element_in_branch = current_branch.LastElementInBranch();
			int first_element_in_branch = current_branch.FirstElementInBranch();
			if (current_element == last_element_in_branch || current_element == first_element_in_branch) {
				continue;
			}
			else {
				if (current_element > last_element_in_branch) {
					list_of_branch.BranchAtPostion(j).PushBackElementToBranch(current_element);
				}
				else if (current_element < first_element_in_branch && !stop_create_new_branch) {
					list_of_branch.PushBackBranchWithInitElementToList(current_element);
				}
				else {
					Branch recreate_branch = current_branch.RecreateBranchWithSubElement(current_element);
					if (recreate_branch.LengthOfBranch() + rest_size >= length_of_longest_increasing_subsequence) {
						list_of_branch.PushBackBranchToList(recreate_branch);
					}
				}
			}
		}

		// Sort & remove duplicate branch LoB
		list_of_branch.SortAndRemoveDuplicateListOfBranch();

		// Update local variable num_of_branch
		num_of_branch = list_of_branch.Num_Of_Branch();

		// Update the number of elements of the longest branch in LoB
		list_of_branch.UpdateLengthOfBranchLongest();
		size_t length_of_branch_longest = list_of_branch.LengthOfBranchLongest();

		// Remove the branch if the number of remaining elements is less than the difference between 
		// the number of elements of the branch and the number of elements of the current maximum branch
		if (rest_size < length_of_longest_increasing_subsequence) {
			for (size_t j = 0; j < num_of_branch; j++) {
				Branch current_branch = list_of_branch.BranchAtPostion(j);
				if (current_branch.LengthOfBranch() + rest_size < length_of_branch_longest) {
					list_of_branch.RemoveAllBranchFromPositionToEnd(j);
					break;
				}
			}
		}

		//// Random elimination for execution time reduction. However, it may produce incorrect results, 
		//// and should only be used when the sequence size is greater than 500.
		//num_of_branch = list_of_branch.Num_Of_Branch();
		//if (i % (max_size / 4) == 0) {
		//	double gamma = (double)num_of_branch * 0.6;
		//	list_of_branch.RemoveAllBranchFromPositionToEnd((int)gamma);
		//}
		//else {
		//	if (i % (max_size / 20) == 0) {
		//		double alpha = (double)(max_size - (double)i * 0.45) / max_size;
		//		double beta = alpha * num_of_branch * 0.96;
		//		list_of_branch.RemoveAllBranchFromPositionToEnd((int)beta);
		//	}
		//}

		end_current_loop = clock();
		time_use_loop = (double)(abs(end_current_loop - start_current_loop)) / CLOCKS_PER_SEC;
		std::cout << "Percentage progress: " << i << '/' << (max_size - 1) << " (" << (100 * i / (max_size - 1)) << "%)" << std::endl;
		std::cout << "Current loop runtime: " << time_use_loop << "s" << std::endl;
	}

	end_funct = clock();
	time_use_funct = (double)(end_funct - start_funct) / CLOCKS_PER_SEC;
	std::cout << "LIS algorithm runtime: " << time_use_funct << "s" << std::endl;

	return list_of_branch;
}

int main() {
	// Info
	std::cout << "Program made by Project Hoon (11/06/2022)" << std::endl;
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
	ListOfBranch list_of_branch = LongestIncreasingSubsequence(arr);

	// Print result
	list_of_branch.PrintListOfBranch();
}
