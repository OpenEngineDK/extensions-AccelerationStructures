// Quad tree builder.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#include <Scene/QuadTreeBuilder.h>
#include <Scene/TransformationNode.h>
#include <Scene/GeometryNode.h>

namespace OpenEngine {
namespace Scene {

/**
 * Construct a quad tree builder.
 *
 * @param count Maximum amount of faces to be contained in a quad node. [default 100]
 * @param size Maximum size the bounding square of a quad node may be. [default 10]
 */
QuadTreeBuilder::QuadTreeBuilder(int count, float size)
    : faces(NULL), mCount(count), mHSize(size/2) {

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
    QuadNode* q = NULL;

    // create a face set and collect all faces in the structure.
    faces = new FaceSet();
    node.Accept(*this);

    // create the tree if the set is non-empty.
    if (faces->Size() != 0)
        q = new QuadNode(faces, mCount, mHSize);

    // clean up
    delete faces;

    // return the tree or NULL
    return q;
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

/**
 * Build a list of all faces found in the structure.
 *
 * @param node Geometry node.
 */
void QuadTreeBuilder::VisitGeometryNode(GeometryNode* node) {
    faces->Add(node->GetFaceSet());
}

} // NS Scene
} // NS OpenEngine
