import java.util.ArrayList;
import java.util.Arrays;

public class FastCollinearPoints {
    private final ArrayList<LineSegment> lineSegments = new ArrayList<>();

    public FastCollinearPoints(Point[] points)     // finds all line segments containing 4 or more points
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


        for (int i = 0; i < copyPoints.length - 3; i++) {
            Arrays.sort(copyPoints);

            // Sort the points according to the slopes they makes with p.
            // Check if any 3 (or more) adjacent points in the sorted order
            // have equal slopes with respect to p. If so, these points,
            // together with p, are collinear.

            Arrays.sort(copyPoints, copyPoints[i].slopeOrder());

            for (int p = 0, first = 1, last = 2; last < copyPoints.length; last++) {
                // find last collinear to p point
                while (last < copyPoints.length
                        && Double.compare(copyPoints[p].slopeTo(copyPoints[first]), copyPoints[p].slopeTo(copyPoints[last])) == 0) {
                    last++;
                }
                // if found at least 3 elements, make segment if it's unique
                if (last - first >= 3 && copyPoints[p].compareTo(copyPoints[first]) < 0) {
                    lineSegments.add(new LineSegment(copyPoints[p], copyPoints[last - 1]));
                }
                // Try to find next
                first = last;
            }
        }
    }

    public int numberOfSegments()        // the number of line segments
    {
        return lineSegments.size();
    }

    public LineSegment[] segments()                // the line segments
    {
        return lineSegments.toArray(new LineSegment[lineSegments.size()]);
    }
}
