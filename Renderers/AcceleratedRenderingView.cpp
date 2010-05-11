// Accelerated rendering view.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#include <Renderers/AcceleratedRenderingView.h>
#include <Display/IViewingVolume.h>

#include <Scene/BSPNode.h>
#include <Scene/QuadNode.h>

namespace OpenEngine {
namespace Renderers {

using namespace OpenEngine::Scene;

//! Rendering view constructor.
AcceleratedRenderingView::AcceleratedRenderingView(){
    
}

AcceleratedRenderingView::~AcceleratedRenderingView() {

}

void AcceleratedRenderingView::Handle(RenderingEventArg arg) {
    this->arg = &arg;
}

void AcceleratedRenderingView::VisitQuadNode(QuadNode* node) {
    if (arg->canvas.GetViewingVolume()->IsVisible(node->GetBoundingBox()))
        node->VisitSubNodes(*this);
}

void AcceleratedRenderingView::VisitBSPNode(BSPNode* node) {
    node->VisitSubNodes(*this);
}

} // NS Renderers
} // NS OpenEngine
