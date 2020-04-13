#include <iostream>
#include <string>
#include <unordered_map> 
#include <set>

using std::cin;
using std::cout;
using std::string;
using std::unordered_map;
using std::set;

class Autocomplete {
public:
	Autocomplete() {}

	void Add(string input) {
		main_set.insert(input);
		if(dictionary_.find(input) == dictionary_.end()) {
			dictionary_[input] = 1;
		} else {
			dictionary_[input] += 1;
		}
		can_correction_ = false;
	} 

	void Cout() {
		cout << "-----\n";
		for(auto i : main_set) {
			cout << i << '\n';
		}
		cout << "-----\n";
		for(auto x : dictionary_) {
			cout << x.first << ' ' << x.second << '\n';
		}
	}

	string Search(string prefix) {
		suitable = prefix;
		string left_border = prefix;
		string right_border = prefix + '{';
		bool expr = (main_set.find(left_border) == main_set.end());
		if(expr) {
			main_set.insert(left_border);
		}
		main_set.insert(right_border);
		auto it_left = main_set.find(left_border);
		auto it_right = main_set.find(right_border);
		auto it = it_left;
		if(expr) {
			++it;
		}
		int max_count = 0;
		string best_str = "-";
		for(; it != it_right; ++it) {
			string str = *it;
			if(dictionary_[str] > max_count) {
				max_count = dictionary_[str];
				best_str = str;
			}
		}
		auxiliary_set = set<string>(it_left, it_right);
		main_set.erase(it_right);
		if(expr) {
			main_set.erase(it_left);
			auxiliary_set.erase(auxiliary_set.begin());
		}
		can_correction_ = true;
		return best_str;
	}

	string Continue(string add_word) {
		if(!can_correction_) {
			cout << "you can't use this function now\n";
			return "-";
		}
		suitable += add_word;
		string left_border = suitable;
		string right_border = suitable + '{';
		bool expr = (main_set.find(left_border) == main_set.end());
		if(expr) {
			auxiliary_set.insert(left_border);
		}
		auxiliary_set.insert(right_border);
		auto it_left = auxiliary_set.find(left_border);
		auto it_right = auxiliary_set.find(right_border);
		auto it = it_left;
		if(expr) {
			++it;
		}
		int max_count = 0;
		string best_str = "-";
		for(; it != it_right; ++it) {
			string str = *it;
			if(dictionary_[str] > max_count) {
				max_count = dictionary_[str];
				best_str = str;
			}
		}
		auxiliary_set = set<string>(it_left, it_right);
		if(expr) {
			auxiliary_set.erase(auxiliary_set.begin());
		}
		return best_str;
	}

private:
	unordered_map<string, int> dictionary_;
	set<string> main_set;
	set<string> auxiliary_set;
	string suitable;
	bool can_correction_;
};

int main() {
	string request;
	Autocomplete my_class;
	while(true) {
		cout << "Hi!\n" 
			 <<	"Enter \"exit\"       if you want to go out.\n" 
			 << "Enter \"add\"        if you want to add some words in dict.\n"
			 << "Enter \"search\"     if you want to search any word.\n"
			 << "Enter \"correction\" if you want to add some letters in last word.\n";
		cout << "-> ";
		cin >> request;
		if(request == "exit") {
			return 0;
		}
		if(request == "add") {
			string word;
			bool flag = true;
			int count;
			cout << "please state the number of entered numbers: ";
			cin >> count;
			cout << "all words must consist only of lowercase small letters\n";
			cout << "list the words: ";
			for(int i = 0; i < count; ++i) {
				std::cin >> word;
				my_class.Add(word);
			}
		}
		if(request == "search") {
			cout << "please enter prefix: ";
			string prefix;
			cin >> prefix;
			cout << "best answer: " << my_class.Search(prefix) << '\n';
		}
		if(request == "correction") {
			cout << "please enter correction: ";
			string prefix;
			cin >> prefix;
			cout << "best answer: " << my_class.Continue(prefix) << '\n';
		}
	}
}