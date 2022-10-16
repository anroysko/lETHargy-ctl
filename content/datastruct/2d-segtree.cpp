/**
 * Author: Yuhao Yao
 * Date: 2022-10-16
 * Description: 2D segment tree. Point apply and thus no lazy propogation.
 * Usage: Always define a global apply function to tell segment tree how you apply modification. 
 *  Combine is set as plus so if you just let $T$ be numerical type then you have range sum in the info and as range query result. To have something different, say rangeMin, define a struct with constructer and + operation.
 * Time: O(\log^2 N) per operation.
 * Status: tested on https://official.contest.yandex.com/opencupXXII/contest/35263/problems/J/?success=69334197#7/2022_01_31/pBnYMDpTsu.
 */
template<class T> struct SegTree2D {
	struct iNode { T info; int ls, rs; };
	struct oNode { int id; int ls, rs; };
	
	int oL, oR, iL, iR;
	// change to array to accelerate, since allocating takes time. (saves ~ 200ms when allocating 1e7)
	vector<iNode> inner;
	vector<oNode> outer;

	// node 0 is left as virtual empty node.
	SegTree2D(int oL, int oR, int iL, int iR, int q): oL(oL), oR(oR), iL(iL), iR(iR), inner(1), outer(1) {
		inner.reserve(q * (__lg(oR - oL + 1) + 2) * (__lg(iR - iL + 1) + 2) + 1);
		outer.reserve(q * (__lg(oR - oL + 1) + 2) + 1);
	}

	int newInner() { inner.push_back({}); return sz(inner) - 1; }
	int newOuter() { outer.push_back({}); return sz(outer) - 1; }

	void pull(int i) { 
		auto &[info, ls, rs] = inner[i];
		info = inner[ls].info + inner[rs].info;
	}
	void apply(int i, const T &val) {
		::apply(inner[i].info, val);
	}

	// return new root id.
	int pointApply(int rt, int op, int ip, const T &val) {
		auto idfs = [&](auto dfs, int &i, int l, int r) {
			if (!i) i = newInner();
			if (l == r) {
				apply(i, val);
				return;
			}
			int mid = (l + r) >> 1;
			if (ip <= mid) dfs(dfs, inner[i].ls, l, mid);
			else dfs(dfs, inner[i].rs, mid + 1, r);
			pull(i);
		};
		auto odfs = [&](auto dfs, int &i, int l, int r) {
			if (!i) i = newOuter();
			idfs(idfs, outer[i].id, iL, iR);
			if (l == r) return;
			int mid = (l + r) >> 1;
			if (op <= mid) dfs(dfs, outer[i].ls, l, mid);
			else dfs(dfs, outer[i].rs, mid + 1, r);
			return;
		};
		odfs(odfs, rt, oL, oR);
		return rt;
	}

	T rangeAsk(int rt, int qol, int qor, int qil, int qir) {
		T res{};
		auto idfs = [&](auto dfs, int i, int l, int r) {
			if (!i || qir < l || r < qil) return;
			if (qil <= l && r <= qir) {
				res = res + inner[i].info;
				return;
			}
			int mid = (l + r) >> 1;
			dfs(dfs, inner[i].ls, l, mid);
			dfs(dfs, inner[i].rs, mid + 1, r);
		};
		auto odfs = [&](auto dfs, int i, int l, int r) {
			if (!i || qor < l || r < qol) return;
			if (qol <= l && r <= qor) {
				idfs(idfs, outer[i].id, iL, iR);
				return;
			}
			int mid = (l + r) >> 1;
			dfs(dfs, outer[i].ls, l, mid);
			dfs(dfs, outer[i].rs, mid + 1, r);
		};
		odfs(odfs, rt, oL, oR);
		return res;
	}
};