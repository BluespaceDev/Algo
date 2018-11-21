import edu.princeton.cs.algs4.WeightedQuickUnionUF;

public class Percolation {
    private static final boolean STATE_CLOSED = false;
    private static final boolean STATE_OPENED = true;

    private boolean[] map;
    private int countOpenSite;
    private final int n, s, e;

    private final WeightedQuickUnionUF uf, ufOnlytop;

    // create n-by-n grid, with all sites blocked
    public Percolation(int n) {
        if (n <= 0) throw new java.lang.IllegalArgumentException();

        this.n = n;
        countOpenSite = 0;

        s = n * n;
        e = s + 1;

        uf = new WeightedQuickUnionUF(n * n + 2);
        ufOnlytop = new WeightedQuickUnionUF(n * n + 2);
        map = new boolean[n * n + 2];
        for (int i = 0; i < n * n + 2; ++i)
            map[i] = STATE_CLOSED;
    }

    // open site (row, col) if it is not open already
    public void open(int row, int col) {
        if (checkIndex(row, col)) throw new java.lang.IllegalArgumentException();

        int index = toIndex(row, col);

        if (STATE_CLOSED == map[index]) {
            map[index] = STATE_OPENED;
            ++countOpenSite;

            if (row == 1) {
                uf.union(index, s);
                ufOnlytop.union(index, s);
            }

            if (!checkIndex(row - 1, col) && map[toIndex(row - 1, col)]) {
                uf.union(index, toIndex(row - 1, col));
                ufOnlytop.union(index, toIndex(row - 1, col));
            }
            if (!checkIndex(row + 1, col) && map[toIndex(row + 1, col)]) {
                uf.union(index, toIndex(row + 1, col));
                ufOnlytop.union(index, toIndex(row + 1, col));
            }
            if (!checkIndex(row, col + 1) && map[toIndex(row, col + 1)]) {
                uf.union(index, toIndex(row, col + 1));
                ufOnlytop.union(index, toIndex(row, col + 1));
            }
            if (!checkIndex(row, col - 1) && map[toIndex(row, col - 1)]) {
                uf.union(index, toIndex(row, col - 1));
                ufOnlytop.union(index, toIndex(row, col - 1));
            }

            if (row == n) uf.union(index, e);
        }
    }

    // is site (row, col) open?
    public boolean isOpen(int row, int col) {
        if (checkIndex(row, col)) throw new java.lang.IllegalArgumentException();
        return map[toIndex(row, col)] == STATE_OPENED;
    }

    // is site (row, col) full?
    public boolean isFull(int row, int col) {
        if (checkIndex(row, col)) throw new java.lang.IllegalArgumentException();
        return ufOnlytop.connected(toIndex(row, col), s);
    }

    // number of open sites
    public int numberOfOpenSites() {
        return countOpenSite;
    }

    // does the system percolate?
    public boolean percolates() {
        return uf.connected(s, e);
    }

    private int toIndex(int row, int col) {
        return (row - 1) * n + col - 1;
    }

    private boolean checkIndex(int row, int col) {
        return (row < 1 || row > n || col < 1 || col > n);
    }

}
