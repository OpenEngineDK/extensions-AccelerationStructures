// BSP tree node.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#include <Scene/BSPNode.h>
#include <Scene/BSPTransformer.h>
#include <Scene/GeometryNode.h>

namespace OpenEngine {
namespace Scene {

/**
 * Copy constructor.
 * Performs a shallow copy.
 *
 * @param node Node to copy.
 */
BSPNode::BSPNode(BSPNode& node) {
    front = node.front;
    back = node.back;
    span = node.span;
    divider = node.divider;
}

ISceneNode* BSPNode::Clone() {
    BSPNode* clone = new BSPNode(*this);
    if (front) clone->front = (BSPNode*)front->Clone();
    if (back) clone->back = (BSPNode*)back->Clone();
    // @todo this is not nice. we assume that only one sub child
    // exists and that it is the geometry node we added upon
    // construction.
    list<ISceneNode*>::iterator itr = subNodes.begin();
    ISceneNode* subclone = (*itr)->Clone();
    clone->AddNode(subclone);
    clone->span = ((GeometryNode*)subclone)->GetFaceSet();
    return clone;    
}

/**
 * Create a BSP tree from a face set.
 * 
 * 1. Finds best dividing plane.
 * 2. Creates front-set and back-set with split.
 * 3. Recursively creates front node and back node from the sets.
 *
 * No local reference is kept to the parameter \a faces and it is the
 * callers responsibility to delete it if necessary.
 *
 * @pre The face set supplied must be non-empty.
 * @param trans Active construction transformer
 * @param faces Face set to build tree from
 *
 * @see BSPTransformer
 */
BSPNode::BSPNode(BSPTransformer& trans, FaceSet* faces)
    : front(NULL), back(NULL), span(NULL) {

    // create face sets
    span = new FaceSet();
    FaceSet* fset = new FaceSet();
    FaceSet* bset = new FaceSet();

    // add a geometry node with the spanning set    
    AddNode(new GeometryNode(span));

    // find divider
    divider = trans.GetFindDividerStrategy()->FindDivider(*faces, epsilon);

    // partition to the sets
    trans.GetPartitionStrategy()->Partition(divider, *faces, *fset, *span, *bset, epsilon);

    // create sub nodes
    if (fset->Size() > 0)
        front = new BSPNode(trans, fset);
    if (bset->Size() > 0)
        back = new BSPNode(trans, bset);
    
    // delete the unused face sets
    delete fset;
    delete bset;
}

/**
 * Destructor.
 */
BSPNode::~BSPNode() {

}

// accept of visitors
void BSPNode::Accept(ISceneNodeVisitor& visitor) { 
    visitor.VisitBSPNode(this);
}

/**
 * Visit sub nodes including the front and back nodes.
 * The visiting order starts with the front set then all sub nodes and
 * last the back node.
 *
 * @param visitor Current visitor.
 */
void BSPNode::VisitSubNodes(ISceneNodeVisitor& visitor) {
    IncAcceptStack();
    list<ISceneNode*>::iterator itr;
    if (GetFront() != NULL )
        GetFront()->Accept(visitor);
    for (itr = subNodes.begin(); itr != subNodes.end(); itr++)
        (*itr)->Accept(visitor);
    if (GetBack() != NULL)
        GetBack()->Accept(visitor);
    DecAcceptStack();
}

/**
 * Get front node.
 *
 * @return Node with front faces, NULL if no front set exists
 */
BSPNode* BSPNode::GetFront() {
    return front;
}

/**
 * Get back node.
 *
 * @return Node with back faces, NULL if no back set exists
 */
BSPNode* BSPNode::GetBack() {
    return back;
}

/**
 * Get faces in divider plane
 *
 * @return Face set of faces in the divider plane
 */
FaceSet* BSPNode::GetSpan() {
    return span;
}

/**
 * Compare the position of a point with the dividing plane of the BSP
 * node.
 *
 * @param point Point to find position of
 * @return relative position value
 * @see Face::ComparePointPlane
 */
int BSPNode::ComparePoint(Vector<3,float> point) {
    return GetDivider()->ComparePointPlane(point);
}


/**
 * Get the dividing face of this node.
 *
 * @return Dividing face
 */
FacePtr BSPNode::GetDivider() {
    return divider;
}

} // NS Scene
} // NS OpenEngine
