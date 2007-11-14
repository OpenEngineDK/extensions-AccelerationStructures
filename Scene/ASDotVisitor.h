// 
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _OE_AS_DOT_VISITOR_H_
#define _OE_AS_DOT_VISITOR_H_

#include <Scene/DotVisitor.h>

namespace OpenEngine {
namespace Scene {

/**
 * Short description.
 *
 * @class ASDotVisitor ASDotVisitor.h Scene/ASDotVisitor.h
 */
class ASDotVisitor : public DotVisitor {
public:
    virtual void VisitQuadNode(QuadNode* node);
    virtual void VisitBSPNode(BSPNode* node);
};

} // NS Scene
} // NS OpenEngine

#endif // _OE_AS_DOT_VISITOR_H_
