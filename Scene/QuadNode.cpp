// Quad tree node.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#include <Scene/QuadNode.h>
#include <Scene/GeometryNode.h>
#include <Resources/IArchiveWriter.h>
#include <Resources/IArchiveReader.h>

namespace OpenEngine {
namespace Scene {

/**
 * Create a quad tree node.
 *
 * 1. If an end condition is satisfied terminates the recursive build.
 *    Else
 *
 * 2. Creates the dividing planes.
 *
 * 3. Creates top-left, top-right, bottom-left and bottom-right face
 *    sets with split. 
 *
 * 4. Recursively creates top-left, top-right, bottom-left and
 *    bottom-right quad nodes from the sets. 
 *
 * No reference will be kept of the face set supplied and it is the
 * callers responsibility to delete is if necessary. 
 *
 * @pre The face set supplied must be non-empty.
 * @param faces Face set to construct from.
 * @param count Maximum number of faces that may be in a leaf node.
 * @param hsize Maximum half size of the bounding square of a leaf node.
 */
QuadNode::QuadNode(FaceSet* faces, const int count, const float hsize)
    : bb(Box(*faces))
    , tl(NULL)
    , tr(NULL)
    , bl(NULL)
    , br(NULL)
{
    // read out the half sizes on the x and z axis.
    float sizeX = bb.GetCorner()[0];
    float sizeZ = bb.GetCorner()[2];

    // if one of the constraints are reached we end the recursive build
    // and add the faces to a geometry sub node.
    if (faces->Size() <= count || (sizeX <= hsize && sizeZ <= hsize)) {
        AddNode(new GeometryNode(new FaceSet(*faces)));
        return;
    }

    // else split and create sub quads

    Vector<2,float> center(bb.GetCenter()[0], bb.GetCenter()[2]);

    // create a horizontal divider
    FacePtr horiz(new Face(Vector<3,float>(center[0],       0, center[1]),
                           Vector<3,float>(center[0],       1, center[1]),
                           Vector<3,float>(center[0]-sizeX, 0, center[1]),
                           Vector<3,float>(0,0,1),
                           Vector<3,float>(0,0,1),
                           Vector<3,float>(0,0,1)));

    // create a vertical divider
    FacePtr verti(new Face(Vector<3,float>(center[0], 0, center[1]),
                           Vector<3,float>(center[0], 1, center[1]),
                           Vector<3,float>(center[0], 0, center[1]+sizeZ),
                           Vector<3,float>(1,0,0),
                           Vector<3,float>(1,0,0),
                           Vector<3,float>(1,0,0)));

    // create face sets
    FaceSet ft;
    FaceSet fb;
    FaceSet* ftl = new FaceSet();
    FaceSet* ftr = new FaceSet();
    FaceSet* fbl = new FaceSet();
    FaceSet* fbr = new FaceSet();

    // split in two sets - top and bottom
    faces->Split(horiz, ft, ft, fb);

    // split in four sets
    ft.Split(verti, *ftl, *ftl, *ftr);
    fb.Split(verti, *fbl, *fbl, *fbr);

    // create the sub nodes
    if (ftl->Size() != 0) tl = new QuadNode(ftl, count, hsize);
    if (ftr->Size() != 0) tr = new QuadNode(ftr, count, hsize);
    if (fbl->Size() != 0) bl = new QuadNode(fbl, count, hsize);
    if (fbr->Size() != 0) br = new QuadNode(fbr, count, hsize);

    // clean the temporary face sets
    delete ftl;
    delete ftr;
    delete fbl;
    delete fbr;
}

void QuadNode::Serialize(Resources::IArchiveWriter& w) {
    w.WriteObject("bb", &bb);
    w.WriteScene("tl",tl);
    w.WriteScene("tr",tr);
    w.WriteScene("bl",bl);
    w.WriteScene("br",br);
}

void QuadNode::Deserialize(Resources::IArchiveReader& r) {
    bb = *dynamic_cast<Box*>(r.ReadObject("bb"));
    tl = dynamic_cast<QuadNode*>(r.ReadScene("tl"));
    tr = dynamic_cast<QuadNode*>(r.ReadScene("tr"));
    bl = dynamic_cast<QuadNode*>(r.ReadScene("bl"));
    br = dynamic_cast<QuadNode*>(r.ReadScene("br"));

}


/**
 * Quad node destructor.
 */
QuadNode::~QuadNode() {

}

/**
 * Copy constructor.
 *
 * @param node Node to copy.
 */
QuadNode::QuadNode(const QuadNode& node)
    : ISceneNode(node)
    , bb(node.bb)
{
    if (node.tl) tl = (QuadNode*)node.tl->Clone();
    if (node.tr) tr = (QuadNode*)node.tr->Clone();
    if (node.bl) bl = (QuadNode*)node.bl->Clone();
    if (node.br) br = (QuadNode*)node.br->Clone();
}

/**
 * Visit sub nodes including the four quad node children.
 * The visiting order starts with the top left and ends at the bottom
 * right and thereafter visits all sub nodes of the node.
 *
 * @param visitor Scene visitor.
 */
void QuadNode::VisitSubNodes(ISceneNodeVisitor& visitor) {
    list<ISceneNode*>::iterator itr;
    if (tl != NULL) tl->Accept(visitor);
    if (tr != NULL) tr->Accept(visitor);
    if (bl != NULL) bl->Accept(visitor);
    if (br != NULL) br->Accept(visitor);
    for (itr = subNodes.begin(); itr != subNodes.end(); itr++)
        (*itr)->Accept(visitor);
}

/**
 * Get the top left quad node.
 *
 * @return Top left node or NULL.
 */
QuadNode* QuadNode::GetTopLeft() const {
    return tl;
}

/**
 * Get the top right quad node.
 *
 * @return Top right node or NULL.
 */
QuadNode* QuadNode::GetTopRight() const {
    return tr;
}

/**
 * Get the bottom left quad node.
 *
 * @return Bottom left node or NULL.
 */
QuadNode* QuadNode::GetBottomLeft() const {
    return bl;
}

/**
 * Get the bottom right quad node.
 *
 * @return Top left node or NULL.
 */
QuadNode* QuadNode::GetBottomRight() const {
    return br;
}

/**
 * Get the bounding square of this node.
 *
 * @return Bounding square.
 */
Box QuadNode::GetBoundingBox() const {
    return bb;
}

} // NS Scene
} // NS OpenEngine
