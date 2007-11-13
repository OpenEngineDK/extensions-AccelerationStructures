// Quad tree builder.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#include <Scene/QuadTreeBuilder.h>
#include <Scene/QuadTransformer.h>
//#include <Scene/TransformationNode.h>
#include <Scene/GeometryNode.h>
#include <Scene/CollectedGeometryTransformer.h>

#include <iostream>

namespace OpenEngine {
namespace Scene {

/**
 * Construct a quad tree builder.
 *
 * @param count Maximum amount of faces to be contained in a quad node. [default 100]
 * @param size Maximum size the bounding square of a quad node may be. [default 10]
 */
QuadTreeBuilder::QuadTreeBuilder(int count, float size)
    : mCount(count), mHSize(size/2) {

}

/**
 * Destructor.
 */
QuadTreeBuilder::~QuadTreeBuilder() {

}

/**
 * Build a quad tree from a scene structure.
 *
 * @param node Root node of a scene to build from.
 * @return Quad tree or NULL if no tree could be built.
 */
QuadNode* QuadTreeBuilder::Build(ISceneNode& node) {

    // create transformers
    CollectedGeometryTransformer collect;
    QuadTransformer quad;
    quad.SetMaxFaceCount(mCount);
    quad.SetMaxQuadSize(mHSize);

    // clone the scene in a new clone container
    // (needed in case build was called on a geometry node).
    SceneNode clone;
    clone.AddNode(node.Clone());

    // transform
    collect.Transform(clone);
    quad.Transform(clone);

    // validate
    QuadNode* qnode = NULL;
    if (clone.GetNumberOfNodes() == 1) {
        qnode = dynamic_cast<QuadNode*>(*(clone.subNodes.begin()));
        clone.RemoveNode(qnode);
    }

    // clone is deleted when we leave scope so we have nothing to delete.

    return qnode;
}

/**
 * Set the maximum amount of faces to be contained in a single quad
 * node.
 * The default is 100.
 *
 * @param count Maximum count.
 */
void QuadTreeBuilder::SetMaxFaceCount(const int count) {
    mCount = count;
}

/**
 * Maximum size the bounding square of a quad node may be.
 * The default is 10.
 *
 * @param size Maximum size of the quad box 
 */
void QuadTreeBuilder::SetMaxQuadSize(const float size) {
    mHSize = size / 2;
}

} // NS Scene
} // NS OpenEngine
