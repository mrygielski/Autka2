#ifndef _3DMATH_H
#define _3DMATH_H
#include <math.h>	// We include math.h so we can use the sqrt() function

/////// * /////////// * /////////// * NEW * /////// * /////////// * /////////// *

#include <float.h>	// This is so we can use _isnan() for acos()
#define PI 3.1415926535897932					// This is our famous PI

// This is used to hold 3D points and vectors.  This will eventually be added upon
// to create a robut class with operator overloading.  For now we just need an x, y, z.
struct CVector2
{
public:
	float x, y, z;						
};


//	This returns a perpendicular vector from 2 given vectors by taking the cross product.
CVector2 Cross(CVector2 vVector1, CVector2 vVector2);

//	This returns a vector between 2 points
CVector2 Vector(CVector2 vPoint1, CVector2 vPoint2);

//	This returns the magnitude of a normal (or any other vector)
float Magnitude(CVector2 vNormal);

//	This returns a normalize vector (A vector exactly of length 1)
CVector2 Normalize(CVector2 vNormal);

//	This returns the normal of a polygon (The direction the polygon is facing)
CVector2 Normal(CVector2 vTriangle[]);

// This returns the distance the plane is from the origin (0, 0, 0)
// It takes the normal to the plane, along with ANY point that lies on the plane (any corner)
float PlaneDistance(CVector2 Normal, CVector2 Point);

// This takes a triangle (plane) and line and returns true if they intersected
bool IntersectedPlane(CVector2 vPoly[], CVector2 vLine[], CVector2 &vNormal, float &originDistance);


/////// * /////////// * /////////// * NEW * /////// * /////////// * /////////// *


// This returns the dot product between 2 vectors
float Dot(CVector2 vVector1, CVector2 vVector2);

// This returns the angle between 2 vectors
double AngleBetweenVectors(CVector2 Vector1, CVector2 Vector2);

// This returns an intersection point of a polygon and a line (assuming intersects the plane)
CVector2 IntersectionPoint(CVector2 vNormal, CVector2 vLine[], double distance);

// This returns true if the intersection point is inside of the polygon
bool InsidePolygon(CVector2 vIntersection, CVector2 Poly[], long verticeCount);

// Use this function to test collision between a line and polygon
bool IntersectedPolygon(CVector2 vPoly[], CVector2 vLine[], int verticeCount);


/////// * /////////// * /////////// * NEW * /////// * /////////// * /////////// *
CVector2 Cross(CVector2 vVector1, CVector2 vVector2)
{
	CVector2 vNormal;									// The vector to hold the cross product

	// Once again, if we are given 2 vectors (directions of 2 sides of a polygon)
	// then we have a plane define.  The cross product finds a vector that is perpendicular
	// to that plane, which means it's point straight out of the plane at a 90 degree angle.
	
	// The X value for the vector is:  (V1.y * V2.z) - (V1.z * V2.y)													// Get the X value
	vNormal.x = ((vVector1.y * vVector2.z) - (vVector1.z * vVector2.y));
														
	// The Y value for the vector is:  (V1.z * V2.x) - (V1.x * V2.z)
	vNormal.y = ((vVector1.z * vVector2.x) - (vVector1.x * vVector2.z));
														
	// The Z value for the vector is:  (V1.x * V2.y) - (V1.y * V2.x)
	vNormal.z = ((vVector1.x * vVector2.y) - (vVector1.y * vVector2.x));

	return vNormal;										// Return the cross product (Direction the polygon is facing - Normal)
}


/////////////////////////////////////// VECTOR \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	This returns a vector between 2 points
/////
/////////////////////////////////////// VECTOR \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

CVector2 Vector(CVector2 vPoint1, CVector2 vPoint2)
{
	CVector2 vVector = {0};								// Initialize our variable to zero

	// In order to get a vector from 2 points (a direction) we need to
	// subtract the second point from the first point.

	vVector.x = vPoint1.x - vPoint2.x;					// Get the X value of our new vector
	vVector.y = vPoint1.y - vPoint2.y;					// Get the Y value of our new vector
	vVector.z = vPoint1.z - vPoint2.z;					// Get the Z value of our new vector

	return vVector;										// Return our new vector
}


/////////////////////////////////////// MAGNITUDE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	This returns the magnitude of a normal (or any other vector)
/////
/////////////////////////////////////// MAGNITUDE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

