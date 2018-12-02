import java.util.ArrayList;
import java.util.Arrays;

public class BruteCollinearPoints {
    private final ArrayList<LineSegment> lineSegments = new ArrayList<LineSegment>();

    public BruteCollinearPoints(Point[] points)    // finds all line segments containing 4 points
    {
        if (points == null) throw new java.lang.IllegalArgumentException("points null");
        for (int i = 0; i < points.length; ++i)
            if (points[i] == null)
                throw new java.lang.IllegalArgumentException("points[" + i + "] = null");

        Point[] copyPoints = Arrays.copyOf(points, points.length);
        Arrays.sort(copyPoints);

        for (int i = 0; i < copyPoints.length - 1; ++i)
            if (copyPoints[i].slopeTo(copyPoints[i + 1]) == Double.NEGATIVE_INFINITY)
                throw new java.lang.IllegalArgumentException("have duplicate points");

        for (int i = 0; i < copyPoints.length; i++)
            for (int j = i + 1; j < copyPoints.length; j++)
                for (int k = j + 1; k < copyPoints.length; k++)
                    for (int l = k + 1; l < copyPoints.length; l++)
                        if (isCollinear(copyPoints[i], copyPoints[j], copyPoints[k], copyPoints[l]))
                            lineSegments.add(new LineSegment(copyPoints[i], copyPoints[l]));


    }

    public int numberOfSegments()        // the number of line segments
    {
        return lineSegments.size();
    }

    public LineSegment[] segments()                // the line segments
    {
        return lineSegments.toArray(new LineSegment[lineSegments.size()]);
    }

    private static boolean isCollinear(Point p, Point q, Point r, Point s) {
        double slope = p.slopeTo(q);
        return Double.compare(slope, p.slopeTo(r)) == 0 && Double.compare(slope, p.slopeTo(s)) == 0;

    }
}
