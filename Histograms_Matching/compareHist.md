Theory
To compare two histograms ( H1 and H2 ), first we have to choose a metric ( d(H1,H2)) to express how well both histograms match.
OpenCV implements the function cv::compareHist to perform a comparison. It also offers 4 different metrics to compute the matching:
Correlation ( CV_COMP_CORREL )
d(H1,H2)=∑I(H1(I)−H1¯)(H2(I)−H2¯)∑I(H1(I)−H1¯)2∑I(H2(I)−H2¯)2‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾√
where
Hk¯=1N∑JHk(J)
and N is the total number of histogram bins.
Chi-Square ( CV_COMP_CHISQR )
d(H1,H2)=∑I(H1(I)−H2(I))2H1(I)
Intersection ( method=CV_COMP_INTERSECT )
d(H1,H2)=∑Imin(H1(I),H2(I))
Bhattacharyya distance ( CV_COMP_BHATTACHARYYA )
d(H1,H2)=1−1H1¯H2¯N2‾‾‾‾‾‾‾‾√∑IH1(I)⋅H2(I)‾‾‾‾‾‾‾‾‾‾‾‾√‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾√