float Magnitude(CVector2 vNormal)
{
	// This will give us the magnitude or "Norm" as some say, of our normal.
	// Here is the equation:  magnitude = sqrt(V.x^2 + V.y^2 + V.z^2)  Where V is the vector

	return (float)sqrt( (vNormal.x * vNormal.x) + (vNormal.y * vNormal.y) + (vNormal.z * vNormal.z) );
}


/////////////////////////////////////// NORMALIZE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	This returns a normalize vector (A vector exactly of length 1)
/////
/////////////////////////////////////// NORMALIZE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

CVector2 Normalize(CVector2 vNormal)
{
	float magnitude = Magnitude(vNormal);				// Get the magnitude of our normal

	// Now that we have the magnitude, we can divide our normal by that magnitude.
	// That will make our normal a total length of 1.  This makes it easier to work with too.

	vNormal.x /= magnitude;								// Divide the X value of our normal by it's magnitude
	vNormal.y /= magnitude;								// Divide the Y value of our normal by it's magnitude
	vNormal.z /= magnitude;								// Divide the Z value of our normal by it's magnitude

	// Finally, return our normalized normal.

	return vNormal;										// Return the new normal of length 1.
}


/////////////////////////////////////// NORMAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	This returns the normal of a polygon (The direction the polygon is facing)
/////
/////////////////////////////////////// NORMAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

CVector2 Normal(CVector2 vTriangle[])					
{														// Get 2 vectors from the polygon (2 sides), Remember the order!
	CVector2 vVector1 = Vector(vTriangle[2], vTriangle[0]);
	CVector2 vVector2 = Vector(vTriangle[1], vTriangle[0]);

	CVector2 vNormal = Cross(vVector1, vVector2);		// Take the cross product of our 2 vectors to get a perpendicular vector

	// Now we have a normal, but it's at a strange length, so let's make it length 1.

	vNormal = Normalize(vNormal);						// Use our function we created to normalize the normal (Makes it a length of one)

	return vNormal;										// Return our normal at our desired length
}


/////////////////////////////////// PLANE DISTANCE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	This returns the distance between a plane and the origin
/////
/////////////////////////////////// PLANE DISTANCE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
									
float PlaneDistance(CVector2 Normal, CVector2 Point)
{	
	float distance = 0;									// This variable holds the distance from the plane tot he origin

	// Use the plane equation to find the distance (Ax + By + Cz + D = 0)  We want to find D.
	// So, we come up with D = -(Ax + By + Cz)
														// Basically, the negated dot product of the normal of the plane and the point. (More about the dot product in another tutorial)
	distance = - ((Normal.x * Point.x) + (Normal.y * Point.y) + (Normal.z * Point.z));

	return distance;									// Return the distance
}




/////// * /////////// * /////////// * NEW * /////// * /////////// * /////////// *

// Since the last tutorial, we added 2 more parameters for the normal and the distance
// from the origin.  This is so we don't have to recalculate it 3 times in our IntersectionPoint() 
// IntersectedPolygon() functions.  We would probably make 2 different functions for
// this so we have the choice of getting the normal and distance back, or not.
// I also changed the vTriangle to "vPoly" because it isn't always a triangle.
// The code doesn't change, it's just more correct (though we only need 3 points anyway).
// For C programmers, the '&' is called a reference and is the same concept as the '*' for addressing.


/////////////////////////////////// INTERSECTED PLANE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	This checks to see if a line intersects a plane
/////
/////////////////////////////////// INTERSECTED PLANE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
											
bool IntersectedPlane(CVector2 vPoly[], CVector2 vLine[], CVector2 &vNormal, float &originDistance)
{
	float distance1=0, distance2=0;						// The distances from the 2 points of the line from the plane
			
	vNormal = Normal(vPoly);							// We need to get the normal of our plane to go any further

	// Let's find the distance our plane is from the origin.  We can find this value
	// from the normal to the plane (polygon) and any point that lies on that plane (Any vertice)
	originDistance = PlaneDistance(vNormal, vPoly[0]);

	// Get the distance from point1 from the plane using: Ax + By + Cz + D = (The distance from the plane)

	distance1 = ((vNormal.x * vLine[0].x)  +					// Ax +
		         (vNormal.y * vLine[0].y)  +					// Bx +
				 (vNormal.z * vLine[0].z)) + originDistance;	// Cz + D
	
	// Get the distance from point2 from the plane using Ax + By + Cz + D = (The distance from the plane)
	
	distance2 = ((vNormal.x * vLine[1].x)  +					// Ax +
		         (vNormal.y * vLine[1].y)  +					// Bx +
				 (vNormal.z * vLine[1].z)) + originDistance;	// Cz + D

	// Now that we have 2 distances from the plane, if we times them together we either
	// get a positive or negative number.  If it's a negative number, that means we collided!
	// This is because the 2 points must be on either side of the plane (IE. -1 * 1 = -1).

	if(distance1 * distance2 >= 0)			// Check to see if both point's distances are both negative or both positive
	   return false;						// Return false if each point has the same sign.  -1 and 1 would mean each point is on either side of the plane.  -1 -2 or 3 4 wouldn't...
					
	return true;							// The line intersected the plane, Return TRUE
}


