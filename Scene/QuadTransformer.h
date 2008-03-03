// Quad transformer.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _QUAD_TRANSFORMER_H_
#define _QUAD_TRANSFORMER_H_

#include <Scene/QuadNode.h>
#include <Scene/GeometryNode.h>
#include <Scene/ISceneNodeVisitor.h>

namespace OpenEngine {
namespace Scene {
        
using OpenEngine::Geometry::FaceSet;

/**
 * Quad tree transformer.
 *
 * A quad tree is a data structure that partitions a space in four
 * spatially equal sizes recursively until some end condition is met.
 *
 * @code
 * // a result could look like the following spatial diagram and tree
 * // structure 
 * +-----+-----+       0
 * |     |     |    .--^--.   
 * |     |     |   /  | |  \ 
 * |     |     |  0   0 0   0
 * +-----+--+--+         .--^--.   
 * |     |  |  |        /  | |  \ 
 * |     +--+--+       0   0 0   0
 * |     |  |  |
 * +-----+--+--+
 * @endcode
 *
 * To build a tree one can use the transformer to construct a
 * structure where all geometry nodes have been partitioned in to a
 * quad tree.
 *
 * @code
 * // first some large scene structure must be available
 * SceneNode* scene;
 * // create a transformer
 * QuadTransformer quadt;
 * // transform the scene
 * quadt.Transform(*scene);
 * @endcode
 *
 * This class can be used in combination with the
 * CollectedGeometryTransformer in order to transform an entire scene
 * to a single quad tree.
 *
 * @see CollectedGeometryTransformer
 * @see GeometryNode
 *
 * @class QuadTransformer QuadTransformer.h Scene/QuadTransformer.h
 */
class QuadTransformer : public ISceneNodeVisitor {
private:
    int mCount; //!< Max face count in lead node.
    float mHSize; //!< Max half size of a leaf node.
public:
    QuadTransformer();
    ~QuadTransformer();

    void Transform(ISceneNode& node);

    void SetMaxFaceCount(const int count);
    void SetMaxQuadSize(const float size);

    void VisitGeometryNode(GeometryNode* node);
};
} // NS Scene
} // NS OpenEngine

#endif // _QUAD_TRANSFORMER_H_
