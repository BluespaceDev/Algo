import edu.princeton.cs.algs4.StdRandom;
import edu.princeton.cs.algs4.StdStats;

public class PercolationStats {
    private static final double CONFIDENCE_95 = 1.96;
    private final double m, stddevValue, conLo, conHi;

    // perform trials independent experiments on an n-by-n grid
    public PercolationStats(int n, int trials) {
        if (n <= 0 || trials <= 0) throw new java.lang.IllegalArgumentException();

        double[] x = new double[trials];
        int totalSites = n * n;
        for (int i = 0; i < trials; ++i) {
            Percolation p = new Percolation(n);
            while (!p.percolates()) {
                int row = StdRandom.uniform(1, n + 1);
                int col = StdRandom.uniform(1, n + 1);
                p.open(row, col);
            }
            x[i] = (double) p.numberOfOpenSites() / totalSites;
        }
        m = StdStats.mean(x);
        stddevValue = StdStats.stddev(x);
        conLo = m - (CONFIDENCE_95 * stddevValue / Math.sqrt(trials));
        conHi = m + (CONFIDENCE_95 * stddevValue / Math.sqrt(trials));
    }

    // sample mean of percolation threshold
    public double mean() {
        return m;
    }

    // sample standard deviation of percolation threshold
    public double stddev() {
        return stddevValue;
    }

    // low  endpoint of 95% confidence interval
    public double confidenceLo() {
        return conLo;
    }

    // high endpoint of 95% confidence interval
    public double confidenceHi() {
        return conHi;
    }

    public static void main(String[] args) {
        PercolationStats ps = new PercolationStats(200, 100);
        System.out.println("mean           = " + ps.mean());
        System.out.println("stddev         = " + ps.stddev());
        System.out.println("95% confidence = " + ps.confidenceLo());
    }
}
