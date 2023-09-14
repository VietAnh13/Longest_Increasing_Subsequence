#include <iostream>
#include <vector>
#include <list>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <set>

// Program made by Project Hoon

// Class Branch - List of Increasing Subsequence (LoIS)
class Branch {
	std::vector<int> branch;  // store elements of LoIS 
	size_t length_of_branch;  // number of elements in LoIS

public:
	// Initialization class Branch
	Branch() {
		branch = std::vector<int>();
		length_of_branch = branch.size();
	}
	Branch(std::vector<int> branch, size_t length_of_branch) {
		this->branch = branch;
		this->length_of_branch = length_of_branch;
	}

	// Return number of elements of LoIS
	size_t LengthOfBranch() {
		return this->length_of_branch;
	}

	// Add an element to the end of LoIS
	void PushBackElementToBranch(int element) {
		branch.push_back(element);
		length_of_branch = branch.size();
	}

	// Returns the last element in LoIS
	int LastElementInBranch() {
		if (branch.size() > 0) {
			return this->branch.back();
		}
	}

	// Returns the first element in LoIS
	int FirstElementInBranch() {
		if (branch.size() > 0) {
			return this->branch.front();
		}
	}

	// Recreate the branch from the original branch with elements smaller than the sub element and sub element
	Branch RecreateBranchWithSubElement(int element) {
		Branch new_branch = Branch();
		size_t i = 0;
		while (branch.at(i) < element) {
			new_branch.PushBackElementToBranch(branch.at(i++));
		}
		new_branch.PushBackElementToBranch(element);
		return new_branch;
	}

	// Override the != operator for the Branch class
	friend bool operator!= (const Branch& branch_x, const Branch& branch_y) {
		return branch_x.branch != branch_y.branch;
	}

	// Override the == operator for the Branch class
	friend bool operator== (const Branch& branch_x, const Branch& branch_y) {
		return branch_x.branch == branch_y.branch;
	}

	// Override the > operator for the Branch class
	friend bool operator> (const Branch& branch_x, const Branch& branch_y) {
		if (branch_x.length_of_branch != branch_y.length_of_branch) {
			return branch_x.length_of_branch > branch_y.length_of_branch;
		}
		else {
			return branch_x.branch > branch_y.branch;
		}
	}

	// Override the < operator for the Branch class
	friend bool operator< (const Branch& branch_x, const Branch& branch_y) {
		if (branch_x.length_of_branch != branch_y.length_of_branch) {
			return branch_x.length_of_branch < branch_y.length_of_branch;
		}
		else {
			return branch_x.branch < branch_y.branch;
		}
	}

	// Print the number of elements in the branch and all elements of the branch to the console
	void PrintBranch() {
		if (length_of_branch > 0) {
			std::cout << "Length of this branch: " << length_of_branch << std::endl;
			for (size_t i = 0; i < branch.size(); i++) {
				std::cout << branch.at(i);
				if (i < branch.size() - 1) {
					std::cout << ", ";
				}
				else {
					std::cout << std::endl;
				}
			}
		}
	}
};

// Binary search (note boundaries in the caller)
int CeilIndex(std::vector<int>& v, int l, int r, int key) {
	while (r - l > 1) {
		int m = l + (r - l) / 2;
		if (v[m] >= key) {
			r = m;
		}
		else {
			l = m;
		}
	}
	return r;
}

int LongestIncreasingSubsequenceLength(std::vector<int>& v) {
	if (v.size() == 0)
		return 0;

	std::vector<int> tail(v.size(), 0);
	int length = 1; // always points empty slot in tail

	tail[0] = v[0];
	for (size_t i = 1; i < v.size(); i++) {

		// new smallest value
		if (v[i] < tail[0]) {
			tail[0] = v[i];
		}

		// v[i] extends largest subsequence
		else if (v[i] > tail[length - 1]) {
			tail[length++] = v[i];
		}

		// v[i] will become end candidate of an existing subsequence or Throw away larger elements in all
		// LIS, to make room for upcoming greater elements than v[i] (and also, v[i] would have already
		// appeared in one of LIS, identify the location and replace it)
		else {
			tail[CeilIndex(tail, -1, length - 1, v[i])] = v[i];
		}
	}
	return length;
}

