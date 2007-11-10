// Binary Space Partitioned tree transformer.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#include<Scene/BSPTransformer.h>

namespace OpenEngine {
namespace Scene {

BSPTransformer::BSPTransformer() {
    
}

BSPTransformer::~BSPTransformer() {
    
}

void BSPTransformer::Transform(ISceneNode& node) {
    node.Accept(*this);
}

void BSPTransformer::VisitGeometryNode(GeometryNode* node) {
    if (node->GetFaceSet()->Size() != 0)
        // node->ReplaceBy(new BSPNode(&this, node->GetFaceSet()));
        node->GetParent()->ReplaceNode(node, new BSPNode(node->GetFaceSet()));
}

} // NS Scene
} // NS OpenEngine
