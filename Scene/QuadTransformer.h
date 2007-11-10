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
namespace OpenEngine {
    namespace Scene {
        
        using OpenEngine::Geometry::FaceSet;

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