/////////////////////////////////// DOT \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	This computers the dot product of 2 vectors
/////
/////////////////////////////////// DOT \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

float Dot(CVector2 vVector1, CVector2 vVector2) 
{
	// The dot product is this equation: V1.V2 = (V1.x * V2.x  +  V1.y * V2.y  +  V1.z * V2.z)
	// In math terms, it looks like this:  V1.V2 = ||V1|| ||V2|| cos(theta)
	// The '.' means DOT.   The || || is magnitude.  So the magnitude of V1 times the magnitude
	// of V2 times the cosine of the angle.  It seems confusing now, but it will become more clear.
	// This function is used for a ton of things, which we will cover in other tutorials.
	// For this tutorial, we use it to compute the angle between 2 vectors.  If the vectors
	// are normalize, the dot product returns the cosine of the angle between the 2 vectors.
	// What does that mean? Well, it doesn't return the actual angle, it returns the value of:
	// cos(angle).	Well, what if we want to get the actual angle?  Then we use the arc cosine.
	// There is more on this in the below function AngleBetweenVectors().  Let's give some
	// applications of using the dot product.  How would you tell if the angle between the
	// 2 vectors is perpendicular (90 degrees)?  Well, if we normalize the vectors we can
	// get rid of the ||V1|| * ||V2|| in front, which just leaves us with:  cos(theta).
	// If a vector is normalize, it's magnitude is 1, so it would be: 1 * 1 * cos(theta) , 
	// which is pointless, so we discard that part of the equation.  So, What is the cosine of 90?
	// If you punch it in your calculator you will find that it's 0.  So that means
	// if the dot product of 2 angles is 0, then they are perpendicular.  What we did in
	// our mind is take the arc cosine of 0, which is 90 (or PI/2 in radians).  More on this below.

			 //    (V1.x * V2.x        +        V1.y * V2.y        +        V1.z * V2.z)
	return ( (vVector1.x * vVector2.x) + (vVector1.y * vVector2.y) + (vVector1.z * vVector2.z) );
}


/////////////////////////////////// ANGLE BETWEEN VECTORS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	This checks to see if a point is inside the ranges of a polygon
/////
/////////////////////////////////// ANGLE BETWEEN VECTORS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

double AngleBetweenVectors(CVector2 Vector1, CVector2 Vector2)
{							
	// Remember, above we said that the Dot Product of returns the cosine of the angle
	// between 2 vectors?  Well, that is assuming they are unit vectors (normalize vectors).
	// So, if we don't have a unit vector, then instead of just saying  arcCos(DotProduct(A, B))
	// We need to divide the dot product by the magnitude of the 2 vectors multiplied by each other.
	// Here is the equation:   arc cosine of (V . W / || V || * || W || )
	// the || V || means the magnitude of V.  This then cancels out the magnitudes dot product magnitudes.
	// But basically, if you have normalize vectors already, you can forget about the magnitude part.

	// Get the dot product of the vectors
	float dotProduct = Dot(Vector1, Vector2);				

	// Get the product of both of the vectors magnitudes
	float vectorsMagnitude = Magnitude(Vector1) * Magnitude(Vector2) ;

	// Get the arc cosine of the (dotProduct / vectorsMagnitude) which is the angle in RADIANS.
	// (IE.   PI/2 radians = 90 degrees      PI radians = 180 degrees    2*PI radians = 360 degrees)
	// To convert radians to degress use this equation:   radians * (PI / 180)
	// TO convert degrees to radians use this equation:   degrees * (180 / PI)
	double angle = acos( dotProduct / vectorsMagnitude );

	// Here we make sure that the angle is not a -1.#IND0000000 number, which means indefinate.
	// acos() thinks it's funny when it returns -1.#IND0000000.  If we don't do this check,
	// our collision results will sometimes say we are colliding when we aren't.  I found this
	// out the hard way after MANY hours and already wrong written tutorials :)  Usually
	// this value is found when the dot product and the maginitude are the same value.
	// We want to return 0 when this happens.
	if(_isnan(angle))
		return 0;
	
	// Return the angle in radians
	return( angle );
}


