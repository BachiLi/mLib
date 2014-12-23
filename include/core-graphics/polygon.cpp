
#ifndef CORE_GRAPHICS_POLYGON_INL_H_
#define CORE_GRAPHICS_POLYGON_INL_H_

namespace ml {

//
// Sutherland-Hodgman Clipping
// http://gamedevelopment.tutsplus.com/tutorials/understanding-sutherland-hodgman-clipping-for-physics-engines--gamedev-11917
//
template<class T>
Polygon<T> Polygon<T>::clip(const Polygon<T> &sourcePoly, const Line2<T> &clipLine, const vec2<T> &clipCentroid)
{
    Polygon<T> output;

    //
    // find the normal of the line segment pointing towards clipCentroid
    //
    vec2<T> normal = clipLine.dir();
    normal = (-normal.y, normal.x);
    if (((clipCentroid - clipLine.p0()) | normal) < 0.0f)
        normal = -normal;

    auto sideTest = [&](const vec2<T> &pt)
    {
        return ((pt - clipLine.p0()) | normal) >= 0.0f;
    };

    vec2<T> startPoint = sourcePoly.points.back();
    for (const vec2<T> &endPoint : sourcePoly.points)
    {
        bool startSide = sideTest(startPoint);
        bool endSide = sideTest(endPoint);

        if (endSide)
        {
            if (!startSide)
            {
                vec2<T> intersection = startPoint;
                intersection::intersectLine2Line2(clipLine, Line2<T>(startPoint, endPoint), intersection);
                output.points.push_back(intersection);
            }
            output.points.push_back(endPoint);
        }
        else if (startSide)
        {
            vec2<T> intersection = startPoint;
            intersection::intersectLine2Line2(clipLine, Line2<T>(startPoint, endPoint), intersection);
            output.points.push_back(intersection);
        }
    }

    return output;
}

template<class T>
Polygon<T> Polygon<T>::clip(const Polygon<T> &sourcePoly, const Polygon<T> &clipPoly)
{
    Polygon<T> output = sourcePoly;
    vec2<T> clipCentroid = clipPoly.centroid();

    for (const LineSegment2<T> &clipSegment : clipPoly.segments())
        output = clip(output, Line2<T>(clipSegment), clipCentroid);

    return output;
}

}  // namespace ml

#endif  // CORE_GRAPHICS_POLYGON_INL_H_