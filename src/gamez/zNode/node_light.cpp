#include "znode.h"

namespace zdb
{
    void CNode::SetDynamicLight(bool self_light, bool apply_to_children)
    {
        m_light_dynamic = self_light;

        if (apply_to_children)
        {
            auto child_iterator = m_child.begin();
            while (child_iterator != m_child.end())
            {
                CNode* child = *child_iterator;

                child->m_light_dynamic = m_light_dynamic;
                child->SetDynamicLight(self_light, apply_to_children);
                
                ++child_iterator;
            }
        }
    }
}