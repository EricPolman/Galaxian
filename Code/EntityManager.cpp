#include "EntityManager.h"

EntityManager::~EntityManager(void)
{
	instanceFlag = false;
	for(std::vector<Entity*>::iterator i = m_entities.begin(); i != m_entities.end(); ++i )
	{
		delete *i;
	}
	m_entities.clear();
	for(std::vector<Entity*>::iterator i = m_toBeRemoved.begin(); i != m_toBeRemoved.end(); ++i )
	{
		delete *i;
	}
	m_toBeRemoved.clear();
}

bool EntityManager::instanceFlag = false;
EntityManager* EntityManager::single = NULL;
EntityManager* EntityManager::GetInstance()
{
    if(! instanceFlag)
    {
        single = new EntityManager();
        instanceFlag = true;
        return single;
    }
    else
    {
        return single;
    }
}


void EntityManager::Add(Entity* a_pEntity)
{
	m_entities.push_back(a_pEntity);
}


void EntityManager::Remove(Entity* a_pEntity)
{
	for(std::vector<Entity*>::iterator i = m_entities.begin(); i != m_entities.end(); i++)
	{
		if(*i == a_pEntity)
		{
			m_entities.erase(i);
			break;
		}
	}
}

void EntityManager::ClearAll()
{
	m_entities.erase(m_entities.begin(), m_entities.end());
	m_entities.clear();
}


void EntityManager::Update(float a_fDeltaTime)
{
	for(std::vector<Entity*>::iterator i = m_entities.begin(); i != m_entities.end();)
	{
		Entity* iEntity = *i;

		if(iEntity->m_state == EntityState::REMOVED)
		{
			m_toBeRemoved.push_back(*i);
			i = m_entities.erase(i);
			continue;
		}
		else
		{
			i++;
		}

		Vector2 iPosition = iEntity->GetPosition();
		Vector2 iSize;
		iSize.x = iEntity->GetSprite()->GetWidth(); 
		iSize.y = iEntity->GetSprite()->GetHeight();

		iEntity->Update(a_fDeltaTime);
		if(!iEntity->m_bIsVisible)
		{
			continue;
		}

		for(std::vector<Entity*>::iterator j = m_entities.begin(); j != m_entities.end(); j++)
		{
			if(iEntity != *j)
			{	
				Entity* jEntity = (*j);
				
				Vector2 jPosition = jEntity->GetPosition();
				Vector2 jSize;
				jSize.x = jEntity->GetSprite()->GetWidth(); 
				jSize.y = jEntity->GetSprite()->GetHeight();

				if(iPosition.x < jPosition.x + jSize.x &&
				   iPosition.x + iSize.x > jPosition.x &&
				   iPosition.y < jPosition.y + jSize.y &&
				   iPosition.y + iSize.y > jPosition.y)
				{
					iEntity->Hit(jEntity);
				}
			}
		}
	}
	if(m_toBeRemoved.size() > 0)
	{
		for(std::vector<Entity*>::iterator i = m_toBeRemoved.begin(); i != m_toBeRemoved.end(); ++i )
		{
			delete *i;
		}
		m_toBeRemoved.clear();
	}
}


void EntityManager::Draw(Tmpl8::Surface* a_screen)
{
	for(std::vector<Entity*>::iterator i = m_entities.begin(); i != m_entities.end(); i++)
	{
		(*i)->Draw(a_screen);
	}
}