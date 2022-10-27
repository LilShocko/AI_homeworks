#include <iostream>
#include<fstream>
#include<string>
#include<vector>
#include<cmath>
#include<map>
#include <algorithm>
using namespace std;

struct flower {
	float sepalLength;
	float sepalWidth;
	float petalLength;
	float petalWidth;
	int iris;
	flower(float _sepalLength,
	float _sepalWidth,
	float _petalLength,
	float _petalWidth,
	int _iris) {
		sepalLength = _sepalLength;
		sepalWidth = _sepalWidth;
		petalLength = _petalLength;
		petalWidth = _petalWidth;
		iris = _iris;

	}
	flower(float _sepalLength,
		float _sepalWidth,
		float _petalLength,
		float _petalWidth) {
		sepalLength = _sepalLength;
		sepalWidth = _sepalWidth;
		petalLength = _petalLength;
		petalWidth = _petalWidth;
		iris = -2;

	}
	void print() {
		cout << sepalLength << "," << sepalWidth << "," << petalLength << "," << petalWidth << "," << iris;
	}
	//0-setosa
	//1-versicolor
	//2-virginica
};

vector<flower> flowerpot;

flower converttoflower(string input) {
	//5.1, 3.5, 1.4, 0.2, Iris - setosa
	string s1;
	string s2;
	string s3;
	string s4;
	int i = 0;
	while (input[i] != ',') {
		s1.push_back(input[i]);
		i++;
	}
	i++;
	while (input[i] != ',') {
		s2.push_back(input[i]);
		i++;
	}
	i++;
	while (input[i] != ',') {
		s3.push_back(input[i]);
		i++;
	}
	i++;
	while (input[i] != ',') {
		s4.push_back(input[i]);
		i++;
	}
	i++;
	input.erase(input.begin(), input.begin() + i);
	if (input[8] == 'o') {
		return flower(stof(s1), stof(s2), stof(s3), stof(s4), 0);
	}
	else if (input[8] == 's') {
		return flower(stof(s1), stof(s2), stof(s3), stof(s4), 1);
	}
	else {
		return flower(stof(s1), stof(s2), stof(s3), stof(s4), 2);
	}
}

void readarf() {
	string line;
	ifstream myfile("iris.arff");
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			if (line[0] >= '0' && line[0] <= '9') {
				flowerpot.push_back(converttoflower(line));
			}
			
		}
		myfile.close();
	}
  }

float computeDistance(flower f1, flower f2) {
	float a = (f1.sepalLength - f2.sepalLength) * (f1.sepalLength - f2.sepalLength);
	float b = (f1.sepalWidth - f2.sepalWidth) * (f1.sepalWidth - f2.sepalWidth);
	float c = (f1.petalLength - f2.petalLength) * (f1.petalLength - f2.petalLength);
	float d = (f1.petalWidth - f2.petalWidth) * (f1.petalWidth - f2.petalWidth);
	return sqrt(a + b + c + d);
}
bool sortbysec(const pair<int, float>& a,
	const pair<int, float>& b)
{
	return (a.second < b.second);
}


string knn(float a, float b, float c, float d, int k) {
	flower unknown(a, b, c, d);
	vector<pair<int,float>> distances;
	int typea=0, typeb=0, typec=0;
	for (int i = 0; i < flowerpot.size(); i++) {
		distances.push_back(make_pair(i, computeDistance(unknown, flowerpot[i])));
	}
	sort(distances.begin(), distances.end(), sortbysec);
	for (auto i : distances) {
		cout << i.first << " " << i.second << endl;
	}
	for (int i = 0; i < k; i++) {
		if (flowerpot[distances[i].first].iris == 0) {
			typea++;
		}
		else if (flowerpot[distances[i].first].iris == 1) {
			typeb++;
		}
		else if(flowerpot[distances[i].first].iris == 2) {
			typec++;
		}
	}
	cout << typea<<" "<<typeb<<" "<<typec<<endl;
	if (typea > typeb && typea > typec) {
		return "Setosa";
	}
	else if (typeb > typea && typeb > typec) {
		return "Versicolor";
	}
	else if (typec > typea && typec > typeb) {
		return "Virginica";
	}
	return "Ne moje da e opredeli (mejdu 2 ili poveche e)";
}


int main(){
	readarf();
	for (auto i : flowerpot) {
		i.print();
		cout << endl;
	}
	cout<<knn(2, 3, 4, 5, 4);
	return 0;
}
