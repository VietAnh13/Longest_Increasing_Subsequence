#pragma once
#include <iostream>
#include <vector>
#include <algorithm>

#ifndef LIS
#define LIS

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

	// Add an element to the beginning of LoIS
	void PushFrontElementToBranch(int element) {
		branch.insert(branch.begin(), 1, element);
		length_of_branch = branch.size();
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

#endif 
