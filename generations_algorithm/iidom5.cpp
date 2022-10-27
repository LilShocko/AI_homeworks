#include <iostream>
#include<vector>
#include<algorithm>
#include<string>
#include <chrono>  
using namespace std;
vector<vector<int>> matrix(6, vector<int>(6));
void init() {
	matrix[0][1] = 1;
	matrix[0][2] = 3;
	matrix[0][3] = 4;
	matrix[0][4] = 5;
	matrix[0][5] = 2;

	matrix[1][0] = 1;
	matrix[1][2] = 1;
	matrix[1][3] = 4;
	matrix[1][4] = 8;
	matrix[1][5] = 9;

	matrix[2][0] = 3;
	matrix[2][1] = 1;
	matrix[2][3] = 5;
	matrix[2][4] = 1;
	matrix[2][5] = 6;

	matrix[3][0] = 4;
	matrix[3][1] = 4;
	matrix[3][2] = 5;
	matrix[3][4] = 2;
	matrix[3][5] = 7;

	matrix[4][0] = 5;
	matrix[4][1] = 8;
	matrix[4][2] = 1;
	matrix[4][3] = 2;
	matrix[4][5] = 3;

	matrix[5][0] = 2;
	matrix[5][1] = 9;
	matrix[5][2] = 6;
	matrix[5][3] = 7;
	matrix[5][4] = 3;

	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
}
string shuffl() {
	string s1 = "012345";
	for (int i = 5; i >= 1; i--) {
		int j = rand() % i+1;
		char a = s1[j];
		s1[j] = s1[i];
		s1[i] = a;
	}
	return s1;
}
int evaluate(string s1) {
	int sum = 0;
	for (int i = 0; i < s1.size()-1; i++) {
		int firstnum = s1[i]-'0';
		int seconnum = s1[i + 1] - '0';
		sum = sum + (matrix[firstnum][seconnum]);
	}
	int num = s1[s1.size() - 1]-'0';
	sum = sum + matrix[num][0];
	return sum;
}
string mutation(string s1) {
	//ima 10% shans da swapne dva random grada
	//tova stava vednaga sled kato se rodi dete
	int x = rand() % 100;
	if (x > 10) {
		return s1;
	}
	else {
		//1,2,3,4,5
		
		int m = rand() % 5 + 1;
		int n = rand() % 5 + 1;
		while (m == n) {
			n = rand() % 5 + 1;
		}
		swap(s1[m], s1[n]);
		return s1;
	}
}
bool is_elemenet(string s1, char a) {
	for (int i = 0; i < s1.size(); i++) {
		if (a == s1[i])return true;
	}
	return false;
}
pair<int, string> crossover(string s1, string s2) {
	int x = rand() % 6;
	string temp(s1.begin(), s1.begin() + x);
	for (int i = 0; i < s2.size(); i++) {
		if (!is_elemenet(temp, s2[i])) {
			temp.push_back(s2[i]);
		}
	}
	temp = mutation(temp);
	return make_pair(evaluate(temp), temp);
}
vector<pair<int, string>> selection(vector<pair<int, string>> population) {
	//30,20,15,10,5,5,5,4,3,3
	//izbirame 16 roditeli i ot tqh pravim 8 deca + zapazvame dvamata nai dobri roditeli
	vector<pair<int, string>> kindergarden;
	for (int i = 0; i < 8; i++) {
		int x = rand() % 100 + 1;//1-100
		pair<int, string> first_parent;
		pair<int, string> second_parent;
		if (x <= 30) {
			first_parent = population[0];
		}
		else if (x > 30 && x <= 50) {
			first_parent = population[1];
		}
		else if (x > 50 && x <= 65) {
			first_parent = population[2];
		}
		else if (x > 65 && x <= 75) {
			first_parent = population[3];
		}
		else if (x > 75 && x <= 80) {
			first_parent = population[4];
		}
		else if (x > 80 && x <= 85) {
			first_parent = population[5];
		}
		else if (x > 85 && x <= 90) {
			first_parent = population[6];
		}
		else if (x > 90 && x <= 94) {
			first_parent = population[7];
		}
		else if (x > 94 && x <= 97) {
			first_parent = population[8];
		}
		else if (x > 97 && x <= 100) {
			first_parent = population[9];
		}

		int y = rand() % 100 + 1;//1-100
		if (y <= 30) {
			second_parent = population[0];
		}
		else if (y > 30 && y <= 50) {
			second_parent = population[1];
		}
		else if (y > 50 && y <= 65) {
			second_parent = population[2];
		}
		else if (y > 65 && y <= 75) {
			second_parent = population[3];
		}
		else if (y > 75 && y <= 80) {
			second_parent = population[4];
		}
		else if (y > 80 && y <= 85) {
			second_parent = population[5];
		}
		else if (y > 85 && y <= 90) {
			second_parent = population[6];
		}
		else if (y > 90 && y <= 94) {
			second_parent = population[7];
		}
		else if (y > 94 && y <= 97) {
			second_parent = population[8];
		}
		else if (y > 97 && y <= 100) {
			second_parent = population[9];
		}
		kindergarden.push_back(crossover(first_parent.second, second_parent.second));
	}
	kindergarden.push_back(population[0]);
	kindergarden.push_back(population[1]);
	sort(kindergarden.begin(), kindergarden.end());
	return kindergarden;
}
void TSP() {
	vector<pair<int,string>> population;
	for (int i = 0; i < 10; i++) {
		string s1 = shuffl();
		population.push_back(make_pair(evaluate(s1),s1));
		//cout << population[i].first <<" "<<population[i].second<<endl;
	}
	//cout << endl;
	sort(population.begin(), population.end());

	for (int i = 0; i < 10; i++) {
		//cout << population[i].first << " " << population[i].second << endl;
	}


	for (int j = 0; j < 100; j++) {
		population = selection(population);
		cout<<population[0].first<<" "<<population[0].second;
		for (int i = 0; i < 10; i++) {
			//cout << population[i].first << " " << population[i].second << endl;
		}
		cout << endl;
	}
}


//problem - VSICHKO E HARD CODENATO
int main(){
	srand(time(NULL));
	init();
	TSP();


	return 0;
}
