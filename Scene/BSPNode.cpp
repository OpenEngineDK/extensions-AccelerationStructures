// BSP tree node.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#include <Scene/BSPNode.h>
#include <Scene/GeometryNode.h>

namespace OpenEngine {
namespace Scene {

/**
 * Copy constructor.
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
 * @param faces Face set to build tree from
 */
BSPNode::BSPNode(FaceSet* faces) : front(NULL), back(NULL), span(NULL) {
    // create face sets
    span = new FaceSet();
    FaceSet* fset = new FaceSet();
    FaceSet* bset = new FaceSet();

    // add a geometry node with the spanning set    
    AddNode(new GeometryNode(span));

    // find divider
    divider = FindDivider(*faces);

    // split to the sets
    faces->Split(divider, *fset, *span, *bset, epsilon);

    // create sub nodes
    if (fset->Size() > 0)
        front = new BSPNode(fset);
    if (bset->Size() > 0)
        back = new BSPNode(bset);
    
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
    list<ISceneNode*>::iterator itr;

    if (GetFront() != NULL )
        GetFront()->Accept(visitor);

    for (itr = subNodes.begin(); itr != subNodes.end(); itr++)
        (*itr)->Accept(visitor);

    if (GetBack() != NULL)
        GetBack()->Accept(visitor);
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
 * Find the best dividing face in the set.
 *
 * This algorithm is based on the choose-dividing-polygon listing
 * found at http://www.devmaster.net/articles/bsp-trees/
 *
 * @pre The face set must be non empty.
 * @param faces Face set to be divided.
 * @return Best dividing face.
 */
FacePtr BSPNode::FindDivider(FaceSet& faces) {
    // adjustable constants
    float relation_minimum = 0.0; // initial minimum balance relation
    float relation_scale   = 0.5; // scale to lower the relation with
    // other declarations
    FaceList::iterator best_face = faces.end();
    int min_split = faces.Size();
    float best_rel = 0.0;
    float cur_rel = 0.0;
    int no_front, no_back, no_span;
    FaceList::iterator ftest, fcomp;
    Vector<3,int> pos;
    // if the set is empty return
    if (min_split == 0)
        throw Exception("Invalid call to find divider with an empty face set.");
    // if only one element is in the set it as best
    if (min_split == 1) best_face = faces.begin();
    // find the best face in the set
    while (best_face == faces.end()) {
        for (ftest = faces.begin(); ftest != faces.end(); ftest++) {
            no_front = no_back = no_span = 0;
            for (fcomp = faces.begin(); fcomp != faces.end(); fcomp++) {
                // ignore the face we are testing
                if (*fcomp == *ftest) continue;
                // count the face positions
                pos = (*ftest)->ComparePosition(*fcomp, epsilon);
                switch (pos.Sum()) {
                case -3:
                case -2:
                    ++no_back; break;
                case 3:
                case 2:
                    ++no_front; break;
                case -1:
                    if (pos[0] * pos[1] * pos[2] == 0) ++no_back;
                    else ++no_span;
                    break;
                case 1:
                    if (pos[0] * pos[1] * pos[2] == 0) ++no_front;
                    else ++no_span;
                    break;
                case 0:
                    if (pos[0] || pos[1] || pos[2]) ++no_span;
                    // else it is in the same plane and we don't care
                    break;
                }
                // compute the division relation
                if (no_front * no_back == 0)
                    cur_rel = 0;
                else if (no_front < no_back)
                    cur_rel = (float)no_front / (float)no_back;
                else if (no_back < no_front)
                    cur_rel = (float)no_back / (float)no_front;
                else
                    cur_rel = 1;
                // if the face we are testing is the best seen save it
                if (cur_rel >= relation_minimum &&
                    (no_span  < min_split ||
                     no_span == min_split && cur_rel > best_rel)) {
                    best_face = ftest;
                    min_split = no_span;
                    best_rel  = cur_rel;
                }
            }
        }
        // lower the scale factor
        relation_minimum *= relation_scale - .01;
    }
    return *best_face;
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
