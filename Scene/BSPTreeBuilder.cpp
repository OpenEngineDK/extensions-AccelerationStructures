// BSP tree builder.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#include <Scene/BSPTreeBuilder.h>
#include <Scene/GeometryNode.h>
#include <Geometry/FaceSet.h>

namespace OpenEngine {
namespace Scene {

/**
 * Construct builder.
 */
BSPTreeBuilder::BSPTreeBuilder()
    : faces(NULL) {

}

/**
 * Destructor.
 */
BSPTreeBuilder::~BSPTreeBuilder() {

}

/**
 * Visit handler for geometry nodes.
 * Collects all faces to build the tree from.
 */
void BSPTreeBuilder::VisitGeometryNode(GeometryNode* node) {
    faces->Add(node->GetFaceSet());
    node->VisitSubNodes(*this);
}

/**
 * Build a BSP tree from a scene structure.
 *
 * @param node Root node of a scene to build from.
 * @return BSP tree or NULL if no tree could be built.
 */
BSPNode* BSPTreeBuilder::Build(ISceneNode& node) {
    BSPNode* bsp = NULL;

    // collect all faces
    faces = new FaceSet();
    node.Accept(*this);

    // create a bsp node with the face set if it is non-empty.
    if (faces->Size() != 0)
        bsp = new BSPNode(faces);

    // clean up and return tree
    delete faces;
    return bsp;
}

} // NS Scene
} // NS OpenEngine