/////////////////////////////////// INTERSECTION POINT \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	This returns the intersection point of the line that intersects the plane
/////
/////////////////////////////////// INTERSECTION POINT \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
											
CVector2 IntersectionPoint(CVector2 vNormal, CVector2 vLine[], double distance)
{
	CVector2 vPoint = {0}, vLineDir = {0};		// Variables to hold the point and the line's direction
	double Numerator = 0.0, Denominator = 0.0, dist = 0.0;

	// Here comes the confusing part.  We need to find the 3D point that is actually
	// on the plane.  Here are some steps to do that:
	
	// 1)  First we need to get the vector of our line, Then normalize it so it's a length of 1
	vLineDir = Vector(vLine[1], vLine[0]);		// Get the Vector of the line
	vLineDir = Normalize(vLineDir);				// Normalize the lines vector


	// 2) Use the plane equation (distance = Ax + By + Cz + D) to find the distance from one of our points to the plane.
	//    Here I just chose a arbitrary point as the point to find that distance.  You notice we negate that
	//    distance.  We negate the distance because we want to eventually go BACKWARDS from our point to the plane.
	//    By doing this is will basically bring us back to the plane to find our intersection point.
	Numerator = - (vNormal.x * vLine[0].x +		// Use the plane equation with the normal and the line
				   vNormal.y * vLine[0].y +
				   vNormal.z * vLine[0].z + distance);

	// 3) If we take the dot product between our line vector and the normal of the polygon,
	//    this will give us the cosine of the angle between the 2 (since they are both normalized - length 1).
	//    We will then divide our Numerator by this value to find the offset towards the plane from our arbitrary point.
	Denominator = Dot(vNormal, vLineDir);		// Get the dot product of the line's vector and the normal of the plane
				  
	// Since we are using division, we need to make sure we don't get a divide by zero error
	// If we do get a 0, that means that there are INFINATE points because the the line is
	// on the plane (the normal is perpendicular to the line - (Normal.Vector = 0)).  
	// In this case, we should just return any point on the line.

	if( Denominator == 0.0)						// Check so we don't divide by zero
		return vLine[0];						// Return an arbitrary point on the line

	// We divide the (distance from the point to the plane) by (the dot product)
	// to get the distance (dist) that we need to move from our arbitrary point.  We need
	// to then times this distance (dist) by our line's vector (direction).  When you times
	// a scalar (single number) by a vector you move along that vector.  That is what we are
	// doing.  We are moving from our arbitrary point we chose from the line BACK to the plane
	// along the lines vector.  It seems logical to just get the numerator, which is the distance
	// from the point to the line, and then just move back that much along the line's vector.
	// Well, the distance from the plane means the SHORTEST distance.  What about in the case that
	// the line is almost parallel with the polygon, but doesn't actually intersect it until half
	// way down the line's length.  The distance from the plane is short, but the distance from
	// the actual intersection point is pretty long.  If we divide the distance by the dot product
	// of our line vector and the normal of the plane, we get the correct length.  Cool huh?

	dist = Numerator / Denominator;				// Divide to get the multiplying (percentage) factor
	
	// Now, like we said above, we times the dist by the vector, then add our arbitrary point.
	// This essentially moves the point along the vector to a certain distance.  This now gives
	// us the intersection point.  Yay!

	vPoint.x = (float)(vLine[0].x + (vLineDir.x * dist));
	vPoint.y = (float)(vLine[0].y + (vLineDir.y * dist));
	vPoint.z = (float)(vLine[0].z + (vLineDir.z * dist));

	return vPoint;								// Return the intersection point
}


/////////////////////////////////// INSIDE POLYGON \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	This checks to see if a point is inside the ranges of a polygon
/////
/////////////////////////////////// INSIDE POLYGON \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

