using namespace std;
int min3 (int a, int b, int c)
{
	return min(a, min(b, c));
}

double editDistance( const string& s1, const string& s2) {
	const int m = s1.size(), n = s2.size();
	int dp[m + 1][n + 1];
	for (int i = 0; i <= m; i++) {
		for (int j = 0; j <= n; j++) {
			if (i == 0)
				dp[i][j] = j;
			else if (j == 0)
				dp[i][j] = i;
			else if (s1[i - 1] == s2[j - 1])
				dp[i][j] = dp[i - 1][j - 1];
			else
				dp[i][j] = 1 + min3(dp[i][j - 1], dp[i - 1][j], dp[i - 1][j - 1]);
		}
	}
	return dp[m][n];
}
