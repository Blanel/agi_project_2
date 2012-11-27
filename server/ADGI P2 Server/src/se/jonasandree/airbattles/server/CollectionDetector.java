package se.jonasandree.airbattles.server;

public class CollectionDetector{
    /**
     * Constructor
     * 
     * @param  epsilon  The lowest value of significant, should really not be zero
     */
    public CollectionDetector(double epsilon){
    	this.epsilon2 = epsilon * epsilon;
    }
    
    /**
     * ε², where ε is the lowest value of significant
     */
    private double epsilon2;
    
    /**
     * Checks whether the a dot is inside a triangle
     * 
     * @param   dotY  The dot's y-component
     * @param   dotX  The dot's x-component
     * @param   y0    The triangle's 0th corner's y-component
     * @param   x0    The triangle's 0th corner's x-component
     * @param   y1    The triangle's 1st corner's y-component
     * @param   x1    The triangle's 1st corner's x-component
     * @param   y2    The triangle's 2nd corner's y-component
     * @param   x2    The triangle's 2nd corner's x-component
     * @return        Whether the dot is inside the triangle
     */
    public boolean dotTriangle(double dotY, double dotX, double y0, double x0, double y1, double x1, double y2, double x2){
		double diff = areaTriangle2(dotY, dotX, y0, x0, y1, x1);
		diff += areaTriangle2(dotY, dotX, y0, x0, y2, x2);
		diff += areaTriangle2(dotY, dotX, y1, x1, y2, x2);
		diff -= areaTriangle2(y0, x0, y1, x1, y2, x2);
		return (-this.epsilon2 < diff) && (diff < this.epsilon2);
    }
    
    /**
     * Checks whether the a line is partially inside a triangle
     * 
     * @param   lineY0  The lines's 0th edge's y-component
     * @param   lineX0  The lines's 0th edge's x-component
     * @param   lineY1  The lines's 1st edge's y-component
     * @param   lineX1  The lines's 1st edge's x-component
     * @param   y0      The triangle's 0th corner's y-component
     * @param   x0      The triangle's 0th corner's x-component
     * @param   y1      The triangle's 1st corner's y-component
     * @param   x1      The triangle's 1st corner's x-component
     * @param   y2      The triangle's 2nd corner's y-component
     * @param   x2      The triangle's 2nd corner's x-component
     * @return          Whether the dot is inside the triangle
     */
    public boolean lineTriangle(double lineY0, double lineX0, double lineY1, double lineX1, double y0, double x0, double y1, double x1, double y2, double x2){
		double k0 = (y0 - y1) / (x0 - x1);
		double k1 = (y1 - y2) / (x1 - x2);
		double k2 = (y2 - y0) / (x2 - x0);
		double kl = (lineY1 - lineY0) / (lineX1 - lineX0);
		
		double m0 = y0 - k0 * x0;
		double m1 = y1 - k1 * x1;
		double m2 = y2 - k2 * x2;
		double ml = lineY0 - k0 * lineX0;
		
		double X0  = (ml - m0) / (k0 - kl);
		double X1  = (ml - m1) / (k1 - kl);
		double X2  = (ml - m2) / (k2 - kl);
		
		double min = Math.min(lineX0, lineX1);
		double max = Math.max(lineX0, lineX1);
		
		if ((Math.min(x0, x1) <= X0) && (X0 <= Math.max(x0, x1)) && (min <= X0) && (X0 <= max))  return true;
		if ((Math.min(x1, x2) <= X1) && (X1 <= Math.max(x1, x2)) && (min <= X1) && (X1 <= max))  return true;
		if ((Math.min(x2, x0) <= X2) && (X2 <= Math.max(x2, x0)) && (min <= X2) && (X2 <= max))  return true;
		return false;
    }
    
    /**
     * Calculates the area of a triangle to the power of two
     * 
     * @param   y0  The triangle's 0th corner's y-component
     * @param   x0  The triangle's 0th corner's x-component
     * @param   y1  The triangle's 1st corner's y-component
     * @param   x1  The triangle's 1st corner's x-component
     * @param   y2  The triangle's 2nd corner's y-component
     * @param   x2  The triangle's 2nd corner's x-component
     * @return      The area of the triangle
     */
    private double areaTriangle2(double y0, double x0, double y1, double x1, double y2, double x2){
		double a2 = (y1 - y2) * (y1 - y2) + (x1 - x2) * (x1 - x2);
		double b2 = (y0 - y2) * (y0 - y2) + (x0 - x2) * (x0 - x2);
		double c2 = (y0 - y1) * (y0 - y1) + (x0 - x1) * (x0 - x1);
		return (2 * (a2 * b2 + a2 * c2 + b2 * c2) - (a2 * a2 + b2 * b2 + c2 * c2)) / 16;
    } 
}