bool InsidePolygon(CVector2 vIntersection, CVector2 Poly[], long verticeCount)
{
	const double MATCH_FACTOR = 0.9999;		// Used to cover up the error in floating point
	double Angle = 0.0;						// Initialize the angle
	CVector2 vA, vB;						// Create temp vectors
	
	// Just because we intersected the plane, doesn't mean we were anywhere near the polygon.
	// This functions checks our intersection point to make sure it is inside of the polygon.
	// This is another tough function to grasp at first, but let me try and explain.
	// It's a brilliant method really, what it does is create triangles within the polygon
	// from the intersection point.  It then adds up the inner angle of each of those triangles.
	// If the angles together add up to 360 degrees (or 2 * PI in radians) then we are inside!
	// If the angle is under that value, we must be outside of polygon.  To further
	// understand why this works, take a pencil and draw a perfect triangle.  Draw a dot in
	// the middle of the triangle.  Now, from that dot, draw a line to each of the vertices.
	// Now, we have 3 triangles within that triangle right?  Now, we know that if we add up
	// all of the angles in a triangle we get 360 right?  Well, that is kinda what we are doing,
	// but the inverse of that.  Say your triangle is an isosceles triangle, so add up the angles
	// and you will get 360 degree angles.  90 + 90 + 90 is 360.

	for (int i = 0; i < verticeCount; i++)		// Go in a circle to each vertex and get the angle between
	{	
		vA = Vector(Poly[i], vIntersection);	// Subtract the intersection point from the current vertex
												// Subtract the point from the next vertex
		vB = Vector(Poly[(i + 1) % verticeCount], vIntersection);
												
		Angle += AngleBetweenVectors(vA, vB);	// Find the angle between the 2 vectors and add them all up as we go along
	}

	// Now that we have the total angles added up, we need to check if they add up to 360 degrees.
	// Since we are using the dot product, we are working in radians, so we check if the angles
	// equals 2*PI.  We defined PI in 3DMath.h.  You will notice that we use a MATCH_FACTOR
	// in conjunction with our desired degree.  This is because of the inaccuracy when working
	// with floating point numbers.  It usually won't always be perfectly 2 * PI, so we need
	// to use a little twiddling.  I use .9999, but you can change this to fit your own desired accuracy.
												
	if(Angle >= (MATCH_FACTOR * (2.0 * PI)) )	// If the angle is greater than 2 PI, (360 degrees)
		return TRUE;							// The point is inside of the polygon
		
	return FALSE;								// If you get here, it obviously wasn't inside the polygon, so Return FALSE
}


/////////////////////////////////// INTERSECTED POLYGON \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	This checks if a line is intersecting a polygon
/////
/////////////////////////////////// INTERSECTED POLYGON \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

bool IntersectedPolygon(CVector2 vPoly[], CVector2 vLine[], int verticeCount)
{
	CVector2 vNormal = {0};
	float originDistance = 0;

	// First we check to see if our line intersected the plane.  If this isn't true
	// there is no need to go on, so return false immediately.
	// We pass in address of vNormal and originDistance so we only calculate it once

									 // Reference   // Reference
	if(!IntersectedPlane(vPoly, vLine,   vNormal,   originDistance))
		return false;

	// Now that we have our normal and distance passed back from IntersectedPlane(), 
	// we can use it to calculate the intersection point.  The intersection point
	// is the point that actually is ON the plane.  It is between the line.  We need
	// this point test next, if we are inside the polygon.  To get the I-Point, we
	// give our function the normal of the plan, the points of the line, and the originDistance.

	CVector2 vIntersection = IntersectionPoint(vNormal, vLine, originDistance);

	// Now that we have the intersection point, we need to test if it's inside the polygon.
	// To do this, we pass in :
	// (our intersection point, the polygon, and the number of vertices our polygon has)

	if(InsidePolygon(vIntersection, vPoly, verticeCount))
		return true;							// We collided!	  Return success


	// If we get here, we must have NOT collided

	return false;								// There was no collision, so return false
}
#endif 


/////////////////////////////////////////////////////////////////////////////////
//
// * QUICK NOTES * 
//
// We added 4 new math functions to our library.  A few of these functions will 
// be used constantly throughout your 3D programming careers, so make sure you know them.
// They are :  Dot()	AngleBetweenVectors()	IntersectionPoint()   InsidePolygon()
//
// We also added a helper function called IntersectedPolygon(), which calls
// IntersectionPoint() and InsidePolygon().  This is the function that the client
// will call.  We don't need to call the other 2 functions by themselves anywhere else.
//
// From now on, the dot product will be one of the biggest math functions you will use.
// It's importance is right behind vectors and normals.
//
// Read more about these functions in 3DMath.cpp
//
//
// Ben Humphrey (DigiBen)
// Game Programmer
// DigiBen@GameTutorials.com
// Co-Web Host of www.GameTutorials.com
//
//


