#include "Globals.h"
#include "Application.h"
#include <iostream>

#include "MathGeoLib/include/Math/float3.h"

#include "MathGeoLib/include/MathGeoLib.h"
#include "MathGeoLib/include/Math/float3x3.h"
#include "MathGeoLib/include/Math/float4x4.h"
#include "Primitive.h"

#include "glmath.h"

#ifdef _DEBUG
#pragma comment (lib, "MathGeoLib/libx86/libdebug/MathGeoLib.lib") /* link Microsoft OpenGL lib   */
#else
#pragma comment (lib, "MathGeoLib/libx86/librelease/MathGeoLib.lib") /* link Microsoft OpenGL lib   */
#endif // _DEBUG

int testing() {
    // Crear instancias de diversas formas geométricas
    Sphere sphere1(float3(0, 0, 0), 1.0f);
    Sphere sphere2(float3(1.5f, 0, 0), 1.0f);

    Cylinder cylinder1(LineSegment(float3(0, 0, 0), float3(0, 0, 2)), 1.0f);
    Cylinder cylinder2(LineSegment(float3(0, 0, 3), float3(0, 0, 5)), 0.5f);

    Capsule capsule1(float3(0, 0, 0), float3(0, 0, 3), 1.0f);
    Capsule capsule2(float3(2.0f, 0, 0), float3(2.0f, 0, 3), 0.5f);

    AABB aabb1(float3(-1, -1, -1), float3(1, 1, 1));
    AABB aabb2(float3(1, 1, 1), float3(2, 2, 2));

    //OBB obb1(float3(0, 0, 0), float3(1, 0, 0), float3(0, 1, 0), float3(0, 0, 1), 1.0f, 2.0f, 3.0f);
    //OBB obb2(float3(3, 0, 0), float3(1, 0, 0), float3(0, 1, 0), float3(0, 0, 1), 1.0f, 2.0f, 3.0f);

    Frustum frustum1; // Debes configurar el frustum según tus necesidades
    Frustum frustum2;

    Plane plane1(float3(0, 0, 1), 1.0f);
    Plane plane2(float3(0, 0, -1), 2.0f);

    LineSegment segment1(float3(0, 0, 0), float3(1, 1, 1));
    LineSegment segment2(float3(2, 0, 0), float3(3, 0, 0));

    Ray ray1(float3(0, 0, 0), float3(1, 1, 1));
    Ray ray2(float3(2, 0, 0), float3(1, 0, 0));

    // Verificar intersecciones
    bool sphereIntersect = sphere1.Intersects(sphere2);
    //bool cylinderIntersect = cylinder1.Intersects(cylinder2);
    bool capsuleIntersect = capsule1.Intersects(capsule2);
    bool aabbIntersect = aabb1.Intersects(aabb2);
    //bool obbIntersect = obb1.Intersects(obb2);
    bool frustumIntersect = frustum1.Intersects(frustum2);
    bool planeIntersect = plane1.Intersects(plane2);
    bool segmentIntersect = segment1.Intersects(segment2);
    //bool rayIntersect = ray1.Intersects(ray2);

    // Imprimir resultados
    std::cout << "Sphere Intersection: " << (sphereIntersect ? "Yes" : "No") << std::endl;
    //std::cout << "Cylinder Intersection: " << (cylinderIntersect ? "Yes" : "No") << std::endl;
    std::cout << "Capsule Intersection: " << (capsuleIntersect ? "Yes" : "No") << std::endl;
    std::cout << "AABB Intersection: " << (aabbIntersect ? "Yes" : "No") << std::endl;
    //std::cout << "OBB Intersection: " << (obbIntersect ? "Yes" : "No") << std::endl;
    std::cout << "Frustum Intersection: " << (frustumIntersect ? "Yes" : "No") << std::endl;
    std::cout << "Plane Intersection: " << (planeIntersect ? "Yes" : "No") << std::endl;
    std::cout << "Segment Intersection: " << (segmentIntersect ? "Yes" : "No") << std::endl;
    //std::cout << "Ray Intersection: " << (rayIntersect ? "Yes" : "No") << std::endl;

    return 0;
}
