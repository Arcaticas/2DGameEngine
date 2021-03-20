


GameObjectOwner::GameObjectOwner(Physics::TwoDPhysicsObj* i_ptr) :
	m_count(new Counters(1,0))
{
	m_ptr = i_ptr;
}

GameObjectOwner::GameObjectOwner(const GameObjectOwner& i_copy)
{
	m_ptr = i_copy.m_ptr;
	m_count = i_copy.m_count;
	(*m_count).m_Owners++;
}

GameObjectOwner::GameObjectOwner(const GameObjectObserver& i_copy)
{
	m_ptr = i_copy.m_ptr;
	m_count = i_copy.m_count;
	(*m_count).m_Owners++;
}

GameObjectOwner::~GameObjectOwner()
{
	if (--((*m_count).m_Owners) == 0)
	{
		delete m_ptr;
		if ((*m_count).m_Observers == 0)
		{
			delete m_count;
		}
	}
}

Physics::TwoDPhysicsObj* GameObjectOwner::operator->()
{
	return m_ptr;
}

Physics::TwoDPhysicsObj& GameObjectOwner::operator*()
{
	assert(m_ptr);
	return *m_ptr;
}


