vi find_basis(vi &a, int k) {
	//consider the vector space V obtained by linear combinations (xor) of elements of a
	//this function finds a basis of V
	//f(mask) = position of the first set bit
	vi basis(k, -1);
	int n = sz(a);

	rep(i, 0, n) {
		int mask = a[i];
		rep(j, 0, k) {
			if ((mask & (1 << j)) == 0) continue;

			if (basis[j] == -1) {
				basis[j] = mask;
				break;
			} else {
				mask ^= basis[j];
			}
		}
	}

	return basis;
}