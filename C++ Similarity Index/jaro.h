using namespace std;
double jaro(const string& s1, const string& s2) {
	int l1 = s1.size(), l2 = s2.size();
	if (l1 == 0)return l2 == 0 ? 1.0 : 0.0;
	const int match_dist = max(l1, l2) / 2 - 1;
	bool s1Match[l1], s2Match[l2];
	fill(s1Match, s1Match + l1, false);
	fill(s2Match, s2Match + l2, false);
	int matches = 0;
	for (int i = 0; i < l1; i++) {
		for (int j = max(0, i - match_dist); j < min(i + match_dist + 1, l2); j++) {
			if (!s2Match[j] && s1[i] == s2[j]) {
				s1Match[i] = true;
				s2Match[j] = true;
				matches++;
				break;
			}
		}
	}
	if (matches == 0)return 0.0;
	double t = 0.0;
	int j = 0;
	for (int i = 0; i < l1; i++) {
		if (s1Match[i]) {
			while (!s2Match[j])j++;
			if (s1[i] != s2[j])t += 1;
			j++;
		}
	}
	t /= 2;
	return (matches / l1 + matches / l2 + (matches - t) / matches) / 3.0;
}

double jaro_winkler(const string& s1, const string& s2) {
	double jaro_dist = jaro(s1, s2);
	if (jaro_dist > 0.7) {
		int prefix = 0;
		for (int i = 0; i < min(s1.length(), s2.length()); i++) {
			if (s1[i] == s2[i])
				prefix++;
			else break;
		}
		prefix = min(4, prefix);
		jaro_dist += 0.1 * prefix * (1 - jaro_dist);
	}
	return jaro_dist;
}