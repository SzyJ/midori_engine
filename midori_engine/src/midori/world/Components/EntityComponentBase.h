// Author: Szymon Jackiewicz
// 
// Project: midori_engine
// File: EntityComponentBase.h
// Date: 08/08/2021

#pragma once

#include "midori/core/Core.h"
#include "midori/core/DeltaTime.h"
#include "midori/world/EntityBase.h"

namespace midori {

    class EntityBase;

    class EntityComponentBase {
    public:
        EntityComponentBase() = default;

    protected:
        ref<const glm::vec3> m_WorldPos;
        ref<const glm::vec3> m_WorldRotation;
        ref<const float> m_Scale;

        friend class EntityComponentManager;
        
        virtual void OnAdd() = 0;
        virtual void OnRemove() = 0;
        virtual void Update(DeltaTime delta) = 0;

    private:
        void OnAdd(EntityBase* entity) {
            //m_WorldPos = entity->m_WorldPos;
            //m_WorldRotation = entity->m_WorldRotation;
            //m_Scale = entity->m_Scale;
            OnAdd();
        }
    };

    class EntityComponentManager {
    public:
        static EntityComponentManager& Get() {
            static EntityComponentManager* instance = new EntityComponentManager();
            return *instance;
        }

        bool RegisterComponent(EntityBase* entity, EntityComponentBase* component) {
            m_ComponentMap.insert(std::make_pair(component, entity));
            component->OnAdd(entity);
        }

        bool UnregisterComponent(EntityComponentBase* component) {
            m_ComponentMap.erase(component);
            component->OnRemove();
        }


    private:
        EntityComponentManager() = default;

        void UpdateComponents(DeltaTime delta) {
            for (auto component : m_ComponentMap) {
                (component.first)->Update(delta);
            }
        }

        std::unordered_map<EntityComponentBase*, EntityBase*> m_ComponentMap;
    };

}