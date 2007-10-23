// Quad tree builder.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _QUAD_TREE_BUILDER_H_
#define _QUAD_TREE_BUILDER_H_

#include <Scene/QuadNode.h>
#include <Scene/ISceneNodeVisitor.h>
#include <Geometry/FaceSet.h>

namespace OpenEngine {
namespace Scene {

using OpenEngine::Geometry::FaceSet;

/**
 * Quad tree builder.
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
 * To build a tree one can use the builder to collect faces and
 * construct a new quad tree structure from them.
 * @code
 * // first some large scene structure must be available
 * SceneNode* scene;
 * // create a builder
 * QuadTreeBuilder builder;
 * // build the tree
 * QuadNode* tree = builder.Build(*scene);
 * // if valid set in as the rendering root
 * if (tree != NULL)
 *     renderer->SetSceneRoot(tree);
 * @endcode
 *
 * @class QuadTreeBuilder QuadTreeBuilder.h Scene/QuadTree/QuadTreeBuilder.h
 */
class QuadTreeBuilder : public ISceneNodeVisitor {
private:
    FaceSet* faces;             //!< collected faces
    int mCount;                 //!< max face count in a leaf node
    float mHSize;               //!< max half size of a leaf node

public:
    QuadTreeBuilder(const int count = 100, const float size = 10);
    ~QuadTreeBuilder();

    QuadNode* Build(ISceneNode& node);
    void SetMaxFaceCount(const int count);
    void SetMaxQuadSize(const float size);

    void VisitGeometryNode(GeometryNode* node);

};

} // NS Scene
} // NS OpenEngine

#endif // _QUAD_TREE_BUILDER_H_
