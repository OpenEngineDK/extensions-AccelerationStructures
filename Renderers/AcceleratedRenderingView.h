// Accelerated rendering view.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _ACCELERATED_RENDERING_VIEW_H_
#define _ACCELERATED_RENDERING_VIEW_H_

#include <Renderers/IRenderingView.h>

namespace OpenEngine {
namespace Renderers {

using namespace OpenEngine::Scene;

/**
 * Accelerated rendering view.
 */
class AcceleratedRenderingView : virtual public IRenderingView {

public:
    AcceleratedRenderingView(Viewport& viewport);
    virtual ~AcceleratedRenderingView();
    void VisitQuadNode(QuadNode* node);
    void VisitBSPNode(BSPNode* node);
};

} // NS Renderers
} // NS OpenEngine

#endif // _ACCELERATED_RENDERING_VIEW_H_
