def solve(u, d):
	print(u)
	a, b = map(int, input().split())
	if b == 0:
		return (a > 0) + 1
	if d == -1:
		d = 2 * solve(a, -1) + 1
	d = d - 1
	return (d >> 1) + solve(a if d % 2 == 1 else b, (d >> 1) + (d % 2)) + 1

ans = solve(1, -1);
print("Answer", ans);
