#include "VertexUI.Control.hpp"
template<class T>
void VControl::EventReceiver(VUIEvent event,T* data){
    for (auto i :Children){
        *i->EventReceiver(event,data);
    }

}