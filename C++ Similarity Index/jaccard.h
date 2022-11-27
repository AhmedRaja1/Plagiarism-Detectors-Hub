using namespace std;
double jaccard( const string& s1, const string& s2) {
	double l1 = s1.size();
	double l2 = s2.size();
	set<string>intersect;
	set<string>a;
	set<string>b;
	string tmp = "";
	for (auto ch : s1) {
		if (ch != ' ')tmp += ch;
		else {
			a.insert(tmp);
			tmp = "";
		}
	}
	for (auto ch : s2) {
		if (ch != ' ')tmp += ch;
		else {
			b.insert(tmp);
			tmp = "";
		}
	}
	set_intersection(a.begin(), a.end(), b.begin(), b.end(), inserter(intersect, intersect.begin()));
	const double sz = intersect.size();
	const double jaccard = sz / (l1 + l2 - sz);
	return jaccard;
}