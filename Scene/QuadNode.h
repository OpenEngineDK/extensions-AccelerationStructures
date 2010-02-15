// Quad tree node.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _QUAD_NODE_H_
#define _QUAD_NODE_H_

#include <Scene/ISceneNode.h>
#include <Geometry/Box.h>
#include <Geometry/FaceSet.h>

// forward declarations
namespace OpenEngine {
    namespace Resources {
        class IArchiveWriter;
        class IArchiveReader;
    }

namespace Scene {

class ISceneNodeVisitor;

using namespace OpenEngine::Geometry;

/**
 * Quad tree node.
 * To build a tree please refer to QuadTreeBuilder.
 *
 * @see QuadTreeBuilder
 *
 * @class QuadNode QuadNode.h Scene/QuadTree/QuadNode.h
 */
class QuadNode : public ISceneNode {
    OE_SCENE_NODE(QuadNode, ISceneNode)

public:
    QuadNode():tl(NULL),tr(NULL),bl(NULL),br(NULL) {}; // empty constructor for serialization
    QuadNode(FaceSet* faces, const int count, const float hsize);
    QuadNode(const QuadNode& node);
    ~QuadNode();

    void VisitSubNodes(ISceneNodeVisitor& visitor);

    QuadNode* GetTopLeft() const;
    QuadNode* GetTopRight() const;
    QuadNode* GetBottomLeft() const;
    QuadNode* GetBottomRight() const;

    Box GetBoundingBox() const;

    void Serialize(Resources::IArchiveWriter& w);
    void Deserialize(Resources::IArchiveReader& r);


private:

    //! bounding square
    Box bb;

    //! sub nodes
    QuadNode *tl, *tr, *bl, *br;


};

} // NS Scene
} // NS OpenEngine


#endif // _QUAD_NODE_H_