// Class ListOfBranch - List of Branch (LoB)
class ListOfBranch {
	std::vector<Branch> list_of_branch;  // store branches of LoB
	size_t num_of_branch;                // number of the branch in LoB
	size_t length_of_branch_longest;     // maximum number of elements of a branch in LoB

public:
	// Initialization class ListOfBranch
	ListOfBranch() {
		list_of_branch = std::vector<Branch>();
		num_of_branch = list_of_branch.size();
		length_of_branch_longest = 0;
	}

	// Add a new (blank) branch to the end of LoB
	void PushBackNewBranchToList() {
		Branch new_branch = Branch();
		PushBackBranchToList(new_branch);
	}

	// Add a branch with init element to the end of LoB
	void PushBackBranchWithInitElementToList(int init_element) {
		Branch new_branch = Branch();
		new_branch.PushBackElementToBranch(init_element);
		PushBackBranchToList(new_branch);
	}

	// Add a branch to the end of LoB
	void PushBackBranchToList(Branch branch) {
		list_of_branch.push_back(branch);
		num_of_branch = list_of_branch.size();
	}

	// Add a branch in front of LoB
	void PushFrontBranchToList(Branch branch) {
		list_of_branch.push_back(branch);
		std::rotate(list_of_branch.rbegin(), list_of_branch.rbegin() + 1, list_of_branch.rend());
		num_of_branch = list_of_branch.size();
	}

	// Remove a branch at the specified position from LoB
	void RemoveBranchAtPositionFromList(size_t position) {
		list_of_branch.erase(list_of_branch.begin() + position);
		num_of_branch = list_of_branch.size();
	}

	// Remove a specified branch from LoB
	void RemoveBranchFromList(Branch branch) {
		for (size_t i = 0; i < list_of_branch.size(); i++) {
			Branch current_branch = list_of_branch.at(i);
			if (current_branch == branch) {
				RemoveBranchAtPositionFromList(i);
				break;
			}
		}
	}

	// Returns number of the branch in LoB
	size_t Num_Of_Branch() {
		return this->num_of_branch;
	}

	// Returns branch at specified position in LoB
	Branch& BranchAtPostion(size_t position) {
		return list_of_branch.at(position);
	}

	// Update maximum number of elements of a branch in LoB
	void UpdateLengthOfBranchLongest() {
		size_t max_length = list_of_branch.at(0).LengthOfBranch();
		for (Branch branch : list_of_branch) {
			if (branch.LengthOfBranch() > max_length) {
				max_length = branch.LengthOfBranch();
			}
		}
		length_of_branch_longest = max_length;
	}

	// Returns maximum number of elements of a branch in LoB
	size_t LengthOfBranchLongest() {
		return this->length_of_branch_longest;
	}

	// Define CompareBranchLength structure for compare two branches
	struct CompareBranchLength {
		inline bool operator() (const Branch& branch_x, const Branch& branch_y) {
			return branch_x > branch_y;
		}
	};

	// Sort branches in descending order of length & remove duplicate branch
	void SortAndRemoveDuplicateListOfBranch() {
		std::sort(list_of_branch.begin(), list_of_branch.end(), CompareBranchLength());
		std::vector<Branch>::iterator iter = std::unique(list_of_branch.begin(), list_of_branch.end());
		list_of_branch.resize(std::distance(list_of_branch.begin(), iter));
		num_of_branch = list_of_branch.size();
	}

	// Remove all branches in LoB starting from specified position
	void RemoveAllBranchFromPositionToEnd(size_t position) {
		list_of_branch.erase(list_of_branch.begin() + position, list_of_branch.end());
		num_of_branch = list_of_branch.size();
	}

	// Print all branch in LoB
	void PrintListOfBranch() {
		if (num_of_branch > 0) {
			for (size_t i = 0; i < list_of_branch.size(); i++) {
				Branch current_branch = list_of_branch.at(i);
				std::cout << "Branch " << (i + 1) << std::endl;
				current_branch.PrintBranch();
			}
		}
	}
};

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
