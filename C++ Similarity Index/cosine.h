using namespace std;
void countOccurences(unordered_map<string, int>&freq, const string& s) {
	string tmp = "";
	for (auto ch : s) {
		if (ch != ' ')tmp += ch;
		else {
			freq[tmp]++;
			tmp = "";
		}
	}
}


int dotprod(unordered_map<string, int>&freq1, unordered_map<string, int>&freq2)
{
	int s = 0;
	for (auto it : freq1) {
		if (freq2.find(it.first) != freq2.end()) {
			s += freq1[it.first] * freq2[it.first];
		}
	}
	return s;
}

int sum(unordered_map<string, int>&freq)
{
	int s = 0;
	for (auto it : freq)
	{
		s = s + pow(it.second, 2);
	}
	return s;
}