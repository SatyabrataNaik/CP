void print2D(vvll &a) {
	rep(i, 0, sz(a)) {
		debug(i, a[i]);
	}
}

void make_col_zero(vvll &a, vll &c, int row, int below_row, int col, ll p) {
	assert(a[row][col] != 0 && sz(a) >= 1);
	int m = sz(a[0]);
	if (a[below_row][col] != 0) {
		//x - row
		//y - below_row
		//below_row - row * y/x
		ll mult = a[below_row][col] * modinv(a[row][col], p) % p;
		rep(j, 0, m) {
			a[below_row][j] -= a[row][j] * mult % p;
			a[below_row][j] %= p;
			if (a[below_row][j] < 0) a[below_row][j] += p;

		}
		c[below_row] -= c[row] * mult % p;
		c[below_row] %= p;
		if (c[below_row] < 0) c[below_row] += p;
	}
	assert(a[below_row][col] == 0);
}

void guass(vvll &a, vll &c, ll p) {
	int n = sz(a); assert(n == sz(c));
	assert(n >= 1);
	int m = sz(a[0]);
	rep(i, 0, n) assert(sz(a[i]) == m);

	rep(i, 0, n) {	
		if (a[i][i] == 0) {
			rep(swap_row, i + 1, n) {
				if (a[swap_row][i] != 0) {
					swap(a[swap_row], a[i]);
					swap(c[swap_row], c[i]);
					break;
				}
			}
		}

		if (a[i][i] != 0) {
			rep(below_row, i + 1, n) {
				make_col_zero(a, c, i, below_row, i, p);
			}
		}

	}
}

void solve_after_gauss(vvll &a, vll &c, ll p, vll &coeffs) {
	//works best for unique solution
	//WARNING: may not work for other cases

	assert(sz(a[0]) == sz(c) && sz(c) == sz(coeffs));

	int m = sz(coeffs);
	int n = sz(a);

	vb done(m, 0);
	repi(i, n - 1, 0) {
		int id = -1;
		int cur_row_not_done = 0;
		rep(j, 0, m) {
			if (a[i][j] != 0 && !done[j]) {
				cur_row_not_done++;
				id = j;
			}
		}
		assert(cur_row_not_done <= 1);
		if (id != -1) {
			assert(!done[id]);
			assert(a[i][id] != 0);

			ll cur_c = c[id];
			rep(j, 0, m) {
				if (done[j]) {
					cur_c -= coeffs[j] * a[i][j];
					cur_c %= p;
					if (cur_c < 0) cur_c += p;
				}
			}
			coeffs[id] = cur_c * modinv(a[i][id], p) % p;
			done[id] = 1;
		}
	}
	rep(j, 0, m) assert(done[j]);
}